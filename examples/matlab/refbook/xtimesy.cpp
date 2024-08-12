/*
 * xtimesy.c
 * Multiplies a real input matrix y by a given real input scalar x.
 *
 * The calling syntax is:
 *
 *		[result] = xtimesy(x, y)
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2018 The MathWorks, Inc.
 */

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void xtimesy(const double        x,
             const double* const y,
             double* const       z,
             const std::size_t   m,
             const std::size_t   n)
{
  std::transform(y, y + m * n, z, [x](const double value) { return x * value; });
}

/* the gateway function */
void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  mxDouble *y, *z, x;

  size_t mrows, ncols;

  /* check for proper number of arguments */
  /* NOTE: You do not need an else statement when using mexErrMsgIdAndTxt
     within an if statement, because it will never get to the else
     statement if mexErrMsgIdAndTxt is executed. (mexErrMsgIdAndTxt breaks you out of
     the MEX-file) */
  if (rhs.size() != 2)
  {
    throw mex::Exception{"MATLAB:xtimesy:invalidNumInputs", "Two inputs required."};
  }

  if (lhs.size() != 1)
  {
    throw mex::Exception{"MATLAB:xtimesy:invalidNumOutputs", "One output required."};
  }

  /* check to make sure the first input argument is a scalar */
  if (!rhs[0].isDouble() || rhs[0].isComplex() || rhs[0].getSize() != 1)
  {
    throw mex::Exception{"MATLAB:xtimesy:fieldNotScalar", "First input argument must be a real scalar value."};
  }

  /* check to make sure the second input argument is a real, double matrix */
  if (!rhs[1].isDouble() || rhs[1].isComplex())
  {
    throw mex::Exception{"MATLAB:xtimesy:fieldNotRealMatrix", "Second input argument must be a real, double matrix."};
  }

  /*  get the scalar input x */
  const double x = mex::NumericArrayCref<double>(rhs[0])[0];

  /*  create a pointer to the input matrix y */
  const double* y = mex::NumericArrayCref<double>(rhs[1]).getData();

  /*  get the dimensions of the matrix input y */
  const std::size_t mrows = rhs[1].getM();
  const std::size_t ncols = rhs[1].getN();

  /*  set the output pointer to the output matrix */
  auto zArray = mex::makeNumericArray<double>(mrows, ncols);

  /*  create a C pointer to a copy of the output matrix */
  double* z = zArray.getData();

  /*  call the C subroutine */
  xtimesy(x, y, z, mrows, ncols);

  lhs[0] = std::move(zArray);
}
