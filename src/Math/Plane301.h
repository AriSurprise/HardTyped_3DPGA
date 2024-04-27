/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  Plane301.h
Purpose: Projective 3+1D G(3,0,1), 1-vector coefficients: 1D restrictions
Details: Representing euclideana geometric points in 3D using a affine,
  homogeneous 3+1D spatial coordinate set.  Dealing with the geometry for the
  objects constrained in none of those 4 degrees of freedom, we have nCr(0,4)
  i.e. 1 dimension of representing that point's size, i.e. a scalar value.
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
#include "../Type/Errata.h" // Interperatively restricted member (wrapper class)
#include "../Util/Value.h"  // Basic inline value manuip. utility functions


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Forward References                             */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

class Line301;
class Point301;
class I301;
class GP301;

namespace dp  //! Contents for use within DigiPen CS / MAT class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  class Plane301 //! PGA, G(3,0,1) Affine Plane reflection vector components
  {
  public:

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Public Constants                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    static const u1 ELEM = 4u; //! Reflect (1) choice(s) among (3+0+1) elements

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                             Constructors                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Projective 3D Plane's defaultable member initialization constructor
    */                                                                      /**/
    Plane301(f4 e0_coefficient = If, f4 e1_coefficient = Of,
      f4 e2_coefficient = Of, f4 e3_coefficient = Of);

    /**
    @brief
        Projective 3D Plane's copy constructor
    */                                                                      /**/
    Plane301(const Plane301& source);

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Accessor Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Affine 3D Plane's bivector magnitude: projective bivector area
    @return
      - Scalar measure of euclidean normal length
    */                                                                      /**/
    inline f4 Area(void) const
    {
      return Mag();
    } // end f4 Plane301::Area(void) const       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Affine 3D Plane magnitude: projective bivector parallelogram square area
    @return
      - Scalar measure of euclidean plane's normal's squared length
    */                                                                      /**/
    inline f4 AreaSq(void) const
    {
      return MagSq();
    } // end f4 Plane301::AreaSq(void) const     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Projective 3D Plane self copy constructor convenience wrapper
    @return
      - memberwise copy of this Plane301 instance
    */                                                                      /**/
    inline Plane301 Copy(void) const
    {
      return Plane301(*this);
    } // end Plane301 Plane301::Copy(void) const #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine 3D Plane's memberwise dot product with itself (squared mag.)
    @return
      - scalar measure of euclidean squared length
    */                                                                      /**/
    inline f4 DotSelf(void) const
    {
      return e1*e1 + e2*e2 + e3*e3; // e0*e0 := +0; need not be counted
    } // end f4 Plane301::DotSelf(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine 3D Plane's e0 direction's (aka plane sum) member reference
    @return
      - reference to this affine Plane's e0 coordinate
    */                                                                      /**/
    inline const f4& E0(void) const
    {
      return e0;
    } // end const f4& Plane301::E0(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine 3D Plane's e1 direction (aka plane x-coord) member reference
    @return
      - reference to this affine Plane's e1 coordinate
    */                                                                      /**/
    inline const f4& E1(void) const
    {
      return e1;
    } // end const f4& Plane301::E1(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine 3D Plane's e2 direction (aka plane y-coord) member reference
    @return
      - reference to this affine Plane's e2 coordinate
    */                                                                      /**/
    inline const f4& E2(void) const
    {
      return e2;
    } // end const f4& Plane301::E2(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine 3D Plane's e3 direction (aka plane z-coord) member reference
    @return
      - reference to this affine Plane's e3 coordinate
    */                                                                      /**/
    inline const f4& E3(void) const
    {
      return e3;
    } // end const f4& Plane301::E3(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine 3D Plane's bivector magnitude: parallelogram area
    @details
        If possible, prefer squared mag from MagSq; avoid sqrt call computation
    @return
      - scalar measure of euclidean normal length
    */                                                                      /**/
    inline f4 Mag(void) const
    {
      return SqrtF(MagSq());
    } // end f4 Plane301::Mag(void) const        #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get affine 3D Plane's bivector magnitude: parallelogram area
    @return
      - scalar measure of euclidean normal length
    */                                                                      /**/
    inline f4 MagSq(void) const
    {
      return DotSelf();
    } // end f4 Plane301::MagSq(void) const      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Invert Plane members to get affine bivector reciprocal / inverse
    @return
      - Reciprocal affine bivector equal to 1 when multiplied with this
    */                                                                      /**/
    inline Plane301 Inverse(void) const
    {
      return Reverse() * InvF(MagSq());
    } // end + Plane301& Plane301::Inverse(void) #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /** Format a Plane for being output as a packed vector notated string
    @brief
        Output as a packed vector string: {"e0":#,"e1":#,"e2":#,"e3":#}
    @details
      - JSON object blob with 4D affine promoted 2->3-blade coefficients
    @return
      - text formatted to Json standards for later deserialization / output
    */
    std::string Json(void) const;


    /**
    @brief
        Get the Point which has equal magnitude but opposite orientation
    @details
      <e123, e023, e031, e012> reverse := <e210, e130, e320, e321>
    @return
      - Trivector with memberwise negated value
    */                                                                      /**/
    inline Plane301 Reverse(void) const
    {
      return Plane301(-e0, -e1, -e2, -e3);
    } // end Plane301 Plane301::Reverse(void) const        #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Plane's e0 direction (aka plane sum value) member
    @param e0_value
      - value to set in the Plane's e0 (aka sum value) member
    @return
      - reference to this Plane for method chaining
    */                                                                      /**/
    inline Plane301& E0(f4 e0_value)
    {
      e0 = e0_value;
      return *this;
    } // end Plane301& Plane301::E0(f4) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Plane's e1 direction (aka plane x-coordinate) member
    @param e1_value
      - value to set in the Plane's e1 (aka x-coordinate) member
    @return
      - reference to this Plane for method chaining
    */                                                                      /**/
    inline Plane301& E1(f4 e1_value)
    {
      e1 = e1_value;
      return *this;
    } // end Plane301& Plane301::E1(f4) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Plane's e2 direction (aka plane y-coordinate) member
    @param e2_value
      - value to set in the Plane's e2 (aka y-coordinate) member
    @return
      - reference to this Plane for method chaining
    */                                                                      /**/
    inline Plane301& E2(f4 e2_value)
    {
      e2 = e2_value;
      return *this;
    } // end Plane301& Plane301::E2(f4) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set affine 3D Plane's e3 direction (aka plane z-coordinate) member
    @param e3_value
      - value to set in the Plane's e3 (aka z-coordinate) member
    @return
      - reference to this Plane for method chaining
    */                                                                      /**/
    inline Plane301& E3(f4 e3_value)
    {
      e3 = e3_value;
      return *this;
    } // end Plane301& Plane301::E3(f4) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Set the affine Plane to a copy of another Plane's values
    @param source
      - the Plane to used in copying values memberwise
    @return
      - reference to this Plane for method chaining
    */                                                                      /**/
    inline Plane301& Set(f4 e0_value, f4 e1_value, f4 e2_value, f4 e3_value)
    {
      e0 = e0_value;
      e1 = e1_value;
      e2 = e2_value;
      e3 = e3_value;
      return *this;

    } // end + Plane301& Plane301::Set(const Plane301&)                       */

    /**
    @brief
        Set the affine Plane to a copy of another Plane's values
    @param source
      - the Plane to used in copying values memberwise
    @return
      - reference to this Plane for method chaining
    */                                                                      /**/
    inline Plane301& Set(const Plane301& source)
    {
      e0 = source.e0;
      e1 = source.e1;
      e2 = source.e2;
      e3 = source.e3;
      return *this;

    } // end + Plane301& Plane301::Set(const Plane301&)                       */


    /**
    @brief
        Format for output as a vector notated string
    @details
      - adds padding for uniform spacing: JSON tightly packs elements
    @return
      - text set to be uniformly spaced for columned clarity / legibility
    */
    std::string String(void) const;


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Private Members                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    //! - Coefficient of e0 (squaring to 0) planar projection (sum) component
    f4 e0;
    //! - Coefficient of e1 (squaring to 1) planar primary axis component
    f4 e1;
    //! - Coefficient of e2 (squaring to 1) planar secondary axis component
    f4 e2;
    //! - Coefficient of e3 (squaring to 1) planar tertiary axis component
    f4 e3;

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                         Operator Overloads                             */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      Create a negated copy of all affine Plane values: <-inner>
    @return
      - copy of the Plane with <-inner> member values
    */
    inline Plane301 operator-(void) const
    {
      return Reverse();
    } // end + Plane301& Plane301::operator=(const Plane301&)        #^^^^^^^^*/


    /**
    @brief
        Invert Plane members to get multiplicative vector reciprocal / inverse
    @return
      - reference to this affine Plane for method chaining
    */
    inline Plane301 operator!(void) const
    {
      return Inverse();
    } // end + Plane301& Plane301::operator!(void)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set the source affine Plane member values into this one's fields
    @param source
      - the affine Plane to have its values copied into this one
    @return
      - reference to this 3D affine Plane for method chaining
    */
    inline Plane301& operator=(const Plane301& source)
    {
      return Set(source);
    } // end + Plane301& Plane301::operator=(const Plane301&)     #^^^^^^^^*/


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
      Calculate the member-wise addition of 2 Planes
    @param other
      - Plane to sum into a copy of this, member-wise
    @return
      - copy of member-wise sum of this and the other into a new one
    */                                                                      /**/
    inline Plane301 operator+(const Plane301& other) const
    {
      return Copy() += other;
    }// end + Plane301 Plane301::operator+(const Plane301&) const    #^^^^^^^^*/


    /**
    @brief
      Add an other Plane's values member-wise into this Plane's values
    @param other
      - source vector to have memberwise summation performed with this
    @return
      - reference to this 3D affine Plane for method chaining
    */                                                                      /**/
    inline Plane301& operator+=(const Plane301& other)
    {
      e0 += other.e0;
      e1 += other.e1;
      e2 += other.e2;
      e3 += other.e3;
      return *this;
    } // end + Plane301& Plane301::operator+=(const Plane301&) const #^^^^^^^^*/


    /**
    @brief
      Calculate the member-wise difference of 2 affine Planess
    @param other
      - source vector to have memberwise difference calculated with this (copy)
    @return
      - memberwise difference of this and the other, copied in a new one
    */                                                                      /**/
    inline Plane301 operator-(const Plane301& other) const
    {
      return Copy() -= other;
    }// end + Plane301 Plane301::operator-(const Plane301&) const    #^^^^^^^^*/


    /**
    @brief
      Subtract an other affine Plane's values member-wise from this one's
    @param other
      - source vector to have negated memberwise summation performed with this
    @return
      - reference to this 3D affine Plane for method chaining
    */                                                                      /**/
    inline Plane301& operator-=(const Plane301& other)
    {
      return *this += -other;
    } // end + Plane301& Plane301::operator+=(const Plane301&) const #^^^^^^^^*/


    /**
    @brief
      Scalar affine Plane product multiplies uniformly by the given scalar
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - resultant, member-wise scaled copy of this affine Plane's values
    */                                                                      /**/
    inline Plane301 operator*(f4 scalar) const
    {
      return Copy() *= scalar;
    } // end + Plane301 Plane301::operator*(f4) const      #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Scalar affine Plane product sets all members scaled by the input
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - reference to this 3D affine Plane for method chaining
    */                                                                      /**/
    inline Plane301& operator*=(f4 scalar)
    {
      return Set(e0*scalar, e1*scalar, e2*scalar, e3*scalar);
    } // end + Plane301& Plane301::operator*=(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get geometric product of this and another Plane set into a new one
    @param other
      - source affine Plane to be multiplied with this affine Plane
    @return
      - Meet & Join of the 2 planes: resultant even subalgebra geometric product
    */                                                                      /**/
    GP301 operator*(const Plane301& other) const;


    /**
    @brief
        Divides all values uniformly by divisor, returning result
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - resultant, member-wise scaled copy of this Plane's values
    */                                                                      /**/
    inline Plane301 operator/(f4 divisor) const
    {
      return Copy() *= InvF(divisor);
    } // end + Plane301 Plane301::operator/(f4) const      #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide all values uniformly by divisor, setting result
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - reference to this 3D affine Plane for method chaining
    */                                                                      /**/
    inline Plane301& operator/=(f4 divisor) { return (*this) *= InvF(divisor);
    } // end + Plane301 Plane301::operator/=(f4)           #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this affine Plane by another, returning result
    @param other
      - affine Plane by which this affine Plane is to be divided
    @return
      - resultant, member-wise scaled copy of this Plane's values
    */                                                                      /**/
    GP301 operator/(const Plane301& other) const;


  }; // end Plane301 class type declaration      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/



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
  inline Plane301 operator*(f4 scalar, const Plane301& rhs)
  { return Plane301(rhs * scalar);
  } // end Plane301 operator*(f4, const Plane301&)       #^^^^^^^^^#^^^^^^^^*/


  /**
  @brief
      Confirm if 2 affine Planes are relatively equal memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for equality
  @param rhs
    - right hand side to be compared memberwise with left hand for equality
  @return
    - true only if all members are in close proximity of one another
  */
  bool operator==(const Plane301& lhs, const Plane301& rhs);


  /**
  @brief
      Confirm if 2 affine Planes are not equal in any values memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for inequality
  @param rhs
    - right hand side to be compared memberwise with left hand for inequality
  @return
    - true if any members are not in close proximity of one another
  */
  bool operator!=(const Plane301& lhs, const Plane301& rhs);


  /**
  @brief
      Output the default string version of the Plane's data
  @param output
    - stream to receive the vector string and and carry contents for output
  @param line
    - number to have its values be converted to text based output
  @return
    - reference to the output stream object having the vector fed in
  */
  std::ostream& operator<<(std::ostream& output, const Plane301& line);


  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                            Helper Constants                             */
  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  //! Zero valued 1D real scalar; error state reserved value
  extern const Plane301& nullPlane031;

} // end dp namespace