/*
 * mexfeval.c : Example MEX-file code emulating the functionality of the
 *              MATLAB command FEVAL
 *
 *              
 * Copyright 1984-2017 The MathWorks, Inc.
 */

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  if (rhs.empty())
  {
    throw mex::Exception{"MATLAB:mexfeval:minrhs", "Not enough input arguments."};
  }

  if (!rhs[0].isChar())
  {
    throw mex::Exception{"MATLAB:mexfeval:invalidInput", "Variable must contain a string."};
  }

  /*
   * overloaded functions could be a problem
   */
  std::string fcn = mex::toAscii(rhs[0]);

  mex::call(lhs, mex::View{rhs.data() + 1, rhs.size() - 1}, fcn.c_str());
}
