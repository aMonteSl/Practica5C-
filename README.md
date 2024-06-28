# P5-SobrecargaArray
## Autor: Adrián Montes Linares

## Objetivo
El objetivo de esta práctica es completar el fichero Coleccion.cpp acabando de definir el funcionamiento de la clase Coleccion para que el main.cpp pueda compilar y ejecutarse sin errores
A continuación los ficheros originales.
## ficheros originales
### Coleccion.h
```cpp
/* Coleccion.h
   Práctica 5
   Coleccion class definition with overloaded operators.
*/

#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Coleccion {
  friend std::ostream &operator<< (std::ostream &, const Coleccion &);
  friend std::istream &operator>> (std::istream &, Coleccion &);

public:
  explicit Coleccion (int = 10); // default constructor
  Coleccion (const Coleccion &); // copy constructor
  ~Coleccion(); // destructor

  size_t getSize() const; // return size

  const Coleccion &operator= (const Coleccion &); // assignment operator
  bool operator== (const Coleccion &) const; // equality operator

  // inequality operator; returns opposite of == operator
  bool operator!= (const Coleccion &right) const { 
    return !(*this == right); // invokes Coleccion::operator==
  } // end function operator!=

  // subscript operator for non-const objects returns modifiable lvalue
  int &operator[] (int);

  // subscript operator for const objects returns rvalue
  int operator[] (int) const;

private:

  size_t size; // pointer-based array size
  int *ptr; // pointer to first element of pointer-based array
}; // end class Coleccion

#endif
```
### Coleccion.cpp
```cpp
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
```
### Main.cpp
```cpp
/* main.cpp
   Practical exercise 5.
   Coleccion class test program.
*/
#include <iostream>
#include <stdexcept>
#include "Coleccion.h"

using namespace std;

int main() {
  Coleccion integers1 (7); // seven-element Coleccion
  Coleccion integers2; // 10-element Coleccion by default

  // print integers1 size and contents
  cout << "Size of Coleccion integers1 is " << integers1.getSize()
    << "\nColeccion after initialization:\n" << integers1;

  // print integers2 size and contents
  cout << "\nSize of Coleccion integers2 is " 
    << integers2.getSize()
    << "\nColeccion after initialization:\n" << integers2;

  // input and print integers1 and integers2
  cout << "\nEnter 17 integers:" << endl;
  cin >> integers1 >> integers2;

  cout << "\nAfter input, the Coleccions contain:\n"
    << "integers1:\n" << integers1
    << "integers2:\n" << integers2;

  // use overloaded inequality (!=) operator
  cout << "\nEvaluating: integers1 != integers2" << endl;

  if (integers1 != integers2)
    cout << "integers1 and integers2 are not equal" << endl;

  // create Coleccion integers3 using integers1 as an
  // initializer; print size and contents
  Coleccion integers3 (integers1); // invokes copy constructor

  cout << "\nSize of Coleccion integers3 is "
    << integers3.getSize()
    << "\nColeccion after initialization:\n" << integers3;

  // use overloaded assignment (=) operator
  cout << "\nAssigning integers2 to integers1:" << endl;
  integers1 = integers2; // note target Coleccion is smaller

  cout << "integers1:\n" << integers1
    << "integers2:\n" << integers2;

  // use overloaded equality (==) operator
  cout << "\nEvaluating: integers1 == integers2" << endl;

  if (integers1 == integers2)
    cout << "integers1 and integers2 are equal" << endl;

  // use overloaded subscript operator to create rvalue
  cout << "\nintegers1[5] is " << integers1 [5];

  // use overloaded subscript operator to create lvalue
  cout << "\n\nAssigning 1000 to integers1[5]" << endl;
  integers1 [5] = 1000;
  cout << "integers1:\n" << integers1;

  
  // attempt to use out-of-range subscript
  try {                                                                 
    cout << "\nAttempt to assign 1000 to integers1[15]" << endl;
    integers1 [15] = 1000; // ERROR: subscript out of range
  } catch (out_of_range &ex) {                                                                 
    cout << "An exception occurred: " << ex.what() << endl;        
  } // end catch
  
} // end main

```
## Metodos a los cuales se les ha definido su funcionalidad
- std::ostream &operator<< (std::ostream &output, const Coleccion &a). Este método permite imprimir objetos de la clase Coleccion en un flujo de salida estándar (std::ostream) de forma formateada, mostrando los elementos del objeto en filas de 4, con un ancho de campo de 12 caracteres cada uno.
```cpp
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
```
- std::istream &operator>> (std::istream &input, Coleccion &a). Este método permite leer datos desde un flujo de entrada estándar (std::istream) y asignarlos a un objeto de la clase Coleccion, elemento por elemento. Luego, devuelve el flujo de entrada para permitir operaciones de extracción encadenadas.
```cpp
std::istream &operator>> (std::istream &input, Coleccion &a) {
  for (size_t i = 0; i < a.size; ++i)
    std::cout << "a[" << i << "]: ",
    input >> a.ptr [i];

  return input; // enables cin >> x >> y;
} // end function operator>>
```
- size_t Coleccion::getSize() const. Este método nos permite obtener el tamazo del objeto Coleccion
```cpp
size_t Coleccion::getSize() const {
  return size; // number of elements in Coleccion
} // end function getSize
```
- const Coleccion &Coleccion::operator= (const Coleccion &right). Este método sobrecarga el operador de asignación (=) para la clase Coleccion. Copia los elementos de una instancia de Coleccion (right) a otra instancia (this). Si los tamaños de los arrays son diferentes, se libera y asigna memoria adecuadamente. Evita la autoasignación. Devuelve una referencia constante a la instancia actual, permitiendo asignaciones encadenadas.
```cpp
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
```
- bool Coleccion::operator== (const Coleccion &right) const. ste método compara dos instancias de la clase Coleccion para verificar si son iguales. Primero, verifica si tienen el mismo tamaño. Luego, itera sobre los elementos de ambas colecciones, comparándolos uno a uno. Si encuentra algún par de elementos diferentes, devuelve false. Si completa la comparación sin encontrar diferencias, devuelve true.
```cpp
bool Coleccion::operator== (const Coleccion &right) const {
  if (size != right.size)
    return false; // Coleccions of different number of elements

  for (size_t i = 0; i < size; ++i)
    if (ptr [i] != right.ptr [i])
      return false; // Coleccions are not equal

  return true; // Coleccions are equal
} // end function operator==
```
- int &Coleccion::operator[] (int subscript). Este método sobrecarga el operador de acceso a elementos ([]) para la clase Coleccion, permitiendo acceder y modificar los elementos de la colección mediante índices. Verifica si el índice está dentro del rango válido y lanza una excepción si no lo está. Luego, devuelve una referencia al elemento en la posición indicada por el índice.
```cpp
int &Coleccion::operator[] (int subscript) {
  // check for subscript out-of-range error
  if (subscript < 0 || subscript >= static_cast<int> (size))
    throw out_of_range ("Subscript out of range");

  return ptr [subscript]; // reference return
} // end function operator[]
```
- int Coleccion::operator[] (int subscript) const. Este método sobrecarga el operador de acceso a elementos ([]) para la clase Coleccion cuando se usa con instancias constantes. Verifica si el índice está dentro del rango válido y lanza una excepción si no lo está. Luego, devuelve una copia del elemento en la posición indicada por el índice.
```cpp
int Coleccion::operator[] (int subscript) const {
  // check for subscript out-of-range error
  if (subscript < 0 || subscript >= static_cast<int> (size))
    throw out_of_range ("Subscript out of range");

  return ptr [subscript]; // returns copy of this element
} // end function operator[]
```
## Compilar y ejecutar
- Se compila con el fichero MakeFile:
```bash
make
```
- Se pueden limpiar los ficheros objetos con el siguiente comando:
```bash
make clean
```
- Para ejecutar el programa:
```bash
./main
```