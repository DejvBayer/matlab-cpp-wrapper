/*=========================================================
 * matrixDivide.c - Example for illustrating how to use 
 * LAPACK within a C MEX-file.
 *
 * X = matrixDivide(A,B) computes the solution to a 
 * system of linear equations A * X = B
 * using LAPACK routine DGESV, where 
 * A is a real N-by-N matrix.
 * X and B are real N-by-1 matrices.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2009-2018 The MathWorks, Inc.
 *=======================================================*/

#include <vector>

#include <lapack.h>

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* Check for proper number of arguments. */
  if (rhs.size() != 2)
  {
    throw mx::Exception{"MATLAB:matrixDivide:rhs", "This function requires 2 input matrices."};
  }

  /* check to make sure the first input argument is a real matrix */
  if (!rhs[0].isDouble() || rhs[0].isComplex())
  {
    throw mx::Exception{"MATLAB:matrixDivide:fieldNotRealMatrix", "First input argument must be a real, double matrix."};
  }
  /* check to make sure the second input argument is a real matrix */
  if (!rhs[1].isDouble() || rhs[1].isComplex())
  {
    throw mx::Exception{"MATLAB:matrixDivide:fieldNotRealMatrix", "Second input argument must be a real, double matrix."};
  }

  /* dimensions of input matrices */
  const std::ptrdiff_t m = static_cast<std::ptrdiff_t>(rhs[0].getDimM());
  const std::ptrdiff_t p = static_cast<std::ptrdiff_t>(rhs[0].getDimN());
  const std::ptrdiff_t n = static_cast<std::ptrdiff_t>(rhs[1].getDimN());

  if (static_cast<std::size_t>(p) != rhs[1].getDimM())
  {
    throw mx::Exception{"MATLAB:matrixDivide:matchdims", "Inner dimensions of matrices do not match."};
  }
  if (p != m)
  {
    throw mx::Exception{"MATLAB:matrixDivide:square", "LAPACK function requires input matrix 1 must be square."};
  }
  if (n != 1)
  {
    throw mx::Exception{"MATLAB:matrixDivide:zerodivide", "For this example input matrix 2 must be a column vector."};
  }

  /* DGESV works in-place, so we copy the inputs first. */
  std::vector<double> Awork{mx::NumericArrayCref<double>{rhs[0]}.begin(), mx::NumericArrayCref<double>{rhs[0]}.end()};

  double* A2 = Awork.data();

  /* Create output for DGESV */
  auto output = mx::makeUninitNumericArray<double>(static_cast<std::size_t>(p), static_cast<std::size_t>(n));
  std::copy(mx::NumericArrayCref<double>{rhs[1]}.begin(), mx::NumericArrayCref<double>{rhs[1]}.end(), output.begin());

  double* B2 = output.getData();

  /* Create inputs for DGESV */
  std::vector<std::ptrdiff_t> pivot(static_cast<std::size_t>(m * p));

  std::ptrdiff_t info{};

  /* Call LAPACK */
  dgesv(&m, &n, A2, &m, pivot.data(), B2, &p, &info);
  
  lhs[0] = std::move(output);
}
