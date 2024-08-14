/* ==========================================================================
 * phonebook.c 
 * example for illustrating how to manipulate structure and cell array
 *
 * takes a (MxN) structure matrix and returns a new structure (1x1)
 * containing corresponding fields: for string input, it will be (MxN)
 * cell array; and for numeric (noncomplex, scalar) input, it will be (MxN)
 * vector of numbers with the same classID as input, such as int, double
 * etc..
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2011 The MathWorks, Inc.
 *==========================================================================*/

#include <cstring>
#include <vector>

#include <mex/mex.hpp>
#include <mex/Function.hpp>

/*  the gateway routine.  */
void mex::Function::operator()(Span<Array> lhs, View<ArrayCref> rhs)
{  
  /* check proper input and output */
  if (rhs.size() != 1)
  {
    throw mex::Exception{"MATLAB:phonebook:invalidNumInputs", "One input required."};
  }
  else if (lhs.size() > 1)
  {
    throw mex::Exception{"MATLAB:phonebook:maxlhs", "Too many output arguments."};
  }
  else if (!rhs[0].isStruct())
  {
    throw mex::Exception{"MATLAB:phonebook:inputNotStruct", "Input must be a structure."};
  }

  StructArrayCref input{rhs[0]};
  
  /* get input arguments */
  const std::size_t nfields      = input.getFieldCount();
  const std::size_t NStructElems = input.getSize();
  /* allocate memory  for storing classIDflags */
  std::vector<ClassId> classIDflags(nfields);
  
  /* check empty field, proper data type, and data type consistency;
    * and get classID for each field. */
  for (std::size_t ifield{}; ifield < nfields; ++ifield)
  {
    for(std::size_t jstruct{}; jstruct < NStructElems; ++jstruct)
    {
      auto printWhere = [ifield, jstruct]()
      {
        mex::printf("FIELD: %d\tSTRUCT INDEX: %d\n", ifield + 1, jstruct + 1);
      };

      ArrayCref tmp = input.getField(jstruct, mex::FieldIndex{ifield}).value();

      if (jstruct == 0)
      {
        if ((!tmp.isChar() && !tmp.isNumeric()) || tmp.isSparse())
        {
          printWhere();
          throw mex::Exception{"MATLAB:phonebook:invalidField", "Above field must have either string or numeric non-sparse data."};
        }

        classIDflags[ifield] = tmp.getClassId();
      }
      else
      {
        if (tmp.getClassId() != classIDflags[ifield])
        {
          printWhere();
          throw mex::Exception{"MATLAB:phonebook:invalidFieldType", "Inconsistent data type in above field!"};
        }
        else if (!tmp.isChar() && (tmp.isComplex() || tmp.getSize() != 1))
        {
          printWhere();
          throw mex::Exception{"MATLAB:phonebook:fieldNotRealScalar", "Numeric data in above field must be scalar and noncomplex!"};
        }
      }
    }
  }
  
  /* allocate memory for storing pointers */
  std::vector<const char*> fnames(nfields);

  /* get field name pointers */
  for (std::size_t ifield{}; ifield < nfields; ++ifield)
  {
    fnames[ifield] = input.getFieldName(mex::FieldIndex{ifield});
  }

  /* create a 1x1 struct matrix for output  */
  mex::StructArray output = mex::makeStructArray(1, 1, fnames);

  for (std::size_t ifield{}; ifield < nfields; ++ifield)
  {
    Array fout{};
    std::byte* pdata{};

    /* create cell/numeric array */
    if (classIDflags[ifield] == mex::ClassId::_char)
    {
      fout = mex::makeCellArray(input.getDims());
    }
    else
    {
      fout  = mex::makeNumericArray(input.getDims(), classIDflags[ifield]);
      pdata = static_cast<std::byte*>(fout.getData());
    }

    /* copy data from input structure array */
    for (std::size_t jstruct{}; jstruct < NStructElems; ++jstruct)
    {
      ArrayCref tmp = input.getField(jstruct, mex::FieldIndex{ifield}).value();

      if (tmp.isChar())
      {
        mex::CellArrayRef{fout}[jstruct] = tmp;
      }
      else
      {
        const std::size_t sizebuf = tmp.getSizeOfElement();
        std::memcpy(pdata, tmp.getData(), sizebuf);
        pdata += sizebuf;
      }
    }

    /* set each field in output structure */
    output.setField(0, mex::FieldIndex{ifield}, std::move(fout));
  }

  lhs[0] = std::move(output);
}
