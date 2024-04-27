/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  GP030.h
Purpose: 3 dimens Cl(0,3,0), even blade set, aka Quaternions / Hamiltonians
Details: The most controversial theme about the Geometric Product is making
  transitions as seamless and intuitive to learning GA as possible. 
  Unfortunately history makes this a complicated process, especially with
  regard to quaternions. Great efforts have historically been taken to abstract
  multivectors, making vectors and scalars the only geometric objects of
  concern to learn about. In 3D, this entails taking the complement of the
  bivector, 2-vector blade to get their 3D duals (vectors), meaning what is
  commonly referred to as the i-'vector', ostensibly correlating to the x-axis,
  in reality represents the e12 bivector scalar, which means that rather than
  e12 corresponding to i it is dual to the basis complement e3, corresponding
  to what we know as k, along the z axis normal.  This makes sense for notation
  in math taking the whole multivector of the basis as a linear probe of unique
  basis combinations in ascending order, mirroring the lower k-vector duals
  element-wise as a set, but working geometrically on a blade of dimensional
  scalars at a time to map each element to its dual within the like-ranked
  blade-dual it produces backwards results.
  This isn't an oversight or admission to hitorical error, but rather due to the
  knowledge available to Hamilton when he was formalizing the concepts. It may
  be obvious even to the relatively uninitiated that a quaternion might seem odd
  in needing 4 components to describe 3 dimensions when a 2D rotation could be
  performed using only the complex numbers with 2 components. His first attempts
  to extend the complex numbers ('couplets' as he called them), were indeed only
  using triplets, but he couldn't make sense of how to resolve multipling both
  an i and j component for some time before the concept of adding a k unit to
  represent their product dawned on him to attempt.
  In geometric algebra terms, what he had done was defined from a basis of a
  scalar and vectors <e1, e2> to create the bivector wedge product of the two:
  { s, {e1, e2}, e12 }.  Under this logic, e12 mapping to k mapping to z seems
  the obvious course of action, however conventionally this works out far more
  consistently in notation when using the even subagebra instead, and that is
  effectively why it worked (the full Cl(0,2,0) multivector's product is the
  same as that of the even subalgebra of Cl(0,3,0)). When using 3 bivectors
  instead of a bivector and 2 vectors however, the geometric ramifications of
  the components become far more clear than the lower dimensional multivector.
  Doing this means each component relates to an oriented plane in a right handed
  coordinate system where the plane is normal to the world axis it excludes, so
  each vector is actually an expression of dual it rotates around, whereas with
  Cl(0,2,0) one is talking about that rotation in the xy plane, the scalar
  coordinates in the e1 & e2 directions, and a scalar representing the inner
  product of e12's relation to each other, which isn't terribly explanatory to
  what allows the geometric effect to manifest the way it does. So while it
  seems like x, or e1 mapping to i makes sense, because e12 mapped to kto begin
  with, when taking the complements into consideration to use all bivectors to
  get that simplicity of the meaning of world plane rotation amounts, starting
  the bivector set as one conventionally might expect with i, it is sadly,
  thusly backwards to how other vector conventions already map.
  The most unrealistic goal would be for one to expect the convention of
  standard vectors using <x,y,z> ordering to be considered wrong / incompatible,
  and so to include the ability to map any vectors to their duals (bivectors in
  3D), those duals must be ordered to be conformant to map to match those
  conventions.  As such, the duals must be ordered in <k,j,i> to map as aliases
  of duals on matching <x,y,z> ordered vectors. This is not an insignificant
  goal to be concerned with, as duals mapping into each other memberwise
  simplifies a number of conceptual leaps required to begin GA math, and
  provides excellent explanatory power to the elegance of GA in general.
  Although it may seem counter-intuitive, this means the imaginary subset being
  <k,j,i> order is all but a necessity to use in compliance with those needs.
  For these reasons, <w,x,y,z> -> <s,k,j,i>, as opposed to most standards which
  actually get things backwards going with <x,y,z,w> -> <i,j,k,s> or perhaps
  <w,x,y,z> -> <s,i,j,k> (also explaining some of the black box overcomplication
  experience quaternions commonly suffer, in some measures). This is only 1 step
  shy of mapping directly onto a 4D vector's <x,y,z,w> layout, in that the w
  value leads as opposed to trailing, but this is done intentionally, as mapping
  a 3D bivector product and scalar onto a 4D object directly is in error, where
  a <1, 3> member set of even subalgebra is not. 3 choose 0 inner product scalar
  coming before 3 choose 2 combinations is semantically more sensible without
  deviating from any meaningful multivector groupings one may otherwise take,
  and besides, the alphabetic extension to correcting for w coming prior to x
  as it might ought to have always been is quite tempting, as opposed to being
  a tacked on reversal with few sensible additional subscript labels to rely on
  people using consistently past 4D vectors anyhow.
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
#include "../Type/ang.h"    // angle extraction requires arc unit parameter
#include "../Util/Value.h"  // Value manipulation; float point approximation
#include "../Type/Errata.h" // Sized primitive type aliases for brevity
#include "../Math/v3f.h"    // angle extraction requires arc unit parameter


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Forward References                             */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


namespace dp  //! Contents for use within DigiPen CS / MAT class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  union GP030 //! Cl(0,3,0) Geometric Product: 3D even-bladed subalgebra
  {
  public:

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                           Public Members                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    struct {
      f4 r;   //! Shared, interior (dot) real scalar: e0's non-orthogonality
      f4 e23; //! e2^e3 oriented plane bivector area scalar, normal to e1
      f4 e31; //! e3^e1 oriented plane bivector area scalar, normal to e2
      f4 e12; //! e1^e2 oriented plane bivector area scalar, normal to e3
    };
    struct {
      f4 real;  //! Complex, shared real scalar      (Interior comb. axis size)
      v3f imag; //! Complex imaginary axis scalars   (axis 1-3 ext. bivectors)
    };
    struct {
      f4 inner;  //! Geometric interior product angle non-orthogonality scalar
      v3f outer; //! Geometric exterior product bivector plane area scalar set
    };
    struct {
      f4 s;   //! Quaternion (H) label: axes interior real scalar
      f4 k;   //! Quaternion (H) label: +1 axis's normal's rh-plane's area
      f4 j;   //! Quaternion (H) label: +2 axis's normal's rh-plane's area
      f4 i;   //! Quaternion (H) label: +3 axis's normal's rh-plane's area
    };
    struct {
      f4 w;   //! Cartesian alias for axes interior, shared real scalar value
      f4 x;   //! Cartesian alias for imag.k-axis (e1's normal) plane's scalar
      f4 y;   //! Cartesian alias for imag.j-axis (e2's normal) plane's scalar
      f4 z;   //! Cartesian alias for imag.i-axis (e3's normal) plane's scalar
    };

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                             Constructors                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Create a complex 3D number (<inner, v3f(imaginary)>, default <1,0,0,0>)
    @param rsw_value
      - (inner | w | s field value) - inner-product Cl(0,3,0) 0-vector scalar
    @param e23kx_value
      - (k | x field value) - k | e12-bivector (x-axis, e3-dual) coord scalar
    @param e31jy_value
      - (j | y field value) - j | e31-bivector (y-axis, e2-dual) coord scalar
    @param e12iz_value
      - (i | z field value) - i | e12-bivector (z-axis, e1-dual) coord scalar
    */
    GP030(f4 rsw_value = If, f4 e23kx_value = Of, f4 e31jy_value = Of,
      f4 e12iz_value = Of);


    /**
    @brief
        Create a complex 3D number (<inner, v3f(imaginary)>, default <1,0,0,0>)
    @param inner
      - (w | s field value) - inner component, 0th dimension scalar
    @param imaginary
      - (<e12|k,e31|j,e23|i> values) - 3D imaginary vector: <k,j,i> values
    */
    GP030(f4 inner, v3f imaginary);


    /** 
    @brief
        Create a GP030 or pure rotational inputs of the given spherical coords
    @param angle
      - arc of sweep in the imaginary ij plane
    @param azimuth
      - arc of sweep about the right hand plane perpendicular to ij and angle
    @param magnitude
      - radius by which to scale angle and azimuth
    */
    GP030(ang angle, ang azimuth = nullang, f4 magnitude = 1.0f);


    /** 
    @brief
        Create a GP030 from the given euler angle rotation set (optionally scale)
    @param yaw
      - rotation in the e12 bivector (about complement e3 | z-axis | i-plane)
    @param pitch
      - rotation in the e12 bivector (about complement e3 | z-axis | i-plane)
    @param roll
      - 
    \par am magnitude
      - radius by which to scale angle and azimuth
    */
    GP030(ang yaw, ang pitch, ang roll, f4 magnitude = 1.0f);


    /**
    @brief
        Create a 3D complex number from another source 3D complex value
    @param source
      - the Cl(0,3,0) Geometric Product to copy memberwise into the new product
    */
    GP030(const GP030& source);


    /**
    @brief
        Create a complex number from a r-value reference function result
    @param result
      - the complex value reference to surrogate into this
    */
    GP030(GP030&& result) noexcept;


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get a complex number with negated imag values: (a-bi-cj-dk)
    @details
      conventional complex dot products yields (a+bi+cj+dk)*(e+fi+gj+hk) :=
      ae-bf-cg-dk+(af+eb)i+(ag+ec)j+(ah+ed)k+(bg-cf)ij+(df-bh)ki+(ch-gd)jk
      whereas using conjugates instead, such that (a+bi+cj+dk)*(e-fi-gj-hk) :=
      ae+bf+cg+dk, more in line with expectations as the imaginary components
      cancel out, leaving only the scalar real component: expected dot results
    @return
      - complex number with negated imaginary component compared to this
    */
    inline GP030 Conjugate(void) const { return GP030(inner, -imag); }
    // end GP030 GP030::Conjugate(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Complex number with -imag values: (a+bi)(a-bi)=a^2+b^2+0i; i cancels
    @return
      - complex number with negated imaginary component compared to this
    */
    inline GP030 Copy(void) const { return GP030(*this); }
    // end GP030 GP030::Copy(void) const         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Complex memberwise product difference due to imag values squaring to -1
    @details
      - imaginary components square to -1 and accordingly subtract compared with
      conventional scalar dot products yielding the memberwise product sum.
      Use DotConjugate for memberwise product sum, per dot product expectations
    @param other
      - 3D complexgeometric product to be memberwise multiplied with this
    @return
      - complex sum of memberwise products: +s2*s2 -i1*i2 -j1*j2 -k1*k2
    */
    inline f4 Dot(const GP030& other) const
    { return s*other.s - i*other.i - j*other.j - k*other.k; }
    // end f4 GP030::Dot(const GP030&) const     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the complex memberwise product sum: cross cancel -other.imag values
    @return
      - Product sum of complex numbers with negated imaginary values from other
    */
    inline f4 DotConjugate(const GP030& other) const
    { return s*other.s + i*other.i + j*other.j + k*other.k; }
    // end f4 GP030::DotConjugate(const GP030&) const      #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the 3D complex number's i-value (+z-axis normal plane area) scalar
    @return
      - reference to contained i-value coord in 3D complex imag.z f4 field
    */
    inline const f4& I(void) const { return i; }
    // end GP030 GP030::I(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get the complex number's imaginary component value set
    @return
      - reference to contained <i,j,k> coords in complex's imaginary fields
    */
    inline const v3f& Imag(void) const { return imag; }
    // end GP030 GP030::Imag(void) const         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get the complex number's imaginary component value set
    @return
      - reference to contained <i,j,k> coords in complex's imaginary fields
    */
    inline const v3f& Imaginary(void) const { return imag; }
    // end GP030 GP030::Imaginary(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get the 3D complex number's j-value (+y-axis normal plane area) scalar
    @return
      - reference to contained j-value coord in 3D complex imag.y f4 field
    */
    inline const f4& J(void) const { return j; }
    // end GP030 GP030::I(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /** Format a complex for being output as a packed vector notated string
    @brief
      Format for output as a packed multivector string: "{[s],{[k],[j],[i]}}"
    @details
      - considered as am object blob with 0 & 2 k-blades
    @return
      - text formatted to Json standards for later deserialization / output
    */
    std::string Json(void) const;


    /**
    @brief
      Get the 3D complex number's k-value (+x-axis normal plane area) scalar
    @return
      - reference to contained k-value coord in 3D complex imag.x f4 field
    */
    inline const f4& K(void) const { return k; }
    // end GP030 GP030::I(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get the complex displacement / diagonal magnitude: sqrt(x^2 + y^2)
    @details
      - Compare using lengthSquared instead where possible for performance
    @return
      - magnitude of the complex's total displacement: sqrt(x^2 + y^2)
    */
    inline f4 Length(void) const { return SqrtF(LengthSquared()); }
    // end GP030 GP030::Length(void) const       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get squared complex displacement / diagonal length: inner^2 + ~outer^2
    @return
      - squared magnitude of complex vector in its diagonal: inner^2 + ~outer^2
    */
    inline f4 LengthSquared(void) const { return DotConjugate(*this); }
    // end GP030 GP030::LengthSquared(void) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      - set the complex number's real component value
    @param rsw_value
      - the float-point value to be set into the real component field
    @return
      - reference to real shared interior product scalar of non-orthogonality
    */
    inline const f4& R(void) const { return r;
    } // end const f4& GP030::R(void) const      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /** Get the complex number's inner product component value
    @brief
      - get the complex number's inner product component value
    @return
      - reference to the contained real coordinate in complex's inner product
    */
    inline const f4& Real(void) const { return real;
    } // end const f4& GP030::Real(void) const   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /** Complex number, divided by its length and converted to a unit vector
    @brief
      - Complex number, divided by its length and converted to a unit vector
    @return
      - unit displacement in the direction of complex number <r|x,i|y> values
    */
    inline GP030 UnitQuat(void) const { return GP030(*this).Normalize();
    } // end GP030 GP030::UnitQuat(void) const   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get the
    @return
      - reference to the contained x-axis coord. in complex k | e12 bivector
    */
    inline const f4& X(void) const { return x;
    } // end + const f4& GP030::X(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the
    @return
      - reference to the contained y-axis coord. in complex j | e31 bivector
    */
    inline const f4& Y(void) const { return y;
    } // end + const f4& GP030::Y(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the
    @return
      - reference to the contained z-axis coord. in complex i | e23 bivector
    */
    inline const f4& Z(void) const { return z;
    } // end + const f4& GP030::Z(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the w-axis (complex real | scalar inner product) coefficient
    @return
      - reference to the w-axis | complex real | (s)calar | inner product
    */
    inline const f4& W(void) const { return w;
    } // end + const f4& GP030::W(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set pure rotational (imaginary) values from spherical coordinates
    @param angle
      - arc of sweep in the imaginary xy plane, e12 bivector orientation, etc
    @param azimuth
      - arc of sweep about the right hand plane perpendicular to ij and angle
    @param magnitude
      - radius by which to scale angle and azimuth
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& Angle(ang angle, ang azimuth = nullang, f4 magnitude = 1.0f);


    /**
    @brief
        Set quaternion from euler-angle value set (plus scalar option)
    @param angle
      - arc of sweep in the imaginary i bivector (z-axis normal) plane
    @param azimuth
      - arc of sweep about the right hand plane perpendicular to angle in i
    @param magnitude
      - radius by which to scale angle and azimuth
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& Angle(ang yaw, ang pitch, ang roll, f4 magnitude = 1.0f);


    /**
    @brief
        Set the complex number's i vector (z-axis; xy|e12-dual) component value
    @param e12iz_value
      - float-point value to be set into the imaginary-i / z-axis member field
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& I(f4 e12iz_value) { i = e12iz_value; return *this;
    } // end + GP030& GP030::I(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex number's j vector (y-axis; zx|e31-dual) component value
    @param e31jy_value
      - float-point value to be set into the imaginary-j / y-axis member field
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& J(f4 e31jy_value) { i = e31jy_value; return *this;
    } // end + GP030& GP030::J(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex number's k vector (x-axis; yz|e23-dual) component value
    @param e23kx_value
      - float-point value to be set into the imaginary-k / x-axis member field
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& K(f4 e23kx_value) { i = e23kx_value; return *this;
    } // end + GP030& GP030::K(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex number's 3D imaginary component values
    @param imaginary
      - 
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& Imag(const dp::v3f& imaginary) { imag = imaginary; return *this;
    } // end + GP030& GP030::Imaginary(const v3f&)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex number's imaginary <k,j,i> component values
    @param imaginary
      - 
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& Imaginary(const dp::v3f& imaginary)
    {
      imag = imaginary; return *this;
    } // end + GP030& GP030::Imaginary(const v3f&)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        This remaps to the complex coordinate on unit circle (with length 1)
    @details
      - indeterminate null or 0 angle defaults to cos(0) + i*sin(0), ie <1,0>
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& Normalize(void);


    /**
    @brief
        Set the 3D complex number's real component value
    @param rsw_value
      - the float-point value to be set into the real component field
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& R(f4 rsw_value) { r = rsw_value;  return *this;
    } // end + GP030& GP030::R(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex number's real component value
    @param rsw_value
      - the float-point value to be set into the real component field
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& Real(f4 rsw_value) { x = rsw_value; return *this;
    } // end + GP030& GP030::Real(f4)  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex <r|s|w, e23|i|x, e31|j|y, e12|i|z> even basis values
    @param rsw_value
      - 
    @param e23kx_value
      - 
    @param e23kx_value
      - 
    @param e31jy_value
      - 
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& Set(f4 rsw_value, f4 e23kx_value, f4 e31jy_value,
      f4 e12iz_value)
    {
      return R(rsw_value).I(e12iz_value).J(e31jy_value).K(e23kx_value);

    } // end + GP030& GP030::Set(f4, f4, f4, f4) #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex <r|s|w, e23|i|x, e31|j|y, e12|i|z> even basis k-vectors
    @param inner
      - inner scalar product of cumulative rotational cos for this quaternion
    @param imaginary
      - outer 3D bivector blade for this quaternion to use as a 2-vector basis
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& Set(f4 inner, const v3f& imaginary)
    {
      return Real(inner).Imag(imaginary);
    } // end + GP030& GP030::Set(f4, const v3f&)


    /**
    @brief
        Set pure imaginary quaternion from spherical coordinates
    @param angle
      - arc of sweep in imaginary-i | +xy-plane | e12-bivector
    @param azimuth
      - arc of sweep about the right hand plane perpendicular to ij and angle
    @param magnitude
      - radius by which to scale angle and azimuth
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& Set(ang angle, ang azimuth, f4 magnitude = 1.0f);


    /**
    @brief
        Set quaternion geometric product copied from a source quaternion
    @param source
      - the complex number to used for memberwise copying
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& Set(const GP030& source)
    {
      return R(source.r).I(source.i).J(source.j).K(source.k);

    } // end + GP030& GP030::Set(const GP030&)


    /**
    @brief
        Format a complex number for output as a vector notated string
    @details
      - adds padding for uniform spacing: JSON tightly packs CSV elements
    @return
      - text set to ( inner, imag<i,j,k> ), uniformly spaced for legibility
    */
    std::string String(void) const;

    /**
    @brief
        Get the exterior (wedge) product of this geometric product and another
    @param other
      Get the exterior (wedge) product of this geometric product and another
    @return
      - Join of Cl(0,3,0) geometric products' bivectors
    */
    inline v3f Wedge(const GP030& other)
    {
      return  v3f(s*other.k + k*other.s - j*other.i + i*other.j,
                  s*other.j + k*other.i + j*other.s - i*other.k,
                  s*other.i - k*other.j + j*other.k + i*other.s);

    } // end + v3f  GP030::Wedge(const GP030&)  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set (w-axis | scalar inner product | complex real) by 3D cartesian labels
    @param rsw_value
      - Coefficient to use in (w-axis | complex real | scalar inner product)
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& W(f4 rsw_value) { w = rsw_value; return *this;
    } // end + GP030&  GP030::W(f4)    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set (x-axis | e23-bivector | complex i) coefficient in 3D cartesian labels
    @param e23kx_value
      - Coefficient to use in (x-axis | complex k | outer product e23 bivector)
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& X(f4 e23kx_value) { y = e23kx_value; return *this;
    } // end GP030&  GP030::X(f4)      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set (y-axis | e31-bivector | j-plane) coefficient in 3D cartesian labels
    @param e31jy_value
      - Coefficient to use in (y-axis | complex j | outer product e31 bivector)
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& Y(f4 e31jy_value) { y = e31jy_value; return *this;
    } // end GP030&  GP030::Y(f4)      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set (z-axis | e23-bivector | i-plane) coefficient in 3D cartesian labels
    @param e12iz_value
      - 
    @return
      - reference to this 3D complex number for method chaining
    */
    GP030& Z(f4 e12iz_value) { y = e12iz_value; return *this;
    } // end GP030&  GP030::Z(f4)      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Operator Overloads                            */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      Create a negated copy of all complex coordinate values: <-real, -imag>
    @return
      - copy of the complex with <-real, -imag> member values
    */
    inline GP030 operator-(void) const { return GP030(-inner, -outer);
    } // end + GP030& GP030::operator=(const GP030&)       #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Negate complex imaginary components to give the complex conjugate
    @details
      - while (~) is semantically more appropriate / conventional in many ways
      (in GA as well as other places), operator precedence is not customizable
      or friendly to bitwise operators, necessitating heavy obligatory use of
      parentheses for mathematical notation parallels, largely undermining the
      syntactic gains operator overloading might ought to afford to begin with:
      use bitwise operators at your own (peril).
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030 operator!(void) const { return Conjugate() / LengthSquared();
    } // end + GP030& GP030::operator!(void)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set the source complex member values into this complex value fields
    @param source
      - the complex number to have its values copied into this complex number
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& operator=(const GP030& source) { return Set(source);
    } // end + GP030& GP030::operator=(const GP030&)       #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Surrogate a complex value reference returned from a function for this
    @param result
      - the complex reference result from a function from which to steal values
    @return
      - reference to this 3D complex number for method chaining
    */
    inline GP030& operator=(GP030&& result) noexcept { return Set(result);
    } // end + GP030& GP030::operator=(GP030&&) noexcept   #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get a member value from the given subscript
    @param channel
      - { (0|'r'|'s'): r, (1|'k'|'x'): k, (2|'j'|'y'): j, (3|'i'|'z'): i }
    @return
      - copy of the contained dimension member value associated to the channel
    */
    f4 operator[](s2 channel) const;


    /**
    @brief
      Get a member value reference from the given subscript
    @param channel
      - { (0|'r'|'s'): r, (1|'k'|'x'): k, (2|'j'|'y'): j, (3|'i'|'z'): i }
    @return
      - reference to the contained field associated to the subscript number
    */
    f4& operator[](s2 channel);


    /**
    @brief
      Calculate the member-wise addition of 2 complex quaternions
    @param other
      - quaternion to sum into a copy of this, member-wise
    @return
      - copy of member-wise sum of this and the other into a new quaternion
    */                                                                      /**/
    inline GP030 operator+(const GP030& other) const { return Copy() += other;
    } // end + GP030 GP030::operator+(const GP030&) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Add an other complex's values member-wise into this complex's values
    @param other
      - source vector to have memberwise summation performed with this
    @return
      - reference to this 3D complex number for method chaining
    */                                                                      /**/
    inline GP030& operator+=(const GP030& other)
    {
      inner += other.inner;
      outer += other.outer;
      return *this;
    } // end + GP030& GP030::operator+=(const GP030&) const          #^^^^^^^^*/


    /**
    @brief
      Calculate the member-wise difference of 2 quaternions
    @param other
      - source vector to have memberwise difference calculated with this (copy)
    @return
      - memberwise difference of this and the other, copied in a new quaternion
    */                                                                      /**/
    inline GP030 operator-(const GP030& other) const { return Copy() -= other;
    } // end + GP030 GP030::operator-(const GP030&) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Subtract an other quaternion's values member-wise from this's values
    @param other
      - source vector to have negated memberwise summation performed with this
    @return
      - reference to this 3D complex number for method chaining
    */                                                                      /**/
    inline GP030& operator-=(const GP030& other) { return *this += -other;
    } // end + GP030& GP030::operator+=(const GP030&) const          #^^^^^^^^*/


    /**
    @brief
      Scalar quaternion product multiplies each field uniformly by that scalar
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - resultant, member-wise scaled copy of this quaternion's values
    */                                                                      /**/
    inline GP030 operator*(f4 scalar) const { return Copy() *= scalar;
    } // end + GP030 GP030::operator*(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Scalar quaternion product sets all members uniformly scaled by the input
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - reference to this 3D complex number for method chaining
    */                                                                      /**/
    inline GP030& operator*=(f4 scalar) { return Set(scalar*real, scalar*imag);
    } // end + GP030& GP030::operator*=(f4) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get geometric product of this and another quaternion set into a new one
    @param other
      - source complex number to be multiplied with this complex number
    @return
      - scaling & rotation of this by another complex number
    */                                                                      /**/
    GP030 operator*(const GP030& other) const { return Copy() *= other;
    } // end + GP030 GP030::operator*(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set product of this and another complex number (resolving i = sqrt(-1))
    @details
      - Given initial (p)roductOf<w, x, y, z>^(q)uaternions:<w, x, y, z>:
          (pw + px*e12 + py*e31 + pz*e23) ^ (qw + qx*e12 + qy*e31 + qz*e23)

        Perform distribution (heeding any bivectors' anti-commutivity):
       =  pw*qw     + pw*qx*e12     + pw*qy*e31     + pw*qz*e23
        + px*qw*e12 + px*qx*e12^e12 + px*qy*e12^e31 + px*qz*e12^e23
        + py*qw*e31 + py*qx*e31^e12 + py*qy*e31^e31 + py*qz*e31^e23
        + pz*qw*e23 + pz*qx*e23^e12 + pz*qy*e23^e31 + pz*qz*e23^e23

        Consolidate bivector wedge products to single bivectors:
          wherein for any a or b: a^a := -1; a^b = - b^a; i.e. for ab^ab
           := a^b^a^b = - a^b^b^a = - ab^ba = - a^(-1)^a = -(-1)a^a = a^a = -1
       =  pw*qw     + pw*qx*e12       + pw*qy*e31       + pw*qz*e23
        + px*qw*e12 - px*qx*(-1)*(-1) + px*qy*(-1)*e23  + px*qz*(-1)*e13
        + py*qw*e31 + py*qx*(-1)*e32  - py*qy*(-1)*(-1) + py*qz*(-1)*e12
        + pz*qw*e23 + pz*qx*(-1)*e31  + pz*qy*(-1)*e21  - pz*qz*(-1)*(-1)

        Use bivector anti-commutivity to negate left -> right hand orientations:
       =  pw*qw     + pw*qx*e12     + pw*qy*e31     + pw*qz*e23
        + px*qw*e12 - px*qx         - px*qy*e23     + px*qz*e31
        + py*qw*e31 + py*qx*e23     - py*qy         - py*qz*e12
        + pz*qw*e23 - pz*qx*e31     + pz*qy*e12     - pz*qz

        Group like bivector factors / scalars:
       =  pw*qw     - px*qx         - py*qy         - pz*qz
        + pw*qx*e12 + px*qw*e12     - py*qz*e12     + pz*qy*e12
        + pw*qy*e31 + px*qz*e31     + py*qw*e31     - pz*qx*e31
        + pw*qz*e23 - px*qy*e23     + py*qx*e23     + pz*qw*e23

        Factor like-bivectors out to reveal conventional quaternion product:
       =  (pw*qw - px*qx - py*qy - pz*qz)
        + (pw*qx + px*qw - py*qz + pz*qy)e12 (=> ~e12 := e3 := k => z := e3)
        + (pw*qy + px*qz + py*qw - pz*qx)e31 (=> ~e31 := e2 := j => y := e2)
        + (pw*qz - px*qy + py*qx + pz*qw)e23 (=> ~e23 := e1 := i => x := e1)

        or put into subscripts of (p,q) for slight concision / legibility:
       =   ((w,w) - (x,x) - (y,y) - (z,z))
        + (((w,x) + (x,w) + (z,y) - (y,z)) e12
        +  ((w,y) + (y,w) + (x,z) - (z,x)) e31
        +  ((w,z) + (z,w) + (y,x) - (x,y)) e23)
          
        i.e, made more concise, this maps onto the inner and outer products:
       =  (p.Dot(q)) + (p.Wedge(q))
       
       => [s,<i,j,k>] -> [s,<e3,e2,e1>]: quaternions just got defined backwards

    @param other
      - source complex number to be multiplied with this complex number
    @return
      - reference to this 3D complex number for method chaining
    */                                                                      /**/
    inline GP030& operator*=(const GP030& other)
    {
      return Real(Dot(other)).Imag(Wedge(other));
    } // end + GP030& GP030::operator*=(const GP030&)      #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divides real & imaginary values uniformly by divisor, returning result
    @details
      - (real, imag)/d = (real, imag)*(1/d) = (real/d, imag/d)
    @param divisor
      - amount by which real and imaginary values are to be uniformly divided
    @return
      - resultant, member-wise scaled copy of this complex's values
    */                                                                      /**/
    inline GP030 operator/(f4 divisor) const { return Copy() *= InvF(divisor);
    } // end + GP030 GP030::operator/(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide real and imaginary values uniformly by divisor, setting result
    @details
      - (real, imag)/d = (real, imag)*(1/d) = (real/d, imag/d)
    @param divisor
      - amount by which real and imaginary values are to be uniformly divided
    @return
      - reference to this 3D complex number for method chaining
    */                                                                      /**/
    inline GP030& operator/=(f4 divisor) { return (*this) *= InvF(divisor);
    } // end + GP030 GP030::operator/=(f4)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this complex number by another complex number, returning result
    @param other
      - complex number by which this complex number is to be divided
    @return
      - resultant, member-wise scaled copy of this complex's values
    */                                                                      /**/
    inline GP030 operator/(const GP030& other) const { return Copy() /= other;
    } // end + GP030 GP030::operator/(const GP030&) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this complex number by another complex number, setting result
    @details
      - (r1+imag1)/(r2+imag2)    = (r1+imag1)/(r2+imag2) * 1
      = (r1+imag1)/(r2+imag2)    * (r2-imag2)/(r2-imag2)
      =  (r1+imag1)(r2-imag2)    / (r2+imag2)(r2-imag2)
      = this.DotConjugate(other) / other.DotConjugate(other)
      = this.DotConjugate(other) / other.LengthSquared()
    @param other
      - complex number by which this complex number is to be divided
    @return
      - reference to this 3D complex number for method chaining
    */                                                                      /**/
    inline GP030& operator/=(const GP030& other)
    {
      return (*this) *= !other;
    } // end + GP030 GP030::operator/=(f4)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  }; // end GP030 union / struct / class type declaration

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                       Helper Function Declarations                       */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  /**
  @brief
      Left hand scalar multiplication scales all members of rhs
  @details
    - Scalars are still commutative even if k-vectors only anti-commute
  @param scalar
    - scalar amount by which to multiply all values of right-hand side
  @param rhs
    - right-hand side argument to be copied and scaled in all fields by scalar
  @return
    - copy of rhs v2f's values, scaled by scalar in <r, e12, e31, e23>
  */                                                                        /**/
  inline GP030 operator*(f4 scalar, const GP030& rhs)
  { return GP030(rhs * scalar); } // end GP030 operator*(f4, const GP030&)    */


  /**
  @brief
      Confirm if 2 complex numbers are relatively equal in real and imag values
  @param lhs
    - left hand side to be compared memberwise with right hand for equality
  @param rhs
    - right hand side to be compared memberwise with left hand for equality
  @return
    - true only if all members are in close proximity of one another
  */
  bool operator==(const GP030& lhs, const GP030& rhs);


  /**
  @brief
      Confirm if 2 complex numbers are not equal in either real or imag values
  @param lhs
    - left hand side to be compared memberwise with right hand for inequality
  @param rhs
    - right hand side to be compared memberwise with left hand for inequality
  @return
    - true if any members are not in close proximity of one another
  */
  bool operator!=(const GP030& lhs, const GP030& rhs);


  /**
  @brief
      Output the string version of each of the complex elements' data
  @param output
    - stream to receive the vector string and and carry contents for output
  @param complex
    - number to have the real & imag values be converted to text based output
  @return
    - reference to the output stream object having the vector fed in
  */
  std::ostream& operator<<(std::ostream& output, const GP030& complex);


  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                            Helper Constants                             */
  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  //! Zero vector in real and imaginary dimensions; error state reserved value
  extern const GP030& nullGP030;

  //! Quaternion alias for Geometric product of even Cl(0,3,0) subalgebra
  typedef GP030 Quat;

  //! Quaternion alias for Geometric product of even Cl(0,3,0) subalgebra
  typedef GP030 Quaternion;

} // end dp namespace