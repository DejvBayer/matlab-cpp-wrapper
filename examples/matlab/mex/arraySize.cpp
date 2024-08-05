/*=================================================================
 * arraySize.c - example used to illustrate memory requirements 
 * of large mxArrays. 
 *
 * Input: Length of square matrix
 * Output: Approximate memory required for matrix (optional)
 *
 * Creates and destroys a square mxArray of uint8 values and  
 * displays the approximate size of the matrix in kilobytes.
 *
 * Copyright 2007-2011 The MathWorks, Inc.
 *=================================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void errorCheck(std::size_t nlhs, mex::View<mex::ArrayCref> rhs)
{
  /* Check for proper number of arguments. */
  if (rhs.size() != 1 || !rhs[0].isNumeric() || rhs[0].getSize() != 1)
  {
    throw mex::Exception{"MATLAB:arraySize:rhs", "This function requires one scalar numeric input."};
  } 

  const double dim = mex::NumericArrayCref<double>{rhs[0]}[0];

  if (dim < 0.0)
  {
    throw mex::Exception{"MATLAB:arraySize:dimensionNegative", "The input dimension must be positive."};
  }

  /* Make sure that it is safe to cast dim to mwSize when using largeArrayDims.*/
  if (dim > MWSIZE_MAX)
  {
    throw mex::Exception{"MATLAB:arraySize:dimensionTooLarge", "The input dimension is larger than the maximum value of mwSize when built with largeArrayDims."};
  }

  if (nlhs > 1)
  {
    throw mex::Exception{"MATLAB:arraySize:lhs","Too many output arguments."};
  }
}

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  errorCheck(lhs.size(), rhs);

  const std::size_t dim = static_cast<std::size_t>(mex::NumericArrayCref<double>(rhs[0])[0]);
  
  /* Create an mxArray of size dim x dim of type uint8.*/
  mex::NumericArray<std::uint8_t> theArray = mex::makeUninitNumericArray<std::uint8_t>({{dim, dim}});

  /* Display the mxArray's dimension. */
  mex::printf("\nDimensions: %" FMT_SIZE_T "u x %" FMT_SIZE_T "u\n", theArray.getDims()[0], theArray.getDims()[1]);

  /* Display the mxArray's size. */
  const std::size_t numberOfElements = theArray.getSize();
  
  /* numberOfElements can be converted to a double without loss of 
    precision because the maximum size of an array is 2^48-1. */
  const double sizeOfDataInKilobytes = numberOfElements * theArray.getSizeOfElement() / 1024.0;
  mex::printf("Size of array in kilobytes: %.0f\n\n", sizeOfDataInKilobytes);

  /* Return result only if one is requested. */
  if (lhs.size() == 1)
  {
    lhs[0] = makeNumericScalar(sizeOfDataInKilobytes);
  }
}



