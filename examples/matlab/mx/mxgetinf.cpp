/*=================================================================
 * mxgetinf.c 
 *
 * mxgetinf takes one input argument of type double floating
 * integers.  For this example, zero values are used to indicate missing
 * data.  It replaces all zeros with NaN.  Values greater than equal to
 * INT_MAX are replaced with infinity.  Values less than or equal to
 * INT_MIN are replaced with minus infinity.  mxgetinf returns the data
 * with the replaced values.
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
    throw mx::Exception{"MATLAB:mxgetinf:invalidNumInputs", "One input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mxgetinf:maxlhs", "Too many output arguments."};
  }
  
  /* Check data type of input argument  */
  if (!rhs[0].isDouble() || rhs[0].isComplex())
  {
    throw mx::Exception{"MATLAB:mxgetinf:invalidInputType", "Input argument must be of type real double."};
  }	
  
  /* Duplicate input array */
  mx::NumericArray<double> output{rhs[0]};
  
  const double inf = mx::getInf();
  const double nan = mx::getNaN();

  /* Check for 0, in real part of data, if the data is zero, replace
     with NaN.  Also check for INT_MAX and INT_MIN and replace with
     INF/-INF respectively.  */
  std::for_each(output.begin(), output.end(), [inf, nan](auto& value)
  {
    if (value == 0)
    {
      value = nan;
    }
    else if (value >= static_cast<double>(std::numeric_limits<int>::max()))
    {
      value = inf;
    }
    else if (value <= static_cast<double>(std::numeric_limits<int>::min()))
    {
      value = -(inf);
    }
  });

  lhs[0] = std::move(output);
}
