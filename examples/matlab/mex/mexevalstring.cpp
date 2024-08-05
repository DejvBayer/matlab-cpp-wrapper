/*=================================================================
 * mexevalstring.c
 *
 * mexevalstring takes no input arguments. It uses mexEvalString to
 * assign a couple of variables in MATLAB.
 *
 * Copyright 1984-2009 The MathWorks, Inc.
 *================================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  /* Check for proper number of input and output arguments */    
  if (!lhs.empty())
  {
    throw mex::Exception{"MATLAB:mexevalstring:nInput", "No input arguments required."};
  }

  if (!lhs.empty())
  {
    throw mex::Exception{"MATLAB:mexevalstring:nOutput", "Too many output arguments."};
  } 

  /* Assign a value to the variable a. */
  mex::eval("a=10");
  
  /* Assign a value to the variable b. */
  mex::eval("b='Hello World'");
}
