/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  MV010.cpp
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
#include "../Math/m4f.h"        // Generating matrices from vector data
#include "../Util/Value.h"      // Rroximity as equality Near@() functions
#include "MV010.h"               // Class declaration header


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                              Private Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

static const u1 SUBSCRIPTS = 2u;    //! MV010 class is fixed at 2 subscripts
static const f4 PROXIMITY = 0.001f; //! Reasonable near offset margin

/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Constructors                                 */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

// Creates a 2 dimensional complex number (<real, imaginary>, default <1,0>)  */
dp::MV010::MV010(f4 xu_value, f4 yv_value) : x(xu_value), y(yv_value)
{ } // end MV010::MV010(f4, f4)

// Creates a complex <real, imaginary> cartesian number from polar inputs     */
dp::MV010::MV010(ang rotation, f4 magnitude)
{
  Angle(rotation, magnitude);
} // end MV010::MV010(ang, f4)

// Creates a copy of a complex number from another source complex value       */
dp::MV010::MV010(const dp::MV010& source) : MV010(source.x, source.y)
{ } // end MV010::MV010(const MV010&)

// Creates a MV010 from a MV010 value reference resultant from a function       */
dp::MV010::MV010(dp::MV010&& result) noexcept
{
  *this = std::move(result);
} // end MV010::MV010(MV010&&)



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Public Methods                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

// Get angle (arctangent), of current cartesian coordinates of this vector    */
dp::ang dp::MV010::Angle(void) const
{
  return ang(static_cast<f4>(atan2(y, x)), arc::radians, winding::ccw);

} // end v4f Angle(void) const


// Set cartesian <r,i> coordinates in vector from polar coordinate inputs     */
dp::MV010& dp::MV010::Angle(dp::ang angle_setting, f4 magnitude)
{
  X(static_cast<f4>(cos(angle_setting.r())) * magnitude);
  Y(static_cast<f4>(sin(angle_setting.r())) * magnitude);
  return *this;

} // end MV010& MV010::Angle(ang, f4)

// Complex number with negated imag value: (a+bi)(a-bi)=a^2+b^2+0i; i cancels */
dp::MV010 dp::MV010::Conjugate(void) const
{
  return MV010(real, -imag);

} // end v4f Conjugate(void) const


// Get the complex number's imaginary component value                         */
const f4& dp::MV010::I(void) const
{
  return y;

} // end const f4& MV010::I(void) const


// Set the complex number's imaginary component value                         */
dp::MV010& dp::MV010::I(f4 ivy_value)
{
  y = ivy_value; return *this;

} // end MV010& MV010::I(f4)


// Get the complex number's imaginary component value                         */
const f4& dp::MV010::Imag(void) const
{
  return y;

} // end const f4& MV010::Imag(void) const


// Set the complex number's imaginary component value                         */
dp::MV010& dp::MV010::Imag(f4 ivy_value)
{
  y = ivy_value; return *this;

} // end MV010& MV010::Imag(f4)


// Get the complex number's imaginary component value                         */
const f4& dp::MV010::Imaginary(void) const
{
  return y;

} // end const f4& MV010::Imaginary(void) const


// Set the complex number's imaginary component value                         */
dp::MV010& dp::MV010::Imaginary(f4 ivy_value)
{
  y = ivy_value; return *this;

} // end MV010& MV010::Imaginary(f4)


// Format a MV010 for being output as a packed vector notated string           */
std::string dp::MV010::JSON(void) const
{
  return "(" + std::to_string(x) + "," + std::to_string(y) + "*i)";

} // end std::string MV010::json(void) const


// Get the MV010 diagonal length / displacement magnitude: sqrt(x^2 + y^2)     */
f4 dp::MV010::Length(void) const
{
  return static_cast<f4>(sqrt(LengthSquared()));

} // end f4 MV010::Length(void) const


// Get squared complex displacement / diagonal length: real^2 + imag^2        */
f4 dp::MV010::LengthSquared(void) const
{
  return (real*real+imag*imag);

} // end f4 MV010::LengthSquared(void) const


// Calculate the elementwise product of (other * this) in a new v3f           */
dp::MV010 dp::MV010::Multiply(const MV010& other) const
{
  MV010 product(x * other.x, y * other.y);
  return product;

} // end v3f Multiply(const v3f&) const


// Set the elementwise product of (other * this) into this vector             */
dp::MV010& dp::MV010::MultiplyWith(const MV010& other)
{
  Set((x * other.x), (y * other.y));
  return *this;

} // end v3f& MultiplyWith(const v3f&)


// This MV010 will be divided by its length and converted to a unit vector     */
dp::MV010& dp::MV010::Normalize(void)
{
  f4 len = Length();
  if (!NearF(len, 0.0f))
  {
    f4 rMag = 1.0f / len; // Reciprocal vector magnitude
    *this *= rMag;
  }
  else // null vector can't be made a unit vector: default a value of x
  {
    Log::Info("MV010::Normalize - null vector input: default used");
    X(1.0f).Y(0.0f);
  }
  return *this;

} // end MV010& MV010::Normalize(void)


// Get the complex number's real component value                              */
const f4& dp::MV010::R(void) const
{
  return x;

} // end const f4& MV010::R(void) const


// Set the complex number's real component value                              */
dp::MV010& dp::MV010::R(f4 rux_value)
{
  x = rux_value; return *this;

} // end MV010& MV010::R(f4)


// Get the complex number's real component value                              */
const f4& dp::MV010::Real(void) const
{
  return x;

} // end const f4& MV010::Real(void) const


// Set the complex number's real component value                              */
dp::MV010& dp::MV010::Real(f4 rux_value)
{
  x = rux_value; return *this;

} // end MV010& MV010::Real(f4)


// Set the MV010 to <x|u, y|v input values                                     */
dp::MV010& dp::MV010::Set(f4 xu_value, f4 yv_value)
{
  X(xu_value).Y(yv_value); return*this;

} // end MV010& MV010::Set(f4, f4)

// Set the complex cartesian equivalent value for the given polar components  */
dp::MV010& dp::MV010::Set(ang angle, f4 magnitude)
{
  Angle(angle, magnitude);
  return *this;

} // end MV010& MV010::Set(ang, f4)

// Set the MV010 values to <source.x, source.y> values                         */
dp::MV010& dp::MV010::Set(const MV010& source)
{
  X(source.x).Y(source.y);
  return *this;

} // end MV010& MV010::Set(const MV010&)

// Set the MV010 to use <result.x, result.y>                                    */
dp::MV010& dp::MV010::Set(MV010&& result) noexcept
{
  *this = std::move(result);
  return *this;

} // end MV010& MV010::Set(MV010&&) noexcept


// Format a v4f for being output as a vector notated string                   */
std::string dp::MV010::String(void) const
{
  std::string vecFormat;
  vecFormat = "[";
  if (x >= 0.0f) { vecFormat += " "; } // (add padding char for non-negatives)
  vecFormat += std::to_string(r) + ", ";
  if (y >= 0.0f) { vecFormat += " "; } // (add padding char for non-negatives)
  vecFormat += std::to_string(i) + "*i ]";
  return vecFormat;

} // end std::string MV010::String(void) const


// Get the complex number's real coordinate value under 2D texture labeling   */
const f4& dp::MV010::U(void) const
{
  return x;

} // end const f4& MV010::U(void) const


// Set the complex number's real coordinate value under 2D texture labeling   */
dp::MV010& dp::MV010::U(f4 xu_value)
{
  x = xu_value; return *this;
} // end MV010& MV010::U(f4)


// Value copy will be divided by its length and converted to a unit vector    */
dp::MV010 dp::MV010::UnitVec(void) const
{
  MV010 unit = *this; // Normalized copy of this
  unit.Normalize();
  return unit;

} // end MV010 MV010::UnitVec(void) const


// Get the complex number's imaginary coord value under 2D texture labeling   */
const f4& dp::MV010::V(void) const
{
  return y;

} // end const f4& MV010::V(void) const


// Set the complex number's imaginary coord value under 2D texture labeling   */
dp::MV010& dp::MV010::V(f4 ivy_value)
{
  y = ivy_value;
  return *this;

} // end MV010&  MV010::V(f4)


// Get the complex number's real coordinate value under 2D cartesian labels   */
const f4& dp::MV010::X(void) const
{
  return x;

} // end const f4& MV010::X(void) const


// Set the complex number's real coordinate value under 2D cartesian labels   */
dp::MV010& dp::MV010::X(f4 rux_value)
{
  x = rux_value;
  return *this;

} // end MV010& MV010::X(f4)


// Get the complex number's imaginary coord value under 2D cartesian labels   */
const f4& dp::MV010::Y(void) const
{
  return y;

} // end const f4& MV010::Y(void) const


// Set the complex number's imaginary coord value under 2D cartesian labels   */
dp::MV010& dp::MV010::Y(f4 yv_value)
{
  y = yv_value;
  return *this;

} // end MV010&  MV010::Y(f4)



/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                            Operator Overloads                              */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

// Creates a negated copy with relevant complex coordinate values             */
dp::MV010 dp::MV010::operator-(void) const
{
  return MV010(-real, -imag);
} // end MV010 MV010::operator-(void) const


// Sets the source MV010 member values into this MV010 value fields               */
dp::MV010& dp::MV010::operator=(const MV010& source)
{
  this->Set(source); return *this;
} // end MV010& MV010::operator=(const MV010&)


// Surrogate a complex value reference returned from a function for this      */
dp::MV010& dp::MV010::operator=(MV010&& result) noexcept
{
  real = std::move(result.real);
  imag = std::move(result.imag);
  return *this;
} // end MV010& MV010::operator=(const MV010&)


// Negates complex imaginary component to give the complex conjugate          */
dp::MV010 dp::MV010::operator!(void) const
{
  return this->Conjugate();
} // end MV010& MV010::operator!(void)


// Get a value from ['r'] or ['i'] channels (or equivalent)                   */
f4 dp::MV010::operator[](s2 channel) const
{
  // Validate channel is either a 0-15 number, or ascii char from '  ' to '~'
  // clamp wildly out of range values into lowest 2 unsigned values
  if (!isascii((s1)channel) /* 'not' 'msb not set' => not valid s2 range */
    || (channel > 0xF /* raw hex value input end range */
      && channel < 0x20  /* ascii control sequence end range */))
  {
    Log::Diag(std::string("MV010::operator[] const - value out of range '")
      + char(channel) + "' read, ", false);
    channel &= 1; // if clamp to bool happens, checks in elses may be skipped
    Log::W(std::string("setting to '") + std::to_string(channel) + "'", true);
  }
  else if (IsUpper((s1)channel)) { channel = tolower((s1)channel); }
  else if (IsDigit((s1)channel)) { channel = ToNumeral((s1)channel) & 1; }
  switch (channel) // Lookup array index equivalent for return
  {
  case 'r': case 'u': case 'x': case 0:
    return real;
  case 'i': case 'v': case 'y': case 1:
    return imag;
  default:
    Log::Diag(std::string("MV010::operator[] const - unsupported char ")
      + char(channel) + " read: default head 'r' == 0 used");
    return real;
  }
} // end f4 MV010::operator[](s2) const


// Get a value from ['r'] or ['i'] channels (or equivalent)                   */
f4& dp::MV010::operator[](s2 channel)
{
  // Validate channel is either a 0-15 number, or ascii char from '  ' to '~'
  // clamp wildly out of range values into lowest 2 unsigned values
  if (!isascii((s1)channel) /* 'not' 'msb not set' => not valid s2 range */
    || (channel > 0xF /* raw hex value input end range */
      && channel < 0x20  /* ascii control sequence end range */))
  {
    Log::Diag(std::string("MV010::operator[] const - value out of range '")
      + char(channel) + "' read, ", false);
    channel &= 1; // if clamp to bool happens, checks in elses may be skipped
    Log::W(std::string("setting to '") + std::to_string(channel) + "'", true);
  }
  else if (IsUpper((s1)channel)) { channel = tolower((s1)channel); }
  else if (IsDigit((s1)channel)) { channel = ToNumeral((s1)channel) & 1; }
  switch (channel) // Lookup array index equivalent for return
  {
  case 'r': case 'u': case 'x': case 0:
    return real;
  case 'i': case 'v': case 'y': case 1:
    return imag;
  default:
    Log::Diag(std::string("MV010::operator[] - unsupported char ")
      + char(channel) + " read: default head 'r' == 0 used");
    return real;
  }
} // end f4& MV010::operator[](s2)


// Calculate the member-wise addition of 2 MV010's and return the result        */
dp::MV010 dp::MV010::operator+(const MV010& other) const
{
  return MV010((x + other.x), (y + other.y));

} // end MV010 MV010::operator+(const MV010&) const


// Add an other MV010's values memberwise into this MV010's values                */
dp::MV010& dp::MV010::operator+=(const MV010& other)
{
  Set((this->real + other.real), (this->imag + other.imag));
  return *this;

} // end MV010& MV010::operator+=(const MV010&)


// Calculate the member-wise difference of 2 MV010's and return the result      */
dp::MV010 dp::MV010::operator-(const MV010& other) const
{
  return MV010((x - other.x), (y - other.y));

} // end MV010 MV010::operator-(const MV010&) const


// Add an other MV010's values memberwise into this MV010's values                */
dp::MV010& dp::MV010::operator-=(const MV010& other)
{
  Set((x - other.x), (y - other.y));
  return *this;

} // end MV010& MV010::operator-=(const MV010&)


// Scalar product multiplies each field uniformly by a scalar constant        */
dp::MV010 dp::MV010::operator*(f4 scalar) const
{
  return MV010((scalar * x), (scalar * y));
} // end MV010 MV010::operator*(f4) const


// Scalar product sets all members to grow uniformly by a scalar constant     */
dp::MV010& dp::MV010::operator*=(f4 scalar)
{
  Set((scalar * x), (scalar * y));
  return *this;
} // end MV010& MV010::operator*=(f4)


// Get product of this and another complex number (resolving i = sqrt(-1))    */
dp::MV010 dp::MV010::operator*(const MV010& other) const
{
  // resolve imaginary square into -real, scale linears by reciprocal reals
  return MV010( (r*other.r-i*other.i), (r*other.i+other.r*i));

} // end MV010 MV010::operator*(const MV010&) const


// Set product of this and another complex number (resolving i = sqrt(-1))    */
dp::MV010& dp::MV010::operator*=(const MV010& other)
{
  // resolve imaginary square into -real, scale linears by reciprocal reals
  Set((r * other.r - i * other.i), (r * other.i + other.r * i));
  return *this;

} // end MV010& MV010::operator*=(const MV010&)


// Perform uniform division by divisor, returning the result                  */
dp::MV010 dp::MV010::operator/(f4 divisor) const
{
  // Get reciprocal of input: multiplication is preferable computationally
  f4 scalar = (1.0f / divisor); // Inverse divisor: a scalar value
  return ((*this) * scalar);
} // end MV010 MV010::operator/(f4) const


// Divides all members uniformly by divisor, setting the result               */
dp::MV010& dp::MV010::operator/=(f4 divisor)
{
  // Get reciprocal of input: multiplication is preferable computationally
  f4 scalar = (1.0f / divisor); // inverse divisor: a scalar value
  return ((*this) *= scalar);
} // end MV010 MV010::operator/=(f4)


// Perform uniform division by divisor, returning the result                  */
dp::MV010 dp::MV010::operator/(const MV010& other) const
{
  // Get reciprocal of input: multiplication is preferable computationally
  f4 scalar = (1.0f / other.LengthSquared()); // Inverse divisor: scalar value
  return (((*this) * !other) * scalar);
} // end MV010 MV010::operator/(f4) const


// Divides all members uniformly by divisor, setting the result               */
dp::MV010& dp::MV010::operator/=(const MV010& other)
{
  // Get reciprocal of input: multiplication is preferable computationally
  f4 scalar = (1.0f / other.LengthSquared()); // inverse divisor: scalar value
  // length squared (||c||^2) = c*(!c), the conjugate, thus multiplying by 1:
  // a/b = (a/b)(!b/!b) = (a*!b)/(b*!b) = (a*!b)/||b||^2, where ||b||^2 is real
  return (((*this) * !other) *= scalar);
} // end MV010 MV010::operator/=(f4)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Helper Functions                               */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


// Left hand scalar multiplication scales only dimensional members of rhs     */
dp::MV010 dp::operator*(f4 scalar, const dp::MV010& rhs)
{
  MV010 scaled((scalar * rhs.x), (scalar * rhs.y));
  return scaled;
} // end MV010 operator*(f4, const MV010&)


// Confirm if 2 complex numbers are relatively equal in real and imag values  */
bool dp::operator==(const MV010& lhs, const MV010& rhs)
{
  return (NearF(lhs.x, rhs.x)
    && NearF(lhs.y, rhs.y));

} // end bool operator==(const MV010&, const MV010&)


// Confirm if 2 complex numbers are not equal in either real or imag values   */
bool dp::operator!=(const MV010& lhs, const MV010& rhs)
{
  return(!NearF(lhs.x, rhs.x)
    || !NearF(lhs.y, rhs.y));

} // end bool operator!=(const MV010&, const MV010&)


// Output the string version of each of the complex elements data             */
std::ostream& dp::operator<<(std::ostream& output, const MV010& complex)
{
  output << complex.String();
  return output;
} // end std::ostream& operator<<(std::ostream&, const MV010&)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                               Helper Consts                                */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

//! Zero vector in real and imaginary dimensions; error state reserved value
const dp::MV010 nullMV010_(0.0f, 0.0f);
const dp::MV010& dp::nullMV010 = nullMV010_;
