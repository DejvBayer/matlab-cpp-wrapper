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

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void errorCheck(std::size_t nlhs, mx::View<mx::ArrayCref> rhs)
{
  /* Check for proper number of arguments. */
  if (rhs.size() != 1 || !rhs[0].isNumeric() || !rhs[0].isScalar())
  {
    throw mx::Exception{"MATLAB:arraySize:rhs", "This function requires one scalar numeric input."};
  } 

  const double dim = rhs[0].getScalarAs<double>();

  if (dim < 0.0)
  {
    throw mx::Exception{"MATLAB:arraySize:dimensionNegative", "The input dimension must be positive."};
  }

  /* Make sure that it is safe to cast dim to mwSize when using largeArrayDims.*/
  if (dim > mx::maxSize)
  {
    throw mx::Exception{"MATLAB:arraySize:dimensionTooLarge", "The input dimension is larger than the maximum value of mwSize when built with largeArrayDims."};
  }

  if (nlhs > 1)
  {
    throw mx::Exception{"MATLAB:arraySize:lhs","Too many output arguments."};
  }
}

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  errorCheck(lhs.size(), rhs);

  const std::size_t dim = static_cast<std::size_t>(rhs[0].getScalarAs<double>());
  
  /* Create an mxArray of size dim x dim of type uint8.*/
  mx::NumericArray<std::uint8_t> theArray = mx::makeUninitNumericArray<std::uint8_t>(dim, dim);

  /* Display the mxArray's dimension. */
  mex::printf("\nDimensions: %zu x %zu\n", theArray.getDimM(), theArray.getDimN());

  /* Display the mxArray's size. */
  const std::size_t numberOfElements = theArray.getSize();
  
  /* numberOfElements can be converted to a double without loss of 
     precision because the maximum size of an array is 2^48-1. */
  const double sizeOfDataInKilobytes = static_cast<double>(numberOfElements * theArray.getSizeOfElement()) / 1024.0;
  mex::printf("Size of array in kilobytes: %.0f\n\n", sizeOfDataInKilobytes);

  /* Return result only if one is requested. */
  if (lhs.size() == 1)
  {
    lhs[0] = mx::makeNumericScalar(sizeOfDataInKilobytes);
  }
}
