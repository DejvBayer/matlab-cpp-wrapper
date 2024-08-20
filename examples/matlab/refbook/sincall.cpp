/*=====================================================================
 * sincall.c
 *
 * example for illustrating how to use mexCallMATLAB
 * 
 * creates an mxArray and passes its associated  pointers (in this demo,
 * only pointer to its real part, pointer to number of rows, pointer to
 * number of columns) to subfunction fill() to get data filled up, then 
 * calls mexCallMATLAB to calculate sin function and plot the result.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2018 The MathWorks, Inc.
 *===================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

static constexpr std::size_t MAX = 1000;

/* subroutine for filling up data */
void fill(double* const     ptr,
          std::size_t&      m,
          std::size_t&      n,
          const std::size_t max)
{
  /* you can fill up to max elements, so (*pr)<=max */
  m = max / 2;
  n = 1;

  for (std::size_t i{}; i < m; ++i)
  { 
    ptr[i] = static_cast<double>(i) * (4.0 * 3.14159 / static_cast<double>(max));
  }
}

/* gateway function */
void mex::Function::operator()(mx::Span<mx::Array>, mx::View<mx::ArrayCref>)
{
  auto rhs = mx::makeNumericArray<double>(MAX, 1);

  /* pass the pointers and let fill() fill up data */
  std::size_t m{};
  std::size_t n{};
  fill(rhs.getData(), m, n, MAX);
  
  rhs.resize(m, n);

  std::array<mx::Array, 2> inplot{};          /* input to plot function */
  inplot[0] = rhs;

  /* get the sin wave */
  mx::Array lhs0{};
  mex::call(mx::makeScalarSpan<mx::Array>(lhs0), mx::makeScalarView<mx::ArrayCref>(rhs), "sin");

  inplot[1] = std::move(lhs0);
  
  /* plot(rhs, sin(rhs)) */
  mex::call({{inplot[0], inplot[1]}}, "plot");
}
