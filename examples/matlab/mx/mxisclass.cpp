/*=================================================================
 * mxisclass.c
 *
 * mxisclass takes no input arguments and returns no output
 * arguments. It creates an inline MATLAB object, and then gets and
 * prints the fields of this object.
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
  if (!rhs.empty())
  {
   throw mex::Exception{"MATLAB:mxisclass:maxrhs", "No input argument required."};
  }

  if(lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:mxisclass:maxlhs", "Too many output arguments."};
  }

  mex::CharArray   input{"sin(3*x)"};
  mex::StructArray output{};
  
  /* Use mexCallMATLAB to call the constructor and create the
   * object in MATLAB */
  mex::call(mex::makeScalarSpan<Array>(output), {{input}}, "inline");
  
  /* Verify that the output an inline object, if it is get
    * its fields and print them. */
  if (!output.isClass("inline"))
  {
    throw mex::Exception{"MATLAB:mxisclass:ctorFailed", "Failed to create an object of class inline"};
  }

  mex::printf("This object contains the following fields:\n");
  mex::printf("name\t\tclass\t\tvalue\n");
  mex::printf("-------------------------------------\n");
  
  /* Get the first field name, then the second, and so on. */
  for (std::size_t i{}; i < output.getFieldCount(); ++i)
  {
    mex::printf("%s", output.getFieldName(mex::FieldIndex{i}));

    auto a = output.getField(mex::FieldIndex{i});

    if (a.has_value())
    {
      mex::printf("\t\t%s\t\t", a->getClassName());
      mex::call({{*a}}, "disp");
    }
  }
}
