/*=================================================================
 * arrayFillGetPr.c - example used to illustrate how to fill an mxArray
 *
 * Create an mxArray and use mxGetDoubles (or mxGetPr for separate complex
 * MEX files) to point to the starting
 * address of its real data. Fill mxArray with the contents
 * of "data" and return it in plhs[0].
 *
 * Input:   none
 * Output:  mxArray
 *
 * Copyright 2008-2018 The MathWorks, Inc.
 *
 *=================================================================*/

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
    throw mex::Exception{"MATLAB:arrayFillGetPr:rhs", "This function takes no input arguments."};
  }

  /* Create an m-by-n mxArray; you will copy existing data into it */
  auto output = mex::makeNumericArray<double>(ROWS, COLUMNS);

  /* Copy data into the mxArray */
  std::copy(data.begin(), data.end(), output.begin());

  lhs[0] = std::move(output);
}
