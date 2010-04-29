#ifndef CF_Math_VectorSliceT_hpp
#define CF_Math_VectorSliceT_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Math/ExprOp.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace CF {

  namespace Math {

    template <class T> class VectorSliceT;

    template <class T> std::ostream& operator<< (std::ostream& out, const VectorSliceT<T>& v);
    template <class T> std::istream& operator>> (std::istream& in, VectorSliceT<T>& v);
    template <class T> bool operator== (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2);
    template <class T> bool operator== (const VectorSliceT<T>& v,  const T& value);
    template <class T> bool operator!= (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2);
    template <class T> bool operator!= (const VectorSliceT<T>& v, const T& value);
    template <class T> T mixedProd (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2, const VectorSliceT<T>& v3, VectorSliceT<T>& temp);
    template <class T> void crossProd (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2, VectorSliceT<T>& result);
    template <class T> T innerProd (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2);
    template <class T> void copy (const VectorSliceT<T>& v1, VectorSliceT<T>& v2);

////////////////////////////////////////////////////////////////////////////////

/// Definition of a class VectorSliceT for numerical applications that
/// manipulates subsets (slices) of elements of a VectorT and provides
/// the same numerical functions and operators given by VectorT.
/// @author Andrea Lani
template <class T>
class VectorSliceT : public Expr<VectorSliceT<T>, T> {
public:

  /// Constructor.
  /// @param start where first element should be addressed
  explicit VectorSliceT(T *const start);

  /// Copy Constructor.
  /// @param orig source to copy from
  VectorSliceT(const VectorSliceT<T>& orig);

  /// Overloading for operator= taking an expression as argument
#define SLICEVEC_EQ_OP(__op__)        \
  template <class EXPR>          \
  const VectorSliceT<T>& operator __op__ (const Expr<EXPR,T>& expr)  \
  {\
for (Uint i = 0; i < _size; ++i) {\
  _start[i] __op__ expr.at(i);\
}\
    return *this;\
}

SLICEVEC_EQ_OP(=)
SLICEVEC_EQ_OP(+=)
SLICEVEC_EQ_OP(-=)
SLICEVEC_EQ_OP(*=)
SLICEVEC_EQ_OP(/=)

#undef SLICEVEC_EQ_OP

/// Overloading for operator= taking a constant value as argument
#define SLICEVEC_EQ_OP_CONST(__op__) \
  const VectorSliceT<T>& operator __op__ (const T& value)  \
  {              \
for (Uint i = 0; i < _size; ++i) {\
  _start[i] __op__ value;\
}\
    return *this;\
}

SLICEVEC_EQ_OP_CONST(=)
SLICEVEC_EQ_OP_CONST(+=)
SLICEVEC_EQ_OP_CONST(-=)
SLICEVEC_EQ_OP_CONST(*=)

#undef SLICEVEC_EQ_OP_CONST

  /// Overloading of the assignment operator "="
  /// The content of the slice is simply copied into the current one,
  /// but remains
  /// other._start != this->_start
  /// @pre the assignee is supposed to have the same size
  ///      as this VectorSliceT (as in std::valarray).
  const VectorSliceT<T>& operator= (const VectorSliceT<T>& other)
  {
    cf_assert(&other != this);
    T* ptr1 = _start;
    T* ptr2 = other._start;
    for (Uint i = 0; i < _size; ++i) {
      *ptr1++ = *ptr2++;
    }
    return *this;
  }

  /// Overloading of "/="
  /// @param value of type T
  const VectorSliceT<T>& operator/= (const T& value)
  {
    T* ptr = _start;
    cf_assert(std::abs(value) > std::numeric_limits<T>::epsilon());
    for (Uint i = 0; i < _size; ++i) {
      *ptr++ /= value;      //1/value is dangerous!!!! conversion to int
    }
    return *this;
  }

  /// Destructor.
  ~VectorSliceT();

  /// Accessor used by the expression template wrapper class
  T at (Uint i) const
  {
    return *(_start + i);
  }

  /// Overloading of the "[]" operator for assignment (writing).
  /// @param iElem index
  T& operator[] (Uint iElem)
  {
    return *(_start + iElem);
  }

  /// Overloading of the "[]" operator for assignment (reading only).
  /// @param iElem index
  const T& operator[] (Uint iElem) const
  {
    return *(_start + iElem);
  }

  /// Calculates the sum of all values stored in VectorSliceT
  /// @return T equal to sum of elements
  T sum() const
  {
    T* ptr = _start;
    T result = T();
    for (Uint i = 0; i < _size; ++i) {
      result += *ptr++;
    }
    return result;
  }

  /// Overloading of the stream operator "<<" for the output
  /// No "\n"ine introduced.
  /// @param out missing documentation
  /// @param v missing documentation
  /// @return missing documentation
  friend std::ostream& operator<< <> (std::ostream& out, const VectorSliceT<T>& v);

  /// Overloading of the stream operator ">>" for the input
  /// @param in missing documentation
  /// @param v missing documentation
  /// @return missing documentation
  friend std::istream& operator>> <> (std::istream& in, VectorSliceT<T>& v);

  /// Overloading of the "==" operator.
  /// @param v1 missing documentation
  /// @param v2 missing documentation
  /// @return true if all elements are equal elementwise
  friend bool operator== <> (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2);

  /// Overloading of the "==" operator.
  /// @param v given array
  /// @param value value for the comparison
  /// @return true if all elements are equal to value
  friend bool operator== <> (const VectorSliceT<T>& v, const T& value);

  /// Overloading of the "!=" operator.
  /// @param v1 missing documentation
  /// @param v2 missing documentation
  /// @return true if not all elements are equal elementwise
  friend bool operator!= <> (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2);

  /// Overloading of the "!=" operator.
  /// @param v given array
  /// @param value value for the comparison
  /// @return true if there is at least one element not
  ///         equal to value
  friend bool operator!= <> (const VectorSliceT<T>& v, const T& value);

  /// Mixed Product of three vectors
  /// @pre size() == 3 == v1.size() == v2.size() == v3.size() == temp.size()
  ///      (cf_assertion can check this)
  /// @param v1   first VectorSliceT
  /// @param v2   second VectorSliceT
  /// @param v3   third VectorSliceT
  /// @param temp temporary VectorSliceT
  /// @return the mixed product
  friend T mixedProd <> (const VectorSliceT<T>& v1,
      const VectorSliceT<T>& v2,
      const VectorSliceT<T>& v3,
      VectorSliceT<T>& temp);

  /// Internal Product for vector*vector operations
  /// \f$ s = v \cdot v1 \f$.
  /// Objects must be of same size.
  /// @param v1 first VectorSliceT
  /// @param v2 second VectorSliceT
  /// @return the inner product of the two given vectors
  friend T innerProd <> (const VectorSliceT<T>& v1,
      const VectorSliceT<T>& v2);

  /// Cross Product for vector*vector operations
  /// @pre v1.size() == v2.size() == result.size() == 3
  ///      (cf_assertion can check this)
  /// @param v1 first VectorSliceT
  /// @param v2 second VectorSliceT
  /// @param result VectorSliceT storing the result
  friend void crossProd <> (const VectorSliceT<T>& v1,
             const VectorSliceT<T>& v2,
             VectorSliceT<T>& result);

  /// Copy one VectorSliceT into another one
  /// @pre v1.size() == v2.size()
  /// @param v1 source vector
  /// @param v2 destination vector
  friend void copy <> (const VectorSliceT<T>& v1,
    VectorSliceT<T>& v2);

  /// Set the size of the slice
  /// @pre this method MUST be called before using whatever operation
  ///      with VectorSliceT
  static void setSize(const Uint size)
  {
    _size = size;
  }

  /// Get the max in the vector
  T emax() const
  {
    T result = _start[0];
    for (Uint i = 1; i < _size; ++i) {
      if (_start[i] > result) { result = _start[i]; }
    }
    return result;
  }

  /// Get the min in the vector
  T emin() const
  {
    T result = _start[0];
    for (Uint i = 1; i < _size; ++i) {
      if (_start[i] < result) { result = _start[i]; }
    }
    return result;
}

  /// Put the absolute value (abs) of the given vector in this
  /// VectorSliceT
  void abs(const VectorSliceT<T>& v);

  /// Reset the pointer
  void reset(T* const newStart)
  {
    _start = newStart;
  }

  /// Gets the size (the number of elements) of the VectorSliceT
  /// @return size of the VectorSliceT
  Uint size() const { return _size; }

private: //data

  /// pointer to the first element of the slice
  T* _start;

  /// size of the slice
  static Uint _size;

}; // class VectorSliceT

////////////////////////////////////////////////////////////////////////////////

template <class T>
Uint VectorSliceT<T>::_size = 0;

////////////////////////////////////////////////////////////////////////////////

template <class T>
VectorSliceT<T>::VectorSliceT(T *const start) :
  Expr<VectorSliceT<T>, T>(*this),
  _start(start)
{
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
VectorSliceT<T>::~VectorSliceT()
{
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
VectorSliceT<T>::VectorSliceT(const VectorSliceT<T>& orig) :
  Expr<VectorSliceT<T>, T>(*this),
  _start(orig._start)
{
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
std::ostream& operator<< (std::ostream& out, const VectorSliceT<T>& v)
{
  const Uint ns = v._size;
  for(Uint i = 0; i < ns; ++i) {
    out << v[i] << " " ;
  }

  return out;
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
std::istream& operator>> (std::istream& in, VectorSliceT<T>& v)
{
  const Uint ns = v._size;
  for(Uint i = 0; i < ns; ++i) {
    in >> v[i];
  }
  return in;
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
bool operator== (const VectorSliceT<T>& v1,
      const VectorSliceT<T>& v2)
{
  for(Uint i = 0; i < v1._size; ++i) {
    if (MathChecks::isNotEqual(v1[i],v2[i])) {
      return false;
    }
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
bool operator== (const VectorSliceT<T>& v,
      const T& value)
{
  for(Uint i = 0; i < v._size; ++i) {
    if (MathChecks::isNotEqual(v[i],value)) {
      return false;
    }
  }
  return true;
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
bool operator!= (const VectorSliceT<T>& v1,
      const VectorSliceT<T>& v2)
{
  return !(v1 == v2);
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
bool operator!= (const VectorSliceT<T>& v,
      const T& value)
{
  return !(v == value);
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
T mixedProd (const VectorSliceT<T>& v1,
      const VectorSliceT<T>& v2,
      const VectorSliceT<T>& v3,
      VectorSliceT<T>& temp)
{
  cf_assert(v1._size == 3);

  crossProd(v1, v2, temp);
  return innerProd(v3, temp);
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
T innerProd (const VectorSliceT<T>& v1, const VectorSliceT<T>& v2)
{
  T* p1 = v1._start;
  T* p2 = v2._start;
  T result = T();
  const Uint ns = v1.size();
  for (Uint i = 0; i < ns; ++i) {
    result += *p1++ * *p2++;
  }
  return result;
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
void crossProd (const VectorSliceT<T>& v1,
    const VectorSliceT<T>& v2,
    VectorSliceT<T>& result)
{
  cf_assert(v1._size == 3);

  result[0] =  v1[1]*v2[2] - v1[2]*v2[1];
  result[1] = -v1[0]*v2[2] + v1[2]*v2[0];
  result[2] =  v1[0]*v2[1] - v1[1]*v2[0];
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
void copy (const VectorSliceT<T>& v1, VectorSliceT<T>& v2)
{
  T* p1 = v1._start;
  T* p2 = v2._start;
  const Uint ns = v1.size();
  for (Uint i = 0; i < ns; ++i) {
    *p1++ = *p2++;
  }
}

////////////////////////////////////////////////////////////////////////////////

template <class T>
void VectorSliceT<T>::abs (const VectorSliceT<T>& v)
{
  T* p1 = _start;
  T* p2 = v._start;
  for (Uint i = 0; i < _size; ++i) {
    *p1++ = std::abs(*p2++);
  }
}

////////////////////////////////////////////////////////////////////////////////

  } // namespace Math

}   // namespace CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Math_VectorSliceT_hpp
