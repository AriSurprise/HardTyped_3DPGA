/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  GP030.cpp
Purpose:  Real and imaginary, 4 byte float point coordinate pair container
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
#include "GP030.h"              // Class declaration header


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Private Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//static const u1 SUBSCRIPTS = 4u;    //! GP030 class is fixed at 4 subscripts

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::GP030::GP030(f4 rsw_value, f4 kx_value, f4 jy_value, f4 iz_value)
  : i(iz_value), j(jy_value), k(kx_value), s(rsw_value) {
} // end + GP030::GP030((f4),(f4),(f4),(f4))     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP030::GP030(f4 real, v3f imaginary)
  : real(real), imag(imaginary){
} // end + GP030::GP030(f4, v3f)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP030::GP030(ang angle, ang azimuth, f4 magnitude)
  : s(Of), i(magnitude*SinF(angle)*CosF(azimuth)),
           j(magnitude*SinF(angle)*SinF(azimuth)), k(magnitude*CosF(angle)) {
} // end + GP030::GP030(ang,(ang),(f4))          #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP030::GP030(ang yaw, ang pitch, ang roll, f4 magnitude)
{
  Angle(yaw, pitch, roll, magnitude);
} // end + GP030::GP030(ang, ang, ang,(f4))      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP030::GP030(const dp::GP030& source) : GP030(source.x, source.y)
{ } // end + GP030::GP030(const GP030&) #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP030::GP030(dp::GP030&& result) noexcept { *this = std::move(result);
} // end + GP030::GP030(GP030&&)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Accessors                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

std::string dp::GP030::Json(void) const
{
  const int f = 3;
  std::string a = StrF(e12, f);
  std::string b = StrF(e31, f);
  std::string c = StrF(e23, f);
  std::string d = StrF(r, f);
  return "{\"inner\":" + d + ",\"outer\":{" + a + "," + b + "," + c + "}}";

} // end + std::string GP030::Json(void) const   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Public Mutators                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

dp::GP030& dp::GP030::Angle(ang angle, ang azimuth, f4 magnitude)
{
  r = Of;
  f4 sa = SinF(angle);
  i = magnitude * sa * CosF(azimuth);
  j = magnitude * sa * SinF(azimuth);
  k = magnitude * CosF(angle);
  return *this;
} // end + GP030& GP030::Angle(ang,(ang),(f4))   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP030& dp::GP030::Angle(ang yaw, ang pitch, ang roll, f4 magnitude)
{
  yaw *= AHALF;
  pitch *= AHALF;
  roll *= AHALF;
  f4 cy = CosF(yaw), sy = SinF(yaw),
     cp = CosF(pitch), sp = SinF(pitch),
     cr = CosF(roll), sr = SinF(roll);
  return (R(cr * cp * cy + sr * sp * sy).
          I(sr * cp * cy - cr * sp * sy).
          J(sr * cp * sy + cr * sp * cy).
          K(cr * cp * sy - sr * sp * cy)) *= magnitude;

} // end + GP030& dp::GP030::Angle(ang, ang, ang,(f4))     #^^^^^^^^^#^^^^^^^^*/


dp::GP030& dp::GP030::Normalize(void)
{
  f4 mag = LengthSquared();
  if (!Is0F(mag))
  {
    mag = SqrtF(mag);
    mag = InvF(mag);
    *this *= mag;
  }
  else // null vector can't be made a unit vector: default to null
  {
    Log::Info("GP030::Normalize - null vector input: default used");
    R(1.0f).I(0.0f).J(0.0f).K(0.0f);
  }
  return *this;

} // end + GP030& GP030::Normalize(void)         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


dp::GP030& dp::GP030::Set(ang angle, ang azimuth, f4 magnitude)
{
  return Angle(angle, azimuth, magnitude);

} // end + GP030& GP030::Set(ang, ang, f4)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


std::string dp::GP030::String(void) const
{
  std::string vecFormat;
  vecFormat = "[";
  vecFormat += (Of <= s? " " : "") + std::to_string(s) + ",<";
  vecFormat += (Of <= i? " " : "") + std::to_string(i) + ", ";
  vecFormat += (Of <= j? " " : "") + std::to_string(j) + ", ";
  vecFormat += (Of <= k? " " : "") + std::to_string(k) + ">]";
  return vecFormat;

} // end + std::string GP030::String(void) const #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                            Operator Overloads                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

f4 dp::GP030::operator[](s2 channel) const
{
  // Validate channel is either a 0-15 number, or ascii char from '  ' to '~'
  // clamp wildly out of range values into lowest 2 unsigned values
  if (!isascii((s1)channel) /* 'not' 'msb not set' => not valid s2 range */
    || (channel > 0xF /* raw hex value input end range */
      && channel < 0x20  /* ascii control sequence end range */))
  {
    Log::Diag(std::string("GP030::operator[] const - value out of range '")
      + char(channel) + "' read, ", false);
    channel &= 1; // if clamp to bool happens, checks in elses may be skipped
    Log::W(std::string("setting to '") + std::to_string(channel) + "'", true);
  }
  else if (IsUpper((s1)channel)) { channel = tolower((s1)channel); }
  else if (IsDigit((s1)channel)) { channel = ToNumeral((s1)channel) & 1; }
  switch (channel) // Lookup array index equivalent for return
  {
  case 'r': case 's': case 'w': case 0:
    return r;
  case 'i': case 'z': case 1:
    return i;
  case 'j': case 'y': case 2:
    return j;
  case 'k': case 'x': case 3:
    return k;
  default:
    Log::Diag(std::string("GP030::operator[] const - unsupported char ")
      + char(channel) + " read: default head 'r' == 0 used");
    return real;
  }
} // end + f4 GP030::operator[](s2) const        #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


f4& dp::GP030::operator[](s2 channel)
{
  // Validate channel is either a 0-15 number, or ascii char from '  ' to '~'
  // clamp wildly out of range values into lowest 2 unsigned values
  if (!isascii((s1)channel) /* 'not' 'msb not set' => not valid s2 range */
    || (channel > 0xF /* raw hex value input end range */
      && channel < 0x20  /* ascii control sequence end range */))
  {
    Log::Diag(std::string("GP030::operator[] const - value out of range '")
      + char(channel) + "' read, ", false);
    channel &= 1; // if clamp to bool happens, checks in elses may be skipped
    Log::W(std::string("setting to '") + std::to_string(channel) + "'", true);
  }
  else if (IsUpper((s1)channel)) { channel = tolower((s1)channel); }
  else if (IsDigit((s1)channel)) { channel = ToNumeral((s1)channel) & 1; }
  switch (channel) // Lookup array index equivalent for return
  {
  case 'r': case 's': case 'w': case 0:
    return r;
  case 'i': case 'z': case 1:
    return i;
  case 'j': case 'y': case 2:
    return j;
  case 'k': case 'x': case 3:
    return k;
  default:
    Log::Diag(std::string("GP030::operator[] - unsupported char ")
      + char(channel) + " read: default head 'r' == 0 used");
    return real;
  }
} // end + f4& GP030::operator[](s2)   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Helper Functions                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


bool dp::operator==(const GP030& lhs, const GP030& rhs)
{
  return (NearF(lhs.x, rhs.x)
    && NearF(lhs.y, rhs.y));

} // end bool operator==(const GP030&, const GP030&)


bool dp::operator!=(const GP030& lhs, const GP030& rhs)
{
  return(!NearF(lhs.x, rhs.x)
    || !NearF(lhs.y, rhs.y));

} // end bool operator!=(const GP030&, const GP030&)


std::ostream& dp::operator<<(std::ostream& output, const GP030& complex)
{
  output << complex.String();
  return output;
} // end std::ostream& operator<<(std::ostream&, const GP030&)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Helper Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//! Zero vector in real and imaginary dimensions; error state reserved value
const dp::GP030 nullGP030_(0.0f, 0.0f);
const dp::GP030& dp::nullGP030 = nullGP030_;
