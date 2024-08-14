/*=================================================================
 *
 * YPRIME.C	Sample .MEX file corresponding to YPRIME.M
 *	        Solves simple 3 body orbit problem
 *
 * The calling syntax is:
 *
 *		[yp] = yprime(t, y)
 *
 *  You may also want to look at the corresponding M-code, yprime.m.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2017 The MathWorks, Inc.
 *
 *=================================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

/* Input Arguments */

#define T_IN rhs[0]
#define Y_IN rhs[1]

/* Output Arguments */

#define YP_OUT lhs[0]

static constexpr double mu  = 1.0 / 82.45;
static constexpr double mus = 1.0 - 1.0 / 82.45;

static void yprime(double yp[], const double[], const double y[])
{
  const double r1 = std::sqrt((y[0] + mu) * (y[0] + mu) + y[2] * y[2]);
  const double r2 = std::sqrt((y[0] - mus) * (y[0] - mus) + y[2] * y[2]);

  /* Print warning if dividing by zero. */
  if (r1 == 0.0 || r2 == 0.0)
  {
    throw mex::Exception{"MATLAB:yprime:divideByZero", "Division by zero!\n"};
  }

  yp[0] = y[1];
  yp[1] = 2 * y[3] + y[0] - mus * (y[0] + mu) / (r1 * r1 * r1) - mu * (y[0] - mus) / (r2 * r2 * r2);
  yp[2] = y[3];
  yp[3] = -2 * y[1] + y[2] - mus * y[2] / (r1 * r1 * r1) - mu * y[2] / (r2 * r2 * r2);
}

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  /* Check for proper number of arguments */

  if (rhs.size() != 2)
  {
    throw mex::Exception{"MATLAB:yprime:invalidNumInputs", "Two input arguments required."};
  }
  else if (lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:yprime:maxlhs", "Too many output arguments."};
  }

  /* check to make sure the first input argument is a real matrix */
  if (!T_IN.isDouble() || T_IN.isComplex())
  {
    throw mex::Exception{"MATLAB:yprime:invalidT", "First input argument must be a real matrix."};
  }

  /* check to make sure the second input argument is a real matrix */
  if (!Y_IN.isDouble() || Y_IN.isComplex())
  {
    throw mex::Exception{"MATLAB:yprime:invalidY", "Second input argument must be a real matrix."};
  }

  /* Check the dimensions of Y.  Y can be 4 X 1 or 1 X 4. */

  const std::size_t m = Y_IN.getDims()[0];
  const std::size_t n = Y_IN.getDims()[1];

  if (std::max(m, n) != 4 || std::min(m, n) != 1)
  {
    throw mex::Exception{"MATLAB:yprime:invalidY", "YPRIME requires that Y be a 4 x 1 vector."};
  }

  /* Create a matrix for the return argument */
  YP_OUT = mex::makeNumericArray<double>({{m, n}});

  /* Do the actual computations in a subroutine */
  yprime(mex::NumericArrayRef<double>{YP_OUT}.getData(),
         mex::NumericArrayCref<double>{T_IN}.getData(),
         mex::NumericArrayCref<double>{Y_IN}.getData());
}
