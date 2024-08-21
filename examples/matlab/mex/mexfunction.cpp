/*=================================================================
 * mexfunction.c
 *
 * This example demonstrates how to use mexFunction.  It returns
 * the number of elements for each input argument, providing the
 * function is called with the same number of output arguments
 * as input arguments.
 

 * This is a MEX-file for MATLAB.
 * Copyright 1984-2018 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* Examine input (right-hand-side) arguments. */
  mex::printf("\n%zu input argument(s).", rhs.size());

  for (std::size_t i{}; i < rhs.size(); ++i)
  {
    mex::printf("\n\tInput Arg %i is of type:\t%s ", i, rhs[i].getClassName());
  }

  /* Examine output (left-hand-side) arguments. */
  mex::printf("\n\n%d output argument(s).\n", lhs.size());

  if (lhs.size() != rhs.size())
  {
    throw mx::Exception{"MATLAB:mexfunction:inputOutputMismatch", "Number of inputs and outputs must match.\n"};
  }

  for (std::size_t i{}; i < lhs.size(); ++i)
  {
    const double nel = static_cast<double>(rhs[i].getSize());

    lhs[i] = mx::makeNumericScalar(nel);
  }
}
