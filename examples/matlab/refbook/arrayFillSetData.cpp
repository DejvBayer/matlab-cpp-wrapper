/*=================================================================
 * arrayFillSetData.c - example used to illustrate how to fill an mxArray
 *
 * Same functionality as arrayFillSetPr.c, except use the appropriate 
 * mxSet* function to operate on data types other than double.
 *
 * UINT16_T declares appropriate uint16 type for platform
 *
 * Input:   none
 * Output:  mxArray
 *
 * Copyright 2008-2018 The MathWorks, Inc.
 *	
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

/* The mxArray in this example is 2x2 */
static constexpr std::size_t ROWS    = 2;
static constexpr std::size_t COLUMNS = 2;

void mex::Function::operator()(mx::Span<mx::Array>, mx::View<mx::ArrayCref>)
{
  static constexpr std::array<std::uint16_t, 4> data{2, 3, 2, 1};  /* existing data */

  static_assert(data.size() == ROWS * COLUMNS);

  throw mx::Exception{"MATLAB:arrayFillSetData:unsupported", "matlab-cpp-wrapper currently does not support setting matrix data."};
}
