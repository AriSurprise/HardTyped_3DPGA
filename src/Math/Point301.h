/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  Point301.h
Purpose: Projective 3+1D G(3,0,1), 3-vector coefficients: 4D restrictions
Details: Representing euclideana geometric points in 3D using a affine,
  homogeneous 3+1D spatial coordinate set.  Dealing with the geometry for the
  objects constrained in 3 of those 4 degrees of freedom, we have nCr(3,4)
  i.e. 4 dimensions of representing that Point's planar intersection coords,
  i.e. 4 magnitudes of 3 projective plane reflection intersections.
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

class I301;
class Plane301;
class Line301;

namespace dp  //! Contents for use within DigiPen CS / MAT class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  class Point301 //! Projective point reflection (rh trivectors of G(3,0,1)
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
      
    */                                                                      /**/
    Point301(f4 e123_value = Of, f4 e023_value = Of, f4 e031_value = Of,
      f4 e012_value = Of);

    /**
    @brief
      
    */                                                                      /**/
    Point301(const Point301& source);

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        
    @return
      - memberwise copy of this Point301 instance
    */                                                                       /**/
    inline Point301 Copy(void) const { return Point301(*this); }
    // end Point301 Point301::Copy(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Get affine 3D Point's memberwise dot product with itself (squared mag.)
    @return
      - scalar measure of euclidean squared length
    */                                                                      /**/
    inline f4 DotSelf(void) const
    {
      return e123 * e123; // e0##^2 := 0; need not be counted
    } // end f4 Point301::DotSelf(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the Plane301 which maps onto this Point301's dual (memberwise copy)
    @details
        Out of scope for here, but dual carries potential for dual meanings too:
        <M>[d-3] could be := <M>[1], or it's own [d-3] grade object, scaling in
        higher / lower dimensions to preserve / extend a component blades' grade
        i.e. this could continue to describe a point in higher dimensions, or,
        promoting by 1 dimension could become a line along with the added dimens
        but to have both behaviors, separate objects are required for duals
    @return
      - the <M>[4-3] part, or 1-vector equivalent, mapped with this 3-vector
    */                                                                       /**/
    Plane301 Dual(void) const;


    /**
    @brief
        Get affine Point's e123 blade coef. (ie homogeneous; e0 dual) reference
    @return
      - reference to this affine 3D Point's e123 blade eocefficient value
    */                                                                      /**/
    inline const f4& E123(void) const
    {
      return e123;
    } // end const f4& Point301::E123(void) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Point's e023 blade coef. (ie x-coord; e1 dual) reference
    @return
      - reference to this affine 3D Point's e023 blade coefficient value
    */                                                                      /**/
    inline const f4& E023(void) const
    {
      return e023;
    } // end const f4& Point301::E023(void) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Point's e031 blade coef. (ie y-coord; e2 dual) reference
    @return
      - reference to this affine 3D Point's e031 blade coefficient value
    */                                                                      /**/
    inline const f4& E031(void) const
    {
      return e031;
    } // end const f4& Point301::E031(void) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine Point's e012 blade coef. (ie z-coord; e3 dual) reference
    @return
      - reference to this affine 3D Point's e023 blade coefficient value
    */                                                                      /**/
    inline const f4& E012(void) const
    {
      return e023;
    } // end const f4& Point301::E012(void) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the affine point whose product is 1 when taken with this
    @return
      - G(3,0,1) affine Point such that Geometric Product with this == [1,<0>]
    */
    inline Point301 Inverse(void) const
    {
      return Reverse() * InvF(MagSq());
    } // end Point301 Point301::Inverse(void) const        #^^^^^^^^^#^^^^^^^^*/


    /** Format a Point for being output as a packed vector notated string
    @brief
        Format for output as a packed vector string: "{"inner":###}"
    @details
      - Considered as an object blob with 1 1D 0-blade named inner
    @return
      - Text formatted to Json standards for later deserialization / output
    */
    std::string Json(void) const;


    /**
    @brief
        Squared norm of the vector displacing the origin to this given point
    @details
        (*this) * (*this).Reverse() -> Dual() in memberwise ordering convention
        where e123 maps to it's planar dual e0, and likewise on per element
      => Copy() * Dual() == (coefficient-product-sum) * e0123 (pseudoscalar)
      => each product is taken with its memberwise reverse (:= dual for this),
        not simply squared coefficients on a technical level, but equivalently,
        and so written as such for concision & clarity to ultimate equivalence
    @return
      - Euclidean length of the vector from the origin to this projective point
    */                                                                      /**/
    inline f4 MagSq(void) const
    {
      return DotSelf();
    } // end f4 Point301::MaqSq(void) const      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the Point which has equal magnitude but opposite orientation
    @details
      <e123, e023, e031, e012> reverse := <e210, e130, e320, e321>
    @return
      - Trivector with memberwise negated value
    */                                                                      /**/
    inline Point301 Reverse(void) const
    {
      return Point301(-e123, -e023, -e031, -e012);
    } // end Point301 Point301::Reverse(void) const        #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Point's e123 blade (aka homogeneous value) member coef.
    @param e123_value
      - value to set in the Point's e123 (aka homogeneous value) member coef.
    @return
      - reference to this Point for method chaining
    */                                                                      /**/
    inline Point301& E123(f4 e123_value)
    {
      e123 = e123_value;
      return *this;
    } // end Point301& Point301::E123(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Point's e023 blade (aka x-coord; e1 dual) member coef.
    @param e023_value
      - value to set in the Point's e023 (aka x-coord; e1 dual) member coef.
    @return
      - reference to this Point for method chaining
    */                                                                      /**/
    inline Point301& E023(f4 e023_value)
    {
      e023 = e023_value;
      return *this;
    } // end Point301& Point301::E023(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Point's e023 blade (aka y-coord; e2 dual) member coef.
    @param e031_value
      - value to set in the Point's e031 (aka y-coord; e2 dual) member coef.
    @return
      - reference to this Point for method chaining
    */                                                                      /**/
    inline Point301& E031(f4 e031_value)
    {
      e031 = e031_value;
      return *this;
    } // end Point301& Point301::E031(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Point's e012 blade (aka z-coord; e3 dual) member coef.
    @param e012_value
      - value to set in the Point's e012 (aka z-coord; e3 dual) member coef.
    @return
      - reference to this Point for method chaining
    */                                                                      /**/
    inline Point301& E012(f4 e012_value)
    {
      e012 = e012_value;
      return *this;
    } // end Point301& Point301::E012(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Update the values to a copy of an existing projective point's members
    @param source
      - 
    @return
      - Reference to this Point for method chaining
    */                                                                      /**/
    inline Point301& Set(f4 e123_value = Of, f4 e023_value = Of,
      f4 e031_value = Of, f4 e012_value = Of)
    {
      e123 = e123_value;
      e023 = e023_value;
      e031 = e031_value;
      e012 = e012_value;
      return *this;

    } // end + Point301& Point301::Set(const Point301&)                       */

    /**
    @brief
        Update the values to a copy of an existing projective point's members
    @param source
      - The Point to used in copying values
    @return
      - Reference to this Point for method chaining
    */                                                                      /**/
    inline Point301& Set(const Point301& source)
    {
      e123 = (source.e123);
      e023 = (source.e023);
      e031 = (source.e031);
      e012 = (source.e012);
      return *this;

    } // end + Point301& Point301::Set(const Point301&)                       */


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
        Get exterior (wedge) product of this Point with a Line: scaled line
    @param line
      - the line to have its product taken with this Point in external 
    @return
      - Join of G(3,0,1) geometric Point (3-vector) & Line (2-vectors)
    */
    Line301 Wedge(const Line301& line);


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Private Members                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    // 4D constraints possible on 3 of 4D (projective point constraint)
    
    //! - Coefficient of the projective point sum constraint (e0 dual)
    f4 e123;
    
    //! - Coefficient of the primary projective plane constraint (e1 dual)
    f4 e023;
    
    //! - Coefficient of the secondary projective plane constraint (e2 dual)
    f4 e031;
    
    //! - Coefficient of the tertiary projective plane constraint (e3 dual)
    f4 e012;


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                         Operator Overloads                             */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      Create a negated copy of all affine Point values: <-inner>
    @return
      - copy of the Point with <-inner> member values
    */
    inline Point301 operator-(void) const
    {
      return Reverse();
    } // end + Point301& Point301::operator=(const Point301&)        #^^^^^^^^*/


    /**
    @brief
      Invert Point components to give the multiplicative conjugate: reciprocal
    @return
      - multiplicative reciprocal ((*this) * !(*this) := {1, 0, ..., 0})
    */
    inline Point301 operator!(void) const
    {
      return Inverse();
    } // end + Point301& Point301::operator!(void)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set the source affine Point member values into this one's fields
    @param source
      - the affine Point to have its values copied into this one
    @return
      - reference to this 3D affine Point for method chaining
    */
    inline Point301& operator=(const Point301& source)
    {
      return Set(source);
    } // end + Point301& Point301::operator=(const Point301&)     #^^^^^^^^*/


    /**
    @brief
      Get a member value from the given subscript
    @param channel
      - map to the letter / number for the desired channel of the object
    @return
      - copy of the contained dimension member value associated to the channel
    */
    f4 operator[](s2 channel) const;


    /**
    @brief
      Get a member value reference from the given subscript
    @param channel
      - map to the letter / number for the desired channel of the object
    @return
      - reference to the contained field associated to the subscript number
    */
    f4& operator[](s2 channel);


    /**
    @brief
      Calculate the member-wise addition of 2 Points
    @param other
      - Point to sum into a copy of this, member-wise
    @return
      - copy of member-wise sum of this and the other into a new one
    */                                                                      /**/
    inline Point301 operator+(const Point301& other) const
    {
      return Copy() += other;
    }// end + Point301 Point301::operator+(const Point301&) const #^^^^^^^^*/


    /**
    @brief
      Add an other Point's values member-wise into this Point's values
    @param other
      - source vector to have memberwise summation performed with this
    @return
      - reference to this 3D affine Point for method chaining
    */                                                                      /**/
    inline Point301& operator+=(const Point301& other)
    {
      e123 += other.e123;
      e023 += other.e023;
      e031 += other.e031;
      e012 += other.e012;
      return *this;
    } // end + Point301& Point301::operator+=(const Point301&) const ^^^^^^*/


    /**
    @brief
      Calculate the member-wise difference of 2 affine Points
    @param other
      - source vector to have memberwise difference calculated with this (copy)
    @return
      - memberwise difference of this and the other, copied in a new one
    */                                                                      /**/
    inline Point301 operator-(const Point301& other) const
    {
      return Copy() -= other;
    }// end + Point301 Point301::operator-(const Point301&) const #^^^^^^^^*/


    /**
    @brief
      Subtract an other affine Point's values member-wise from this one's
    @param other
      - source vector to have negated memberwise summation performed with this
    @return
      - reference to this 3D affine Point for method chaining
    */                                                                      /**/
    inline Point301& operator-=(const Point301& other)
    {
      return *this += -other;
    } // end + Point301& Point301::operator+=(const Point301&) const ^^^^^^*/


    /**
    @brief
      Scalar affine Point product multiplies uniformly by the given scalar
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - resultant, member-wise scaled copy of this affine Point's values
    */                                                                      /**/
    inline Point301 operator*(f4 scalar) const
    {
      return Copy() *= scalar;
    } // end + Point301 Point301::operator*(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Scalar affine Point product scales all members uniformly by the input
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - reference to this 3D affine Point for method chaining
    */                                                                      /**/
    inline Point301& operator*=(f4 scalar)
    {
      return Set(e123*scalar, e023*scalar, e031*scalar, e012*scalar);
    } // end + Point301& Point301::operator*=(f4) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get geometric product of this and another Point set into a new one
    @details
      (u.e123 + u.e023 + u.e031 + u.e012)*(v.e123 + v.e023 + v.e031 + v.e012)
       -> (w123 + x023 + y031 + z012) * (d123 + a023 + b031 + c012)
      =>+ wd123123 + wa123023 + wb123031 + wc123012
        + xd023123 + xa023023 + xb023031 + xc023012
        + yd031123 + ya031023 + yb031031 + yc031012
        + zd012123 + za012023 + zb012031 + zc012012
      =>- wd112233 + wa012233 + wb021133 + wc031122
        - xd012233 - xa002233 - xb120033 + xc310022
        - yd021133 + ya120033 - yb001133 - yc230011
        - zd031122 - za310022 + zb230011 - zc001122
      => -wd + wa01 + wb02 + wc03 - xd01 - yd02 - zd03
      => -wd + (wa-xd)*e01 + (wb-yd)*e02 + (wc-zd)*e03
      =>         -(v.e123*v.e123)
        + (u.e123*v.e023 - u.e023*v.e123) * e01
        + (u.e123*v.e031 - u.e031*v.e123) * e02
        + (u.e123*v.e012 - u.e012*v.e123) * e03
    @param other
      - source affine Point to be multiplied with this affine Point
    @return
      - scaling & rotation of this by another affine Point
    */                                                                      /**/
    GP301 operator*(const Point301& other) const;


    /**
    @brief
        Divides all values uniformly by divisor, returning result
    @details
      - (real, imag)/d = (real, imag)*(1/d) = (real/d, imag/d)
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - resultant, member-wise scaled copy of this Point's values
    */                                                                      /**/
    inline Point301 operator/(f4 divisor) const
    {
      return Copy() /= divisor;
    } // end + Point301 Point301::operator/(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide all values uniformly by divisor, setting result
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - reference to this 3D affine Point for method chaining
    */                                                                      /**/
    inline Point301& operator/=(f4 divisor)
    {
      return (*this) *= InvF(divisor);
    } // end + Point301 Point301::operator/=(f4) #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this affine Point by another, returning result
    @param other
      - affine Point by which this affine Point is to be divided
    @return
      - resultant, member-wise scaled copy of this Point's values
    */                                                                      /**/
    GP301 operator/(const Point301& other) const;


  }; // end Point301 union / struct / class type declaration        #^^^^^^^^*/



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
  inline Point301 operator*(f4 scalar, const Point301& rhs)
  { return Point301(rhs * scalar);
  } // end Point301 operator*(f4, const Point301&)       #^^^^^^^^^#^^^^^^^^*/


  /**
  @brief
      Confirm if 2 affine Points are relatively equal memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for equality
  @param rhs
    - right hand side to be compared memberwise with left hand for equality
  @return
    - true only if all members are in close proximity of one another
  */
  bool operator==(const Point301& lhs, const Point301& rhs);


  /**
  @brief
      Confirm if 2 affine Points are not equal in any values memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for inequality
  @param rhs
    - right hand side to be compared memberwise with left hand for inequality
  @return
    - true if any members are not in close proximity of one another
  */
  bool operator!=(const Point301& lhs, const Point301& rhs);


  /**
  @brief
      Output the default string version of the Point's data
  @param output
    - stream to receive the vector string and and carry contents for output
  @param point
    - number to have its values be converted to text based output
  @return
    - reference to the output stream object having the vector fed in
  */
  std::ostream& operator<<(std::ostream& output, const Point301& point);


  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                            Helper Constants                             */
  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  //! Zero valued 1D real scalar; error state reserved value
  extern const Point301& nullPoint031;

} // end dp namespace