/*=================================================================
 * mxmalloc.c
 * 
 * This function takes a MATLAB string as an argument and copies it in 
 * NULL terminated ANSI C string. Use this function only with 
 * MATLAB strings represented in single-byte encoding schemes.
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 1984-2017 The MathWorks, Inc.
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{  
  /* Check for proper number of input and output arguments */
  if (rhs.size() != 1)
  { 
    throw mx::Exception{"MATLAB:mxmalloc:invalidNumInputs", "One input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:MXMALLOC:maxlhs", "Too many output arguments."};
  }
  
  /* Check for proper input type */
  if (!rhs[0].isChar() || rhs[0].getDims()[0] != 1)
  {
    throw mx::Exception{"MATLAB:mxmalloc:invalidInput", "Input argument must be a string."};
  }
  
  std::string str = mx::CharArrayCref{rhs[0]}.toAscii();

  mex::printf("The input string is:  %s\n", str.c_str());
  /* NOTE: You could add your own code here to manipulate 
     the string */
}
