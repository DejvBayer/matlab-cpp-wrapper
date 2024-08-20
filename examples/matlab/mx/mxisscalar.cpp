/*=================================================================
 * mxisscalar.c 
 * This example tests an input variable. 
 * If the input is a scalar, returns the scalar value. 
 * Otherwise, displays an error message.
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 2015 The MathWorks, Inc.
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{  
  /* Check for proper number of input and output arguments */
  if (rhs.size() != 1)
  {
    throw mx::Exception{"MATLAB:mxIsScalar:invalidNumInputs","One input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mxIsScalar:maxlhs", "Too many output arguments."};
  }
  
  /* Check to be sure input argument is a scalar */
  if (!rhs[0].isScalar())
  {
    throw mx::Exception{"MATLAB:mxIsScalar:invalidInputType", "Input must be a scalar."};
  }
  
  /* Get input variable */
  const double variable = rhs[0].getScalarAs<double>();

  /* Initialize a scalar double precision array */
  lhs[0] = mx::makeNumericScalar(variable);
}
