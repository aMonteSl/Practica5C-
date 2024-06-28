// Coleccion class member -and friend- function definitions.
#include <iostream>
#include <iomanip>
#include <stdexcept> 
#include "Coleccion.h" // Coleccion class definition

using namespace std;

// default constructor for class Coleccion (default size 10)
// considering arraySize > 0, otherwise an exception should be thrown
Coleccion::Coleccion (int arraySize)
  : size (arraySize),
    ptr (new int [size]) {
  for (size_t i = 0; i < size; ++i)
    ptr [i] = 0; // set pointer-based array element
} // end Coleccion default constructor

// copy constructor for class Coleccion; must receive a reference to a Coleccion
Coleccion::Coleccion (const Coleccion &arrayToCopy)
  : size (arrayToCopy.size),
  ptr (new int [size]) {
    for (size_t i = 0; i < size; ++i)
      ptr [i] = arrayToCopy.ptr [i]; // copy into object
} // end Coleccion copy constructor

// destructor for class Coleccion
Coleccion::~Coleccion() {
  delete [] ptr; // release pointer-based array space
} // end destructor


// A partir de aqui codigo mio

std::ostream &operator<< (std::ostream &output, const Coleccion &a) {
  // output private ptr-based array
  for (size_t i = 0; i < a.size; ++i) {
    output << setw (12) << a.ptr [i];

    if ((i + 1) % 4 == 0) // 4 numbers per row of output
      output << endl;
  } // end for

  if (a.size % 4 != 0) // end last line of output
    output << endl;

  return output; // enables cout << x << y;
} // end function operator<<

std::istream &operator>> (std::istream &input, Coleccion &a) {
  for (size_t i = 0; i < a.size; ++i)
    std::cout << "a[" << i << "]: ",
    input >> a.ptr [i];

  return input; // enables cin >> x >> y;
} // end function operator>>

size_t Coleccion::getSize() const {
  return size; // number of elements in Coleccion
} // end function getSize

const Coleccion &Coleccion::operator= (const Coleccion &right) {
  if (&right != this) { // avoid self-assignment
    // for arrays of different sizes, deallocate original
    // left-side array, then allocate new left-side array
    if (size != right.size) {
      delete [] ptr; // release space
      size = right.size; // resize this object
      ptr = new int [size]; // create space for array copy
    } // end inner if

    for (size_t i = 0; i < size; ++i)
      ptr [i] = right.ptr [i]; // copy array into object
  } // end outer if

  return *this; // enables x = y = z, for example
} // end function operator=

bool Coleccion::operator== (const Coleccion &right) const {
  if (size != right.size)
    return false; // Coleccions of different number of elements

  for (size_t i = 0; i < size; ++i)
    if (ptr [i] != right.ptr [i])
      return false; // Coleccions are not equal

  return true; // Coleccions are equal
} // end function operator==

int &Coleccion::operator[] (int subscript) {
  // check for subscript out-of-range error
  if (subscript < 0 || subscript >= static_cast<int> (size))
    throw out_of_range ("Subscript out of range");

  return ptr [subscript]; // reference return
} // end function operator[]

int Coleccion::operator[] (int subscript) const {
  // check for subscript out-of-range error
  if (subscript < 0 || subscript >= static_cast<int> (size))
    throw out_of_range ("Subscript out of range");

  return ptr [subscript]; // returns copy of this element
} // end function operator[]