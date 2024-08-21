/*
 * mexeval.c : Example MEX-file code emulating the functionality of the
 *             MATLAB command EVAL
 *
 *              
 * Copyright 1984-2011 The MathWorks, Inc.
 */

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array>, mx::View<mx::ArrayCref> rhs)
{
  if (rhs.empty())
  {
    throw mx::Exception{"MATLAB:mexeval:minrhs", "Function requires one input.\n"};
  }
  else if (!rhs[0].isChar())
  {
    throw mx::Exception{"MATLAB:mexeval:UndefinedFunction", "Function 'mexeval' defined only for for variables of class 'char'\n"};
  }
  else
  {
    /* causes MATLAB to execute the string as an expression 
     * or statement the biggest limitation is that it won't 
     * evaluate any left-hand arguments except 'ans'
     */
    std::string fcn = mx::toAscii(mx::CharArrayCref{rhs[0]});
    
    try
    {
      mex::eval(fcn);
    }
    catch (const mx::Exception&)
    {
      if (rhs.size() == 2)
      {
        /* provides the ability to catch errors.  It
         * executes string s1 and returns if the operation was
         * successful. If the operation generates an error,
         * string s2 is evaluated before returning.
         */        
        std::string cmd = mx::toAscii(mx::CharArrayCref{rhs[1]});
        
        mex::eval(cmd);
      }
    }
  }
}
