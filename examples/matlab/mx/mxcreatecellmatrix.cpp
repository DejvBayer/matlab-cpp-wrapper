/*=================================================================
 * mxcreatecellmatrix.c
 *
 * mxcreatecellmatrix takes the input arguments and places them in a
 * cell array. This cell array is returned back to MATLAB as the result.
 *
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2018 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  /* Check for proper number of input and output arguments */
  if (rhs.size() < 1)
  {
    throw mex::Exception{"MATLAB:mxcreatecellmatrix:minrhs", "At least one input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:mxcreatecellmatrix:maxlhs", "Too many output arguments."};
  }

  /* Create a nrhs x 1 cell mxArray. */
  auto cell_array = mex::makeCellArray(rhs.size(), 1);

  /* Fill cell matrix with input arguments */
  for (std::size_t i{}; i < rhs.size(); ++i)
  {
    cell_array[i] = rhs[i];
  }

  lhs[0] = std::move(cell_array);
}
