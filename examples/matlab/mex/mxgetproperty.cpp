/*=================================================================
 * mxgetproperty.c 
 *
 * This example demonstrates how to use mxGetProperty and mxSetProperty.  The input
 * to this function is a handle graphics handle.  mxgetproperty.c gets the
 * Color property of the handle that was passed into the function. It
 * then changes the colors, and uses mxSetProperty to set the Color property
 * of the handle to the new color values.
 *
 *
 * This is a MEX-file for MATLAB.  
 * Copyright 1984-2020 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <cstring>

#include <matlabw/mex/mex.hpp>
#include <matlabw/mex/Function.hpp>

using namespace matlabw;

static constexpr std::size_t RED   = 0;
static constexpr std::size_t GREEN = 1;
static constexpr std::size_t BLUE  = 2;

void mex::Function::operator()(mx::Span<mx::Array> lhs, mx::View<mx::ArrayCref> rhs)
{
  /* Assume that the first input argument is a graphics
     handle. Check to make sure the input is a double and that only
     one input is specified.*/
  if (rhs.size() != 1)
  {
    throw mx::Exception{"MATLAB:mxgetproperty:minrhs", "Not enough input arguments."};
  }
  
  /* Check for the correct number of outputs */
  if (lhs.size() > 1)
  {
    throw mx::Exception{"MATLAB:mxgetproperty:maxlhs", "Too many output arguments."};
  }

  mx::Array array{rhs[0]};
      
  /* Check to make sure input argument is a object */
  if (std::strncmp(array.getClassName(), "matlabw.graphics", 15))
  {
    throw mx::Exception{"MATLAB:mxgetproperty:inputMustBeObject", "Must be called with a valid graphics handle.\n"};
  }
  
  /* Get the "Color" property associated with this handle. */
  auto color_array = mx::getProperty(array, "Color");
  
  if (!color_array.has_value())
  {
    throw mx::Exception{"MATLAB:mxgetproperty:errGettingHandleProperty", "Could not get this handle property"};
  }
  
  /* Make copy of "Color" propery */
  mx::Array value{*color_array};
  
  /* The returned "Color" property is a 1-by-3 matrix of primary colors. */ 
  double* color = value.getDataAs<double>();
  
  /* Change the color values */
  color[RED]   = (1.0 + color[RED]) / 2.0;
  color[GREEN] = color[GREEN] / 2.0;
  color[BLUE]  = color[BLUE] / 2.0;
  
  /* Reset the "Color" property to use the new color. */
  mx::setProperty(array, "Color", value);
}
