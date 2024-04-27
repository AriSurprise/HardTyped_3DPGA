/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  GP301.h
Purpose: G(3,0,1) 3+1 dimens, even grade blade-sets, aka Dual Quaternions
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
#include "../Math/v3f.h"    // Bivector members read as float 2-blade triplets
#include "../Math/v4f.h"    // Dual quaternion read of latter member layout
#include "../Math/v6f.h"    // Bivector members read as 1 full, 6D 2-blade
#include "../Math/GP030.h"  // Quaternion read of subalgebra first half


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Forward References                             */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


namespace dp  //! Contents for use within DigiPen CS / MAT class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  union GP030; // Quaternion / G(0,3,0) even subalgebra: params / arithmetic

  union GP301 //! G(3,0,1) product: even sub-algebra, screw motion, motor/rotor
  {
  public:

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                           Public Members                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    struct {
      f4 l;     //! Interior (dot / real) product: e0123's non-orthogonality
      f4 e23;   //! e2^e3 oriented 2-vector planar area scalar
      f4 e31;   //! e3^e1 oriented 2-vector planar area scalar
      f4 e12;   //! e1^e2 oriented 2-vector planar area scalar
      f4 e01;   //! e0^e1 affine dual 2-vector planar area scalar
      f4 e02;   //! e2^e0 affine dual 2-vector planar area scalar
      f4 e03;   //! e0^e3 affine dual 2-vector planar area scalar
      f4 e0123; //! e0^01^e2^e3 4-vector 4D pseudoscalar / basis study number
    };
    struct {
      f4 scalar;  //! 4D real / scalar coefficient   (Interior comb. axis size)
      v6f bivector; //! 4D bivector coefficients   (right-hand nCr(4,2) planes)
      f4 quadrivector; //! 4D study number / pseudoscalar   (basis ext. scalar)
    };
    struct {
      GP030 real; //! Real / imaginary complex first basis half <r,e12,e31,e23>
      v4f dual;   //! Geometric e01, e02, e03 bivector plane area scalar set
    };
    struct {
      f4 shared;  //! Basis' shared real scalar        (Interior comb. axis size)
      v3f moment; //! Complex imaginary scalars  ([e1,e3] complex dual bivectors)
      v3f dir;    //! Dual affine axis scalars  (e0 ^ [e1,e3] dual bivectors)
      f4 screw;   //! Basis' study number / pseudoscalar  (basis exterior scalar)
    };
    struct {
      f4 inner;    //! Geometric int. product angle non-orthogonality scalar
      v3f complex; //! Geometric e23, e31, e12 bivector plane area scalar set
      v3f dualized;//! Geometric e01, e02, e03 bivector plane area scalar set
      f4 det;      //! Geometric pseudoscalar / study number / det scalar
    };
    struct {
      f4 inr;  //! Geometric interior product angle non-orthogonality scalar
      v3f cx;  //! Geometric exterior product bivectors area scalar set
      v3f dl;  //! Geometric exterior product bivector plane area scalar set
      f4 I301; //! Geometric exterior product bivector plane area scalar set
    };
    struct {
      f4 s;   //! Dual Quaternion label: axes interior real scalar
      f4 k;   //! Dual Quaternion label: e01 axis's dual, rh-plane's area
      f4 j;   //! Dual Quaternion label: e02 axis's dual, rh-plane's area
      f4 i;   //! Dual Quaternion label: e03 axis's dual, rh-plane's area
      f4 ek;  //! Dual Quaternion label: k(e23)'s affine complement
      f4 ej;  //! Dual Quaternion label: j(e31)'s affine complement
      f4 ei;  //! Dual Quaternion label: i(e12)'s affine complement
      f4 e;   //! Dual Quaternion label: 4D pseudoscalar / basis study number
    };
    struct {
      f4 r;   //! Cartesian alias for axes interior, shared real scalar value
      f4 u;   //! Cartesian alias of complex.k (e23 bivector: e01 dual) coeff
      f4 v;   //! Cartesian alias of complex.j (e31 bivector: e02 dual) coeff
      f4 n;   //! Cartesian alias of complex.i (e12 bivector: e03 dual) coeff
      f4 x;   //! Cartesian alias of dual.x (e01 bivector: e23 dual) coeff
      f4 y;   //! Cartesian alias of dual.y (e02 bivector: e31 dual) coeff
      f4 z;   //! Cartesian alias of dual.z (e01 bivector: e12 dual) coeff
      f4 w;   //! Cartesian alias of basis blade / psuedoscalar / e0123 / det
    };

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                             Constructors                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Create a complex 3D number (<inner, v3f(imaginary)>, default <1,0,0,0>)
    @param rs_value
      - (inner | l | s field value) - inner-product Cl(0,3,0) 0-vector scalar
    @param 
      - ( |  field value) - k | e12-bivector (x-axis, e3-dual) coord scalar
    @param e31jy_value
      - (j | y field value) - j | e31-bivector (y-axis, e2-dual) coord scalar
    @param e12iz_value
      - (i | z field value) - i | e12-bivector (z-axis, e1-dual) coord scalar
    */
    GP301(f4 rs_value = If,
        f4 e12iz_value = Of, f4 e31jy_value = Of, f4 e23kx_value = Of,
        f4 ek01u_value = Of, f4 ej20v_value = Of, f4 ei03t_value = Of,
        f4 e0123p_value = Of);


    /**
    @brief
        Create a complex 3D number (<inner, v3f(imaginary)>, default <1,0,0,0>)
    @param interior
      - (l | s field value) - inner component, 0th dimension scalar
    @param complex_bivectors
      - (<e12|k,e31|j,e23|i> values) - 3D imaginary vector: <k,j,i> values
    @param dual_bivectors
      - (<e01|k,e02|j,e03|i> values) - 3D dual vector: <ek,ej,ei> values
    @param pseudoscalar
      - (e0123 | pseudoscalar value) - 1D I determinant term of G(3,0,1) space
    */
    GP301(f4 interior,
      v3f complex_bivectors, v3f dual_bivectors,
      f4 pseudoscalar);


    /**
    @brief
        Create a complex 4D number from a pair of quaternions presumed dualized
    @param quaternion
      - even subalgebra of rotational subspace of this affine even subalgebra
    @param qDual
      - even subalgebra to use as dualized portion of this even subalgebra
    */
    GP301(const GP030& quaternion, const GP030& qDual);


    /** 
    @brief
        Create a GP301 or pure rotational inputs of the given spherical coords
    @param angle
      - arc of sweep in the imaginary ij plane
    @param azimuth
      - arc of sweep about the right hand plane perpendicular to ij and angle
    @param magnitude
      - radius by which to scale angle and azimuth
    */
    GP301(ang angle, ang azimuth = nullang, f4 magnitude = 1.0f);


    /** 
    @brief
        Create a GP301 from the given euler angle rotation set (optionally scale)
    @param yaw
      - rotation in the e12 bivector (about complement e3 | z-axis | i-plane)
    @param pitch
      - rotation in the e12 bivector (about complement e3 | z-axis | i-plane)
    @param roll
      - 
    \par am magnitude
      - radius by which to scale angle and azimuth
    */
    GP301(ang yaw, ang pitch, ang roll, f4 magnitude = 1.0f);


    /**
    @brief
        Create a geometric product from another source 3D complex value
    @param source
      - the Cl(0,3,0) Geometric Product to copy memberwise into the new product
    */
    GP301(const GP301& source);


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get a copy of this with with negated imag & det values: (a-c<>+d<>-b)
    @details
      In general GA contextualizes the concept generalization of conjugates
      fairly simply: since a^b := -b^a, the treament which produces -b^a is the
      conjugate of a^b, canceling out extraneous factors to produce the real
      result as desired when taking squared terms to produce euclidean length.
      Treated as an 8 tuple there are many conjugates one might take of a DQuat
      the complex extension in 3+1D has 3 possible interpretations
    @return
      - geometric product with negated imaginary component compared to this
    */
    inline GP301 Conjugate(void) const
    {
      return GP301(inner, -complex, dualized, -det);
    } // end GP301 GP301::Conjugate(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Geometric product with memberwise value copies of this
    @return
      - geometric product with values copied from components of this
    */
    inline GP301 Copy(void) const
    {
      return GP301(*this);
    } // end GP301 GP301::Copy(void) const       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Non-dual memberwise product difference due to bivector anti-commutivity
    @param other
      - geometric product to be memberwise multiplied with this
    @return
      - non-dual memberwise products' sum: +s2*s2 -i1*i2 -j1*j2 -k1*k2
    */
    inline f4 Dot(const GP301& other) const
    {
      return l*other.l + e23*other.e23 + e31*other.e31 + e12*other.e12;
    } // end f4 GP301::Dot(const GP301&) const   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the memberwise product sum with cross cancelled anti-commutivity
    @return
      - Product sum of non-dual hyper-real numbers: euclidean square norm
    */                                                                      /**/
    inline f4 DotSelf(void) const
    {
      return l*l + e23*e23 + e31*e31 + e12*e12;
    } // end f4 GP301::DotSelf(const GP301&) const         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get product's i-value (+xy-plane's area) scalar
    @return
      - reference to contained i-value coord in 3D complex imag.z f4 field
    */                                                                      /*
    inline const f4& I(void) const
    {
      return e12;
    } // end GP301 GP301::I(void) const          #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get non-dual bivector members (e23, e31, e12) in complex labels
    @return
      - reference to contained <i,j,k> coords in complex's imaginary fields
    */                                                                      /**/
    inline const v3f& Imag(void) const
    {
      return moment;
    } // end GP301 GP301::Imag(void) const       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get product's non-dual bivector members (e23, e31, e12) in complex labels
    @return
      - reference to contained <i,j,k> coords in complex's imaginary fields
    */                                                                      /**/
    inline const v3f& Imaginary(void) const
    {
      return moment;
    } // end GP301 GP301::Imaginary(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the geometric product's inverse resulting in 1 when taken with this
    @return
      - product which when taken with this, cancels to a <1,<0>,0> result
    */                                                                      /**/
    inline GP301 Inverse(void) const
    {
      return Reverse() * InvF(MagSq());
    } // end GP301 GP301::Imaginary(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get product's j-value (-xz-plane's area) scalar
    @return
      - reference to contained j-value coord in 3D complex imag.y f4 field
    */                                                                      /**/
    inline const f4& J(void) const
    {
      return e31;
    } // end const f4& GP301::J(void) const      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


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
      Get the geometric product's k-value (+x-axis normal plane area) scalar
    @return
      - reference to contained k-value coord in 3D complex imag.x f4 field
    */
    inline const f4& K(void) const
    {
      return e23;
    } // end const f4& GP301::K(void) const      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get the complex displacement / diagonal magnitude: sqrt(x^2 + y^2)
    @details
      - Compare using lengthSquared instead where possible for performance
    @return
      - magnitude of the complex's total displacement: sqrt(x^2 + y^2)
    */
    inline f4 Mag(void) const
    {
      return SqrtF(MagSq());
    } // end GP301 GP301::Mag(void) const        #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get squared magnitude or euclidean length: l^2 + e23^2 + e31^2 + e12^2
    @return
      - diagonal magnitude^2 of component measure: l^2 + e23^2 + e31^2 + e12^2
    */
    inline f4 MagSq(void) const
    {
      return DotSelf();
    } // end GP301 GP301::MagSq(void) const      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      - set the geometric product's inner, scalar component value
    @param rs_value
      - the float-point value to be set into the real component field
    @return
      - reference to real shared interior product scalar of non-orthogonality
    */
    inline const f4& R(void) const
    {
      return r;
    } // end const f4& GP301::R(void) const      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the geometric product's real (1st) quaternion value
    @return
      - reference to the contained real coordinate in complex's inner product
    */
    inline const GP030& Real(void) const { return real;
    } // end const f4& GP301::Real(void) const   #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get reverse-oriented, equivalent geometric product to this screw motion
    @details
      =>  e3210 + e30 + e20 + e10 + e21 + e13 + e32 + l
        = l + e32 + e13 + e21 + e10 + e20 + e30 + e3210
        = l - e23 - e31 - e12 - e01 - e02 - e03 + e0123
      ==  (-1)^{0(0-1)/2}<M>[0] + (-1)^{2(2-1)/2}<M>[2] + (-1)^{4(4-1)/2}<M>[4]
        = (-1)^{0}<M>[0] + (-1)^{1}<M>[2] + (-1)^{6}<M>[4]
        = <M>[0] - <M>[2] + <M>[4]
        = l -(e23 + e31 + e12 + e01 + e02 + e03)+ e0123
      or= ((!(0&2)<<1)-1)<M>[0] + ((!(2&2)<<1)-1)<M>[2] + ((!(4&2)<<1)-1)<M>[4]
      or= (((!0)<<1)-1)<M>[0] + (((!1)<<1)-1)<M>[2] + (((!0)<<1)-1)<M>[4]
        = ((1 << 1) - 1)<M>[0] + ((0 << 1) - 1)<M>[2] + ((1 << 1) - 1)<M>[4]
        = (2 - 1)<M>[0] + (0 - 1)<M>[2] + (2 - 1)<M>[4]
        = +<M>[0] - <M>[2] + <M>[4]
    @return
      - memberwise negated geo. product; opposed orientation equivalent to this
    */
    inline GP301 Reverse(void) const
    {
      return GP301(l, -e23, -e31, -e12, -e01, -e02, -e03, e0123);
    } // end GP301 GP301::Reverse(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Copy of this, divided by its length and converted to a unit vector
    @return
      - unit displacement in the direction of geometric product <r|x,i|y> values
    */
    inline GP301 UnitDQuat(void) const { return Copy().Normalize();
    } // end GP301 GP301::UnitDQuat(void) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get the
    @return
      - reference to the contained x-axis coord. in complex k | e12 bivector
    */
    inline const f4& X(void) const { return e01;
    } // end + const f4& GP301::X(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the
    @return
      - reference to the contained y-axis coord. in complex j | e31 bivector
    */
    inline const f4& Y(void) const { return e02;
    } // end + const f4& GP301::Y(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the
    @return
      - reference to the contained z-axis coord. in complex i | e23 bivector
    */
    inline const f4& Z(void) const { return e03;
    } // end + const f4& GP301::Z(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get the l-axis (complex real | scalar inner product) coefficient
    @return
      - reference to the l-axis | complex real | (s)calar | inner product
    */
    inline const f4& W(void) const { return e0123;
    } // end + const f4& GP301::W(void) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the product's i vector (z-axis; xy|e12-dual) component value
    @param e12iz_value
      - float-point value to be set into the imaginary-i / z-axis member field
    @return
      - reference to this geometric product for method chaining
    */                                                                      /*
    inline GP301& I(f4 e12iz_value)
    {
      i = e12iz_value;
      return *this;
    } // end + GP301& GP301::I(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the product's j vector (y-axis; zx|e31-dual) component value
    @param e31jy_value
      - float-point value to be set into the j-plane / dual-y-axis member field
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& J(f4 e31jy_value)
    {
      e31 = e31jy_value;
      return *this;
    } // end + GP301& GP301::J(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the product's k vector (x-axis; yz|e23-dual) component value
    @param e23kx_value
      - float-point value to be set into the k-plane / dual-x-axis member field
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& K(f4 e23kx_value)
    {
      e23 = e23kx_value;
      return *this;
    } // end + GP301& GP301::K(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the quaternion numbers' 3D axis values with imaginary coefs
    @param imaginary
      - imaginary coefficient triplet to read into real bivectors <e23,e31,e12>
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    GP301& Imag(const dp::v3f& imaginary)
    {
      complex = imaginary;
      return *this;
    } // end + GP301& GP301::Imaginary(const v3f&)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the product's imaginary <k,j,i> component values
    @param imaginary
      - 
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    GP301& Imaginary(const dp::v3f& imaginary)
    {
      complex = imaginary;
      return *this;
    } // end + GP301& GP301::Imaginary(const v3f&)         #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        This remaps to the complex coordinate on unit circle (with length 1)
    @details
      - indeterminate null or 0 angle defaults to cos(0) + i*sin(0), ie <1,0>
    @return
      - reference to this geometric product for method chaining
    */
    GP301& Normalize(void);


    /**
    @brief
        Set the geometric product's real component value
    @param rs_value
      - the float-point value to be set into the real component field
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& R(f4 rs_value)
    {
      r = rs_value;
      return *this;
    } // end + GP301& GP301::R(f4)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the product's real component value
    @param rs_value
      - the float-point value to be set into the real component field
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& Real(f4 rs_value)
    {
      r = rs_value;
      return *this;
    } // end + GP301& GP301::Real(f4)  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex <r|s|l, e23|i|x, e31|j|y, e12|i|z> even basis values
    @param rs_value
      - float value to be set into the real component field
    @param e23kx_value
      - float value to be set into e23 component (k-plane or e01 dual) field
    @param e31jy_value
      - float value to be set into e31 component (j-plane or e02 dual) field
    @param e12iz_value
      - float value to be set into e12 component (i-plane or e03 dual) field
    @param ek01x_value
      - float value to be set into the e01 component (dual-x or e23 dual) field
    @param ej02y_value
      - float value to be set into the e02 component (dual-y or e31 dual) field
    @param ei03z_value
      - float value to be set into the e03 component (dual-z or e23 dual) field
    @param e0123Iw_value
      - float value to be set into the e0123 component (pseudoscalar) field
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& Set(f4 rs_value, f4 e23kx_value, f4 e31jy_value,
      f4 e12iz_value, f4 ek01x_value, f4 ej02y_value, f4 ei03z_value,
      f4 e0123Iw_value)
    {
      l = rs_value;
      e23 = (e23kx_value);
      e31 = (e31jy_value);
      e12 = (e12iz_value);
      e01 = (ek01x_value);
      e02 = (ej02y_value);
      e03 = (ei03z_value);
      I301 = (e0123Iw_value);
      return  (*this);

    } // end + GP301& GP301::Set(f4, f4, f4, f4) #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set the complex <r|s|l, e23|i|x, e31|j|y, e12|i|z> even basis k-vectors
    @param inner
      - inner scalar product of cumulative rotational cos for this quaternion
    @param imaginary
      - outer 3D bivector blade for this quaternion to use as a 2-vector basis
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& Set(f4 inner, const v3f& moment, const v3f& direction,
      f4 screw)
    {
      return Set(inner, moment.x, moment.y, moment.z,
        direction.x, direction.y, direction.z, screw);
    } // end + GP301& GP301::Set(f4, const v3f&)


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
      - reference to this geometric product for method chaining
    */
    GP301& Set(ang angle, ang azimuth, f4 magnitude = 1.0f);


    /**
    @brief
        Set quaternion geometric product copied from a source quaternion
    @param source
      - the product to used for memberwise copying
    @return
      - reference to this geometric product for method chaining
    */
    inline GP301& Set(const GP301& source)
    {
      return Set(source.l, source.e23, source.e31, source.e12,
                 source.e01, source.e02, source.e03, source.I301);

    } // end + GP301& GP301::Set(const GP301&)


    /**
    @brief
        Format a I301 for output as a vector notated string
    @details
      - adds padding for uniform spacing: JSON tightly packs CSV elements
    @return
      - text set to ( inner, imag<i,j,k> ), uniformly spaced for legibility
    */
    std::string String(void) const;

    /**
    @brief
        Get the commutator (cross) product of this geometric product and another
    @param other
      - source rotor to have commutator product taken with this
    @return
      - Join of G(3,0,1) geometric products' bivectors
    */
    inline v6f Commute(const GP301& other) const
    {
      return  v6f
        ((l*other.e23 + e23 * other.l) + (e12*other.e31 - e31*other.e12)),
        ((l*other.e31 + e31 * other.l) + (e23*other.e12 - e12*other.e23)),
        ((l*other.e12 + e12 * other.l) + (e31*other.e23 - e23*other.e31)),
        ((l*other.e01 + e01 * other.l) + (e23*other.e02 + e31*other.e03)
       - (e03*other.e31 + e02*other.e23) - (e0123*other.e12 + e12*other.e0123)),
        ((l*other.e02 + e02*other.l) + (e0123*other.e31 + e31*other.e0123)
       + (e01*other.e23 + e12*other.e03) - (e03*other.e12 + e23*other.e01)),
        ((l*other.e03 + e03*other.l) + (e01*other.e31 + e02*other.e12)
       - (e12*other.e02 + e31*other.e01) - (e23*other.e0123 + e0123*other.e23));

    } // end + v3f  GP301::Commute(const GP301&)  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Get the exterior (wedge) product of this geometric product and another
    @param other
      - source rotor to have wedge product taken with this
    @return
      - Join of G(3,0,1) geometric products' quadrivector
    */
    inline f4 Wedge(const GP301& other) const
    {
      return (l*other.e0123 + e0123*other.l) + (e23*other.e03 + e03*other.e23)
           + (e12*other.e01 + e01*other.e12) - (e31*other.e02 + e02*other.e31);

    } // end + v3f  GP301::Commute(const GP301&)  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set (l | determinant | basis-blade | pseudoscalar) by 3D cartesian labels
    @param e0123Iw_value
      - Coefficient to use in (l | determinant | basis-blade | pseudoscalar)
    @return
      - reference to this geometric product for method chaining
    */
    GP301& W(f4 e0123pssw_value)
    {
      e0123 = e0123pssw_value;
      return *this;
    } // end + GP301&  GP301::W(f4)    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set (dual-x-axis | e01-bivector) coefficient in 3D cartesian labels
    @param ek01x_value
      - Coefficient to use in (dual-x-axis | commutator product e01 bivector)
    @return
      - reference to this geometric product for method chaining
    */
    GP301& X(f4 ek01x_value)
    {
      e01 = ek01x_value;
      return *this;
    } // end GP301&  GP301::X(f4)      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set (dual-y-axis | e02-bivector) coefficient in 3D cartesian labels
    @param ej02y_value
      - Coefficient to use in (dual-y-axis | commutator product e02 bivector)
    @return
      - reference to this geometric product for method chaining
    */
    inline GP301& Y(f4 ej02y_value)
    {
      e02 = ej02y_value;
      return *this;
    } // end GP301&  GP301::Y(f4)      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Set (dual-z-axis | e03-bivector) coefficient in 3D cartesian labels
    @param ei03z_value
      - 
    @return
      - reference to this geometric product for method chaining
    */
    GP301& Z(f4 ei03z_value)
    {
      e03 = ei03z_value;
      return *this;
    } // end GP301&  GP301::Z(f4)      #^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Operator Overloads                            */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      Create a negated copy of all complex coordinate values: <-real, -imag>
    @return
      - copy of the complex with uniformly negated member values
    */
    inline GP301 operator-(void) const
    { return GP301(-inner, -complex, -dualized, -det);
    } // end + GP301& GP301::operator=(const GP301&)       #^^^^^^^^^#^^^^^^^^*/


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
      - reference to this geometric product for method chaining
    */
    inline GP301 operator!(void) const { return Inverse();
    } // end + GP301& GP301::operator!(void)     #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set the source complex member values into this complex value fields
    @param source
      - the product to have its values copied into this product
    @return
      - reference to this geometric product for method chaining
    */
    inline GP301& operator=(const GP301& source) { return Set(source);
    } // end + GP301& GP301::operator=(const GP301&)       #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Surrogate a complex value reference returned from a function for this
    @param result
      - the complex reference result from a function from which to steal values
    @return
      - reference to this geometric product for method chaining
    */
    inline GP301& operator=(GP301&& result) noexcept { return Set(result);
    } // end + GP301& GP301::operator=(GP301&&) noexcept   #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Get a member value from the given subscript
    @param channel
      - 
    @return
      - copy of the contained dimension member value associated to the channel
    */
    f4 operator[](s2 channel) const
    {
      switch (channel)
      {
      case 'R': case 'L': case 'D': case -8:// case 'S': // octal 123 also 83
        return -l;
      case 'r': case 'l': case 'd': case 's': case 0: case 8:
        return l;
      case 'X': case 10: case 'A': case -1:
        return -e01;
      case 'x': case -10: case 'a': case 1:
        return e01;
      case 'Y': case 20: case 'B': case -2:
        return -e02;
      case 'y': case -20: case 'b': case 2:
        return e02;
      case 'Z': case 30: case 'C': case -3:
        return -e03;
      case 'z': case -30: case 'c': case 3:
        return e03;
      case 'N': case 'I': case -4: case 32: case -23:
        return -e23;
      case 'n': case 'i': case 4: case -32: case 23:
        return e23;
      case 'V': case 'J': case -5: case 13: case -31:
        return -e31;
      case 'v': case 'j': case 5: case 31: case -13:
        return e31;
      case 'U': case 'K': case -6: case 21: case -12:
        return -e12;
      case 'u': case 'k': case 6: case 12: case -21:
        return e12;
      case 'W': case -7: case 3210:
        return -e0123;
      case 'w': case 7: case 0123: case 123:
        return e0123;
      }
      channel = ModC((s1)channel, 8);
      switch (channel)
      {
      case 7:   return e0123;
      case 6:   return e12;
      case 5:   return e31;
      case 4:   return e23;
      case 3:   return e03;
      case 2:   return e02;
      case 1:   return e01;
      default:  return l;
      }
    } // end + f4 GP301::operator[](s2) const    #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get a member value reference from the given subscript
    @details
        
    @param channel
      - Number or letter to associate with the given channel label
    @return
      - Reference to the contained field associated to the subscript number
    */
    inline f4& operator[](s2 channel)
    {
      switch (channel)
      {
      case 'R': case 'L': case 'D': case -8:// case 'S': // octal 123 also 83
      case 'r': case 'l': case 'd': case 's': case 0: case 8:
        return l;
      case 'X': case 10: case 'A': case -1:
      case 'x': case -10: case 'a': case 1:
        return e01;
      case 'Y': case 20: case 'B': case -2:
      case 'y': case -20: case 'b': case 2:
        return e02;
      case 'Z': case 30: case 'C': case -3:
      case 'z': case -30: case 'c': case 3:
        return e03;
      case 'N': case 'I': case -4: case 32: case -23:
      case 'n': case 'i': case 4: case -32: case 23:
        return e23;
      case 'V': case 'J': case -5: case 13: case -31:
      case 'v': case 'j': case 5: case 31: case -13:
        return e31;
      case 'U': case 'K': case -6: case 21: case -12:
      case 'u': case 'k': case 6: case 12: case -21:
        return e12;
      case 'W': case -7: case 3210:
      case 'w': case 7: case 0123: case 123:
        return e0123;
      }
      channel = ModC((s1)channel, 8);
      switch (channel)
      {
      case 7:   return e0123;
      case 6:   return e12;
      case 5:   return e31;
      case 4:   return e23;
      case 3:   return e03;
      case 2:   return e02;
      case 1:   return e01;
      default:  return l;
      }
    } // end + f4& GP301::operator[](s2)         #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Calculate the member-wise addition of 2 complex quaternions
    @param other
      - quaternion to sum into a copy of this, member-wise
    @return
      - copy of member-wise sum of this and the other into a new quaternion
    */                                                                      /**/
    inline GP301 operator+(const GP301& other) const { return Copy() += other;
    } // end + GP301 GP301::operator+(const GP301&) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Add an other complex's values member-wise into this complex's values
    @param other
      - source vector to have memberwise summation performed with this
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& operator+=(const GP301& other)
    {
      inner += other.inner;
      complex += other.complex;
      dualized += other.dualized;
      det += other.det;
      return *this;
    } // end + GP301& GP301::operator+=(const GP301&) const          #^^^^^^^^*/


    /**
    @brief
      Calculate the member-wise difference of 2 quaternions
    @param other
      - source vector to have memberwise difference calculated with this (copy)
    @return
      - memberwise difference of this and the other, copied in a new quaternion
    */                                                                      /**/
    inline GP301 operator-(const GP301& other) const
    {
      return Copy() -= other;
    } // end + GP301 GP301::operator-(const GP301&) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Subtract an other quaternion's values member-wise from this's values
    @param other
      - source vector to have memberwise difference calculated with this
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& operator-=(const GP301& other)
    {
      return *this += -other;
    } // end + GP301& GP301::operator+=(const GP301&) const          #^^^^^^^^*/


    /**
    @brief
      Scalar quaternion product multiplies each field uniformly by that scalar
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - resultant, member-wise scaled copy of this quaternion's values
    */                                                                      /**/
    inline GP301 operator*(f4 scalar) const { return Copy() *= scalar;
    } // end + GP301 GP301::operator*(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Scalar quaternion product sets all members uniformly scaled by the input
    @param scalar
      - scalar amount by which to multiply all member values
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& operator*=(f4 scalar)
    {
      return Set
      (
        scalar*l,
        scalar*e23, scalar*e31, scalar*e12, scalar*e01, scalar*e02, scalar*e03,
        scalar*e0123
      );
    } // end + GP301& GP301::operator*=(f4) const          #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Get geometric product of this and another quaternion set into a new one
    @param other
      - source product to be multiplied with this product
    @return
      - transformation of this by another geometric product
    */                                                                      /**/
    inline GP301 operator*(const GP301& other) const
    {
      return Copy() *= other;
    } // end + GP301 GP301::operator*(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
      Set product of this and another geometric product (resolving i = sqrt(-1))
    @details
      Given initial
        this := (d)ual:<r,u,v,n,x,y,z,w> * other := (q)uat:<r,u,v,n,x,y,z,w>
     => (d.r*l+d.u*e23+d.v*e31+d.n*e12+d.x*e01+d.y*e02+d.z*e03+d.w*I)
      * (q.r*l+q.u*e23+q.v*e31+q.n*e12+q.x*e01+q.y*e02+q.z*e03+q.w*I)

      (fitting to 80 char width takes some syntax shortcuts: sorry)
      Distribute (mind bivector anti-commutivity; d*q := dq order of scalars):
     = rr*1  +ru*e23  +rv*e31  +rn*e12  +rx*e01  +ry*e02  +rz*e03  +rw*I
      +ur*e23+uu*e2323+uv*e2331+un*e2312+ux*e2301+uy*e2302+uz*e2303+uw*e23*I
      +vr*e31+vu*e3123+vv*e3131+vn*e3112+vx*e3101+vy*e3102+vz*e3103+vw*e31*I
      +nr*e12+nu*e1223+nv*e1231+nn*e1212+nx*e1201+ny*e1202+nz*e1203+nw*e12*I
      +xr*e01+xu*e0123+xv*e0131+xn*e0112+xx*e0101+xy*e0102+xz*e0103+xw*e01*I
      +yr*e02+yu*e0223+yv*e0231+yn*e0212+yx*e0201+yy*e0202+yz*e0203+yw*e02*I
      +zr*e03+zu*e0323+zv*e0331+zn*e0312+zx*e0301+zy*e0302+zz*e0303+zw*e03*I
      +wr*I  +wu*I*e23+wv*I*e31+wn*I*e12+wx*I*e01+wy*I*e02+wz*I*e03+ww*e03*I*I
      (where e0123 := I which is the basis blade wedging all vectors)

      Re-order like wedges to be adjacent; moves negate per anti-commutivity:
     = rr*1  +ru*e23  +rv*e31  +rn*e12  +rx*e01  +ry*e02  +rz*e03  +rw*I
      +ur*e23-uu*e2233-uv*e1233+un*e3122+ux*e0123-uy*e0322+uz*e0233-uw*e012233
      +vr*e31+vu*e1233-vv*e1133-vn*e2311+vx*e0311+vy*e0123-vz*e0133-vw*e021133
      +nr*e12-nu*e3122+nv*e2311-nn*e1122-nx*e0211+ny*e0122+nz*e0123-nw*e031122
      +xr*e01+xu*e0123-xv*e0311+xn*e0211-xx*e0011-xy*e1200+xz*e3100-xw*e230011
      +yr*e02+yu*e0322+yv*e0123-yn*e0122+yx*e1200-yy*e0022-yz*e2300-yw*e310022
      +zr*e03-zu*e0233+zv*e0133+zn*e0123-zx*e3100+zy*e2300-zz*e0033-zw*e120033
      +wr*I  -wu*e01*1-wv*e02*1-wn*e03*1-wx*e23*0-wy*e31*0-wz*e12*0+ww*e00112233
      (bottom row partially pre-factored scalars, shortening *0*1 to *0, etc)

      Convert vector wedge pairs (squares) to scalars (e0 := 0, e1,2,3 := 1):
     = rr*1  +ru*e23  +rv*e31  +rn*e12  +rx*e01  +ry*e02  +rz*e03  +rw*e0123
      +ur*e23-uu*1*1  -uv*e12*1+un*e31*1+ux*e0123-uy*e03*1+uz*e02*1-uw*e01*1*1
      +vr*e31+vu*e12*1-vv*1*1  -vn*e23*1+vx*e03*1+vy*e0123-vz*e01*1-vw*e02*1*1
      +nr*e12-nu*e31*1+nv*e23*1-nn*1*1  -nx*e02*1+ny*e01*1+nz*e0123-nw*e03*1*1
      +xr*e01+xu*e0123-xv*e03*1+xn*e02*1-xx*0*1  -xy*e12*0+xz*e31*0-xw*e23*0*1
      +yr*e02+yu*e03*1+yv*e0123-yn*e01*1+yx*e12*0-yy*0*1  -yz*e23*0-yw*e31*0*1
      +zr*e03-zu*e02*1+zv*e01*1+zn*e0123-zx*e31*0+zy*e23*0-zz*0*1  -zw*e12*0*1
      +wr*I  -wu*e01*1-wv*e02*1-wn*e03*1-wx*e23*0-wy*e31*0-wz*e12*0+ww*0*1*1*1

      Simplify out scalars:
     = rr    +ru*e23  +rv*e31  +rn*e12  +rx*e01  +ry*e02  +rz*e03  +rw*e0123
      +ur*e23-uu      -uv*e12  +un*e31  +ux*e0123-uy*e03  +uz*e02  -uw*e01
      +vr*e31+vu*e12  -vv      -vn*e23  +vx*e03  +vy*e0123-vz*e01  -vw*e02
      +nr*e12-nu*e31  +nv*e23  -nn      -nx*e02  +ny*e01  +nz*e0123-nw*e03
      +xr*e01+xu*e0123-xv*e03  +xn*e02  -0       -0       +0       -0
      +yr*e02+yu*e03  +yv*e0123-yn*e01  +0       -0       -0       -0
      +zr*e03-zu*e02  +zv*e01  +zn*e0123-0       +0       -0       -0
      +wr*e0123-wu*e01-wv*e02  -wn*e03  -0       -0       -0       +0

      Group like terms:
     = rr    -uu      -vv      -nn
      +ur*e23  +ru*e23  +nv*e23  -vn*e23
      +vr*e31  +rv*e31  +un*e31  -nu*e31
      +nr*e12  +rn*e12  +vu*e12  -uv*e12
      +xr*e01  +rx*e01  -uw*e01  -wu*e01  +zv*e01  -vz*e01  +ny*e01  -yn*e01
      +yr*e02  +ry*e02  -vw*e02  -wv*e02  +uz*e02  -zu*e02  -nx*e02  +xn*e02
      +zr*e03  +rz*e03  -nw*e03  -wn*e03  +yu*e03  -uy*e03  +vx*e03  -xv*e03
      +wr*e0123+rw*e0123+ux*e0123+xu*e0123+vy*e0123+yv*e0123+nz*e0123+zn*e0123

      Factor common basis blade factors:
     = (rr -uu -vv -nn)
      +(ur +ru +nv -vn) e23
      +(vr +rv +un -nu) e31
      +(nr +rn +vu -uv) e12
      +(xr +rx -uw -wu +zv -vz +ny -yn) e01
      +(yr +ry -vw -wv +uz -zu -nx +xn) e02
      +(zr +rz -nw -wn +yu -uy +vx -xv) e03
      +(wr +rw +ux +xu +vy +yv +nz +zn) e0123

      Expand to d.# * q.#:
     = (d.r*q.r -d.u*q.u -d.v*q.v -d.n*q.n)
      +(d.u*q.r +d.r*q.u +d.n*q.v -d.v*q.n) e23
      +(d.v*q.r +d.r*q.v +d.u*q.n -d.n*q.u) e31
      +(d.n*q.r +d.r*q.n +d.v*q.u -d.u*q.v) e12
  +(d.x*q.r +d.r*q.x -d.u*q.w -d.w*q.u +d.z*q.v -d.v*q.z +d.n*q.y -d.y*q.n) e01
  +(d.y*q.r +d.r*q.y -d.v*q.w -d.w*q.v +d.u*q.z -d.z*q.u -d.n*q.x +d.x*q.n) e02
  +(d.z*q.r +d.r*q.z -d.n*q.w -d.w*q.n +d.y*q.u -d.u*q.y +d.v*q.x -d.x*q.v) e03
  +(d.w*q.r +d.r*q.w +d.u*q.x +d.x*q.u +d.v*q.y +d.y*q.v +d.n*q.z +d.z*q.n)e0123

      Relabel d|q:<r,u,v,n,x,y,z,w> -> |other:<l,e23,e31,e12,e01,e02,e03,e0123>:
     = (l*other.l   -e23*other.e23 -e31*other.e31 -e12*other.e12),
       (e23*other.l +l*other.e23 +e12*other.e31 -e31*other.e12),
       (e31*other.l +l*other.e31 +e23*other.e12 -e12*other.e23),
       (e12*other.l +l*other.e12 +e31*other.e23 -e23*other.e31),
       (e01*other.l +l*other.e01 -e23*other.e0123 -e0123*other.e23
       +e03*other.e31 -e31*other.e03 +e12*other.e02 -e02*other.e12),
       (e02*other.l +l*other.e02 -e31*other.e0123 -e0123*other.e31
       +e23*other.e03 -e03*other.e23 -e12*other.e01 +e01*other.e12),
       (e03*other.l +l*other.e03 -e12*other.e0123 -e0123*other.e12
       +e02*other.e23 -e23*other.e02 +e31*other.e01 -e01*other.e31),
       (e0123*other.l +l*other.e0123 +e23*other.e01 +e01*other.e23
       +e31*other.e02 +e02*other.e31 +e12*other.e03 +e03*other.e12)
    @param other
      - source geometric (0+3+1)D number to be multiplied with this one
    @return
      - reference to this 4D geometric number for method chaining
    */                                                                      /**/
    inline GP301& operator*=(const GP301& other)
    {
      Set
      (
        (l * other.l - e23 * other.e23 - e31 * other.e31 - e12 * other.e12),
        (e23 * other.l + l * other.e23 + e12 * other.e31 - e31 * other.e12),
        (e31 * other.l + l * other.e31 + e23 * other.e12 - e12 * other.e23),
        (e12 * other.l + l * other.e12 + e31 * other.e23 - e23 * other.e31),
        (e01 * other.l + l * other.e01 - e23 * other.e0123 - e0123 * other.e23
       + e03 * other.e31 - e31 * other.e03 + e12 * other.e02 - e02 * other.e12),
        (e02 * other.l + l * other.e02 - e31 * other.e0123 - e0123 * other.e31
       + e23 * other.e03 - e03 * other.e23 - e12 * other.e01 + e01 * other.e12),
        (e03 * other.l + l * other.e03 - e12 * other.e0123 - e0123 * other.e12
       + e02 * other.e23 - e23 * other.e02 + e31 * other.e01 - e01 * other.e31),
        (e0123 * other.l + l * other.e0123 + e23 * other.e01 + e01 * other.e23
       + e31 * other.e02 + e02 * other.e31 + e12 * other.e03 + e03 * other.e12)
      );
      return *this;
    } // end + GP301& GP301::operator*=(const GP301&)      #^^^^^^^^^#^^^^^^^^*/


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
    inline GP301 operator/(f4 divisor) const { return Copy() *= InvF(divisor);
    } // end + GP301 GP301::operator/(f4) const  #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide real and imaginary values uniformly by divisor, setting result
    @details
      - (real, imag)/d = (real, imag)*(1/d) = (real/d, imag/d)
    @param divisor
      - amount by which real and imaginary values are to be uniformly divided
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& operator/=(f4 divisor) { return (*this) *= InvF(divisor);
    } // end + GP301 GP301::operator/=(f4)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this geometric product by another geometric product, returning result
    @param other
      - geometric product by which this geometric product is to be divided
    @return
      - resultant, member-wise scaled copy of this complex's values
    */                                                                      /**/
    inline GP301 operator/(const GP301& other) const { return Copy() /= other;
    } // end + GP301 GP301::operator/(const GP301&) const  #^^^^^^^^^#^^^^^^^^*/


    /**
    @brief
        Divide this geometric product by another geometric product, setting result
    @details
      - (r1+imag1)/(r2+imag2)    = (r1+imag1)/(r2+imag2) * 1
      = (r1+imag1)/(r2+imag2)    * (r2-imag2)/(r2-imag2)
      =  (r1+imag1)(r2-imag2)    / (r2+imag2)(r2-imag2)
      = this.DotSelf(other) / other.DotSelf(other)
      = this.DotSelf(other) / other.MagSq()
    @param other
      - geometric product by which this geometric product is to be divided
    @return
      - reference to this geometric product for method chaining
    */                                                                      /**/
    inline GP301& operator/=(const GP301& other)
    {
      return (*this) *= !other;
    } // end + GP301 GP301::operator/=(f4)       #^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  }; // end GP301 union / struct / class type declaration

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
    - copy of rhs v2f's values, scaled by scalar in <r, e12, e31, e23>
  */
  GP301 operator*(f4 scalar, const GP301& rhs);


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
  bool operator==(const GP301& lhs, const GP301& rhs);


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
  bool operator!=(const GP301& lhs, const GP301& rhs);


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
  std::ostream& operator<<(std::ostream& output, const GP301& complex);


  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                            Helper Constants                             */
  /*^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  //! Zero vector in real and imaginary dimensions; error state reserved value
  extern const GP301& nullGP031;

  //! Quaternion alias for Geometric product of even Cl(0,3,0) subalgebra
  typedef GP301 DQuat;

  //! Quaternion alias for Geometric product of even Cl(0,3,0) subalgebra
  typedef GP301 DualQuaternion;

} // end dp namespace