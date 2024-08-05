/*
 * Example of how to use the mxGPUArray API in a MEX file.  This example shows
 * how to write a MEX function that takes a gpuArray input and returns a
 * gpuArray output, e.g. B=mexFunction(A).
 *
 * Copyright 2012 The MathWorks, Inc.
 */

#include <mex/mex.hpp>
#include <mex/Function.hpp>

/*
 * Device code
 */
void __global__ TimesTwo(const double* const A,
                         double* const       B,
                         const unsigned      N)
{
  /* Calculate the global linear index, assuming a 1-d grid. */
  const unsigned i = blockDim.x * blockIdx.x + threadIdx.x;

  if (i < N)
  {
    B[i] = 2.0 * A[i];
  }
}

/*
 * Host code
 */
void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  /* Declare all variables.*/
  static constexpr char errId[]  = "parallel:gpu:mexGPUExample:InvalidInput";
  static constexpr char errMsg[] = "Invalid input to MEX file.";

  /* Choose a reasonably sized number of threads for the block. */
  static constexpr unsigned threadsPerBlock = 256;

  /* Throw an error if the input is not a GPU array. */
  if (rhs.size() != 1 || !rhs[0].isGpuArray())
  {
    throw mex::Exception{errId, errMsg};
  }

  mex::gpu::Array A{rhs[0]};

  /*
    * Verify that A really is a double array before extracting the pointer.
    */
  if (A.getClassId() != mex::ClassId::_double)
  {
    throw mex::Exception{errId, errMsg};
  }

  /*
    * Now that we have verified the data type, extract a pointer to the input
    * data on the device.
    */
  const double* d_A = mex::gpu::NumericArrayCref<double>{A}.getData();

  /* Create a GPUArray to hold the result and get its underlying pointer. */
  mex::gpu::NumericArray<double> B = mex::gpu::makeUninitNumericArray<double>(A.getDims());

  double* d_B = B.getData();

  /*
    * Call the kernel using the CUDA runtime API. We are using a 1-d grid here,
    * and it would be possible for the number of elements to be too large for
    * the grid. For this example we are not guarding against this possibility.
    */
  const unsigned N = static_cast<unsigned>(A.getSize());
  const unsigned blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
  TimesTwo<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, N);

  /* Wrap the result up as a MATLAB gpuArray for return. */
  lhs[0] = B.release();
}
