/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  Plane301.cpp
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
#include "../Math/GP301.h"     // Plane301 pair Geometric product (meet+join)
#include "Plane301.h"          // Class declaration header


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Private Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::Plane301::Plane301(f4 e0_coefficient, f4 e1_coefficient,
  f4 e2_coefficient, f4 e3_coefficient)
  : e0(e0_coefficient),
  e1(e1_coefficient), e2(e2_coefficient), e3(e3_coefficient)
{
} // end + Plane301::Plane301((f4))    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::Plane301::Plane301(const dp::Plane301& source)
  : Plane301(source.e0, source.e1, source.e2, source.e3)
{
} // end + Plane301::Plane301(const Plane301&)   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Accessors                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::Plane301::Json(void) const
{
  const int f = 3;
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += "\"e0\":" + StrF(e0, f) + ",";
  vecFormat += "\"e1\":" + StrF(e1, f) + ",";
  vecFormat += "\"e2\":" + StrF(e2, f) + ",";
  vecFormat += "\"e3\":" + StrF(e3, f) + "]";
  return vecFormat;

} // end + std::string Plane301::Json(void) const         #^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Mutators                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::Plane301::String(void) const
{
  const int f = 3;
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += (Of <= e0 ? " " : "") + StrF(e0, f) + ", ";
  vecFormat += (Of <= e1 ? " " : "") + StrF(e1, f) + ", ";
  vecFormat += (Of <= e2 ? " " : "") + StrF(e2, f) + ", ";
  vecFormat += (Of <= e3 ? " " : "") + StrF(e3, f) + "]";
  return vecFormat;

} // end + std::string Plane301::String(void) const #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                            Operator Overloads                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

f4 dp::Plane301::operator[](s2 channel) const
{
  switch (channel)
  {
  case 1: case -3:  return e1;
  case 2: case -2:  return e2;
  case 3: case -1:  return e3;
  case 0: case -4:  return e0;
  }
  channel = ModC((s1)channel, 4);
  switch (channel)
  {
  case 1:   return e1;
  case 2:   return e2;
  case 3:   return e3;
  default:  return e0;
  }
} // end + f4 Plane301::operator[](s2) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


f4& dp::Plane301::operator[](s2 channel)
{
  switch (channel)
  {
  case 1: case -3:  return e1;
  case 2: case -2:  return e2;
  case 3: case -1:  return e3;
  case 0: case -4:  return e0;
  }
  channel = ModC((s1)channel, 4);
  switch (channel)
  {
  case 1:   return e1;
  case 2:   return e2;
  case 3:   return e3;
  default:  return e0;
  }
} // end + f4& Plane301::operator[](s2)         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::GP301 dp::Plane301::operator*(const Plane301& other) const
{
  //    p(e0 + e1 + e2 + e3) * q(e0 + e1 + e2 + e3)
  // =>  (x0 + y1 + z2 + w3) *  (s0 + t1 + u2 + v3)
  // =>  xs00 + xt01 + xu02 + xv03    =>       0  + xt01 + xu02 + xv03
  //   + ys10 + yt11 + yu12 + yv13         - ys01 + yt   + yu12 - yv31
  //   + zs20 + zt21 + zu22 + zv23         - zs02 - zt12 + zu   + zv23
  //   + ws30 + wt31 + wu32 + wv33         - ws03 + wt31 - wu23 + wv
  // =>  yt + zu + wv   =>    yt + zu + wv
  //   + xt01 - ys01        (xt - ys) * e01
  //   + xu02 - zs02        (xu - zs) * e02
  //   + xv03 - ws03        (xv - ws) * e03
  //   + zv23 - wu23        (zv - wu) * e23
  //   + wt31 - yv31        (wt - yv) * e31
  //   + yu12 - zt12        (yu - zt) * e12
  // =>  p[1]*q[1] + p[2]*q[2] + p[3]*q[3]
  //          (p[0]*q[1] - p[1]*q[0])
  //          (p[0]*q[2] - p[2]*q[0])
  //          (p[0]*q[3] - p[3]*q[0])
  //          (p[2]*q[3] - p[3]*q[2])
  //          (p[3]*q[1] - p[1]*q[3])
  //          (p[1]*q[2] - p[2]*q[1])
  return GP301
    (e1*other.e1 + e2*other.e2 + e3*other.e3,
            e0*other.e1 - e1*other.e0,
            e0*other.e2 - e2*other.e0,
            e0*other.e3 - e3*other.e0,
            e2*other.e3 - e3*other.e2,
            e3*other.e1 - e1*other.e3,
            e1*other.e2 - e2*other.e1,
                        Of);

} // end + GP301 Plane301::operator*=(const Plane301&)     #^^^^^^^^^#^^^^^^^^*/

dp::GP301 dp::Plane301::operator/(const Plane301& other) const
{
  return (*this) * !other;
}


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Helper Functions                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


bool dp::operator==(const Plane301& lhs, const Plane301& rhs)
{
  return NearF(lhs.e0, rhs.e0)
    && NearF(lhs.e1, rhs.e1)
    && NearF(lhs.e2, rhs.e2)
    && NearF(lhs.e3, rhs.e3);

} // end bool operator==(const Plane301&, const Plane301&)


bool dp::operator!=(const Plane301& lhs, const Plane301& rhs)
{
  return !(lhs == rhs);

} // end bool operator!=(const Plane301&, const Plane301&)


std::ostream& dp::operator<<(std::ostream& output, const Plane301& plane)
{
  output << plane.String();
  return output;
} // end std::ostream& operator<<(std::ostream&, const Plane301&)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Helper Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//! Zero vector in real and imaginary dimensions; error state reserved value
const dp::Plane301 nullPlane031_(Of);
const dp::Plane301& dp::nullPlane031 = nullPlane031_;
