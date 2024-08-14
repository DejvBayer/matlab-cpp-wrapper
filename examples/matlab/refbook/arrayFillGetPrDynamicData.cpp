/*=================================================================
 * arrayFillGetPrDynamicData.c - example used to illustrate how to fill an mxArray
 *
 * Create an mxArray and use mxGetDoubles (or mxGetPr for separate complex
 * MEX files) to point to the starting
 * address of its real data, as in the arrayFillGetPr.c example.
 * Create a dynamic data array and copy your data into it.
 * Fill mxArray with the contents of "dynamicData" and return it in plhs[0].
 *
 * Input:   none
 * Output:  mxArray
 *
 * Copyright 2008-2018 The MathWorks, Inc.
 *
 *=================================================================*/

#include <vector>

#include <mex/mex.hpp>
#include <mex/Function.hpp>

/* The mxArray in this example is 2x2 */
static constexpr std::size_t ROWS    = 2;
static constexpr std::size_t COLUMNS = 2;

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  static constexpr std::array data{2.1, 3.4, 2.3, 2.45}; /* existing data */

  static_assert(data.size() == ROWS * COLUMNS);

  /* Check for proper number of arguments. */
  if (rhs.size() != 0)
  {
    throw mex::Exception{"MATLAB:arrayFillGetPrDynamicData:rhs", "This function takes no input arguments."};
  }

  /* Create a local array and load data */
  std::vector<double> dynamicData{data.begin(), data.end()};

  /* Create a 2-by-2 mxArray; you will copy existing data into it */
  auto output = mex::makeNumericArray<double>(ROWS, COLUMNS);

  /* Copy data into the mxArray */
  std::copy(dynamicData.begin(), dynamicData.end(), output.begin());

  lhs[0] = std::move(output);
}
