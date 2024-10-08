/*=================================================================
 * mxgeteps.c
 *
 * This is an example of how to use mxGetEps.  The function takes two
 * real double arrays and does an element-by-element compare of each
 * element for equality within eps. Eps is the distance from 1.0 to
 * the next largest floating point number and is used as the default
 * tolerance.  If all the elements are equal within eps, a 1 is returned.
 * If they are not all equal within eps, a 0 is returned.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2018 The MathWorks, Inc.
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  std::size_t j{};

  /* Check for proper number of input and output arguments */
  if (rhs.size() != 2)
  {
    throw mx::Exception{"MATLAB:mxgeteps:invalidNumInputs", "Two input arguments required."};
  }
  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mxgeteps:maxlhs", "Too many output arguments."};
  }

  /* Check data type of first input argument */
  if (!rhs[0].isDouble() || !rhs[1].isDouble() || rhs[0].isComplex() || rhs[1].isComplex())
  {
    throw mx::Exception{"MATLAB:mxgeteps:inputNotRealDouble", "Input arguments must be real of type double."};
  }

  /* Check that dimensions are the same for input arguments. */
  if (rhs[0].getRank() != rhs[1].getRank())
  {
    throw mx::Exception{"MATLAB:mxgeteps:numElementMismatch", "Inputs must have the same number of dimensions.\n"};
  }

  /* Check that inputs have the same dimensions. */
  if (!std::equal(rhs[0].getDims().begin(), rhs[0].getDims().end(), rhs[1].getDims().begin()))
  {
    throw mx::Exception{"MATLAB:mxgeteps:numDimensionsMismatch", "Inputs must have the same dimensions.\n"};
  }

  /* Get the number of elements in the input argument */
  const std::size_t elements = rhs[0].getSize();

  /* Get the input values */
  const double* first_ptr  = rhs[0].getDataAs<double>();
  const double* second_ptr = rhs[1].getDataAs<double>();

  /* Create output */
  auto ret = mx::makeNumericScalar(0.0);

  /* Get the value of eps */
  const double eps = mx::getEps();

  /* Check for equality within eps */
  for (j = 0; j < elements; ++j)
  {
    if (std::abs(first_ptr[j] - second_ptr[j]) > std::abs(second_ptr[j] * eps))
    {
      break;
    }
  }

  if (j == elements)
  {
    ret[0] = 1.0;
  }

  lhs[0] = std::move(ret);
}
