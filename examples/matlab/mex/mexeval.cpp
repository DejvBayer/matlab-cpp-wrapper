/*
 * mexeval.c : Example MEX-file code emulating the functionality of the
 *             MATLAB command EVAL
 *
 *              
 * Copyright 1984-2011 The MathWorks, Inc.
 */

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array>, View<ArrayCref> rhs)
{
  if (rhs.empty())
  {
    throw mex::Exception{"MATLAB:mexeval:minrhs", "Function requires one input.\n"};
  }
  else if (rhs[0].getClassId() != mex::ClassId::_char)
  {    
    throw mex::Exception{"MATLAB:mexeval:UndefinedFunction", "Function 'mexeval' defined only for for variables of class 'char'\n"};
  }  
  else
  {
    /* causes MATLAB to execute the string as an expression 
     * or statement the biggest limitation is that it won't 
     * evaluate any left-hand arguments except 'ans'
     */
    const std::size_t buflen = rhs[0].getDims()[0];

    std::string fcn(buflen, '\0');

    mxGetString(rhs[0].get(), fcn.data(), buflen);
    
    try
    {
      mex::eval(fcn.c_str());
    }
    catch (const mex::Exception&)
    {
      if (rhs.size() == 2)
      {
        /* provides the ability to catch errors.  It
        * executes string s1 and returns if the operation was
        * successful. If the operation generates an error,
        * string s2 is evaluated before returning.
        */        
        const std::size_t buflen = rhs[1].getDims()[0];

        std::string cmd(buflen, '\0');
        
        mxGetString(rhs[1].get(), cmd.data(), buflen);
        mex::eval(cmd.c_str());
      }
    }
  }
}
