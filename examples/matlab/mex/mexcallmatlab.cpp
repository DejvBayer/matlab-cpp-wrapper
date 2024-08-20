/*=================================================================
 * mexcallmatlabw.c
 *
 * mexcallmatlabw takes no inputs.  This routine first forms and
 * displays the following matrix (in MATLAB notation):
 *
 *      hankel(1:4,4:-1:1) + sqrt(-1)*toeplitz(1:4,1:4)
 *
 * Next it finds the eigenvalues and eigenvectors (using the MATLAB
 * function EIG), and displays the eigenvalue matrix.  Then it
 * calculates the inverse of the eigenvalues to demonstrate manipulation
 * of MATLAB results and how to deal with complex arithmetic.  Finally,
 * the program displays the inverse values.
 *
 * Copyright 1984-2017 The MathWorks, Inc.
 *================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

static constexpr std::size_t n = 4;

static double& XR(mx::NumericArrayRef<std::complex<double>> a, std::size_t i, std::size_t j)
{
  return reinterpret_cast<double*>(a.getData() + i + n * j)[0];
}

static double& XI(mx::NumericArrayRef<std::complex<double>> a, std::size_t i, std::size_t j)
{
  return reinterpret_cast<double*>(a.getData() + i + n * j)[1];
}

static void fill_array(mx::NumericArrayRef<std::complex<double>> a)
{
      /* Remember, MATLAB stores matrices in their transposed form,
       i.e., columnwise, like FORTRAN. */

    /* Fill real and imaginary parts of array. */
    for (std::size_t j{}; j < n; j++) {
        for (std::size_t i{}; i <= j; i++) {
            XR(a, i, j) = static_cast<double>(n + i - j);
            XR(a, j, i) = XR(a, i, j);
            XI(a, i, j) = static_cast<double>(j - i + 1);
            XI(a, j, i) = XI(a, i, j);
        }
    }
    /* Reorder columns of xr. */
    for (std::size_t j{}; j < n / 2; j++) {
        for (std::size_t i{}; i < n; i++) {
            const double tmp = XR(a, i, j);
            const std::size_t jj = n - j;
            XR(a, i, j) = XR(a, i, jj);
            XR(a, i, jj) = tmp;
        }
    }
}


/* Invert diagonal elements of complex matrix of order 4 */
static void invertd(mx::NumericArrayRef<std::complex<double>> x)
{  
  for(std::size_t i{}; i < n; i++)
  {
    const double temp = XR(x, i, i) * XR(x, i, i) + XI(x, i, i) * XI(x, i, i);
    XR(x, i, i) = XR(x, i, i)/temp;
    XI(x, i, i) = - XI(x, i, i)/temp;
  }
}

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  std::array<mx::Array, 2> tmplhs{};
  
  /* Check for proper number of input and output arguments */    
  if (rhs.size() != 0)
  {
    throw mx::Exception{"MATLAB:mexcallmatlabw:maxrhs", "No input arguments required."};
  }

  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mexcallmatlabw:maxlhs", "Too many output arguments."};
  } 
  
  /* Allocate x matrix */
  auto x = mx::makeNumericArray<std::complex<double>>(n, n);
  
  /* create values in some arrays -- remember, MATLAB stores matrices
      column-wise */
  fill_array(x);
  
  /* print out initial matrix */
  mex::call({{x}}, "disp");
  
  /* calculate eigenvalues and eigenvectors */
  mex::call(tmplhs, {{x}}, "eig");
  /* print out eigenvalue matrix */
  mex::call({{tmplhs[1]}}, "disp");
  
  /* take inverse of complex eigenvalues, just on diagonal */
  invertd(mx::NumericArrayRef<std::complex<double>>{tmplhs[1]});
  /* and print these out */
  mex::call({{tmplhs[1]}}, "disp");
  
  lhs[0] = tmplhs[0];
}
