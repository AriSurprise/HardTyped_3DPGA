/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  mNMf.cpp
Purpose:  2D NxN, column major square matrix; inputs / outputs in row major
Language: C++ / Eng, MSVC (used, but should work with most compilers)
Platform: MSVC / Windows 10 (used, but should have no requirements)
Project:  a.Surprise_MAT345_3
Author:   Ari Surprise, a.surprise, 40000218
Creation date:  Spring 2023
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
#^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
#pragma once

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                                  Includes                                  */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

#include "../File/Log.h"    // Error / warning output message / logging
#include "../Math/mNf.h"    // Square matrix to non-square potential initializations
#include "../Math/mNMf.h"   // Associated class declaration header
#include "../Util/Value.h"  // Basic numerical operations: clamp, swap, min, max, etc

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::mNMf::mNMf(void)
  : dimens({ 2u, 2u }), cell({ 1u, 0u, 0u,1u })
{ } // end mNMf(void) Default 2x2 matrix constructor                          */


dp::mNMf::mNMf(u2 cols, std::initializer_list<f8> data)
  : mNMf(cols, dp::vNf(data))
{ } // end mNf(initializer_list<f8>, u2) 1D initializer list constructor      */

dp::mNMf::mNMf(u2 cols, const vNf& data)
{
  // Set matrix dimensions
  dimens.col = (u4)(cols ? cols : 1);
  dimens.row = ((u4)data.Dimens() / dimens.col);
  cell.Resize(dimens.Area());
  // Populate cells with row major data
  for (um i = 0; i < data.Dimens(); ++i) { cell[i] = data[i]; }
  // Initialize any trailing 0's not included in initial value list
  for (um i = data.Dimens(); i < cell.Dimens(); ++i) { cell[i] = Of; }

} // end mNMf(const vNf&, u2) 1D unwrapped matrix row constructor             */


dp::mNMf::mNMf(const std::vector<vNf>& data)
{
  um max_cols = 0; // Maximum column size of any given input row vectors
  for (um i = 0; i < data.size(); ++i)
  {
    max_cols = MaxUM(max_cols, data[i].Dimens());
  }
  // Set matrix dimensions
  dimens.Set((u4)data.size(), (u4)max_cols);
  cell.Resize(dimens.Area());
  // Populate cells with row major data
  for (um r = 0; r < dimens.row; ++r)
  {
    um ri = r * dimens.col, // Row initial index in 1D cell list
      rt = (r + 1) * dimens.col; // Row terminal index in 1D cell list
    // Populate row data with input
    for (um c = 0; c < data[r].Dimens(); ++c) { cell[ri + c] = data[r][c]; }
    // Initialize row remainder without input to 0
    for (um c = ri + data[r].Dimens(); c < rt; ++c) { cell[c] = Of; }
  }
} // end mNMf(const vector<vNf>&, u2)                                         */


dp::mNMf::mNMf(const v2u& dimens, f4 scalar)
  : dimens(dimens.row ? dimens.row : 1u, dimens.col ? dimens.col : 1u)
{
  // Scale matrix to input dimensions
  cell.Resize(this->dimens.Area());
  // Initialize matrix cells
  for (u4 r = 0; r < this->dimens.row; ++r)
  {
    // Per-row subscript breakdown
    u4 ri = r * this->dimens.col, // Row initial index in 1D cell list
      rp = ri + (r < this->dimens.col ? r : 0), // Row pivot index in cell
      rt = (r + 1) * this->dimens.col; // Row terminal index in 1D cell list
    for (u4 c = ri; c < rp; ++c) { cell[c] = Of; } // Pre
    if (0 < ri || ri < rp) { cell[rp] = scalar; } // Pivot
    for (u4 c = rp; c < rt; ++c) { cell[c] = Of; } // Post
  }
} // end mNf(const v2u&, f4) Arbitrary matrix dimensional variable identity   */


dp::mNMf::mNMf(const mNf& source)
  : dimens((u4)(source.Dimens() ? source.Dimens() : 1),
    (u4)(source.Dimens() ? source.Dimens() : 1))
{
  cell.Resize(dimens.Area());
  cell[0] = If;
  for (um r = 0; r < dimens.row; ++r)
  {
    um ri = r * dimens.col;
    for (um c = 0; c < dimens.col; ++c) { cell[ri + c] = source[r][c]; }
  }
} // end mNMf(const mNf&)                                                     */


dp::mNMf::mNMf(const mNMf& source)
  : cell(source.cell), dimens(source.dimens)
{ } // end mNMf(const mNMf&)                                                  */

dp::mNMf::mNMf(mNMf&& result) noexcept
  : cell(std::move(result.cell)), dimens(std::move(result.dimens))
{ } // end mNMf(const mNMf&&) noexcept                                        */



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Public Methods                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::mNMf::JSON(void) const
{
  // Set up {col, data[]} constructor
  if (cell.Dimens() == 0) { return "{0,{}}"; }
  // Add 2-Dimensional breaking intervals
  std::string result("{" + std::to_string(dimens.col) + ",{");
  // Add 2D matrix cell data as 1D array
  for (um i = 0; i < cell.Dimens(); ++i)
  {
    result += "," + std::to_string(cell[i]);
  }
  result += "}}";
  return result;

} // end std::string mNMf::JSON(void) const                                   */


dp::mNMf& dp::mNMf::Resize(const v2u& dimen, s4 row_shift, s4 col_shift,
  const v2f& augment)
{
  mNMf s; // source matrix (copy / backup of initial state)
  s.dimens = dimens; // defer resize & copying source data cells to needed time
  dimens.Set(dimen.row? dimen.row: 1, dimen.col? dimen.col: 1);
  um r,c, // iterators for current row, column values
     sri, ri; // (source) matrix's initial row index (+ column) offset
  v2u indent, // source <row, col> offsets for old dimensions
    pad, // initial <row, col> offsets for new dimensions
    span(dimens); // source data's <row, col> spread to read from in new dimens

  // If moving data down/right...
  if ((s4)s.dimens.row < row_shift || (s4)s.dimens.col < col_shift
    || (s4)dimens.row < row_shift || (s4)dimens.col < col_shift)
  {
    // Shifted beyond all source data or new dimensional ranges: shortcut
    cell.Resize(dimens.Area());
    for (c = 0; c < cell.Dimens(); ++c) { cell[c] = augment.low; }
    return *this;
  }
  if (IsNegI(col_shift)) // If moving data left...
  {
    indent.col = -col_shift;
    // Shifted beyond source data or new dimensions' width
    if (s.dimens.col < indent.col)
    {
      cell.Resize(dimens.Area());
      for (c = 0; c < cell.Dimens(); ++c) { cell[c] = augment.high; }
      return *this;
    }
  }
  else
  {
    pad.col = col_shift;
    if (dimens.col <= pad.col)
    {
      cell.Resize(dimens.Area());
      for (c = 0; c < cell.Dimens(); ++c) { cell[c] = augment.low; }
      return *this;
    }
  }
  if (IsNegI(row_shift)) // If shifting up...
  {
    indent.row = -row_shift;
    if (s.dimens.row < indent.row)
    {
      cell.Resize(dimens.Area());
      for (c = 0; c < cell.Dimens(); ++c) { cell[c] = augment.high; }
      return *this;
    }
  }
  else
  {
    pad.row = row_shift;
    if (dimens.row <= pad.row)
    {
      cell.Resize(dimens.Area());
      for (c = 0; c < cell.Dimens(); ++c) { cell[c] = augment.low; }
      return *this;
    }
  }


  // Perform deferred copy of source matrix (precluded paths to skip)
  s.cell = cell; // Backup old dimension positions
  cell.Resize(dimens.Area()); // Truncate / extend new dimensions post-backup
  span.Set(MinU(MinU(span.row, s.dimens.row-indent.row), dimens.row-pad.row),
           MinU(MinU(span.col, s.dimens.col-indent.col), dimens.col-pad.col));

  // Overwrite any low cells from partial down-shifting to old data start
  sri = pad.row * dimens.col; // up to first non negative source cell
  for (c = 0; c < sri; ++c) { cell[c] = augment.low; }

  // Copy old cell location data to new cell locations
  for (r = 0; r < span.row; ++r) // Populate new dimensions per row
  {
    // Get initial row indices
    sri = (r+indent.row) * s.dimens.col + indent.col;
    ri = (r+pad.row) * dimens.col;
    // Set pre-data columns uniformly
    for (c = 0; c < pad.col; ++c) { cell[ri + c] = augment.low; }
    // Set data columns to their correspondent source cell values
    for (c = 0; c < span.col; ++c) { cell[ri+pad.col+c] = s.cell[sri+c]; }
    // Set post-data columns uniformly
    for (c = pad.col+span.col; c<dimens.col; ++c) { cell[ri+c] = augment.high; }
  }
  // Set all trailing cells uniformly after data copy completion 
  for (c = (span.row+pad.row)*dimens.col; c < cell.Dimens(); ++c)
  {
    cell[c] = augment.high;
  }
  return *this;

} // end mNMf& mNMf::Resize(const v2u&, s4, s4, const v2f&)                   */


dp::mNMf& dp::mNMf::Set(const vNf& source)
{
  cell = source;
  dimens.Set((u4)source.Dimens(), 1u);
  return *this;

} // end mNf& mNf::Set(const vNf&)                                            */


dp::mNMf& dp::mNMf::Set(u2 cols, const vNf& source)
{
  u2 c = cols? cols : 1;
  u2 r = source.Dimens()? (u2)(source.Dimens() / c) : 1;
  dimens.Set(c, r);
  cell = source;
  cell.Resize(dimens.Area());
  return *this;

} // end mNf& mNf::SetTranspose(const vNf&)                                   */


dp::mNMf& dp::mNMf::Set(const mNf& source)
{
  u4 d = (u4)source.Dimens();
  cell.Resize(d * d);
  dimens.Set(d, d);
  for (um r = 0; r < d; ++r)
  {
    um ri = r * d;
    for (um c = 0; c < d; ++c)
    {
      cell[ri+c] = source[c][r];
    }
  }
  return *this;

} // end mNf& mNf::Set(const mNf&)                                            */


dp::mNMf& dp::mNMf::Set(const mNMf& source)
{
  // Straight memberwise copy
  cell = source.cell;
  dimens = source.dimens;
  return *this;

} // end mNf& mNf::Set(const mNMf&)                                           */


std::string dp::mNMf::ToString(bool lineBreaks) const
{
  if (cell.Dimens() == 0) { return "[null]"; }
  std::string end = lineBreaks ? "],\n [" : "],[";
  std::string result("[[" + std::to_string(cell[0]));
  for (um c = 1; c < dimens.col; ++c)
  {
    result += ", " + std::to_string(cell[c]);
  }
  for (um r = 1; r < dimens.row; ++r)
  {
    um ri = r * dimens.col;
    result += end + std::to_string(cell[ri]);
    for (um c = 1; c < dimens.col; ++c)
    {
      result += ", " + std::to_string(cell[ri+c]);
    }
  }
  result += "]]";
  return result;

} // end std::string mNf::ToString(void) const                                */


dp::mNMf& dp::mNMf::Transpose(void)
{
  vNf m(cell);
  um ri;
  for (um r = 0; r < dimens.row; ++r)
  {
    ri = r * dimens.col;
    for (um c = 0; c < dimens.col; ++c)
    {
      cell[c*dimens.row + r] = m[ri + c];
    }
  }
  dimens.Swap();
  return *this;

} // end mNf& mNf::Transpose(void)                                            */


dp::mNMf dp::mNMf::Transposed(void) const
{ return Copy().Transpose(); } // end mNf mNf::Transposed(void) const         */



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                            Operator Overloads                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::mNMf& dp::mNMf::operator=(const vNf& source)
{
  return this->Set(source);

} // end mNf& mNf::operator=(const vNf&)                                      */

dp::mNMf& dp::mNMf::operator=(const mNf& source)
{
  return this->Set(source);

} // end mNf& mNf::operator=(const mNf&)                                      */


dp::mNMf& dp::mNMf::operator=(const mNMf& source)
{
  return this->Set(source);

} // end mNf& mNf::operator=(const mNMf&)                                     */


dp::mNMf& dp::mNMf::operator=(mNMf&& result) noexcept
{
  cell = std::move(result.cell);
  return *this;

} // end mNf& mNf::operator=(mNf&&) noexcept                                  */


dp::mNMf dp::mNMf::operator-(void) const
{
  mNMf copy(Dimens());
  for (size_t i = 0; i < cell.Dimens(); ++i)
  {
    copy.cell[i] = -cell[i]; // Copy each element, negated
  }
  return copy;

} // end mNf mNf::operator-(void) const                                       */


dp::mNMf dp::mNMf::operator!(void) const
{
  return Transposed();

} // end mNf mNf::operator!(void)                                             */


const f4& dp::mNMf::operator[](const v2u& index) const
{
  return cell[(index.row * dimens.col) + index.col];

} // end const f4& mNMf::operator[](const v2u&) const                         */


f4& dp::mNMf::operator[](const v2u& index)
{
  return cell[index.row * dimens.col + index.col];

} // end f4* mNMf::operator[](const v2u&)                                     */


dp::mNMf dp::mNMf::operator+(const mNMf& other) const
{
  return Copy() += other;

} // end mNMf mNMf::operator+(const mNMf&)


dp::mNMf& dp::mNMf::operator+=(const mNMf& other)
{
  for (u4 i = 0; i < cell.Dimens(); ++i) { cell[i] += other.cell[i]; }
  return *this;

} // end mNMf& mNMf::operator+=(const mNMf&)


dp::mNMf dp::mNMf::operator-(const mNMf& other) const
{
  return Copy() += -other;

} // end mNMf mNMf::operator-(const mNMf&)


dp::mNMf& dp::mNMf::operator-=(const mNMf& other)
{
  return *this += -other;

} // end mNNf& mNMf::operator-=(const mNMf&)


dp::mNMf dp::mNMf::operator*(f4 scalar) const
{
  return Copy() *= scalar;

} // end mNf mNf::operator*(f4) const

dp::mNMf& dp::mNMf::operator*=(f4 scalar)
{
  for (u4 i = 0; i < cell.Dimens(); ++i) { cell *= scalar; }
  return *this;

} // end mNf& mNf::operator*=(f4) const