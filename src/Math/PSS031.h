/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  PSS031.h
Purpose: Projective 3+1D Cl(3,0,1), 4-vector coefficient: 1D restrictions
Details: Representing euclideana geometric volumes in 3D using a projective,
  homogeneous 3+1D spatial coordinate set.  Dealing with the geometry for the
  objects constrained in none of those 4 degrees of freedom, we have nCr(0,4)
  i.e. 1 dimension of representing that volume's size, i.e. a scalar value.
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

class Volume031;
class Plane301;
class Line031;
class Point031;

namespace dp  //! Contents for use within DigiPen CS / MAT class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  class PSS031 //! 
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
    PSS031(f4 scale = If);

    /**
    @brief
      
    */                                                                      /**/
    PSS031(const PSS031& source);

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      
    @return
      - internal member reference
    */                                                                      /**/
    // end const f4& PSS031::Get(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        
    @return
      - memberwise copy of this PSS031 instance
    */                                                                       /**/
    inline PSS031 Copy(void) const { return PSS031(*this); }
    // end PSS031 PSS031::Copy(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /** Format a Volume for being output as a packed vector notated string
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
      - the Volume to used in copying values
    @return
      - reference to this Volume for method chaining
    */
    inline PSS031& Set(const PSS031& source)
    {
      inner = (source.inner);
      return *this;

    } // end + PSS031& PSS031::Set(const PSS031&)


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
        Get exterior (wedge) product of this Volume with a Line: scaled line
    @param line
      - the line to have its product taken with this volume in external 
    @return
      - Join of Cl(3,0,1) geometric Volume (0-vector) & Line (2-vectors)
    */
    Line031 Wedge(const Line031& line);


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Private Members                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    //! - 1D constraints possible on 0 of 4D volume (determinant; uniform scale)
    f4 inner;

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                         Operator Overloads                             */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      Create a negated copy of all projective Volume values: <-inner>
    @return
      - copy of the Volume with <-inner> member values
    */
    inline PSS031 operator-(void) const
    {
      return PSS031(-inner);
    } // end + PSS031& PSS031::operator=(const PSS031&)     #^^^^^^^^*/


    /**
    @brief
      Invert Volume components to give the multiplicative conjugate: reciprocal
    @return
      - reference to this projective Volume for method chaining
    */
    inline PSS031 operator!(void) const
    {
      return InvF(inner);
    } // end + PSS031& PSS031::operator!(void)       #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set the source projective Volume member values into this one's fields
    @param source
      - the projective Volume to have its values copied into this one
    @return
      - reference to this 3D projective Volume for method chaining
    */
    inline PSS031& operator=(const PSS031& source)
    {
      return Set(source);
    } // end + PSS031& PSS031::operator=(const PSS031&)     #^^^^^^^^*/


    /**
    @brief
      Get a member value from the given subscript
    @param channel
      - map to the letter / number for the desired channel of the object
    @return
      - copy of the contained dimension member value associated to the channel
    */
    f4 operator[](s1 channel) const;


    /**
    @brief
      Get a member value reference from the given subscript
    @param channel
      - map to the letter / number for the desired channel of the object
    @return
      - reference to the contained field associated to the subscript number
    */
    f4& operator[](s1 channel);


    /**
    @brief
      Calculate the member-wise addition of 2 Volumes
    @param other
      - Volume to sum into a copy of this, member-wise
    @return
      - copy of member-wise sum of this and the other into a new one
    */                                                                      /**/
    inline PSS031 operator+(const PSS031& other) const
    {
      return Copy() += other;
    }// end + PSS031 PSS031::operator+(const PSS031&) const #^^^^^^^^*/


    /**
    @brief
      Add an other Volume's values member-wise into this Volume's values
    @param other
      - source vector to have memberwise summation performed with this
    @return
      - reference to this 3D projective Volume for method chaining
    */                                                                      /**/
    inline PSS031& operator+=(const PSS031& other)
    {
      inner += other.inner;
      return *this;
    } // end + PSS031& PSS031::operator+=(const PSS031&) const ^^^^^^*/


    /**
    @brief
      Calculate the member-wise difference of 2 projective Volumess
    @param other
      - source vector to have memberwise difference calculated with this (copy)
    @return
      - memberwise difference of this and the other, copied in a new one
    */                                                                      /**/
    inline PSS031 operator-(const PSS031& other) const
    {
      return Copy() -= other;
    }// end + PSS031 PSS031::operator-(const PSS031&) const #^^^^^^^^*/


    /**
    @brief
      Subtract an other projective Volume's values member-wise from this one's
    @param other
      - source vector to have negated memberwise summation performed with this
    @return
      - reference to this 3D projective Volume for method chaining
    */                                                                      /**/
    inline PSS031& operator-=(const PSS031& other)
    {
      return *this += -other;
    } // end + PSS031& PSS031::operator+=(const PSS031&) const ^^^^^^*/


    /**
    @brief
      Scalar projective Volume product multiplies uniformly by the given scalar
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - resultant, member-wise scaled copy of this projective Volume's values
    */                                                                      /**/
    inline PSS031 operator*(f4 scalar) const
    {
      return Copy() *= scalar;
    } // end + PSS031 PSS031::operator*(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Scalar projective Volume product sets all members uniformly scaled by the input
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - reference to this 3D projective Volume for method chaining
    */                                                                      /**/
    inline PSS031& operator*=(f4 scalar)
    {
      return Set(inner*scalar);
    } // end + PSS031& PSS031::operator*=(f4) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get geometric product of this and another Volume set into a new one
    @param other
      - source projective Volume to be multiplied with this projective Volume
    @return
      - scaling & rotation of this by another projective Volume
    */                                                                      /**/
    PSS031 operator*(const PSS031& other) const
    {
      return Copy() *= other;
    } // end + PSS031 PSS031::operator*(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        
    @param other
      - source projective Volume to be multiplied with this one
    @return
      - reference to this 3D projective Volume for method chaining
    */                                                                      /**/
    inline PSS031& operator*=(const PSS031& other)
    {
      return Set(inner * other.inner);
    } // end + PSS031& PSS031::operator*=(const PSS031&)    #^^^^^^^^*/


    /**
    @brief
        Divides all values uniformly by divisor, returning result
    @details
      - (real, imag)/d = (real, imag)*(1/d) = (real/d, imag/d)
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - resultant, member-wise scaled copy of this Volume's values
    */                                                                      /**/
    inline PSS031 operator/(f4 divisor) const
    {
      return Copy() *= InvF(divisor);
    } // end + PSS031 PSS031::operator/(f4) const    #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide all values uniformly by divisor, setting result
    @param divisor
      - amount by which all values are to be uniformly divided
    @return
      - reference to this 3D projective Volume for method chaining
    */                                                                      /**/
    inline PSS031& operator/=(f4 divisor) { return (*this) *= InvF(divisor);
    } // end + PSS031 PSS031::operator/=(f4)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this projective Volume by another, returning result
    @param other
      - projective Volume by which this projective Volume is to be divided
    @return
      - resultant, member-wise scaled copy of this Volume's values
    */                                                                      /**/
    inline PSS031 operator/(const PSS031& other) const
    { return Copy() /= other;
    }// end + PSS031 PSS031::operator/(const PSS031&) const #^^^^^^^^*/


    /**
    @brief
        Divide this projective Volume by another, setting result
    @param other
      - projective Volume by which this one is to be divided
    @return
      - reference to this projective Volume for method chaining
    */                                                                      /**/
    inline PSS031& operator/=(const PSS031& other)
    {
      return (*this) *= !other;
    } // end + PSS031 PSS031::operator/=(f4)         #^^^^^^^^^#^^^^^^^^*/


  }; // end PSS031 union / struct / class type declaration        #^^^^^^^^*/



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
  inline PSS031 operator*(f4 scalar, const PSS031& rhs)
  { return PSS031(rhs * scalar);
  } // end PSS031 operator*(f4, const PSS031&)       #^^^^^^^^^#^^^^^^^^*/


  /**
  @brief
      Confirm if 2 projective Volumes are relatively equal memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for equality
  @param rhs
    - right hand side to be compared memberwise with left hand for equality
  @return
    - true only if all members are in close proximity of one another
  */
  bool operator==(const PSS031& lhs, const PSS031& rhs);


  /**
  @brief
      Confirm if 2 projective Volumes are not equal in any values memberwise
  @param lhs
    - left hand side to be compared memberwise with right hand for inequality
  @param rhs
    - right hand side to be compared memberwise with left hand for inequality
  @return
    - true if any members are not in close proximity of one another
  */
  bool operator!=(const PSS031& lhs, const PSS031& rhs);


  /**
  @brief
      Output the default string version of the Volume's data
  @param output
    - stream to receive the vector string and and carry contents for output
  @param volume
    - number to have its values be converted to text based output
  @return
    - reference to the output stream object having the vector fed in
  */
  std::ostream& operator<<(std::ostream& output, const PSS031& volume);


  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                            Helper Constants                             */
  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  //! Zero valued 1D real scalar; error state reserved value
  extern const PSS031& nullPSS031;

} // end dp namespace