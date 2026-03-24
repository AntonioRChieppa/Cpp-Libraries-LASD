
#ifndef PQHEAP_HPP
#define PQHEAP_HPP

/* ************************************************************************** */

#include "../pq.hpp"
#include "../../heap/vec/heapvec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PQHeap : virtual public PQ<Data>, virtual protected HeapVec<Data>{
  // Must extend PQ<Data>,
  // Could extend HeapVec<Data>

private:

  // ...

protected:

  // using Container::???;
  using Container::size;
  unsigned long capacity = 0;
  using HeapVec<Data>::Elements;

  // ...

public:

  // Default constructor
  // PQHeap() specifiers;
  PQHeap();

  /* ************************************************************************ */

  // Specific constructors
  // PQHeap(argument) specifiers; // A priority queue obtained from a TraversableContainer
  PQHeap(const TraversableContainer<Data> &);
  // PQHeap(argument) specifiers; // A priority queue obtained from a MappableContainer
  PQHeap(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // PQHeap(argument) specifiers;
  PQHeap(const PQHeap &);

  // Move constructor
  // PQHeap(argument) specifiers;
  PQHeap(PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~PQHeap() specifiers;
  virtual ~PQHeap() = default;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  PQHeap & operator=(const PQHeap &);

  // Move assignment
  // type operator=(argument) specifiers;
  PQHeap & operator=(PQHeap &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const PQHeap &) const noexcept;

  // type operator!=(argument) specifiers;
  bool operator!=(const PQHeap &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from PQ)

  // type Tip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  const Data & Tip() override;
  // type RemoveTip(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  void RemoveTip() override;
  // type TipNRemove(argument) specifiers; // Override PQ member (must throw std::length_error when empty)
  Data TipNRemove() override;

  // type Insert(argument) specifiers; // Override PQ member (Copy of the value)
  void Insert(const Data &) override;
  // type Insert(argument) specifiers; // Override PQ member (Move of the value)
  void Insert(Data &&) noexcept override;
  // type Change(argument) specifiers; // Override PQ member (Copy of the value)
  void Change(unsigned long, const Data &) override;
  // type Change(argument) specifiers; // Override PQ member (Move of the value)
  void Change(unsigned long, Data &&) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  // type Resize(argument) specifiers; // Override ResizableContainer member
  void Resize(unsigned long) override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

  // faccio using poichè in HeapVec espongo solo la versione const
  using HeapVec<Data>::operator[];
  using HeapVec<Data>::Front;
  using HeapVec<Data>::Back;


protected:

  // Auxiliary functions, if necessary!
  void HeapifyDown(unsigned long, unsigned long);
  inline void HeapifyUp(unsigned long);
  
};

/* ************************************************************************** */

}

#include "pqheap.cpp"

#endif
