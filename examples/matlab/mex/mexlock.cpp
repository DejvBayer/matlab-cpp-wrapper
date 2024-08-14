/*=================================================================
 * mexlock.c
 *
 * This example demonstrates how to use mexLock, mexUnlock, and 
 * mexIsLocked.
 *
 * You must call mexlock with one argument.  If you pass in a 1, it
 * will lock the MEX-file. If you pass in a -1, it will unlock the
 * MEX-file. If you pass in 0, it will report lock status.   It uses
 * mexIsLocked to check the status of the MEX-file. If the file is
 * already in the state you requested, the MEX-file errors out.
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 1984-2011 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{  
  /* Check for proper number of input and output arguments */   
  if (rhs.size() != 1 || !rhs[0].isDouble() || !rhs[0].isScalar())
  {
    throw mex::Exception{"MATLAB:mexlock:inputNotRealScalarDouble", "Input argument must be a real scalar double"};
  }
  
  if (!lhs.empty())
  {
    throw mex::Exception{"MATLAB:mexlock:maxlhs", "No output arguments expected."};
  }

  const double lock = mex::NumericArrayCref<double>{rhs[0]}[0];
  
  if ((lock != 0.0) && lock != 1.0 && lock != -1.0)
  {
    throw mex::Exception{"MATLAB:mexlock:invalidInputValue", "Input argument must be either 1 to lock or -1 to unlock or 0 for lock status.\n"};
  }
  
  if (isLocked())
  {
    if (lock > 0.0)
    {
      throw mex::Exception{"MATLAB:mexlock:invalidLockState", "MEX-file is already locked\n"};
    }
    else if (lock < 0.0)
    {
      unlock();
      mex::printf("MEX-file is unlocked\n");
    }
    else
    {
      mex::printf("MEX-file is locked\n");
    }
  }
  else
  {
    if (lock < 0.0)
    {
      throw mex::Exception{"MATLAB:mexlock:invalidUnlockState", "MEX-file is already unlocked\n"};
    }
    else if (lock > 0.0)
    {
      this->lock();
      mex::printf("MEX-file is locked\n");
    }
    else
    {
      mex::printf("MEX-file is unlocked\n");
    }
  }
}
