/*
 * mexfeval.c : Example MEX-file code emulating the functionality of the
 *              MATLAB command FEVAL
 *
 *              
 * Copyright 1984-2017 The MathWorks, Inc.
 */

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  if (rhs.empty())
  {
    throw mx::Exception{"MATLAB:mexfeval:minrhs", "Not enough input arguments."};
  }

  if (!rhs[0].isChar())
  {
    throw mx::Exception{"MATLAB:mexfeval:invalidInput", "Variable must contain a string."};
  }

  /*
   * overloaded functions could be a problem
   */
  std::string fcn = mx::toAscii(rhs[0]);

  mex::call(lhs, rhs.subspan(1), fcn);
}
