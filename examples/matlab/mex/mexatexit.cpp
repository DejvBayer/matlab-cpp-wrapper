/*=================================================================
 * mexatexit.c 
 * 
 * This example demonstrates how to use mexAtExit.  It allows you to
 * write strings to a data file, matlabw.data.  The MEX-file
 * mexatexit.c registers an exit function that closes the datafile.
 * The input to the MEX-file mexatexit is a string.  You may continue
 * calling the function with new strings to add to the file
 * matlabw.data. The data file will not be closed until the MEX-file is
 * cleared or MATLAB is exited, which cause the exit function to be
 * executed.

 * This is a MEX-file for MATLAB.  
 * Copyright 1984-2011 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <cstdio>
#include <memory>

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

struct FileDeleter
{
  /* Here is the exit function, which gets run when the MEX-file is
     cleared and when the user exits MATLAB. The mexAtExit function
     should always be declared as static. */
  void operator()(FILE* fp) const noexcept
  {
    mex::printf("Closing file matlabw.data.\n");
    std::fclose(fp);
  }
};

static std::unique_ptr<FILE, FileDeleter> fp{};

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* Check for proper number of input and output arguments */    
  if (rhs.size() != 1)
  {
    throw mx::Exception{"MATLAB:mexatexit:invalidNumInputs", "One input argument required."};
  }

  if(lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mexatexit:maxrhs", "Too many output arguments."};
  }

  if (!rhs[0].isChar())
  {
    throw mx::Exception{"MATLAB:mexatexit:invalidInput", "Input must be of type string.\n."};
  }
  
  if (!fp)
  {
    FILE* tmpfp = std::fopen("matlabw.data", "w");

    if (tmpfp == NULL)
    {
      throw mx::Exception{"MATLAB:mexatexit:errorOpeningFile", "Could not open file matlabw.data."}; 
    }

    mex::printf("Opening file matlabw.data.\n");

    /* Register an exit function. You should only register the
       exit function after the file has been opened successfully*/
    fp.reset(tmpfp);
  }

  /* The user passes a string in prhs[0]; write the string
      to the data file. NOTE: you must free str after it is used */
  std::string str = mx::toAscii(rhs[0]);

  if (static_cast<std::size_t>(std::fprintf(fp.get(), "%s\n", str.c_str())) != str.size() + 1)
  {
    throw mx::Exception{"MATLAB:mexatexit:errorWritingFile", "Could not write data to file.\n"};
  }

  mex::printf("Writing data to file.\n");
} 
