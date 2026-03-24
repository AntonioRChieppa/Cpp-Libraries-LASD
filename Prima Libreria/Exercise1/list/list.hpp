
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List : virtual public MutableLinearContainer<Data>, ClearableContainer{
  // Must extend MutableLinearContainer<Data>,
  //             ClearableContainer

private:

  // ...

protected:

  // using Container::???;
  using Container::size;

  struct Node {

    Data element;
    Node *next = nullptr;

    /* ********************************************************************** */

    inline Node() = default;
    // Specific constructors
    inline Node(const Data &);
    inline Node(Data &&) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    inline Node(const Node&);

    // Move constructor
    inline Node(Node&&) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node();

    /* ********************************************************************** */

    // Comparison operators
    bool operator == (const Node &) const noexcept;
    inline bool operator != (const Node &) const noexcept;

    /* ********************************************************************** */

    // Specific member functions

  };

  Node *head = nullptr;
  Node *tail = nullptr;

public:

  // Default constructor
  // List() specifiers;
  List() = default;
  

  /* ************************************************************************ */

  // Specific constructor
  // List(argument) specifiers; // A list obtained from a TraversableContainer
  List(const TraversableContainer<Data> &);
  // List(argument) specifiers; // A list obtained from a MappableContainer
  List(MappableContainer<Data> &&) noexcept;

  /* ************************************************************************ */

  // Copy constructor
  // List(argument) specifiers;
  List(const List &);

  // Move constructor
  // List(argument) specifiers;
  List(List &&) noexcept;

  /* ************************************************************************ */

  // Destructor
  // ~List() specifiers;
  virtual ~List();
  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;
  List & operator=(const List &);

  // Move assignment
  // type operator=(argument) specifiers;
  List & operator=(List &&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  bool operator==(const List &) const noexcept;
  // type operator!=(argument) specifiers;
  bool operator!=(const List &) const noexcept;

  /* ************************************************************************ */

  // Specific member functions

  // type InsertAtFront(argument) specifier; // Copy of the value
  void InsertAtFront(const Data &);
  // type InsertAtFront(argument) specifier; // Move of the value
  void InsertAtFront(Data &&);
  // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
  void RemoveFromFront();
  // type FrontNRemove() specifier; // (must throw std::length_error when empty)
  Data FrontNRemove();

  // type InsertAtBack(argument) specifier; // Copy of the value
  void InsertAtBack(const Data &);
  // type InsertAtBack(argument) specifier; // Move of the value
  void InsertAtBack(Data &&);
  // type RemoveFromBack() specifier; // (must throw std::length_error when empty)
  void RemoveFromBack();
  // type BackNRemove() specifier; // (must throw std::length_error when empty)
  Data BackNRemove();

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableLinearContainer)

  // type operator[](argument) specifiers; // Override MutableLinearContainer member (must throw std::out_of_range when out of range)
  Data & operator[](const unsigned long) override;

  // type Front() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  Data & Front() override;

  // type Back() specifiers; // Override MutableLinearContainer member (must throw std::length_error when empty)
  Data & Back() override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  // type operator[](argument) specifiers; // Override LinearContainer member (must throw std::out_of_range when out of range)
  const Data & operator[](const unsigned long) const override;

  // type Front() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  const Data & Front() const override;

  // type Back() specifiers; // Override LinearContainer member (must throw std::length_error when empty)
  const Data & Back() const override;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  // type Map(argument) specifiers; // Override MappableContainer member
  inline void Map(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  // type PreOrderMap(argument) specifiers; // Override PreOrderMappableContainer member
  inline void PreOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  // type PostOrderMap(argument) specifiers; // Override PostOrderMappableContainer member
  inline void PostOrderMap(MapFun) override;

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  // type Traverse(arguments) specifiers; // Override TraversableContainer member
  inline void Traverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  // type PreOrderTraverse(arguments) specifiers; // Override PreOrderTraversableContainer member
  inline void PreOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  // type PostOrderTraverse(arguments) specifiers; // Override PostOrderTraversableContainer member
  inline void PostOrderTraverse(TraverseFun) const override;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  // type Clear() specifiers; // Override ClearableContainer member
  void Clear() override;

protected:

  // Auxiliary functions, if necessary!
  void AttachAtFront(Node *) noexcept;
  void AttachAtBack(Node *) noexcept;
  Node* DetachFront();
  Node * DetachBack();
  Data DataNDelete(Node *);
  inline void PostOrderMapR(MapFun, Node *);
  inline void PostOrderTraverseR(TraverseFun, Node *) const;
  



};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
