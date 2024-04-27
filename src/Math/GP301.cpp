/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  GP301.cpp
Purpose:  Dual Quaternion or G(3,0,1) even subalgebra / geometric product
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
#include "../Type/ang.h"        // Wrapper type for measures of arc spans
#include "../Util/ASCIIValue.h" // char range based [] operator manipulation
#include "../File/Log.h"        // Message management for errors, warnings, etc
#include "../Util/Value.h"      // Rroximity as equality Near@() functions
#include "GP030.h"              // Quaternion initializers & arithmetic 
#include "GP301.h"              // Class declaration header


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Private Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

static const u1 SUBSCRIPTS = 4u;    //! GP301 class is fixed at 4 subscripts

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::GP301::GP301(f4 rsw_value, f4 e23kx_value, f4 e31jy_value, f4 e12iz_value,
  f4 ek01v_value, f4 ej20u_value, f4 ei03t_value, f4 e0123p_value)
  : l(rsw_value),
  e23(e23kx_value), e31(e31jy_value), e12(e12iz_value),
  e01(ek01v_value), e02(ej20u_value), e03(ei03t_value),
  e0123(e0123p_value)
{
} // end + GP301::GP301((f4),(f4),(f4),(f4),(f4),(f4),(f4),(f4))     #^^^^^^^^*/


dp::GP301::GP301(f4 interior, v3f real, v3f dual, f4 pseudoscalar)
  : GP301(interior, real.x,real.y,real.z, dual.x,dual.y,dual.z, pseudoscalar)
{
} // end + GP301::GP301(f4, v3f, v3f, f4)        #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP301::GP301(const GP030& quat, const GP030& dual)
  : real(quat.real, quat.imag), dual(dual.imag, dual.real)
{
} // end + GP301::GP301(f4, v3f, v3f, f4)        #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP301::GP301(const dp::GP301& source)
  : GP301(source.l, source.e23, source.e31, source.e12,
        source.e01, source.e02, source.e03, source.e0123)
{
} // end + GP301::GP301(const GP301&)  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Accessors                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::GP301::Json(void) const
{
  const int f = 3;
  return "{\"r\":" + StrF(r, f)
    + ",\"e23\":" + StrF(e23, f)
    + ",\"e31\":" + StrF(e31, f)
    + ",\"e12\":" + StrF(e12, f)
    + ",\"e01\":" + StrF(e01, f)
    + ",\"e02\":" + StrF(e02, f)
    + ",\"e03\":" + StrF(e03, f)
    + ",\"e0123\":" + StrF(e0123, f) + "}";

} // end + std::string GP301::Json(void) const   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


std::string dp::GP301::String(void) const
{
  const int f = 3;
  return (IsNegF(r) ? "[" : "[ ") + StrF(r, f)
    + (IsNegF(e23) ? "," : ", ") + StrF(e23, f)
    + (IsNegF(e31) ? "," : ", ") + StrF(e31, f)
    + (IsNegF(e12) ? "," : ", ") + StrF(e12, f)
    + (IsNegF(e01) ? "," : ", ") + StrF(e01, f)
    + (IsNegF(e02) ? "," : ", ") + StrF(e02, f)
    + (IsNegF(e03) ? "," : ", ") + StrF(e03, f)
    + (IsNegF(e0123)? "," : ", ") + StrF(e0123, f) + "]";

} // end + std::string GP301::String(void) const #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Mutators                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::GP301& dp::GP301::Normalize(void)
{
  f4 mag = MagSq();
  if (Is1F(mag)) { return *this; }
  if (!Is0F(mag))
  {
    mag = SqrtF(mag);
    mag = InvF(mag);
    *this *= mag;
  }
  else // null vector can't be made a unit vector: default to null
  {
    Log::Info("GP301::Normalize - null vector input: default used");
    Set(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  }
  return *this;

} // end + GP301& GP301::Normalize(void)         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                            Operator Overloads                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

/*f4 dp::GP301::operator[](s2 channel) const
{
  // Validate channel is either a 0-15 number, or ascii char from '  ' to '~'
  // clamp wildly out of range values into lowest 2 unsigned values
  if (!isascii(channel) // 'not' 'msb not set' => not valid s2 range
    || (channel > 0xF // raw hex value input end range
      && channel < 0x20)) // ascii control sequence end range
  {
    Log::Diag(std::string("GP301::operator[] const - value out of range '")
      + char(channel) + "' read, ", false);
    channel &= 1; // if clamp to bool happens, checks in elses may be skipped
    Log::W(std::string("setting to '") + std::to_string(channel) + "'", true);
  }
  else if (IsUpper(channel)) { channel = tolower(channel); }
  else if (IsDigit(channel)) { channel = ToNumeral(channel) & 1; }
  switch (channel) // Lookup array index equivalent for return
  {
  case 'r': case 's': case 'w': case 0:
    return r;
  case 'i': case 'z': case 1:
    return e23;
  case 'j': case 'y': case 2:
    return e31;
  case 'k': case 'x': case 3:
    return e12;
  default:
    Log::Diag(std::string("GP301::operator[] const - unsupported char ")
      + char(channel) + " read: default head 'r' == 0 used");
    return l;
  }
} // end + f4 GP301::operator[](s2) const        #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Helper Functions                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::GP301 dp::operator*(f4 scalar, const dp::GP301& rhs)
{
  return rhs * scalar;
} // end GP301 operator*(f4, const GP301&)


bool dp::operator==(const GP301& lhs, const GP301& rhs)
{
  return (NearF(lhs.r, rhs.r)
    && NearF(lhs.e23, rhs.e23)
    && NearF(lhs.e31, rhs.e31)
    && NearF(lhs.e12, rhs.e12)
    && NearF(lhs.e01, rhs.e01)
    && NearF(lhs.e02, rhs.e02)
    && NearF(lhs.e03, rhs.e03)
    && NearF(lhs.e0123, rhs.e0123));

} // end bool operator==(const GP301&, const GP301&)


bool dp::operator!=(const GP301& lhs, const GP301& rhs)
{
  return !(lhs == rhs);

} // end bool operator!=(const GP301&, const GP301&)


std::ostream& dp::operator<<(std::ostream& output, const GP301& complex)
{
  output << complex.String();
  return output;
} // end std::ostream& operator<<(std::ostream&, const GP301&)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Helper Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//! Zero vector in real and imaginary dimensions; error state reserved value
const dp::GP301 nullGP031_(0.0f, 0.0f);
const dp::GP301& dp::nullGP031 = nullGP031_;
