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

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* Check for proper number of input and output arguments */
  if (rhs.size() < 1)
  {
    throw mx::Exception{"MATLAB:mxcreatecellmatrix:minrhs", "At least one input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mxcreatecellmatrix:maxlhs", "Too many output arguments."};
  }

  /* Create a nrhs x 1 cell mxArray. */
  auto cell_array = mx::makeCellArray(rhs.size(), 1);

  /* Fill cell matrix with input arguments */
  for (std::size_t i{}; i < rhs.size(); ++i)
  {
    cell_array[i] = rhs[i];
  }

  lhs[0] = std::move(cell_array);
}
