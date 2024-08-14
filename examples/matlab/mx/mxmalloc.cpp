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

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{  
  /* Check for proper number of input and output arguments */
  if (rhs.size() != 1)
  { 
    throw mex::Exception{"MATLAB:mxmalloc:invalidNumInputs", "One input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:MXMALLOC:maxlhs", "Too many output arguments."};
  }
  
  /* Check for proper input type */
  if (!rhs[0].isChar() || rhs[0].getDims()[0] != 1)
  {
    throw mex::Exception{"MATLAB:mxmalloc:invalidInput", "Input argument must be a string."};
  }
  
  std::string str = mex::CharArrayCref{rhs[0]}.toAscii();

  mex::printf("The input string is:  %s\n", str.c_str());
  /* NOTE: You could add your own code here to manipulate 
     the string */
}
