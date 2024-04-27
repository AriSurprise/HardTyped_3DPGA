/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#
File Name:  mNMf.h
Purpose:  2D NxM, column major matrix; inputs / outputs in row major
Details:  Arbitrary sized matrices are best stored contiguously as 1D arrays
  but for implementation expedience, the base array being used is a vNf member.
  While column major storage by subscript is used by convention in other
  graphically driven vector objects, non-square matrix data is not stepped over
  in the same sort of processes, and need not have the mindset towards columns
  read as basis vectors for efficiency or any other obvious benefit. Conversely,
  it stands to add confusion far more likely to adopt column major in terms of
  dimensions of resultant matrices, where conventions only exist to leave user
  expectation to look for products where a.row by a.col * b.row by b.col output
  in a.row by b.col formats: the opposite wouldn't improve anyone's UX except,
  maybe at most, me, having to abide by my own invented conventions more easily.
Language: C++ / Eng, MSVC (used, but should work with most compilers)
Platform: MSVC / Windows 10 (used, but should have no requirements)
Project:  a.Surprise_MAT345_3
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
#include <vector>       // Constructor with series of existing column vectors
#include <initializer_list> // Preferable variadic element list construction
// "./src/..."
#include "../Type/Errata.h" // Platform primitive type aliases for easier porting
#include "../Math/v2u.h"       // Dimensions given as a pair of <row, column> sizes 
#include "../Math/v2f.h"       // Dimension resize parameter taking <low, high> values
#include "../Math/vNf.h"       // Member requires exposed visibility to instantiate


/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
/*                             Forward References                             */
/*^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

namespace dp //! Contents for use within DigiPen MAT (& CS) class assignments
{

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                             Public Classes                               */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  class mNMf //! 2 dimensional N by M, column major matrix
  {
  public:

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                             Constructors                               */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
      - Create a default 2x2 identity matrix: 1's in the pivots, 0 elsewhere
    @details
      - 2 being the minimal "matrix" scale to not imply vectors: 2x2 default
    */
    mNMf(void);

    /**
    @brief
      - set matrix from row major input and the given row break col# intervals
    @details
      - basis length should be row divisible, but adds 0's to fill as needed
    @param cols
      - number of elements in data before a new row is added to the matrix
    @param data
      - row major numeric cell data, which should have cols divisible size
    */
    mNMf(u2 cols, std::initializer_list<f8> data);

    /**
    @brief
      - set matrix from row major vector, with given row break col# intervals
    @details
      - adds trailing 0's to data to fill as needed, to fill last row/cols
    @param cols
      - number of elements in data before a new row is added to the matrix
    @param data
      - row major numeric cell data, which should have cols divisible size
    */
    mNMf(u2 cols, const vNf& data);

    /**
    @brief
      - set matrix from row vectors (promotes ragged to highest given size)
    @details
      - vNf per data can be any length: implies <..., 0> if ragged & short
    @param data
      - list of uniform dimension vectors comprising matrix row data
    */
    mNMf(const std::vector<vNf>& data);

    
    /** Create an N dimensional identity matrix: 1's in the pivots, 0 elsewhere
    @brief
      - create an N dimensional identity matrix: 1's in the pivots, 0 elsewhere
    @param dimens
      - number of rows or columns corresponding to square matrix term count
    @param scalar
      - scalar value to be used uniformly in each trace element (col == row)
    */
    mNMf(const v2u& dimens, f4 scalar = 1.0f);


    /** Create a copy of another matrix from copied row / column data values
    @brief
      - create a copy of another matrix from copied row / column data values
    @param source
      - existing matrix to have it's row / column values copied into the new one
    @param row
      - 
    */
    mNMf(const vNf& source, bool row = false);


    /** Create a copy of another matrix from copied row / column data values
    @brief
      - create a copy of another matrix from copied row / column data values
    @param source
      - square matrix to have its values copied to this arbitrary matrix
    */
    mNMf(const mNf& source);


    /** Create a copy of another matrix from copied row / column data values
    @brief
      - create a copy of another matrix from copied row / column data values
    @param source
      - existing matrix to have it's row / column values copied into the new one
    */
    mNMf(const mNMf& source);


    /** Create this matrix from a function result's row / column data values
    @brief
      - create this matrix from a function result's row / column data values
    @param result
      - matrix function return to have it's row / column values stolen by this
    */
    mNMf(mNMf&& result) noexcept;

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /**
    @brief
        Get the row * col dimensional product for the NxM matrix data in use
    @return
      - element count for product of rows and columns in existing matrix data
    */
    inline const um& Area(void) const
    { return cell.Dimens(); } // end inline const um& Area(void) const        */


    /** Get a copy of this NxM matrix data in use
    @brief
      - get a copy of this NxM matrix data in use
    @return
      - memberwise copy of row and column data for this matrix data
    */
    inline mNMf Copy(void) const
    { return mNMf(*this); } // end inline mNMf Copy(void) const               */


    /**
    @brief
        Get the <row, col> dimensions of the NxM matrix data in use
    @return
      - element count vector of < rows, columns > for the existing matrix data
    */
    inline const v2u& Dimens(void) const
    { return dimens; } // end inline const v2u& Dimens(void) const            */


    /** JSON formatted string containing each member value in row major format
    @brief
      - JSON formatted string containing each member value in row major format
    @return
      - string containing packed tightly ascii copy of contained matrix data
    */
    std::string JSON(void) const;


    /**
    @brief
      - Update dimensions of existing matrix data, moving existing cell values
    @param dimen
      - [1,65.5k): dimensions which new matrix cells will be made to span
    @param row_shift
      - number of rows to shift existing cell data ([-]: up, [+]: down)
    @param col_shift
      - number of columns to shift existing cell data ([-]: left, [+]: right)
    @param augment
      - cells without source data set to low if low indexed or high if high
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& Resize(const v2u& dimen, s4 row_shift = 0, s4 col_shift = 0,
      const v2f& augment = { If, Of });


    /** Set matrix column / row data to another source's column / row values
    @brief
      - set matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& Set(const vNf& source);


    /** Set matrix column / row data to another source's column / row values
    @brief
      - set matrix column / row data to another source's column / row values
    @param source
      - vector to have its data members set as this matrix's data
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& Set(u2 cols, const vNf& source);


    /** Set matrix column / row data to another source's column / row values
    @brief
      - set matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& Set(const mNf& source);


    /** Set matrix column / row data to another source's column / row values
    @brief
      - set matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& SetTranspose(const mNf& source);


    /** Set matrix column / row data to another source's column / row values
    @brief
      - set matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& SetTranspose(const mNMf& source);


    /** Set matrix column / row data to another source's column / row values
    @brief
      - set matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& Set(const mNMf& source);


    /** JSON formatted string containing each member value in row major format
    @brief
      - JSON formatted string containing each member value in row major format
    @param lineBreaks
      - if enabled / true, rows will end with new lines (undesirable in serdes)
    @return
      - string containing packed tightly ascii copy of contained matrix data
    */
    std::string ToString(bool lineBreaks = false) const;


    /** Set the matrix to have swapped contents for rows and columns
    @brief
      - set the matrix to have swapped contents for rows and columns
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& Transpose(void);


    /** Get a copy of this matrix with swapped contents for rows and columns
    @brief
      - get a copy of this matrix with swapped contents for rows and columns
    @return
      - copy of this matrix with swapped row and column data fields
    */
    mNMf Transposed(void) const;


    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                          Operator Overloads                            */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /** Set a matrix column / row data to another source's column / row values
    @brief
      - set a matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator=(const vNf& source);

    /** Set a matrix column / row data to another source's column / row values
    @brief
      - set a matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator=(const mNMf& source);


    /** Set this matrix from a function result's row / column data values
    @brief
      - set this matrix from a function result's row / column data values
    @param result
      - returned matrix to have it's row / column values stolen by this
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator=(mNMf&& result) noexcept;

    /** Set a matrix column / row data to another source's column / row values
    @brief
      - set a matrix column / row data to another source's column / row values
    @param source
      - matrix to have its data members copied into this matrix
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator=(const mNf& source);


    /** Set this matrix from a function result's row / column data values
    @brief
      - set this matrix from a function result's row / column data values
    @param result
      - returned matrix to have it's row / column values stolen by this
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator=(mNf&& result) noexcept;


    /** Get a copy of the matrix with memberwise negated elements
    @brief
      - get a copy of the matrix with memberwise negated elements
    @return
      - copy of existing matrix data with negated values memberwise
    */
    mNMf operator-(void) const;


    /** Get the transpose of the current matrix (reversed rows and columns)
    @brief
      - get the transpose of the current matrix (reversed rows and columns)
    @return
      - matrix undergoing the reverse change of basis from this matrix
    */
    mNMf operator!(void) const;


    /** Get a column vNf from the matrix's column values ([0,(N-1)])
    @brief
      - get a column vNf from the matrix's column values ([0,(N-1)])
    @param index
      - value in [0,(N-1)] range to access that ordered column vector
    @return
      - reference to the column vector subscript ([0,(N-1)])
    */
    const f4& operator[](const v2u& index) const;


    /** Get a column vNf from the matrix's column values ([0,(N-1)])
    @brief
      - get a column vNf from the matrix's column values ([0,(N-1)])
    @param index
      - value in [0,(N-1)] range to access that ordered column vector
    @return
      - reference to the column vector subscript ([0,(N-1)])
    */
    f4& operator[](const v2u& index);


    /** Calculate the member-wise addition of 2 matrices, returning the sum
    @brief
      - calculate the member-wise addition of 2 matrices, returning the sum
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be added to this matrix's row / column data, member-wise
    @return
      - copy of this matrix with each entry added, member-wise, by other
    */
    mNMf operator+(const mNMf& other) const;


    /** Add an other matrix's values member-wise, setting the sum into this
    @brief
      - add an other matrix's values member-wise, setting the sum into this
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be added to this matrix's row / column data, member-wise
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator+=(const mNMf& other);


    /** Get member-wise subtraction of 2 matrices, returning the difference
    @brief
      - get member-wise subtraction of 2 matrices, returning the difference
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be subtracted from this matrix's data, member-wise
    @return
      - copy of this matrix with each entry subtracted, member-wise, by other
    */
    mNMf operator-(const mNMf& other) const;


    /** Subtract an other matrix's values member-wise, setting the difference
    @brief
      - subtract an other matrix's values member-wise, setting the difference
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be subtracted from this matrix's data, member-wise
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator-=(const mNMf& other);


    /** Scalar multiplication multiplies each member by scalar constant
    @brief
      - scalar multiplication multiplies each member by scalar constant
    @param scalar
      - scalar amount by which to multiply each matrix element
    @return
      - copy of this matrix's data, scaled memberwise by scalar
    */
    mNMf operator*(f4 scalar) const;


    /** Scale each matrix element by scalar, setting the product into this
    @brief
      - scale each matrix element by scalar, setting the product into this
    @param scalar
      - scalar amount by which to multiply each matrix element
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator*=(f4 scalar);


    /** Get the concatenated matrix of (this * other): both transformations
    @brief
      - get the concatenated matrix of (this * other): both transformations
    @details
      - to allow ubiquitous function, lower dimensional vectors will be
      promoted to fit, while higher dimensional vectors will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be right concatenated with this matrix
    @return
      - copy of this matrix, concatenated with the other
    */
    vNf operator*(const vNf& vector) const;


    /** Get the concatenated matrix of (this * other): both transformations
    @brief
      - get the concatenated matrix of (this * other): both transformations
    @details
      - to allow ubiquitous function, lower dimensional vectors will be
      promoted to fit, while higher dimensional vectors will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be right concatenated with this matrix
    @return
      - copy of this matrix, concatenated with the other
    */
    mNMf& operator*=(const vNf& vector) const;


    /** Get the concatenated matrix of (this * other): both transformations
    @brief
      - get the concatenated matrix of (this * other): both transformations
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be right concatenated with this matrix
    @return
      - copy of this matrix, concatenated with the other
    */
    mNMf operator*(const mNf& other) const;


    /** Matrix multiplication concatenates 2 sequential transformations into 1
    @brief
      - matrix multiplication concatenates 2 sequential transformations into 1
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - multiplicand to use with this (cell = this[row] * other[col])
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator*=(const mNf& other);


    /** Get the concatenated matrix of (this * other): both transformations
    @brief
      - get the concatenated matrix of (this * other): both transformations
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - matrix to be right concatenated with this matrix
    @return
      - copy of this matrix, concatenated with the other
    */
    mNMf operator*(const mNMf& other) const;


    /** Matrix multiplication concatenates 2 sequential transformations into 1
    @brief
      - matrix multiplication concatenates 2 sequential transformations into 1
    @details
      - to allow ubiquitous function, lower dimensional matrices will be
      promoted to fit, while higher dimensional matrices will promote this
      matrix with null values, setting the memberwise results with those 0s
      (to return the overall, larger data set without truncating data).
      In keeping with mathematical standards that disallow most divergent
      dimensional matrix math, warnings will be logged accordingly.
    @param other
      - multiplicand to use with this (cell = this[row] * other[col])
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNMf& operator*=(const mNMf& other);


    /** Perform division on all members, returning the result
    @brief
      - perform division on all members, returning the result
    @param inverseScalar
      - scalar amount by which to multiply the reciprocal of per matrix element
    @return
      - copy of this matrix, scaled up by (1.0 / inverseScalar)
    */
    mNf operator/(f4 inverseScalar) const;


    /** Division multiplies all members by reciprocal of inverseScalar
    @brief
      - division multiplies all members by reciprocal of inverseScalar
    @param inverseScalar
      - scalar amount by which to multiply the reciprocal of per matrix element
    @return
      - reference to the modified matrix for easier subsequent inline action
    */
    mNf& operator/=(f4 inverseScalar);



    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                            Public Members                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  private:

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                           Private Methods                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
    /*                           Private Members                              */
    /*^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

    //! Column major lists of vectors comprising the basis
    vNf cell;

    //! < Row, Column > size of matrix cell elements
    v2u dimens;

  }; // end mNMf struct definitions



  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                     Helper Constant Declarations                         */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                       Helper Class Declarations                          */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/


  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                     Helper Function Declarations                         */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  

  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/
  /*                     Helper Operator Declarations                         */
  /*^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^^#^^^^^^^^*/

  /** Scale each matrix element by scalar, setting the product into this
  @brief
    - scale each matrix element by scalar, setting the product into this
  @param scalar
    - scalar amount by which to multiply each matrix element
  @param rhs
    - matrix to be scaled member-wise by the scalar amount
  @return
    - copy of the rhs matrix scaled member-wise by scalar
  */
  mNMf operator*(f4 scalar, const mNMf& rhs);


  /** Confirm if 2 matrix's are relatively equal across all matrix elements
  @brief
    - confirm if 2 matrix's are relatively equal across all matrix elements
  @details
    - inequal dimensions may be equal, only if all asymmetrical cells == 0
  @param lhs
    - left-hand side to be compared for equality against the right-hand side
  @param rhs
    - right-hand side to be compared for equality against the left-hand side
  @return
    - true if all matrix elements are equal, false if any are not
  */
  bool operator==(const mNMf& lhs, const mNMf& rhs);


  /** Confirm if 2 matrix's are relatively inequal in any matrix element
  @brief
    - confirm if 2 matrix's are relatively inequal in any matrix element
  @details
    - inequal dimensions may be equal, only if all asymmetrical cells == 0
  @param lhs
    - left-hand side to be compared for inequality against the right-hand side
  @param rhs
    - right-hand side to be compared for inequality against the left-hand side
  @return
    - true if any matrix elements is inequal, false if none are
  */
  bool operator!=(const mNMf& lhs, const mNMf& rhs);

  
  /** Output the string version of the vector data: <vector>, (point) or [clip]
  @brief
    - output the string version of the vector data: <vector>, (point) or [clip]
  @param output
    - output stream buffer to have the matrix data fed into it for display
  @param matrix
    - right-hand side to display in string representation of data contained
  @return
    - reference to the modified output stream buffer object
  */
  std::ostream& operator<<(std::ostream& output, const mNMf& matrix);

} // end dp namespace
