/*
 * doubleelement.c - example found in API guide
 *
 * constructs a 2-by-2 matrix with unsigned 16-bit integers, doubles
 * each element, and returns the matrix
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2007 The MathWorks, Inc.
 */

#include <mex/mex.hpp>
#include <mex/Function.hpp>

/* the computational subroutine */
void dbl_elem(unsigned short *x)
{
  static constexpr unsigned short scalar = 2;

  for (std::size_t i{}; i < 2; ++i)
  {
    for (std::size_t j{}; j < 2; ++j)
    {
      *(x + i * 2 + j) = scalar * *(x + i * 2 + j);
    }
  }
}

/* the gateway function */
void mex::Function::operator()(Span<Array> lhs, View<ArrayCref>)
{
  static constexpr std::array<std::size_t, 2> dims{2, 2};

  std::array<unsigned short, 4> data{1, 2, 3, 4};

  /* call the computational subroutine */
  dbl_elem(data.data());

  /* create a 2-by-2 array of unsigned 16-bit integers */
  auto array = mex::makeNumericArray<unsigned short>(dims);

  /* populate the real part of the created array */
  std::copy(data.begin(), data.end(), array.begin());

  lhs[0] = std::move(array);
}
