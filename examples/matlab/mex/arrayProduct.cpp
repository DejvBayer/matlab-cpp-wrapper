/*==========================================================
 * arrayProduct.c - example in MATLAB External Interfaces
 *
 * Multiplies an input scalar (multiplier) 
 * times a 1xN matrix (inMatrix)
 * and outputs a 1xN matrix (outMatrix)
 *
 * The calling syntax is:
 *
 *		outMatrix = arrayProduct(multiplier, inMatrix)
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2007-2012 The MathWorks, Inc.
 *
 *========================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

/* The computational routine */
void arrayProduct(double x, const double* y, double* z, std::size_t n)
{
  /* multiply each element y by x */
  for (std::size_t i{}; i < n; ++i)
  {
    z[i] = x * y[i];
  }
}

/* The gateway function */
void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* check for proper number of arguments */
  if (rhs.size() != 2)
  {
    throw mx::Exception{"MyToolbox:arrayProduct:nrhs", "Two inputs required."};
  }

  if (lhs.size() != 1)
  {
    throw mx::Exception("MyToolbox:arrayProduct:nlhs", "One output required.");
  }

  /* make sure the first input argument is scalar */
  if (!rhs[0].isDouble() || rhs[0].isComplex() || !rhs[0].isScalar())
  {
    throw mx::Exception{"MyToolbox:arrayProduct:notScalar", "Input multiplier must be a scalar."};
  }
  
  /* make sure the second input argument is type double */
  if (!rhs[1].isDouble() || rhs[1].isComplex())
  {
    throw mx::Exception{"MyToolbox:arrayProduct:notDouble", "Input matrix must be type double."};
  }
  
  /* check that number of rows in second input argument is 1 */
  if (rhs[1].getDimM() != 1)
  {
    throw mx::Exception{"MyToolbox:arrayProduct:notRowVector", "Input must be a row vector."};
  }
  
  /* get the value of the scalar input */
  const double multiplier = rhs[0].getScalarAs<double>();

  /* create a pointer to the real data in the input matrix  */
  const double* inMatrix = rhs[1].getDataAs<double>();

  /* get dimensions of the input matrix */
  const std::size_t ncols = rhs[1].getDimN();

  /* create the output matrix */
  mx::NumericArray<double> out = mx::makeUninitNumericArray<double>(1, ncols);

  /* get a pointer to the real data in the output matrix */
  double* outMatrix = out.getData();

  /* call the computational routine */
  arrayProduct(multiplier, inMatrix, outMatrix, ncols);

  lhs[0] = std::move(out);
}
