/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  Point301.cpp
Purpose:  Projective 3+1D G(3,0,1), 1-vector coefficients: 1D restrictions
Language: C++ / Eng, MSVC (used, but should work with most compilers)
Platform: MSVC / Windows 10 (used, but should have no platform requirements)
Project:  a.Surprise_CS393
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

// <stl>
#include <ostream>      // Output stream definition for operator overload
// "./src/..."
#include "../File/Log.h"       // Message management for errors, warnings, etc
#include "GP301.h"             // 
#include "Plane301.h"          // 
#include "Point301.h"          // Class declaration header


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Private Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//static const u1 SUBSCRIPTS = 4u;  //! Point301 class is fixed at 4 subscripts

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::Point301::Point301(f4 e123_value, f4 e023_value, f4 e031_value,
  f4 e012_value)
  : e123(e123_value), e023(e023_value), e031(e031_value), e012(e012_value)
{
} // end + Point301::Point301((f4))    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::Point301::Point301(const dp::Point301& source)
  : Point301(source.e123, source.e023, source.e031, source.e012)
{ } // end + Point301::Point301(const Point301&)        #^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Accessors                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::Plane301 dp::Point301::Dual(void) const
{
  return Plane301(e123, e023, e031, e012);

} // end Plane301 Point301::Dual(void) const     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::Point301::Json(void) const
{
  const int f = 3;
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += "\"e123\":" + StrF(e123, f) + ",";
  vecFormat += "\"e023\":" + StrF(e023, f) + ",";
  vecFormat += "\"e031\":" + StrF(e031, f) + ",";
  vecFormat += "\"e012\":" + StrF(e012, f) + "]";
  return vecFormat;

} // end + std::string Point301::Json(void) const          #^^^^^^^^^#^^^^^^^^*/

std::string dp::Point301::String(void) const
{
  const int f = 3;
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += (Of <= e123 ? " " : "") + StrF(e123, f) + ", ";
  vecFormat += (Of <= e023 ? " " : "") + StrF(e023, f) + ", ";
  vecFormat += (Of <= e031 ? " " : "") + StrF(e031, f) + ", ";
  vecFormat += (Of <= e012 ? " " : "") + StrF(e012, f) + "]";
  return vecFormat;

} // end + std::string Point301::String(void) const        #^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Mutators                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                            Operator Overloads                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

f4 dp::Point301::operator[](s2 channel) const
{
  switch (channel)
  {
  case 1: case -3: case 23: case 230:  return e023;
  case 2: case -2: case 31: case 310:  return e031;
  case 3: case -1: case 12: case 120:  return e012;
  case 0: case -4: case 123:           return e123;
  }
  channel = ModC((s1)channel, 4);
  switch (channel)
  {
  case 1:   return e023;
  case 2:   return e031;
  case 3:   return e012;
  default:  return e123;
  }
} // end + f4 Point301::operator[](s2) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


f4& dp::Point301::operator[](s2 channel)
{
  channel = ModC((s1)channel, 4);
  switch (channel)
  {
  case 1:   return e023;
  case 2:   return e031;
  case 3:   return e012;
  default:  return e123;
  }
} // end + f4& Point301::operator[](s2)         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::GP301 dp::Point301::operator*(const Point301& other) const
{
  return GP301(-(this->e123 * other.e123),
    this->e012 * other.e031 - this->e031 * other.e012,
    this->e023 * other.e012 - this->e012 * other.e023,
    this->e031 * other.e023 - this->e023 * other.e031,
    this->e023 * other.e123 - this->e123 * other.e023,
    this->e031 * other.e123 - this->e123 * other.e031,
    this->e012 * other.e123 - this->e123 * other.e012,
    Of);
}

dp::GP301 dp::Point301::operator/(const Point301& other) const
{ return (*this) * !other;
} // end + GP301 Point301::operator/(const Point301&)      #^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Helper Functions                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


bool dp::operator==(const Point301& lhs, const Point301& rhs)
{
  return NearF(lhs.e123, rhs.e123)
    && NearF(lhs.e023, rhs.e023)
    && NearF(lhs.e031, rhs.e031)
    && NearF(lhs.e012, rhs.e012);

} // end bool operator==(const Point301&, const Point301&)


bool dp::operator!=(const Point301& lhs, const Point301& rhs)
{
  return !(lhs == rhs);

} // end bool operator!=(const Point301&, const Point301&)


std::ostream& dp::operator<<(std::ostream& output, const Point301& point)
{
  output << point.String();
  return output;
} // end std::ostream& operator<<(std::ostream&, const Point301&)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Helper Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//! Zero vector in real and imaginary dimensions; error state reserved value
const dp::Point301 nullPoint031_(Of);
const dp::Point301& dp::nullPoint031 = nullPoint031_;
