/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  Line301.cpp
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
#include "../File/Log.h"  // Message management for errors, warnings, etc
#include "v3f.h"          // Class declaration header
#include "GP301.h"        // Even subalgebra (result of like blade products)
#include "Line301.h"      // Class declaration header


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Private Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//static const u1 SUBSCRIPTS = 4u;    //! Line301 class is fixed at 4 subscripts

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::Line301::Line301(f4 e23_value, f4 e31_value, f4 e12_value, f4 e01_value,
  f4 e02_value, f4 e03_value)
  : e23(e23_value), e31(e23_value), e12(e12_value),
    e01(e01_value), e02(e02_value), e03(e03_value)
{
} // end + Line301::Line301((f4),(f4),(f4),(f4),(f4),(f4)) #^^^^^^^^^#^^^^^^^^*/

dp::Line301::Line301(const v3f& moment, const v3f& dir)
  : Line301(moment.x, moment.y, moment.z, dir.x, dir.y, dir.z)
{
} // end + Line301::Line301(const v3f&,const v3f&)         #^^^^^^^^^#^^^^^^^^*/

dp::Line301::Line301(const dp::Line301& source)
  : Line301(source.e23, source.e31, source.e12, source.e01, source.e02,
    source.e03)
{ } // end + Line301::Line301(const Line301&)    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Accessors                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::Line301::Json(void) const
{
  const int f = 3;
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += "\"e23\":" + StrF(e23, f) + ",";
  vecFormat += "\"e31\":" + StrF(e31, f) + ",";
  vecFormat += "\"e12\":" + StrF(e12, f) + ",";
  vecFormat += "\"e01\":" + StrF(e01, f) + ",";
  vecFormat += "\"e02\":" + StrF(e02, f) + ",";
  vecFormat += "\"e03\":" + StrF(e03, f) + "]";
  return vecFormat;

} // end + std::string Line301::Json(void) const #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::Line301::String(void) const
{
  const int f = 3;
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += (Of <= e23 ? " " : "") + StrF(e23, f) + ", ";
  vecFormat += (Of <= e31 ? " " : "") + StrF(e31, f) + ", ";
  vecFormat += (Of <= e12 ? " " : "") + StrF(e12, f) + ", ";
  vecFormat += (Of <= e01 ? " " : "") + StrF(e01, f) + ", ";
  vecFormat += (Of <= e02 ? " " : "") + StrF(e02, f) + ", ";
  vecFormat += (Of <= e03 ? " " : "") + StrF(e03, f) + "]";
  return vecFormat;

} // end + std::string Line301::String(void) const         #^^^^^^^^^#^^^^^^^^*/

dp::GP301 dp::Line301::operator*(const Line301& other) const
{
  return GP301
  (
    (-e23*other.e23 - e31*other.e31 - e12*other.e12),

    ( e23*other.e31 - e31*other.e23),
    (-e23*other.e12 + e12*other.e23),
    ( e31*other.e12 - e12*other.e31),

    (e23*other.e02 - e02*other.e23 + e03*other.e31 - e31*other.e03),
    (e01*other.e23 - e23*other.e01 + e12*other.e03 - e03*other.e12),
    (e31*other.e01 - e01*other.e31 - e12*other.e02 + e02*other.e12),

    (e03*other.e23 + e23*other.e03 + e01*other.e12 + e12*other.e01
   + e02*other.e31 + e31*other.e02)
  );
}


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Mutators                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Helper Functions                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


bool dp::operator==(const Line301& lhs, const Line301& rhs)
{
  return NearF(lhs.e23, rhs.e23)
    && NearF(lhs.e31, rhs.e31)
    && NearF(lhs.e12, rhs.e12)
    && NearF(lhs.e01, rhs.e01)
    && NearF(lhs.e02, rhs.e02)
    && NearF(lhs.e03, rhs.e03);

} // end bool operator==(const Line301&, const Line301&)


bool dp::operator!=(const Line301& lhs, const Line301& rhs)
{
  return !(lhs == rhs);

} // end bool operator!=(const Line301&, const Line301&)


std::ostream& dp::operator<<(std::ostream& output, const Line301& line)
{
  output << line.String();
  return output;
} // end std::ostream& operator<<(std::ostream&, const Line301&)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Helper Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//! Zero vector in real and imaginary dimensions; error state reserved value
const dp::Line301 nullLine301_(Of, Of, Of, Of, Of, Of);
const dp::Line301& dp::nullLine301 = nullLine301_;
