/**
 * mexcallmatlabwwithtrap.c 
 *
 * This example demonstrates how to use mexCallMATLABWithTrap. 
 *
 * Copyright 2011 The MathWorks, Inc.
 */

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* Check for proper number of input and output arguments */    
  if (rhs.size() != 1)
  { 
    throw mx::Exception{"MATLAB:mexcallmatlabwwithtrap:invalidInput", "Only one input argument allowed"};
  }
  else if (!rhs[0].isChar())
  {
    throw mx::Exception{"MATLAB:mexcallmatlabwwithtrap:invalidInput", "Input argument must be a string"};
  }

  if (lhs.size() > 0)
  {
    throw mx::Exception{"MATLAB:mexcallmatlabwwithtrap:maxlhs", "Too many output arguments."};
  }

  std::string function_name = mx::toAscii(rhs[0]);

  /* Invoke the function specified as the first input, which must take 
   * zero inputs and have zero outputs */
  mex::call({}, function_name);

  mex::printf("%s called successfully\n", function_name.c_str());
}
