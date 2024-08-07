/*=================================================================
 * mxisscalar.c 
 * This example tests an input variable. 
 * If the input is a scalar, returns the scalar value. 
 * Otherwise, displays an error message.
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 2015 The MathWorks, Inc.
 *=================================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{  
  /* Check for proper number of input and output arguments */
  if (rhs.size() != 1)
  {
    mexErrMsgIdAndTxt("MATLAB:mxIsScalar:invalidNumInputs","One input argument required.");
  }

  if (lhs.size() > 1)
  {
    mexErrMsgIdAndTxt("MATLAB:mxIsScalar:maxlhs", "Too many output arguments.");
  }
  
  /* Check to be sure input argument is a scalar */
  if (!rhs[0].isScalar())
  {
    mexErrMsgIdAndTxt("MATLAB:mxIsScalar:invalidInputType", "Input must be a scalar.");
  }
  
  /* Get input variable */
  const double variable = mex::NumericArray<double>{rhs[0]}[0];

  /* Initialize a scalar double precision array */
  lhs[0] = mex::makeNumericScalar(variable);
}
