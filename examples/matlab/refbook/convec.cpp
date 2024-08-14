/*=========================================================
 * convec.c
 * example for passing complex data from MATLAB to C and back again
 *
 * convolves  two complex input vectors
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2017 The MathWorks, Inc.
 *=======================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

/* computational subroutine */
void convec(const std::complex<double>* const x,
            const std::complex<double>* const y,
            std::complex<double>* const       z,
            const std::size_t                 nx,
            const std::size_t                 ny)
{
  /* perform the convolution of the complex vectors */
  for (std::size_t i{}; i < nx; ++i)
  {
    for (std::size_t j{}; j < ny; ++j)
    {
      z[i + j] += x[i] * y[j];
    }
  }
}

/* The gateway routine. */
void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{  
  /* check for the proper number of arguments */
  if (rhs.size() != 2)
  {
    throw mex::Exception{"MATLAB:convec:invalidNumInputs", "Two inputs required."};
  }

  if (lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:convec:maxlhs", "Too many output arguments."};
  }

  /* Check that both inputs are row vectors */
  if (rhs[0].getM() != 1 || rhs[1].getM() != 1)
  {
    throw mex::Exception{"MATLAB:convec:inputsNotVectors", "Both inputs must be row vectors."};
  }

  constexpr std::size_t rows = 1; 

  /* Check that both inputs are complex*/
  if (!rhs[0].isComplex() || !rhs[1].isComplex())
  {
    throw mex::Exception{"MATLAB:convec:inputsNotComplex", "Inputs must be complex.\n"};
  }

  /* get the length of each input vector */
  const std::size_t nx = rhs[0].getN();
  const std::size_t ny = rhs[1].getN();

  /* create a new array and set the output pointer to it */
  const std::size_t cols = nx + ny - 1;
  auto output = mex::makeNumericArray<std::complex<double>>(rows, cols);

  /* call the C subroutine */
  convec(mex::NumericArrayCref<std::complex<double>>{rhs[0]}.getData(),
         mex::NumericArrayCref<std::complex<double>>{rhs[1]}.getData(),
         output.getData(),
         nx,
         ny);

  lhs[0] = std::move(output);
}
