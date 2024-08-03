/*
  This file is part of mex-cpp-wrapper library.

  Copyright (c) 2024 David Bayer

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef MEX_VARIABLE_HPP
#define MEX_VARIABLE_HPP

#include <mex.hpp>

#include "Array.hpp"
#include "ArrayRef.hpp"
#include "Exception.hpp"

namespace mex
{
  /// @brief The workspace enumeration.
  enum class Workspace
  {
    base,   ///< The base workspace.
    global, ///< The global workspace.
    caller, ///< The caller workspace.
  };

  namespace detail
  {
    /**
     * @brief Get the name of the workspace.
     * @param workspace The workspace enumeration.
     * @return The name of the workspace.
     */
    [[nodiscard]] inline const char* getWorkspaceName(Workspace workspace)
    {
      switch (workspace)
      {
      case Workspace::base:
        return "base";
      case Workspace::global:
        return "global";
      case Workspace::caller:
        return "caller";
      default:
        throw Exception{"invalid workspace"};
      }
    }
  } // namespace detail

  /**
   * @brief Put a variable into the specified workspace.
   * @param workspace The workspace into which to put the variable.
   * @param name The name of the variable to put.
   * @param value The reference to the variable value.
   */
  inline void putVariable(Workspace workspace, const char* name, ArrayRef value)
  {
    if (!value.isValid())
    {
      throw Exception{"invalid variable value"};
    }

    if (name == nullptr)
    {
      throw Exception{"invalid variable name"};
    }

    const char* workspaceName = detail::getWorkspaceName(workspace);

    if (mexPutVariable(workspaceName, name, value.get()) != 0)
    {
      throw Exception{"failed to put variable"};
    }
  }

  /**
   * @brief Get a variable reference from the specified workspace.
   * @param workspace The workspace from which to get the variable.
   * @param name The name of the variable to get.
   * @return The reference to the variable value.
   */
  [[nodiscard]] inline ArrayCref getVariableRef(Workspace workspace, const char* name)
  {
    if (name == nullptr)
    {
      throw Exception{"invalid variable name"};
    }

    const char* workspaceName = detail::getWorkspaceName(workspace);

    const mxArray* array = mexGetVariablePtr(workspaceName, name);

    if (array == nullptr)
    {
      throw Exception{"failed to get variable reference"};
    }

    return ArrayCref{array};
  }

  /**
   * @brief Get a variable from the specified workspace.
   * @param workspace The workspace from which to get the variable.
   * @param name The name of the variable to get.
   * @return The copy of variable value.
   */
  [[nodiscard]] inline Array getVariable(Workspace workspace, const char* name)
  {
    if (name == nullptr)
    {
      throw Exception{"invalid variable name"};
    }

    const char* workspaceName = detail::getWorkspaceName(workspace);

    mxArray* array = mexGetVariable(workspaceName, name);

    if (array == nullptr)
    {
      throw Exception{"failed to get variable"};
    }

    return Array{array};
  }
} // namespace mex

#endif /* MEX_VARIABLE_HPP */
