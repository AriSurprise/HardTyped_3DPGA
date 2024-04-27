/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  I301.cpp
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
#include "../File/Log.h"        // Message management for errors, warnings, etc
#include "I301.h"          // Class declaration header


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Private Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//static const u1 SUBSCRIPTS = 4u;    //! I301 class is fixed at 4 subscripts

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::I301::I301(f4 scale)
  : inner(scale)
{
} // end + I301::I301((f4))            #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::I301::I301(const dp::I301& source)
  : I301(source.inner)
{ } // end + I301::I301(const I301&)        #^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Accessors                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::I301::Json(void) const
{
  const int f = 3;
  std::string d = StrF(inner, f);
  return "{\"inner\":" + d + "}}";

} // end + std::string I301::Json(void) const         #^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Mutators                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::I301::String(void) const
{
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += (Of <= inner? " " : "") + StrF(inner) + "]";
  return vecFormat;

} // end + std::string I301::String(void) const #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                            Operator Overloads                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

f4 dp::I301::operator[](s2 channel) const { return inner;
} // end + f4 I301::operator[](s2) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


f4& dp::I301::operator[](s2 channel) { return inner;
} // end + f4& I301::operator[](s2)         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Helper Functions                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


bool dp::operator==(const I301& lhs, const I301& rhs)
{
  return (NearF(lhs.inner, rhs.inner));

} // end bool operator==(const I301&, const I301&)


bool dp::operator!=(const I301& lhs, const I301& rhs)
{
  return !(lhs == rhs);

} // end bool operator!=(const I301&, const I301&)


std::ostream& dp::operator<<(std::ostream& output, const I301& Pseudoscalar)
{
  output << Pseudoscalar.String();
  return output;
} // end std::ostream& operator<<(std::ostream&, const I301&)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Helper Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//! Zero vector in real and imaginary dimensions; error state reserved value
const dp::I301 nullPseudoscalar031_(Of);
const dp::I301& dp::nullPseudoscalar031 = nullPseudoscalar031_;
