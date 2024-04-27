/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  I301.h
Purpose: Projective 3+1D G(3,0,1), 0-vector coefficient: 1D restrictions
Details: Representing euclideana geometric Pseudoscalars in 3D using a affine,
  homogeneous 3+1D spatial coordinate set.  Dealing with the geometry for the
  objects constrained in none of those 4 degrees of freedom, we have nCr(0,4)
  i.e. 1 dimension of representing that Pseudoscalar's size, i.e. a scalar value.
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

class Plane301;
class Line301;
class Point301;

namespace dp  //! Contents for use within DigiPen CS / MAT class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  class I301 //! 
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
    I301(f4 scale = If);

    /**
    @brief
      
    */                                                                      /**/
    I301(const I301& source);

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      
    @return
      - internal member reference
    */                                                                      /**/
    // end const f4& I301::Get(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        
    @return
      - memberwise copy of this I301 instance
    */                                                                       /**/
    inline I301 Copy(void) const { return I301(*this); }
    // end I301 I301::Copy(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /** Format a Pseudoscalar for being output as a packed vector notated string
    @brief
      Format for output as a packed vector string: "{"inner":###}"
    @details
      - considered as an object blob with 1 1D 0-blade named inner
    @return
      - text formatted to Json standards for later deserialization / output
    */
    std::string Json(void) const;

    /**
    @brief
        
    @param source
      - the Pseudoscalar to used in copying values
    @return
      - reference to this Pseudoscalar for method chaining
    */
    inline I301& Set(const I301& source)
    {
      inner = (source.inner);
      return *this;

    } // end + I301& I301::Set(const I301&)


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
        Get exterior (wedge) product of this Pseudoscalar with a Line: scaled line
    @param line
      - the line to have its product taken with this Pseudoscalar in external 
    @return
      - Join of G(3,0,1) geometric Pseudoscalar (4-vector) & Line (2-vectors)
    */
    Line301 Wedge(const Line301& line);


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Private Members                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    //! - 1D constraints possible on 0 of 4D Pseudoscalar (determinant; uniform scale)
    f4 inner;

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                         Operator Overloads                             */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      Create a negated copy of all affine Pseudoscalar values: <-inner>
    @return
      - copy of the Pseudoscalar with <-inner> member values
    */
    inline I301 operator-(void) const
    {
      return I301(-inner);
    } // end + I301& I301::operator=(const I301&)     #^^^^^^^^*/


    /**
    @brief
      Invert Pseudoscalar components to give the multiplicative conjugate: reciprocal
    @return
      - reference to this affine Pseudoscalar for method chaining
    */
    inline I301 operator!(void) const
    {
      return InvF(inner);
    } // end + I301& I301::operator!(void)       #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set the source affine Pseudoscalar member values into this one's fields
    @param source
      - the affine Pseudoscalar to have its values copied into this one
    @return
      - reference to this 3D affine Pseudoscalar for method chaining
    */
    inline I301& operator=(const I301& source)
    {
      return Set(source);
    } // end + I301& I301::operator=(const I301&)     #^^^^^^^^*/


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
      Calculate the member-wise addition of 2 Pseudoscalars
    @param other
      - Pseudoscalar to sum into a copy of this, member-wise
    @return
      - copy of member-wise sum of this and the other into a new one
    */                                                                      /**/
    inline I301 operator+(const I301& other) const
    {
      return Copy() += other;
    }// end + I301 I301::operator+(const I301&) const #^^^^^^^^*/


    /**
    @brief
      Add an other Pseudoscalar's values member-wise into this Pseudoscalar's values
    @param other
      - source vector to have memberwise summation performed with this
    @return
      - reference to this 3D affine Pseudoscalar for method chaining
    */                                                                      /**/
    inline I301& operator+=(const I301& other)
    {
      inner += other.inner;
      return *this;
    } // end + I301& I301::operator+=(const I301&) const ^^^^^^*/


    /**
    @brief
      Calculate the member-wise difference of 2 affine Pseudoscalarss
    @param other
      - source vector to have memberwise difference calculated with this (copy)
    @return
      - memberwise difference of this and the other, copied in a new one
    */                                                                      /**/
    inline I301 operator-(const I301& other) const
    {
      return Copy() -= other;
    }// end + I301 I301::operator-(const I301&) const #^^^^^^^^*/


    /**
    @brief
      Subtract an other affine Pseudoscalar's values member-wise from this one's
    @param other
      - source vector to have negated memberwise summation performed with this
    @return
      - reference to this 3D affine Pseudoscalar for method chaining
    */                                                                      /**/
    inline I301& operator-=(const I301& other)
    {
      return *this += -other;
    } // end + I301& I301::operator+=(const I301&) const ^^^^^^*/


    /**
    @brief
      Scalar affine Pseudoscalar product multiplies uniformly by the given scalar
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - resultant, member-wise scaled copy of this affine Pseudoscalar's values
    */                                                                      /**/
    inline I301 operator*(f4 scalar) const
    {
      return Copy() *= scalar;
    } // end + I301 I301::operator*(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Scalar affine Pseudoscalar product sets all members uniformly scaled by the input
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - reference to this 3D affine Pseudoscalar for method chaining
    */                                                                      /**/
    inline I301& operator*=(f4 scalar)
    {
      return Set(inner*scalar);
    } // end + I301& I301::operator*=(f4) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get geometric product of this and another Pseudoscalar set into a new one
    @param other
      - source affine Pseudoscalar to be multiplied with this affine Pseudoscalar
    @return
      - scaling & rotation of this by another affine Pseudoscalar
    */                                                                      /**/
    I301 operator*(const I301& other) const
    {
      return Copy() *= other;
    } // end + I301 I301::operator*(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        
    @param other
      - source affine Pseudoscalar to be multiplied with this one
    @return
      - reference to this 3D affine Pseudoscalar for method chaining
    */                                                                      /**/
    inline I301& operator*=(const I301& other)
    {
      return Set(inner * other.inner);
    } // end + I301& I301::operator*=(const I301&)    #^^^^^^^^*/


    /**
    @brief
        Divides all values uniformly by divisor, returning result
    @details
      - (real, imag)/d = (real, imag)*(1/d) = (real/d, imag/d)
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - resultant, member-wise scaled copy of this Pseudoscalar's values
    */                                                                      /**/
    inline I301 operator/(f4 divisor) const
    {
      return Copy() *= InvF(divisor);
    } // end + I301 I301::operator/(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide all values uniformly by divisor, setting result
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - reference to this 3D affine Pseudoscalar for method chaining
    */                                                                      /**/
    inline I301& operator/=(f4 divisor) { return (*this) *= InvF(divisor);
    } // end + I301 I301::operator/=(f4)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this affine Pseudoscalar by another, returning result
    @param other
      - affine Pseudoscalar by which this affine Pseudoscalar is to be divided
    @return
      - resultant, member-wise scaled copy of this Pseudoscalar's values
    */                                                                      /**/
    inline I301 operator/(const I301& other) const
    { return Copy() /= other;
    }// end + I301 I301::operator/(const I301&) const #^^^^^^^^*/


    /**
    @brief
        Divide this affine Pseudoscalar by another, setting result
    @param other
      - affine Pseudoscalar by which this one is to be divided
    @return
      - reference to this affine Pseudoscalar for method chaining
    */                                                                      /**/
    inline I301& operator/=(const I301& other)
    {
      return (*this) *= !other;
    } // end + I301 I301::operator/=(f4)         #^^^^^^^^^#^^^^^^^^*/


  }; // end I301 union / struct / class type declaration        #^^^^^^^^*/



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
  inline I301 operator*(f4 scalar, const I301& rhs)
  { return I301(rhs * scalar);
  } // end I301 operator*(f4, const I301&)       #^^^^^^^^^#^^^^^^^^*/


  /**
  @brief
      Confirm if 2 affine Pseudoscalars are relatively equal memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for equality
  @param rhs
    - right hand side to be compared memberwise with left hand for equality
  @return
    - true only if all members are in close proximity of one another
  */
  bool operator==(const I301& lhs, const I301& rhs);


  /**
  @brief
      Confirm if 2 affine Pseudoscalars are not equal in any values memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for inequality
  @param rhs
    - right hand side to be compared memberwise with left hand for inequality
  @return
    - true if any members are not in close proximity of one another
  */
  bool operator!=(const I301& lhs, const I301& rhs);


  /**
  @brief
      Output the default string version of the Pseudoscalar's data
  @param output
    - stream to receive the vector string and and carry contents for output
  @param pseudoscalar
    - number to have its values be converted to text based output
  @return
    - reference to the output stream object having the vector fed in
  */
  std::ostream& operator<<(std::ostream& output, const I301& pseudoscalar);


  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                            Helper Constants                             */
  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  //! Zero valued 1D real scalar; error state reserved value
  extern const I301& nullPseudoscalar031;

} // end dp namespace