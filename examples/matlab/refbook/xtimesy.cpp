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

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void xtimesy(const double        x,
             const double* const y,
             double* const       z,
             const std::size_t   m,
             const std::size_t   n)
{
  std::transform(y, y + m * n, z, [x](const double value) { return x * value; });
}

/* the gateway function */
void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* check for proper number of arguments */
  /* NOTE: You do not need an else statement when using mexErrMsgIdAndTxt
     within an if statement, because it will never get to the else
     statement if mexErrMsgIdAndTxt is executed. (mexErrMsgIdAndTxt breaks you out of
     the MEX-file) */
  if (rhs.size() != 2)
  {
    throw mx::Exception{"MATLAB:xtimesy:invalidNumInputs", "Two inputs required."};
  }

  if (lhs.size() != 1)
  {
    throw mx::Exception{"MATLAB:xtimesy:invalidNumOutputs", "One output required."};
  }

  /* check to make sure the first input argument is a scalar */
  if (!rhs[0].isDouble() || rhs[0].isComplex() || rhs[0].getSize() != 1)
  {
    throw mx::Exception{"MATLAB:xtimesy:fieldNotScalar", "First input argument must be a real scalar value."};
  }

  /* check to make sure the second input argument is a real, double matrix */
  if (!rhs[1].isDouble() || rhs[1].isComplex())
  {
    throw mx::Exception{"MATLAB:xtimesy:fieldNotRealMatrix", "Second input argument must be a real, double matrix."};
  }

  /*  get the scalar input x */
  const double x = rhs[0].getScalarAs<double>();

  /*  create a pointer to the input matrix y */
  const double* y = rhs[1].getDataAs<double>();

  /*  get the dimensions of the matrix input y */
  const std::size_t mrows = rhs[1].getDimM();
  const std::size_t ncols = rhs[1].getDimN();

  /*  set the output pointer to the output matrix */
  auto zArray = mx::makeNumericArray<double>(mrows, ncols);

  /*  create a C pointer to a copy of the output matrix */
  double* z = zArray.getData();

  /*  call the C subroutine */
  xtimesy(x, y, z, mrows, ncols);

  lhs[0] = std::move(zArray);
}
