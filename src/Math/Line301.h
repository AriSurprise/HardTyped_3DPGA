/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  Line301.h
Purpose: Projective 3+1D G(3,0,1), 2-vector coefficients: 6D restrictions
Details: Representing euclideana geometric lines in 3D using a affine,
  homogeneous 3+1D spatial coordinate set.  Dealing with the geometry for the
  objects constrained in 2 of those 4 degrees of freedom, we have nCr(2,4)
  i.e. 6 dimensions of representing that Line's 3D moment and direction.
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
#include <string>       // String building methods for text value output
// "./src/..."
#include "../Type/Errata.h" // Byte-size labeled primitive aliases for brevity
#include "../Util/Value.h"  // Basic inline value manuip. utility functions
// Interperatively restricted base class (wrapper)


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Forward References                             */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

union v3f;
union v6f;
class GP301;
class Point301;
class Plane301;
class I301;

namespace dp  //! Contents for use within DigiPen CS / MAT class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  class Line301 //! 6D G(3,0,1) bivector set; <moment, dir> plucker coords
  {
  public:

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Public Constants                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                             Constructors                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Constructor from coord values for 3D moment and direction coefficients
    */                                                                      /**/
    Line301(f4 e23_value = Of, f4 e31_value = Of, f4 e12_value = Of,
      f4 e01_value = Of, f4 e02_value = Of, f4 e03_value = Of);

    /**
    @brief
        Constructor from 3D moment and direction sets (plucker coordinates)
    */                                                                      /**/
    Line301(const v3f& moment, const v3f& dir);

    /**
    @brief
        Constructor from generic 6D coordinate set (abstracted: several reads)
    @details
        plucker coords => direct value coefficients
        point or vector pair => difference vector -> plucker coords
        [(p), <v>] or [<v>,(p)] => ray w/ dir. vector => conv. origin -> moment
    @param coords
      - <x,y,z,w,v,u> vector value of coordinates to be directed in usage
    @param plucker
      - <<moment>,<direction>> 3D vector pair of coords given as input format
    @param p1
      - <(x,y,z),*,*,*> given as point input format for the first 3 values
    @param p2
      - <*,*,*,(x,y,z)> given as point input format for the last 3 values
    */                                                                      /**/
    Line301(const v6f& coords, bool plucker, bool p1, bool p2);

    /**
    @brief
      
    */                                                                      /**/
    Line301(const Line301& source);

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /*
    @brief
        Getter for * coordinate of this affine / projective Line
    @return
      - reference to internal * member
    */                                                                      /**/
    // end const f4& Line301::E(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Copy constructor syntactic alternative as accessor method
    @return
      - memberwise copy of this Line301 instance
    */                                                                      /**/
    inline Line301 Copy(void) const
    {
      return Line301(*this);
    } // end Line301 Line301::Copy(void) const   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Get affine 3D Line's memberwise dot product with itself (squared mag.)
    @details
        Technical simplification from ((*this) ^ Complement()).Complement()
    @return
      - scalar measure of euclidean squared length
    */                                                                      /**/
    inline f4 DotSelf(void) const
    {
      return e23*e23 + e31*e31 + e12*e12; // e0#^2 := 0; need not be counted
    } // end f4 Line301::DotSelf(void) const     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Line's e23 blade coef. (aka moment's x-coord) reference
    @return
      - reference to this affine 3D Line's e23 blade coefficient value
    */                                                                      /**/
    inline const f4& E23(void) const
    {
      return e23;
    } // end const f4& Line301::E23(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Point's e31 blade coef. (aka moment's y-coord) reference
    @return
      - reference to this affine 3D Line's e31 blade coefficient value
    */                                                                      /**/
    inline const f4& E31(void) const
    {
      return e31;
    } // end const f4& Line301::E31(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Point's e12 blade coef. (aka moment's z-coord) reference
    @return
      - reference to this affine 3D Line's e12 blade coefficient value
    */                                                                      /**/
    inline const f4& E12(void) const
    {
      return e12;
    } // end const f4& Line301::E12(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Line's e01 blade coef. (aka direction's x-coord) reference
    @return
      - reference to this affine 3D Line's e01 blade coefficient value
    */                                                                      /**/
    inline const f4& E01(void) const
    {
      return e01;
    } // end const f4& Line301::E01(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Line's e02 blade coef. (aka direction's y-coord) reference
    @return
      - reference to this affine 3D Line's e02 blade coefficient value
    */                                                                      /**/
    inline const f4& E02(void) const
    {
      return e02;
    } // end const f4& Line301::E02(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Line's e03 blade coef. (aka direction's z-coord) reference
    @return
      - reference to this affine 3D Line's e03 blade coefficient value
    */                                                                      /**/
    inline const f4& E03(void) const
    {
      return e03;
    } // end const f4& Line301::E03(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the affine Line whose product is 1 when taken with this
    @return
      - G(3,0,1) affine Line such that Geometric Product with this == [1,<0>]
    */
    inline Line301 Inverse(void) const
    {
      return Reverse() * InvF(MagSq());
    } // end Point301 Point301::Inverse(void) const        #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get an object string: "{"e23":#,e31":#,e12":#,e01":#,e02":#,e03":#,}"
    @details
      - considered as an object blob with 1 6D 2-vector, named memberwise
    @return
      - text formatted to Json standards for later deserialization / output
    */
    std::string Json(void) const;


    /**
    @brief
        Calculate the squared area of this set of 
    @return
      - memberwise copy of this Line301 instance
    */                                                                       /**/
    inline f4 MagSq(void) const
    {
      return DotSelf();
    } // end f4 Line301::MagSq(void) const        #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the Line which has equal magnitude but opposite orientation
    @details
      <e23,e31,e12,e01,e02,e03> reverse := <e30,e20,e10,e21,e13,e32>
    @return
      - Trivector with memberwise negated value
    */                                                                      /**/
    inline Line301 Reverse(void) const
    {
      return Line301(-e23, -e31, -e12, -e01, -e02, -e03);
    } // end Line301 Line301::Reverse(void) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Line's e23 blade (aka moment x-coordinate) member coef.
    @param e23_value
      - value to set in the Point's e123 (aka homogeneous value) member coef.
    @return
      - reference to this affine 3D Line for method chaining
    */                                                                      /**/
    inline Line301& E23(f4 e23_value)
    {
      e23 = e23_value;
      return *this;
    } // end Line301& Line301::E123(f4) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Set the Line to the given Line member parameter set
    @param e23_value
      - bivector coefficient of the whole for oriented area in the e2^e3 plane
    @param e31_value
      - bivector coefficient of the whole for oriented area in the e3^e1 plane
    @param e12_value
      - bivector coefficient of the whole for oriented area in the e1^e2 plane
    @param e01_value
      - bivector coefficient of the whole for projected area in the e0^e1 plane
    @param e02_value
      - bivector coefficient of the whole for projected area in the e0^e2 plane
    @param e03_value
      - bivector coefficient of the whole for projected area in the e0^e3 plane
    @return
      - reference to this Line for method chaining
    */                                                                      /**/
    inline Line301& Set(f4 e23_value, f4 e31_value, f4 e12_value, f4 e01_value,
      f4 e02_value, f4 e03_value)
    {
      e23 = e23_value;
      e31 = e31_value;
      e12 = e12_value;
      e01 = e01_value;
      e02 = e02_value;
      e03 = e03_value;
      return *this;

    } // end + Line301& Line301::Set((f4),(f4),(f4),(f4),(f4),(f4))  #^^^^^^^^*/

    /**
    @brief
        Set the Line to a memberwise copy of the source Line parameter
    @param source
      - the Line to used in copying values
    @return
      - reference to this Line for method chaining
    */                                                                      /**/
    inline Line301& Set(const Line301& source)
    {
      e23 = (source.e23);
      e31 = (source.e31);
      e12 = (source.e12);
      e01 = (source.e01);
      e02 = (source.e02);
      e03 = (source.e03);
      return *this;

    } // end + Line301& Line301::Set(const Line301&)       #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Format for output as a vector notated string
    @details
      - adds padding for uniform spacing: JSON tightly packs elements
    @return
      - text set to be uniformly spaced for columned clarity / legibility
    */
    std::string String(void) const;

    /**
    @brief
        Get exterior (wedge) product of this Line with a Line: scaled line
    @param line
      - the line to have its product taken with this Line in external 
    @return
      - Join of G(3,0,1) geometric Line (2-vector) & another Line
    */
    I301 Wedge(const Line301& line);


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Private Members                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    // 6D constraints possible on 2 of 4D data (linear plucker coordinates)

    //! - Coefficient of the area along the e2^e3 oriented projective plane
    f4 e23;

    //! - Coefficient of the area along the e3^e1 oriented projective plane
    f4 e31;

    //! - Coefficient of the area along the e1^e2 oriented projective plane
    f4 e12;

    //! - Coefficient of the magnitude in the e0^e1 projective direction
    f4 e01;

    //! - Coefficient of the magnitude in the e0^e2 projective direction
    f4 e02;

    //! - Coefficient of the magnitude in the e0^e3 projective direction
    f4 e03;

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                         Operator Overloads                             */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      Create a negated copy of all affine 3D Line values: <-moment, -dir>
    @return
      - copy of the Line with negated memberwise values (oriented reverse)
    */
    inline Line301 operator-(void) const
    {
      return Reverse();
    } // end + Line301 Line301::operator-(void) const      #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Invert Line components to give the multiplicative conjugate: reciprocal
    @return
      - reference to this affine Line for method chaining
    */
    inline Line301 operator!(void) const
    {
      return Inverse();
    } // end + Line301& Line301::operator!(void) #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set the source affine Line member values into this one's fields
    @param source
      - the affine Line to have its values copied into this one
    @return
      - reference to this 3D affine Line for method chaining
    */
    inline Line301& operator=(const Line301& source)
    {
      return Set(source);
    } // end + Line301& Line301::operator=(const Line301&) #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get a member value from the given subscript
    @param channel
      - map to the letter / number for the desired channel of the object
    @return
      - copy of the contained dimension member value associated to the channel
    */
    inline f4 operator[](s2 channel) const
    {
      switch (channel)
      {
      case 3:           return e03;
      case 2:           return e02;
      case 1:           return e01;
      case 12: case 4:  return e12;
      case 31: case 5:  return e31;
      case 23: case 0:  return e23;
      case 30: case -3: return -e03;
      case 20: case -2: return -e02;
      case 10: case -1: return -e01;
      case 32: case -6: return -e23;
      case 13: case -5: return -e31;
      case 21: case -4: return -e12;
      }
      channel = ModC((s1)channel, 6);
      switch (channel)
      {
      case 5:   return e03;
      case 4:   return e02;
      case 3:   return e01;
      case 2:   return e12;
      case 1:   return e31;
      default:  return e23;
      }
    } // end + f4 Line301::operator[](s2) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get a member value reference from the given subscript
    @param channel
      - map to the letter / number for the desired channel of the object
    @return
      - reference to the contained field associated to the subscript number
    */
    inline f4& operator[](s2 channel)
    {
      switch (channel)
      {
      case 3: case 30: case -3: return e03;
      case 2: case 20: case -2: return e02;
      case 1: case 10: case -1: return e01;
      case 12: case 4: case 32: case -6:  return e12;
      case 31: case 5: case 13: case -5:  return e31;
      case 23: case 0: case 21: case -4:  return e23;
      }
      channel = ModC((s1)channel, 6);
      switch (channel)
      {
      case 5:   return e03;
      case 4:   return e02;
      case 3:   return e01;
      case 2:   return e12;
      case 1:   return e31;
      default:  return e23;
      }
    } // end + f4& Line301::operator[](s2)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Calculate the member-wise addition of 2 Lines
    @param other
      - Line to sum into a copy of this, member-wise
    @return
      - copy of member-wise sum of this and the other into a new one
    */                                                                      /**/
    inline Line301 operator+(const Line301& other) const
    {
      return Copy() += other;
    }// end + Line301 Line301::operator+(const Line301&) const #^^^^^^^^*/


    /**
    @brief
      Add an other Line's values member-wise into this Line's values
    @param other
      - source vector to have memberwise summation performed with this
    @return
      - reference to this 3D affine Line for method chaining
    */                                                                      /**/
    inline Line301& operator+=(const Line301& other)
    {
      e23 += other.e23;
      e31 += other.e31;
      e12 += other.e12;
      e01 += other.e01;
      e02 += other.e02;
      e03 += other.e03;
      return *this;
    } // end + Line301& Line301::operator+=(const Line301&) const ^^^^^^*/


    /**
    @brief
      Calculate the member-wise difference of 2 affine Lines
    @param other
      - source vector to have memberwise difference calculated with this (copy)
    @return
      - memberwise difference of this and the other, copied in a new one
    */                                                                      /**/
    inline Line301 operator-(const Line301& other) const
    {
      return Copy() -= other;
    }// end + Line301 Line301::operator-(const Line301&) const #^^^^^^^^*/


    /**
    @brief
      Subtract an other affine Line's values member-wise from this one's
    @param other
      - source vector to have negated memberwise summation performed with this
    @return
      - reference to this 3D affine Line for method chaining
    */                                                                      /**/
    inline Line301& operator-=(const Line301& other)
    {
      return *this += -other;
    } // end + Line301& Line301::operator+=(const Line301&) const ^^^^^^*/


    /**
    @brief
      Scalar affine Line product multiplies uniformly by the given scalar
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - resultant, member-wise scaled copy of this affine Line's values
    */                                                                      /**/
    inline Line301 operator*(f4 scalar) const
    {
      return Copy() *= scalar;
    } // end + Line301 Line301::operator*(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Scalar affine Line product sets all members uniformly scaled by the input
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - reference to this 3D affine Line for method chaining
    */                                                                      /**/
    inline Line301& operator*=(f4 scalar)
    {
      return Set(e23*scalar, e31 * scalar, e12 * scalar,
                 e01 * scalar, e02 * scalar, e03 * scalar);
    } // end + Line301& Line301::operator*=(f4) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get geometric product of this and another Line set into a new one
    @details
        (+x*e23 +y*e31 +z*e12 +u*e01 +v*e02 +n*e03)
      * (+a*e23 +b*e31 +c*e12 +r*e01 +s*e02 +t*e03)

      +xa*e2323 +xb*e2331 +xc*e2312 +xr*e2301 +xs*e2302 +xt*e2303
      +ya*e3123 +yb*e3131 +yc*e3112 +yr*e3101 +ys*e3102 +yt*e3103
      +za*e1223 +zb*e1231 +zc*e1212 +zr*e1201 +zs*e1202 +zt*e1203
      +ua*e0123 +ub*e0131 +uc*e0112 +ur*e0101 +us*e0102 +ut*e0103
      +va*e0223 +vb*e0231 +vc*e0212 +vr*e0201 +vs*e0202 +vt*e0203
      +na*e0323 +nb*e0331 +nc*e0312 +nr*e0301 +ns*e0302 +nt*e0303

      -xa       +xb*e21   +xc*e31   +xr*e0123 +xs*e03   +xt*e02
      +ya*e12   -yb       -yc*e23   +yr*e03   +ys*e0123 -yt*e01
      -za*e31   +zb*e23   -zc       -zr*e02   +zs*e01   +zt*e0123
      +ua*e0123 -ub*e03   +uc*e02   +0        +0        +0
      +va*e03   +vb*e0123 -vc*e01   +0        +0        +0
      -na*e02   +nb*e01   +nc*e0123 +0        +0        +0

       (-xa-yb-zc)
      +(zb-yc)*e23
      +(xc-za)*e31
      +(ya-xb)*e12
      +(zs+nb-yt-vc)*e01
      +(xt+uc-zr-na)*e02
      +(xs+yr+va-ub)*e03
      +(xr+ys+zt+ua+vb+nc)*e0123
    @param other
      - source affine Line to be multiplied with this affine Line
    @return
      - scaling & rotation of this by another affine Line
    */                                                                      /**/
    GP301 operator*(const Line301& other) const;


    /**
    @brief
        Divides all values uniformly by divisor, returning result
    @details
      - (real, imag)/d = (real, imag)*(1/d) = (real/d, imag/d)
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - resultant, member-wise scaled copy of this Line's values
    */                                                                      /**/
    inline Line301 operator/(f4 divisor) const
    {
      return Copy() *= InvF(divisor);
    } // end + Line301 Line301::operator/(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide all values uniformly by divisor, setting result
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - reference to this 3D affine Line for method chaining
    */                                                                      /**/
    inline Line301& operator/=(f4 divisor) { return (*this) *= InvF(divisor);
    } // end + Line301 Line301::operator/=(f4)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this affine Line by another, returning result
    @param other
      - affine Line by which this affine Line is to be divided
    @return
      - resultant, member-wise scaled copy of this Line's values
    */                                                                      /**/
    GP301 operator/(const Line301& other) const;


  }; // end Line301 union / struct / class type declaration        #^^^^^^^^*/



  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                       Helper Function Declarations                       */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  /**
  @brief
      Left hand scalar multiplication scales all members of rhs
  @param scalar
    - scalar amount by which to multiply all values of right-hand side
  @param rhs
    - right-hand side argument to be copied and scaled in all fields by scalar
  @return
    - copy of rhs's values, scaled by scalar in each field
  */                                                                        /**/
  inline Line301 operator*(f4 scalar, const Line301& rhs)
  { return Line301(rhs * scalar);
  } // end Line301 operator*(f4, const Line301&)       #^^^^^^^^^#^^^^^^^^*/


  /**
  @brief
      Confirm if 2 affine Lines are relatively equal memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for equality
  @param rhs
    - right hand side to be compared memberwise with left hand for equality
  @return
    - true only if all members are in close proximity of one another
  */
  bool operator==(const Line301& lhs, const Line301& rhs);


  /**
  @brief
      Confirm if 2 affine Lines are not equal in any values memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for inequality
  @param rhs
    - right hand side to be compared memberwise with left hand for inequality
  @return
    - true if any members are not in close proximity of one another
  */
  bool operator!=(const Line301& lhs, const Line301& rhs);


  /**
  @brief
      Output the default string version of the Line's data
  @param output
    - stream to receive the vector string and and carry contents for output
  @param line
    - number to have its values be converted to text based output
  @return
    - reference to the output stream object having the vector fed in
  */
  std::ostream& operator<<(std::ostream& output, const Line301& line);


  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                            Helper Constants                             */
  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  //! Zero valued 1D real scalar; error state reserved value
  extern const Line301& nullLine301;

} // end dp namespace