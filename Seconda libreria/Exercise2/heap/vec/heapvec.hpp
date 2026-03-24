
#ifndef HEAPVEC_HPP
#define HEAPVEC_HPP

/* ************************************************************************** */

#include "../heap.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HeapVec : virtual public Heap<Data>, protected SortableVector<Data>{
  // Must extend Heap<Data>,
  // Could extend Vector<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size; // HeapSize
  using SortableVector<Data>::Elements;

  // ...

public:

  // Default constructor
  // HeapVec() specifiers;
  HeapVec() = default;

  /* ************************************************************************ */

  // Specific constructors
  // HeapVec(argument) specifiers; // A heap obtained from a TraversableContainer
  HeapVec(const TraversableContainer<Data> &);
  // HeapVec(argument) specifiers; // A heap obtained from a MappableContainer
  HeapVec(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // HeapVec(argument) specifiers;
  HeapVec(const HeapVec &);

  // Move constructor
  // HeapVec(argument) specifiers;
  HeapVec(HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~HeapVec() specifiers;
  virtual ~HeapVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  HeapVec & operator=(const HeapVec &);

  // Move assignment
  // type operator=(argument) specifiers;
  HeapVec & operator=(HeapVec &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const HeapVec &) const noexcept;
  
  // type operator!=(argument) specifiers;
  bool operator!=(const HeapVec &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions 

  // type operator[](argument) specifiers; 
  const Data & operator[](unsigned long) const override;

  // type Front() specifiers; 
  const Data & Front() const override;

  // type Back() specifiers;
  const Data & Back() const override;

  // Override esplicito necessario per poter avere solo metodi di accesso non distruttivi (const)

  /* ************************************************************************ */

  // Specific member functions (inherited from Heap)

  // type IsHeap(argument) specifiers; // Override Heap member
  bool IsHeap() const override;

  // type Heapify(argument) specifiers; // Override Heap member
  void Heapify() override;

  /* ************************************************************************ */

  // Specific member function (inherited from SortableLinearContainer)

  // type Sort(argument) specifiers; // Override SortableLinearContainer member
  virtual void Sort() noexcept override;

  /* ************************************************************************ */
 
  using Vector<Data>::Clear;

protected:

  // Auxiliary functions, if necessary!

  // Specific constructor
  void RecursiveHeapify(unsigned long, unsigned long);
  void HeapSort() noexcept;

};

/* ************************************************************************** */

}

#include "heapvec.cpp"

#endif
