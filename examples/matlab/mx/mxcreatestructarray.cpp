/*=================================================================
 * mxcreatestructarray.c
 *
 * mxcreatestructarray illustrates how to create a MATLAB structure
 * from a corresponding C structure.  It creates a 1-by-4 structure mxArray,
 * which contains two fields, name and phone number where name is store as a
 * string and phone number is stored as a double.  The structure that is
 * passed back to MATLAB could be used as input to the phonebook.c example
 * in $MATLAB/extern/examples/refbook.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2018 The MathWorks, Inc.
 * All rights reserved.
 *=================================================================*/

#include <mex/mex.hpp>
#include <mex/Function.hpp>

struct Phonebook
{
  const char* name;
  double      phone;
};

void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{
  static constexpr std::array field_names{"name", "phone"};
  static constexpr std::array friends{Phonebook{"Jordan Robert", 3386},
                                      Phonebook{"Mary Smith",    3912},
                                      Phonebook{"Stacy Flora",   3238},
                                      Phonebook{"Harry Alpert",  3077}};
  mwSize dims[2] = {1, friends.size()};

  /* Check for proper number of input and  output arguments */
  if (!rhs.empty())
  {
    throw mex::Exception{"MATLAB:mxcreatestructarray:maxrhs", "No input argument required."};
  }

  if (lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:mxcreatestructarray:maxlhs", "Too many output arguments."};
  }

  /* Create a 1-by-n array of structs. */
  auto array = mex::makeStructArray(1, friends.size(), field_names);

  /* This is redundant, but here for illustration.  Since we just
     created the structure and the field number indices are zero
     based, name_field will always be 0 and phone_field will always
     be 1 */
  
  const mex::FieldIndex name_field  = array.getFieldIndex("name");
  const mex::FieldIndex phone_field = array.getFieldIndex("phone");

  /* Populate the name and phone fields of the phonebook structure. */
  for (std::size_t i{}; i < friends.size(); ++i)
  {
    /* Use mxSetFieldByNumber instead of mxSetField for efficiency
     * mxSetField(plhs[0],i,"name",mxCreateString(friends[i].name); */
    array.setField(i, name_field, mex::makeCharArray(friends[i].name));

    /* Use mxSetFieldByNumber instead of mxSetField for efficiency
     * mxSetField(plhs[0],i,"name",mxCreateString(friends[i].name); */
    array.setField(i, phone_field, mex::makeNumericScalar(friends[i].phone));
  }

  lhs[0] = std::move(array);
}
