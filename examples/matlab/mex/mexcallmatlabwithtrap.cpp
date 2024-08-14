/**
 * mexcallmatlabwithtrap.c 
 *
 * This example demonstrates how to use mexCallMATLABWithTrap. 
 *
 * Copyright 2011 The MathWorks, Inc.
 */

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  mxArray * exception = NULL;

  /* Check for proper number of input and output arguments */    
  if (rhs.size() != 1)
  { 
    throw mex::Exception{"MATLAB:mexcallmatlabwithtrap:invalidInput", "Only one input argument allowed"};
  }
  else if (!rhs[0].isChar())
  {
    throw mex::Exception{"MATLAB:mexcallmatlabwithtrap:invalidInput", "Input argument must be a string"};
  }

  if (lhs.size() > 0)
  {
    throw mex::Exception{"MATLAB:mexcallmatlabwithtrap:maxlhs", "Too many output arguments."};
  }

  std::string function_name = mex::toAscii(rhs[0]);

  /* Invoke the function specified as the first input, which must take 
   * zero inputs and have zero outputs */
  mex::call({}, function_name);

  mex::printf("%s called successfully\n", function_name.c_str());
}
