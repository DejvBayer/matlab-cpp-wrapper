/*=================================================================
 * mexgetarray.c
 *
 * This example demonstrates how to use mexGetVariable, mexPutVariable, and
 * mexFunctionName. This function takes no input arguments. It counts
 * the number of times mexgetarray.c is called.  It has an internal
 * counter in the MEX-file and a counter in the MATLAB global
 * workspace.  Even if the MEX-file is cleared, it will not lose count
 * of the number of times the MEX-file has been called.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2018 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <cstring>

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

static int mex_count = 0;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  char array_name[40];
  
  /* Check for proper number of input and output arguments */
  if (!rhs.empty())
  {
    throw mx::Exception{"MATLAB:mexgetarray:minrhs", "No input arguments required."};
  }

  if (!lhs.empty())
  {
    throw mx::Exception{"MATLAB:mexgetarray:maxrhs", "Too many output arguments."};
  }

  /* Make copy of MEX-file name, then create variable for MATLAB
     workspace from MEX-file name. */
  std::strcpy(array_name, getName());
  std::strcat(array_name, "_called");

  /* Get variable that keeps count of how many times MEX-file has
     been called from MATLAB global workspace. */
  mx::NumericArray<double> array{};
  
  /* Check status of MATLAB and MEX-file MEX-file counter */
  if (auto arrayOpt = mex::getVariable(mex::Workspace::global, array_name); !arrayOpt.has_value())
  {
    if (mex_count != 0)
    {
      mex_count = 0;
      mex::printf("Variable %s\n", array_name);
      throw mx::Exception{"MATLAB:mexgetarray:invalidGlobalVarState",
                          "Global variable was cleared from the MATLAB global workspace.\nResetting count.\n"};
    }

    /* Since variable does not yet exist in MATLAB workspace,
      * create it and place it in the global workspace. */
    array = mx::makeNumericScalar<double>();
  }
  else
  {
    array = mx::NumericArray<double>{std::move(arrayOpt.value())};
  }

  /* Increment both MATLAB and MEX counters by 1 */
  array[0] += 1;
  mex_count = static_cast<int>(array[0]);
  mex::printf("%s has been called %i time(s)\n", getName(), mex_count);

  /* Put variable in MATLAB global workspace */
  mex::putVariable(mex::Workspace::global, array_name, array);
}
