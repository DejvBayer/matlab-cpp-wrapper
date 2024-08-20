/*=================================================================
 * mxisfinite.c 
 *
 * mxisfinite takes one input argument of type double. It returns one
 * output argument of type integer (32 bits) with equivalent values.
 * Values greater than the integer maximum or less than the integer
 * minimum are stored as INT_MAX/INT_MIN respectively.  NaNs in the
 * input argument are flagged as a warning and stored as zero.
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 1984-2017 The MathWorks, Inc.
 *=================================================================*/

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

/* Function that converts double to int32 */
static std::int32_t dtoi32(double d)
{
  using Int32Limits = std::numeric_limits<std::int32_t>;

  std::int32_t i{};
  
  if (mx::isFinite(d))
  {
    if (d < static_cast<double>(Int32Limits::max()) && d > static_cast<double>(Int32Limits::min()))
    {
      i = static_cast<std::int32_t>(d);
    }
    else
    {
      i = ((d > 0.0) ? Int32Limits::max() : Int32Limits::min());
    }
  }
  else if (mx::isInf(d))
  {
    i = ((d > 0.0) ? Int32Limits::max() : Int32Limits::min());
    /* NOTE: Test for NaN is here for illustration only. If a double
     * is not finite and is not infinity, then it is a NaN */
  }
  else if (mx::isNaN(d))
  {
    mex::warn("MATLAB:mxisfinite:NaN", "dtoi32: NaN detected. Translating to 0.\n");

    i = 0;
  }

  return i;
}

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* Check for proper number of input and output arguments */    
  if (rhs.size() != 1)
  {
    throw mx::Exception{"MATLAB:mxisfinite:invalidNumInputs", "One input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mxisfinite:maxlhs", "Too many output arguments."};
  }
  
  /* Check data type of input argument  */
  if (!rhs[0].isDouble())
  {
    throw mx::Exception{"MATLAB:mxisfinite:invalidInputType", "Input argument must be of type double."};
  }	

  if (rhs[0].isEmpty())
  {
    throw mx::Exception{"MATLAB:mxisfinite:empty", "Input argument is empty\n"};
  }

  if (rhs[0].isComplex())
  {
    mx::NumericArrayCref<std::complex<double>> c{rhs[0]};

    auto c32 = mx::makeNumericArray<std::complex<std::int32_t>>(c.getDims());

    std::transform(c.begin(),
                   c.end(),
                   c32.begin(),
                   [](const std::complex<double>& x)
    {
      return std::complex<std::int32_t>{dtoi32(x.real()), dtoi32(x.imag())};
    });

    lhs[0] = std::move(c32);
  }
  else
  {
    mx::NumericArrayCref<double> r{rhs[0]};

    auto r32 = mx::makeNumericArray<std::int32_t>(r.getDims());

    std::transform(r.begin(),
                   r.end(),
                   r32.begin(),
                   dtoi32);

    lhs[0] = std::move(r32);
  }
}
