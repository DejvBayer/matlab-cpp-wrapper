/*=================================================================
 * mxcalcsinglesubscript.c 
 *
 * This is an example of how to use mxCalcSingleSubscript.  To run
 * this example, you pass in a N-dimensional array of doubles and
 * MATLAB indices to the element you would like returned. It will
 * return the element you selected. The number of indices you pass in
 * must match the number of dimensions in your array. The array may
 * consist of real or complex values.  This example demonstrates
 * that MATLAB uses 1 based indexing and C uses 0 based indexing.
 * It details how to convert from MATLAB to C based indexing,
 * while accessing elements in a N-dimensional array.
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 1984-2017 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <vector>

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{  
  /* Check for proper number of input and output arguments */
  if (rhs.size() != 2)
  {
    throw mex::Exception{"MATLAB:mxcalcsinglesubscript:invalidNumInputs", "Two input arguments required."};
  }

  if (lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:mxcalcsinglesubscript:maxlhs", "Too many output arguments."};
  }
  
  /* Check data type of first input argument */
  if (!rhs[0].isDouble())
  {
    throw mex::Exception{"MATLAB:mxcalcsinglesubscript:invalidFirstInputType", "First input argument must be a double."};
  }

  /* Check data type of second argument */
  if (!rhs[1].isDouble() || rhs[1].isComplex())
  {
    throw mex::Exception{"MATLAB:mxcalcsinglesubscript:invalidSecondInputType", "Second input argument must be a real double."};
  }

  /* Get the number of dimensions in array */
  const std::size_t nsubs = rhs[0].getRank();
  
  /* Check for the correct number of indices  */
  if (rhs[1].getRank() != nsubs)
  {
    throw mex::Exception{"MATLAB:mxcalcsinglesubscript:inputMismatch", "You must specify an index for each dimension."};
  }
  
  /* Allocate memory for the subs array on the fly */
  std::vector<std::size_t> subs(nsubs);
  
  /* Get the indices and account for the fact that MATLAB is 1
   * based and C is zero based.  While doing this, check to make
   * sure that an index was not specified that is larger than size
   * of input array */
  mex::NumericArrayCref<double> temp{rhs[1]};

  std::transform(temp.begin(),
                 temp.end(),
                 subs.begin(),
                 [](const double& x) { return static_cast<std::size_t>(x) - 1; });

  if (std::any_of(subs.begin(),
                  subs.end(),
                  [&](const std::size_t& x) { return x >= rhs[0].getDims()[x]; }))
  {
    throw mex::Exception{"MATLAB:mxcalcsinglesubscript:badsubscript", "You indexed above the size of the array."};
  }
  
  /* Find the index of location selected.  Note, for example, that
    * (3,4) in MATLAB corresponds to (2,3) in C. */
  const std::size_t index = mex::calcSingleSubscript(rhs[0], subs);
  
  /* Create the output array */
  if (rhs[0].isComplex())
  {
    const auto value = mex::NumericArrayCref<std::complex<double>>{rhs[0]}[index];
    
    lhs[0] = mex::makeNumericScalar(value);
  }
  else
  {
    const auto value = mex::NumericArrayCref<double>{rhs[0]}[index];
    
    lhs[0] = mex::makeNumericScalar(value);
  }
}
