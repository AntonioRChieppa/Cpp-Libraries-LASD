#include <iostream>
#include <stdexcept>
#include <string>
#include <limits>
#include <cmath>


#include "../container/container.hpp"
#include "../container/traversable.hpp"
#include "../container/Testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../set/set.hpp"

#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

#include "../heap/vec/heapvec.hpp"
#include "../pq/heap/pqheap.hpp"

#include "../zlasdtest/container/traversable.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */
int totalMyTests = 0;
int passedMyTests = 0;

void check(bool condition, const string& message) {
  ++totalMyTests;
  if (condition) {
    ++passedMyTests;
    cout << "[PASSED] " << message << endl;
  } else {
    cout << "[FAILED] " << message << endl;
  }
}

// ----------------- Inizio Tests 1a Libreria ----------------

// ----------------- Vector<int> MyTests -----------------

void MyTestVectorInt() {
  cout << "---! Exercise 1A - 1B MyTest !---\n" << endl;
  cout << "--- MyTest Vector<int> ---" << endl;
  lasd::Vector<int> v(3);
  v[0] = 10; v[1] = 20; v[2] = 30;

  v.Resize(2);
  check(v.Size() == 2, "Vector<int> resized down to 2");
  check(v[1] == 20, "Element at index 1 still valid after resize down");

  v.Resize(5);
  check(v.Size() == 5, "Vector<int> resized up to 5");
  check(v[3] == 0 && v[4] == 0, "New elements default-initialized");

  lasd::Vector<int> vCopy = v;
  check(vCopy.Size() == v.Size(), "Copied Vector<int> has same size");
  vCopy[0] = 100;
  check(v[0] == 10, "Original unchanged after copy modification");

  lasd::Vector<int> vMove = std::move(vCopy);
  check(vMove.Size() == 5, "Moved Vector<int> retains size");
  check(vCopy.Empty(), "Moved-from Vector<int> is empty");

  vMove.Clear();
  check(vMove.Empty(), "Vector<int> empty after Clear()");
}

// ----------------- Vector<Double> MyTests -----------------

void MyTestVectorDouble() {
  cout << "\n--- MyTest Vector<double> ---" << endl;
  lasd::Vector<double> v;
  v.Resize(4);
  v[0] = 1.1; v[1] = 2.2; v[2] = 3.3; v[3] = 4.4;

  v.Resize(6);
  v[4] = 5.5; v[5] = 6.6;
  check(v.Size() == 6, "Vector<double> resized up to 6");
  v.Resize(3);
  check(v.Size() == 3, "Vector<double> resized down to 3");

  lasd::Vector<double> vAssign;
  vAssign = v;
  check(vAssign.Size() == 3, "Copy assignment retains size");

  lasd::Vector<double> vMove;
  vMove = std::move(vAssign);
  check(vMove.Size() == 3, "Move assignment retains size");
  check(vAssign.Empty(), "Moved-from Vector<double> is empty");
}

// ----------------- Vector<char> MyTests -----------------

void MyTestVectorChar() {
  cout << "\n--- MyTest Vector<char> ---" << endl;
  lasd::Vector<char> v(2);
  v[0] = 'A'; v[1] = 'B';

  v.Resize(4);
  check(v[2] == '\0' && v[3] == '\0', "New Vector<char> elements default to '\\0'");

  lasd::Vector<char> vCopy(v);
  vCopy[0] = 'Z';
  check(v[0] == 'A', "Original vector unchanged after copy modification");

  lasd::Vector<char> vMove(std::move(vCopy));
  check(vMove.Size() == 4, "Moved vector retains size");
  check(vCopy.Empty(), "Moved-from vector is empty");
}

// ----------------- Vector<String> MyTests -----------------

void MyTestVectorString() {
  cout << "\n--- MyTest Vector<string> ---" << endl;
  lasd::Vector<string> v;
  v.Resize(3);
  v[0] = "foo";
  v[1] = "bar";
  v[2] = "baz";

  v.Resize(2);
  check(v.Size() == 2, "Vector<string> resized down to 2");
  check(v[1] == "bar", "Element at index 1 retained after resize down");

  v.Resize(5);
  check(v[3].empty() && v[4].empty(), "New elements default to empty string");

  lasd::Vector<string> vCopy = v;
  vCopy[0] = "changed";
  check(v[0] == "foo", "Original vector unchanged after copy mod");

  lasd::Vector<string> vMove = std::move(vCopy);
  check(vMove.Size() == 5, "Moved vector retains size");
  check(vCopy.Empty(), "Moved-from vector empty");
}

// ----------------- List<Int> MyTests -----------------

void MyTestListInt() {
  cout << "\n--- MyTest List<int> ---" << endl;
  lasd::List<int> l;

  l.InsertAtFront(10);
  l.InsertAtBack(20);
  l.InsertAtFront(5);
  check(l.Size() == 3, "List<int> size after multiple inserts");
  check(l.Front() == 5, "Front element after inserts");
  check(l.Back() == 20, "Back element after inserts");

  l.RemoveFromFront();
  check(l.Front() == 10, "Front element after removal");
  l.RemoveFromBack();
  check(l.Back() == 10, "Back element after removal");

  lasd::List<int> lCopy(l);
  check(lCopy.Size() == 1 && lCopy.Front() == 10, "Copy constructor copies elements");

  lasd::List<int> lAssign;
  lAssign = l;
  check(lAssign.Size() == 1 && lAssign.Back() == 10, "Assignment copies elements");

  lasd::List<int> lMove(std::move(lAssign));
  check(lMove.Size() == 1 && lMove.Front() == 10, "Move constructor works");
  check(lAssign.Empty(), "Moved-from list empty");

  lMove.Clear();
  check(lMove.Empty(), "List empty after clear");
}

// ----------------- List<Double> MyTests -----------------

void MyTestListDouble() {
  cout << "\n--- MyTest List<double> ---" << endl;
  lasd::List<double> l;

  l.InsertAtBack(1.1);
  l.InsertAtFront(2.2);
  l.InsertAtBack(3.3);
  check(l.Size() == 3, "List<double> size after inserts");

  l.RemoveFromBack();
  check(l.Back() == 1.1, "Back element after removal");
  l.RemoveFromFront();
  check(l.Front() == 1.1, "Front element after removal");

  lasd::List<double> lCopy(l);
  check(lCopy.Size() == 1, "Copy constructor copies correctly");

  lasd::List<double> lAssign;
  lAssign = l;
  check(lAssign.Front() == 1.1, "Assignment copies correctly");

  lasd::List<double> lMove(std::move(lAssign));
  check(lMove.Size() == 1, "Move constructor works");
  check(lAssign.Empty(), "Moved-from list empty");

  lMove.Clear();
  check(lMove.Empty(), "List empty after clear");
}

// ----------------- List<Char> MyTests -----------------

void MyTestListChar() {
  cout << "\n--- MyTest List<char> ---" << endl;
  lasd::List<char> l;

  l.InsertAtBack('a');
  l.InsertAtFront('b');
  l.InsertAtBack('c');
  check(l.Size() == 3, "List<char> size after inserts");
  check(l.Front() == 'b', "Front is 'b'");
  check(l.Back() == 'c', "Back is 'c'");

  l.RemoveFromFront();
  check(l.Front() == 'a', "Front after removal");
  l.RemoveFromBack();
  check(l.Back() == 'a', "Back after removal");

  lasd::List<char> lCopy(l);
  check(lCopy.Size() == 1 && lCopy.Front() == 'a', "Copy constructor works");

  lasd::List<char> lAssign;
  lAssign = l;
  check(lAssign.Back() == 'a', "Assignment works");

  lasd::List<char> lMove(std::move(lAssign));
  check(lMove.Size() == 1, "Move constructor works");
  check(lAssign.Empty(), "Moved-from list empty");

  lMove.Clear();
  check(lMove.Empty(), "List empty after clear");
}

// ----------------- List<String> MyTests -----------------

void MyTestListString() {
  cout << "\n--- MyTest List<string> ---" << endl;
  lasd::List<string> l;

  l.InsertAtBack("foo");
  l.InsertAtFront("bar");
  l.InsertAtBack("baz");
  check(l.Size() == 3, "List<string> size after inserts");
  check(l.Front() == "bar", "Front is 'bar'");
  check(l.Back() == "baz", "Back is 'baz'");

  l.RemoveFromFront();
  check(l.Front() == "foo", "Front after removal");
  l.RemoveFromBack();
  check(l.Back() == "foo", "Back after removal");

  lasd::List<string> lCopy(l);
  check(lCopy.Size() == 1 && lCopy.Front() == "foo", "Copy constructor works");

  lasd::List<string> lAssign;
  lAssign = l;
  check(lAssign.Back() == "foo", "Assignment works");

  lasd::List<string> lMove(std::move(lAssign));
  check(lMove.Size() == 1, "Move constructor works");
  check(lAssign.Empty(), "Moved-from list empty");

  lMove.Clear();
  check(lMove.Empty(), "List empty after clear");
}

// ----------------- SetVec<int> MyTests -----------------

void MyTestSetVecInt() {
  cout << "\n--- MyTest SetVec<int> ---" << endl;
  lasd::SetVec<int> s;

  s.Insert(10);
  s.Insert(20);
  s.Insert(30);
  check(s.Exists(20), "SetVec<int> contains 20 after insert");
  check(!s.Exists(40), "SetVec<int> does not contain 40");

  size_t sizeBefore = s.Size();
  s.Insert(10);
  check(s.Size() == sizeBefore, "SetVec<int> size unchanged after duplicate insert");

  s.Remove(20);
  check(!s.Exists(20), "SetVec<int> no longer contains 20 after removal");
  s.Remove(100); 
  check(s.Size() == 2, "SetVec<int> size after removing non-existing element remains same");

  lasd::SetVec<int> sCopy(s);
  check(sCopy.Size() == s.Size(), "Copy constructor copies size");
  check(sCopy.Exists(10), "Copy contains 10");
  check(sCopy.Exists(30), "Copy contains 30");

  lasd::SetVec<int> sAssign;
  sAssign = s;
  check(sAssign.Exists(10) && sAssign.Exists(30), "Assignment operator copies elements");

  lasd::SetVec<int> sMove(std::move(sAssign));
  check(sMove.Exists(10), "Move constructor preserves elements");
  check(sAssign.Empty(), "Moved-from SetVec<int> is empty");

  sMove.Clear();
  check(sMove.Empty(), "SetVec<int> empty after Clear()");
}

//----------------- SetVec<Double> MyTests -----------------

void MyTestSetVecDouble() {
  cout << "\n--- MyTest SetVec<double> ---" << endl;
  lasd::SetVec<double> s;

  s.Insert(1.5);
  s.Insert(2.5);
  s.Insert(3.5);
  check(s.Exists(2.5), "SetVec<double> contains 2.5");
  check(!s.Exists(4.5), "SetVec<double> does not contain 4.5");

  size_t initialSize = s.Size();
  s.Insert(1.5);
  check(s.Size() == initialSize, "Duplicate insert does not increase size");

  s.Remove(2.5);
  check(!s.Exists(2.5), "SetVec<double> no longer contains 2.5");

  lasd::SetVec<double> sCopy(s);
  lasd::SetVec<double> sMoved = std::move(sCopy);
  check(sMoved.Exists(1.5) && sMoved.Exists(3.5), "Move constructor keeps elements");
  check(sCopy.Empty(), "Moved-from SetVec<double> is empty");

  sMoved.Clear();
  check(sMoved.Empty(), "SetVec<double> empty after Clear()");
}

//----------------- SetVec<Char> MyTests -----------------

void MyTestSetVecChar() {
  cout << "\n--- MyTest SetVec<char> ---" << endl;
  lasd::SetVec<char> s;

  s.Insert('a');
  s.Insert('z');
  s.Insert('m');
  check(s.Exists('a') && s.Exists('z') && s.Exists('m'), "Inserted chars exist");

  s.Remove('z');
  check(!s.Exists('z'), "Char 'z' removed");

  lasd::SetVec<char> sCopy(s);
  check(sCopy.Exists('a') && sCopy.Exists('m'), "Copy retains chars");

  lasd::SetVec<char> sMove(std::move(sCopy));
  check(sMove.Exists('a'), "Move constructor keeps 'a'");
  check(sCopy.Empty(), "Moved-from SetVec<char> empty");

  sMove.Clear();
  check(sMove.Empty(), "SetVec<char> empty after Clear()");
}

//----------------- SetVec<String> MyTests -----------------

void MyTestSetVecString() {
  cout << "\n--- MyTest SetVec<string> ---" << endl;
  lasd::SetVec<string> s;

  s.Insert("hello");
  s.Insert("world");
  s.Insert("MyTest");
  check(s.Exists("world"), "SetVec<string> contains 'world'");

  s.Remove("MyTest");
  check(!s.Exists("MyTest"), "'MyTest' removed from SetVec<string>");

  lasd::SetVec<string> sCopy(s);
  lasd::SetVec<string> sMoved = std::move(sCopy);
  check(sMoved.Exists("hello"), "Moved SetVec<string> retains 'hello'");
  check(sCopy.Empty(), "Moved-from SetVec<string> empty");

  sMoved.Clear();
  check(sMoved.Empty(), "SetVec<string> empty after Clear()");
}

//----------------- SetLst<Int> MyTests -----------------

void MyTestSetLstInt() {
  cout << "\n--- MyTest SetLst<int> ---" << endl;
  lasd::SetLst<int> s;

  s.Insert(7);
  s.Insert(14);
  s.Insert(21);
  check(s.Exists(14), "SetLst<int> contains 14");
  check(!s.Exists(100), "SetLst<int> does not contain 100");

  size_t sizeBefore = s.Size();
  s.Insert(7);
  check(s.Size() == sizeBefore, "Duplicate insert does not increase SetLst<int> size");

  s.Remove(14);
  check(!s.Exists(14), "14 removed from SetLst<int>");

  lasd::SetLst<int> sCopy(s);
  lasd::SetLst<int> sAssigned;
  sAssigned = s;
  check(sCopy.Exists(7) && sCopy.Exists(21), "Copy constructor copies elements");
  check(sAssigned.Exists(7) && sAssigned.Exists(21), "Assignment operator copies elements");

  lasd::SetLst<int> sMoved(std::move(sAssigned));
  check(sMoved.Exists(7), "Move constructor preserves elements");
  check(sAssigned.Empty(), "Moved-from SetLst<int> is empty");

  sMoved.Clear();
  check(sMoved.Empty(), "SetLst<int> empty after Clear()");
}

//----------------- SetLst<Double> MyTests -----------------

void MyTestSetLstDouble() {
  cout << "\n--- MyTest SetLst<double> ---" << endl;
  lasd::SetLst<double> s;

  s.Insert(0.1);
  s.Insert(0.2);
  s.Insert(0.3);
  check(s.Exists(0.2), "SetLst<double> contains 0.2");

  s.Remove(0.2);
  check(!s.Exists(0.2), "0.2 removed from SetLst<double>");

  size_t sizeBefore = s.Size();
  s.Insert(0.1);
  check(s.Size() == sizeBefore, "Duplicate insert does not increase size");

  lasd::SetLst<double> sCopy(s);
  check(sCopy.Exists(0.1) && sCopy.Exists(0.3), "Copy constructor copies elements");

  lasd::SetLst<double> sAssign;
  sAssign = s;
  check(sAssign.Exists(0.3), "Assignment operator copies elements");

  lasd::SetLst<double> sMove(std::move(sAssign));
  check(sMove.Exists(0.1), "Move constructor preserves elements");
  check(sAssign.Empty(), "Moved-from SetLst<double> is empty");

  size_t sizeNow = sMove.Size();
  sMove.Remove(5.5);
  check(sMove.Size() == sizeNow, "Remove non-existing element does not change size");

  sMove.Clear();
  check(sMove.Empty(), "SetLst<double> empty after Clear()");
}

//----------------- SetLst<Char> MyTests -----------------

void MyTestSetLstChar() {
  cout << "\n--- MyTest SetLst<char> ---" << endl;
  lasd::SetLst<char> s;

  s.Insert('x');
  s.Insert('y');
  s.Insert('z');
  check(s.Exists('y'), "SetLst<char> contains 'y'");

  s.Remove('y');
  check(!s.Exists('y'), "Char 'y' removed");

  size_t sizeBefore = s.Size();
  s.Insert('x');
  check(s.Size() == sizeBefore, "Duplicate insert does not increase size");

  lasd::SetLst<char> sCopy(s);
  check(sCopy.Exists('x') && sCopy.Exists('z'), "Copy constructor copies elements");

  lasd::SetLst<char> sAssign;
  sAssign = s;
  check(sAssign.Exists('z'), "Assignment operator copies elements");

  lasd::SetLst<char> sMove(std::move(sAssign));
  check(sMove.Exists('x'), "Move constructor preserves elements");
  check(sAssign.Empty(), "Moved-from SetLst<char> is empty");

  size_t sizeNow = sMove.Size();
  sMove.Remove('q');
  check(sMove.Size() == sizeNow, "Remove non-existing element does not change size");

  sMove.Clear();
  check(sMove.Empty(), "SetLst<char> empty after Clear()");
}

//----------------- SetLst<String> MyTests -----------------

void MyTestSetLstString() {
  cout << "\n--- MyTest SetLst<string> ---" << endl;
  lasd::SetLst<string> s;

  s.Insert("one");
  s.Insert("two");
  s.Insert("three");
  check(s.Exists("two"), "SetLst<string> contains 'two'");

  s.Remove("two");
  check(!s.Exists("two"), "'two' removed from SetLst<string>");

  size_t sizeBefore = s.Size();
  s.Insert("one");
  check(s.Size() == sizeBefore, "Duplicate insert does not increase size");

  lasd::SetLst<string> sCopy(s);
  check(sCopy.Exists("one") && sCopy.Exists("three"), "Copy constructor copies elements");

  lasd::SetLst<string> sAssign;
  sAssign = s;
  check(sAssign.Exists("three"), "Assignment operator copies elements");

  lasd::SetLst<string> sMove(std::move(sAssign));
  check(sMove.Exists("one"), "Move constructor preserves elements");
  check(sAssign.Empty(), "Moved-from SetLst<string> is empty");

  size_t sizeNow = sMove.Size();
  sMove.Remove("nonexistent");
  check(sMove.Size() == sizeNow, "Remove non-existing element does not change size");

  sMove.Clear();
  check(sMove.Empty(), "SetLst<string> empty after Clear()");
}

// ----------------- Fine Tests 1a Libreria ----------------

// ----------------- Inizio Tests 2a Libreria ----------------

// ----------------- HeapVec<int> MyTests -----------------

void MyTestHeapVecInt() {
  cout << "---! Exercise 2A - 2B MyTest !---\n" << endl;
  cout << "\n--- MyTest HeapVec<int> ---" << endl;

  lasd::HeapVec<int> h;
  check(h.Empty(), "HeapVec<int> empty after default ctor");
  check(h.Size() == 0, "HeapVec<int> size 0 after default ctor");
  h.Clear();
  check(h.Empty(), "HeapVec<int> empty after Clear on empty heap");

  lasd::SortableVector<int> v(5);
  v[0]=5; v[1]=1; v[2]=3; v[3]=4; v[4]=2;
  lasd::HeapVec<int> h2(v);
  check(h2.IsHeap(), "HeapVec<int> heapified from vector");
  h2.Sort();
  check(!h2.IsHeap(), "HeapVec<int> not heap after Sort");
  h2.Heapify();
  check(h2.IsHeap(), "HeapVec<int> heapified after Heapify");

  h2.Heapify();
  check(h2.IsHeap(), "HeapVec<int> Heapify on already heapified heap");

  lasd::HeapVec<int> h3;
  h3.Heapify();
  check(h3.Empty(), "HeapVec<int> Heapify on empty heap does not crash");

  lasd::HeapVec<int> h4(h2);
  check(h4 == h2, "HeapVec<int> copy constructor");
  lasd::HeapVec<int> h5(std::move(h4));
  check(h5.IsHeap(), "HeapVec<int> move constructor keeps heap property");
  check(h4.Empty(), "HeapVec<int> moved-from is empty");

  lasd::HeapVec<int> h6;
  h6 = h2;
  check(h6 == h2, "HeapVec<int> copy assignment");

  lasd::HeapVec<int> h7;
  h7 = std::move(h6);
  check(h7.IsHeap(), "HeapVec<int> move assignment keeps heap property");
  check(h6.Empty(), "HeapVec<int> moved-from is empty after move assignment");

  h7.Clear();
  check(h7.Empty(), "HeapVec<int> Clear empties heap");

  lasd::SortableVector<int> v2(10);
  for (int i = 0; i < 10; ++i) v2[i] = 10 - i;
  lasd::HeapVec<int> h8(v2);
  check(h8.IsHeap(), "HeapVec<int> heapified from descending vector");

  lasd::SortableVector<int> v3(10);
  for (int i = 0; i < 10; ++i) v3[i] = i;
  lasd::HeapVec<int> h9(v3);
  check(h9.IsHeap(), "HeapVec<int> heapified from ascending vector");

  lasd::SortableVector<int> v4(6);
  v4[0]=1; v4[1]=2; v4[2]=2; v4[3]=1; v4[4]=2; v4[5]=1;
  lasd::HeapVec<int> h10(v4);
  check(h10.IsHeap(), "HeapVec<int> heapified from vector with duplicates");

  lasd::SortableVector<int> v5(5);
  for (unsigned long i = 0; i < 5; ++i) v5[i] = 42;
  lasd::HeapVec<int> h11(v5);
  check(h11.IsHeap(), "HeapVec<int> heapified from vector with all equal elements");

  lasd::SortableVector<int> v6(1);
  v6[0]=99;
  lasd::HeapVec<int> h12(v6);
  check(h12.IsHeap(), "HeapVec<int> heapified from vector size 1");

  lasd::SortableVector<int> v7;
  lasd::HeapVec<int> h13(v7);
  check(h13.Empty(), "HeapVec<int> heapified from empty vector");

  h13.Sort();
  check(h13.Empty(), "HeapVec<int> Sort on empty heap does not crash");

  h12.Sort();
  check(h12.Size() == 1, "HeapVec<int> Sort on heap size 1 does not crash");

  check(h12 != h13, "HeapVec<int> operator!= works");

  lasd::HeapVec<int> h14;
  check(h13 == h14, "HeapVec<int> operator== on empty heaps");

  check(!(h12 == h13), "HeapVec<int> operator== on different heaps");

  lasd::HeapVec<int> h15(h12);
  check(!(h12 != h15), "HeapVec<int> operator!= on equal heaps");

  // --- STRESS TESTS ---
  {
    lasd::SortableVector<int> v(1000);
    for (int i = 0; i < 1000; ++i) v[i] = rand();
    lasd::HeapVec<int> hBig(v);
    check(hBig.IsHeap(), "HeapVec<int> heapified from large random vector");
    hBig.Sort();
    check(!hBig.IsHeap(), "HeapVec<int> not heap after Sort (large)");
    hBig.Heapify();
    check(hBig.IsHeap(), "HeapVec<int> heapified again after Sort (large)");
  }

  {
    lasd::SortableVector<int> v(100);
    for (int i = 0; i < 100; ++i) v[i] = i;
    lasd::HeapVec<int> hAsc(v);
    check(hAsc.IsHeap(), "HeapVec<int> heapified from ascending vector (large)");
  }

  {
    lasd::SortableVector<int> v(100);
    for (int i = 0; i < 100; ++i) v[i] = 100 - i;
    lasd::HeapVec<int> hDesc(v);
    check(hDesc.IsHeap(), "HeapVec<int> heapified from descending vector (large)");
  }

  {
    lasd::SortableVector<int> v(100);
    for (int i = 0; i < 100; ++i) v[i] = (i % 2 == 0) ? 1 : 2;
    lasd::HeapVec<int> hDup(v);
    check(hDup.IsHeap(), "HeapVec<int> heapified from alternating duplicates");
  }

  {
    for (int rep = 0; rep < 5; ++rep) {
      lasd::SortableVector<int> v(50);
      for (int i = 0; i < 50; ++i) v[i] = i;
      lasd::HeapVec<int> h(v);
      check(h.IsHeap(), "HeapVec<int> is heap after heapify from vector");
      h.Clear();
      check(h.Empty(), "HeapVec<int> empty after Clear (repeated)");
    }
  }
 
  {
    lasd::SortableVector<int> v(200);
    for (int i = 0; i < 200; ++i) v[i] = rand();
    lasd::HeapVec<int> h1(v);
    lasd::HeapVec<int> h2(h1);
    check(h2.IsHeap(), "HeapVec<int> copy constructor on large heap");
    lasd::HeapVec<int> h3(std::move(h1));
    check(h3.IsHeap(), "HeapVec<int> move constructor on large heap");
    h2 = h3;
    check(h2.IsHeap(), "HeapVec<int> copy assignment on large heap");
    h1 = std::move(h2);
    check(h1.IsHeap(), "HeapVec<int> move assignment on large heap");
  }
}

// ----------------- HeapVec<double> MyTests -----------------

void MyTestHeapVecDouble() {
  cout << "\n--- MyTest HeapVec<double> ---" << endl;

  lasd::HeapVec<double> h;
  check(h.Empty(), "HeapVec<double> empty after default ctor");
  h.Clear();
  check(h.Empty(), "HeapVec<double> empty after Clear");

  lasd::SortableVector<double> v(4);
  v[0]=1.1; v[1]=2.2; v[2]=3.3; v[3]=4.4;
  lasd::HeapVec<double> h2(v);
  check(h2.IsHeap(), "HeapVec<double> heapified from vector");

  h2.Sort();
  check(!h2.IsHeap(), "HeapVec<double> not heap after Sort");
  h2.Heapify();
  check(h2.IsHeap(), "HeapVec<double> heapified after Heapify");

  lasd::SortableVector<double> v2(3);
  v2[0]=std::numeric_limits<double>::infinity();
  v2[1]=std::numeric_limits<double>::quiet_NaN();
  v2[2]=-std::numeric_limits<double>::infinity();
  lasd::HeapVec<double> h3(v2);
  check(h3.Size() == 3, "HeapVec<double> heapified with inf and NaN");

  lasd::SortableVector<double> v3(5);
  for (unsigned long i = 0; i < 5; ++i) v3[i] = 2.5;
  lasd::HeapVec<double> h4(v3);
  check(h4.IsHeap(), "HeapVec<double> heapified from vector with all equal elements");

  lasd::HeapVec<double> h5(h4);
  check(h4 == h5, "HeapVec<double> operator== on equal heaps");
  check(!(h4 != h5), "HeapVec<double> operator!= on equal heaps");

  lasd::HeapVec<double> h6;
  lasd::HeapVec<double> h7;
  check(h6 == h7, "HeapVec<double> operator== on empty heaps");

  check(h4 != h6, "HeapVec<double> operator!= on different heaps");

  // --- STRESS TESTS ---
  {
    lasd::SortableVector<double> v(1000);
    for (int i = 0; i < 1000; ++i) v[i] = (double)rand() / (rand() + 1);
    lasd::HeapVec<double> hBig(v);
    check(hBig.IsHeap(), "HeapVec<double> heapified from large random vector");
    hBig.Sort();
    check(!hBig.IsHeap(), "HeapVec<double> not heap after Sort (large)");
    hBig.Heapify();
    check(hBig.IsHeap(), "HeapVec<double> heapified again after Sort (large)");
  }

  {
    lasd::SortableVector<double> v(100);
    for (int i = 0; i < 100; ++i) v[i] = i * 0.1;
    lasd::HeapVec<double> hAsc(v);
    check(hAsc.IsHeap(), "HeapVec<double> heapified from ascending vector (large)");
  }
  
  {
    lasd::SortableVector<double> v(100);
    for (int i = 0; i < 100; ++i) v[i] = (100 - i) * 0.1;
    lasd::HeapVec<double> hDesc(v);
    check(hDesc.IsHeap(), "HeapVec<double> heapified from descending vector (large)");
  }
 
  {
    lasd::SortableVector<double> v(100);
    for (int i = 0; i < 100; ++i) v[i] = (i % 2 == 0) ? 1.5 : 2.5;
    lasd::HeapVec<double> hDup(v);
    check(hDup.IsHeap(), "HeapVec<double> heapified from alternating duplicates");
  }
 
  {
    for (int rep = 0; rep < 5; ++rep) {
      lasd::SortableVector<double> v(50);
      for (int i = 0; i < 50; ++i) v[i] = i * 0.1;
      lasd::HeapVec<double> h(v);
      check(h.IsHeap(), "HeapVec<double> is heap after heapify from vector");
      h.Clear();
      check(h.Empty(), "HeapVec<double> empty after Clear (repeated)");
    }
  }

  {
    lasd::SortableVector<double> v(200);
    for (int i = 0; i < 200; ++i) v[i] = (double)rand() / (rand() + 1);
    lasd::HeapVec<double> h1(v);
    lasd::HeapVec<double> h2(h1);
    check(h2.IsHeap(), "HeapVec<double> copy constructor on large heap");
    lasd::HeapVec<double> h3(std::move(h1));
    check(h3.IsHeap(), "HeapVec<double> move constructor on large heap");
    h2 = h3;
    check(h2.IsHeap(), "HeapVec<double> copy assignment on large heap");
    h1 = std::move(h2);
    check(h1.IsHeap(), "HeapVec<double> move assignment on large heap");
  }
}

// ----------------- HeapVec<char> MyTests -----------------

void MyTestHeapVecChar() {
  cout << "\n--- MyTest HeapVec<char> ---" << endl;

  lasd::HeapVec<char> h;
  check(h.Empty(), "HeapVec<char> empty after default ctor");
  h.Clear();
  check(h.Empty(), "HeapVec<char> empty after Clear");

  lasd::SortableVector<char> v(4);
  v[0]='a'; v[1]='b'; v[2]='c'; v[3]='d';
  lasd::HeapVec<char> h2(v);
  check(h2.IsHeap(), "HeapVec<char> heapified from vector");

  h2.Sort();
  check(!h2.IsHeap(), "HeapVec<char> not heap after Sort");
  h2.Heapify();
  check(h2.IsHeap(), "HeapVec<char> heapified after Heapify");

  lasd::SortableVector<char> v2(5);
  for (unsigned long i = 0; i < 5; ++i) v2[i] = 'z';
  lasd::HeapVec<char> h3(v2);
  check(h3.IsHeap(), "HeapVec<char> heapified from vector with all equal elements");

  lasd::HeapVec<char> h4(h3);
  check(h3 == h4, "HeapVec<char> operator== on equal heaps");
  check(!(h3 != h4), "HeapVec<char> operator!= on equal heaps");

  lasd::HeapVec<char> h5;
  lasd::HeapVec<char> h6;
  check(h5 == h6, "HeapVec<char> operator== on empty heaps");

  check(h3 != h5, "HeapVec<char> operator!= on different heaps");

  // --- STRESS TESTS ---
  {
    lasd::SortableVector<char> v(1000);
    for (int i = 0; i < 1000; ++i) v[i] = (char)('a' + rand() % 26);
    lasd::HeapVec<char> hBig(v);
    check(hBig.IsHeap(), "HeapVec<char> heapified from large random vector");
    hBig.Sort();
    check(!hBig.IsHeap(), "HeapVec<char> not heap after Sort (large)");
    hBig.Heapify();
    check(hBig.IsHeap(), "HeapVec<char> heapified again after Sort (large)");
  }

  {
    lasd::SortableVector<char> v(26);
    for (int i = 0; i < 26; ++i) v[i] = (char)('a' + i);
    lasd::HeapVec<char> hAsc(v);
    check(hAsc.IsHeap(), "HeapVec<char> heapified from ascending vector (large)");
  }

  {
    lasd::SortableVector<char> v(26);
    for (int i = 0; i < 26; ++i) v[i] = (char)('z' - i);
    lasd::HeapVec<char> hDesc(v);
    check(hDesc.IsHeap(), "HeapVec<char> heapified from descending vector (large)");
  }

  {
    lasd::SortableVector<char> v(100);
    for (int i = 0; i < 100; ++i) v[i] = (i % 2 == 0) ? 'x' : 'y';
    lasd::HeapVec<char> hDup(v);
    check(hDup.IsHeap(), "HeapVec<char> heapified from alternating duplicates");
  }

  {
    for (int rep = 0; rep < 5; ++rep) {
      lasd::SortableVector<char> v(26);
      for (int i = 0; i < 26; ++i) v[i] = (char)('a' + i);
      lasd::HeapVec<char> h(v);
      check(h.IsHeap(), "HeapVec<char> is heap after heapify from vector");
      h.Clear();
      check(h.Empty(), "HeapVec<char> empty after Clear (repeated)");
    }
  }
 
  {
    lasd::SortableVector<char> v(100);
    for (int i = 0; i < 100; ++i) v[i] = (char)('a' + rand() % 26);
    lasd::HeapVec<char> h1(v);
    lasd::HeapVec<char> h2(h1);
    check(h2.IsHeap(), "HeapVec<char> copy constructor on large heap");
    lasd::HeapVec<char> h3(std::move(h1));
    check(h3.IsHeap(), "HeapVec<char> move constructor on large heap");
    h2 = h3;
    check(h2.IsHeap(), "HeapVec<char> copy assignment on large heap");
    h1 = std::move(h2);
    check(h1.IsHeap(), "HeapVec<char> move assignment on large heap");
  }
}

// ----------------- HeapVec<string> MyTests -----------------

void MyTestHeapVecString() {
  cout << "\n--- MyTest HeapVec<string> ---" << endl;

  lasd::HeapVec<string> h;
  check(h.Empty(), "HeapVec<string> empty after default ctor");
  h.Clear();
  check(h.Empty(), "HeapVec<string> empty after Clear");

  lasd::SortableVector<string> v(4);
  v[0]="a"; v[1]="b"; v[2]="c"; v[3]="d";
  lasd::HeapVec<string> h2(v);
  check(h2.IsHeap(), "HeapVec<string> heapified from vector");

  h2.Sort();
  check(!h2.IsHeap(), "HeapVec<string> not heap after Sort");
  h2.Heapify();
  check(h2.IsHeap(), "HeapVec<string> heapified after Heapify");

  lasd::SortableVector<string> v2(5);
  for (unsigned long i = 0; i < 5; ++i) v2[i] = "z";
  lasd::HeapVec<string> h3(v2);
  check(h3.IsHeap(), "HeapVec<string> heapified from vector with all equal elements");

  lasd::HeapVec<string> h4(h3);
  check(h3 == h4, "HeapVec<string> operator== on equal heaps");
  check(!(h3 != h4), "HeapVec<string> operator!= on equal heaps");

  lasd::HeapVec<string> h5;
  lasd::HeapVec<string> h6;
  check(h5 == h6, "HeapVec<string> operator== on empty heaps");

  check(h3 != h5, "HeapVec<string> operator!= on different heaps");

  // --- STRESS TESTS ---
  {
    lasd::SortableVector<string> v(500);
    for (int i = 0; i < 500; ++i) v[i] = std::to_string(rand());
    lasd::HeapVec<string> hBig(v);
    check(hBig.IsHeap(), "HeapVec<string> heapified from large random vector");
    hBig.Sort();
    check(!hBig.IsHeap(), "HeapVec<string> not heap after Sort (large)");
    hBig.Heapify();
    check(hBig.IsHeap(), "HeapVec<string> heapified again after Sort (large)");
  }
  
  {
    lasd::SortableVector<string> v(26);
    for (int i = 0; i < 26; ++i) v[i] = string(1, 'a' + i);
    lasd::HeapVec<string> hAsc(v);
    check(hAsc.IsHeap(), "HeapVec<string> heapified from ascending vector (large)");
  }
  
  {
    lasd::SortableVector<string> v(26);
    for (int i = 0; i < 26; ++i) v[i] = string(1, 'z' - i);
    lasd::HeapVec<string> hDesc(v);
    check(hDesc.IsHeap(), "HeapVec<string> heapified from descending vector (large)");
  }
 
  {
    lasd::SortableVector<string> v(100);
    for (int i = 0; i < 100; ++i) v[i] = (i % 2 == 0) ? "foo" : "bar";
    lasd::HeapVec<string> hDup(v);
    check(hDup.IsHeap(), "HeapVec<string> heapified from alternating duplicates");
  }
  
  {
    for (int rep = 0; rep < 5; ++rep) {
      lasd::SortableVector<string> v(26);
      for (int i = 0; i < 26; ++i) v[i] = string(1, 'a' + i);
      lasd::HeapVec<string> h(v);
      check(h.IsHeap(), "HeapVec<string> is heap after heapify from vector");
      h.Clear();
      check(h.Empty(), "HeapVec<string> empty after Clear (repeated)");
    }
  }
  
  {
    lasd::SortableVector<string> v(100);
    for (int i = 0; i < 100; ++i) v[i] = std::to_string(rand());
    lasd::HeapVec<string> h1(v);
    lasd::HeapVec<string> h2(h1);
    check(h2.IsHeap(), "HeapVec<string> copy constructor on large heap");
    lasd::HeapVec<string> h3(std::move(h1));
    check(h3.IsHeap(), "HeapVec<string> move constructor on large heap");
    h2 = h3;
    check(h2.IsHeap(), "HeapVec<string> copy assignment on large heap");
    h1 = std::move(h2);
    check(h1.IsHeap(), "HeapVec<string> move assignment on large heap");
  }
}

// ----------------- PQHeap<int> MyTests -----------------

void MyTestPQHeapInt() {
  cout << "\n--- MyTest PQHeap<int> ---" << endl;

  lasd::PQHeap<int> pq;
  check(pq.Empty(), "PQHeap<int> empty after default ctor");
  pq.Clear();
  check(pq.Empty(), "PQHeap<int> empty after Clear");

  pq.Insert(10);
  check(pq.Tip() == 10, "PQHeap<int> Tip after first insert");
  pq.Insert(20);
  check(pq.Tip() == 20, "PQHeap<int> Tip after inserting greater value");
  pq.Insert(5);
  check(pq.Tip() == 20, "PQHeap<int> Tip remains maximum");

  pq.RemoveTip();
  check(pq.Tip() == 10, "PQHeap<int> Tip after RemoveTip");
  int tip = pq.TipNRemove();
  check(tip == 10, "PQHeap<int> TipNRemove returns maximum");
  check(pq.Tip() == 5, "PQHeap<int> Tip after TipNRemove");

  pq.RemoveTip();
  check(pq.Empty(), "PQHeap<int> empty after final RemoveTip");

  for (int i = 0; i < 100; ++i) pq.Insert(i);
  check(pq.Tip() == 99, "PQHeap<int> Tip after 100 inserts");
  pq.Clear();
  check(pq.Empty(), "PQHeap<int> empty after massive Clear");

  pq.Insert(1); pq.Insert(2); pq.Insert(3);
  pq.RemoveTip();
  check(pq.Tip() == 2, "PQHeap<int> RemoveTip alternated");

  pq.Insert(5); pq.Insert(4);
  pq.Change(1, 10);
  check(pq.Tip() == 10, "PQHeap<int> Change increases priority");

  pq.Change(0, 1);
  check(pq.Tip() == 5, "PQHeap<int> Change decreases priority");

  pq.Change(0, 1);
  check(pq.Tip() == 2, "PQHeap<int> Change with same value");

  bool thrown = false;
  try { pq.Change(100, 1); } catch (const std::out_of_range&) { thrown = true; }
  check(thrown, "PQHeap<int> Change out of range index throws");

  pq.Clear();
  thrown = false;
  try { pq.Tip(); } catch (const std::length_error&) { thrown = true; }
  check(thrown, "PQHeap<int> Tip on empty heap throws");

  thrown = false;
  try { pq.RemoveTip(); } catch (const std::length_error&) { thrown = true; }
  check(thrown, "PQHeap<int> RemoveTip on empty heap throws");

  thrown = false;
  try { pq.TipNRemove(); } catch (const std::length_error&) { thrown = true; }
  check(thrown, "PQHeap<int> TipNRemove on empty heap throws");

  // --- STRESS TESTS ---
  {
    lasd::PQHeap<int> pq2;
    for (int i = 0; i < 1000; ++i) pq2.Insert(i);
    check(pq2.Tip() == 999, "PQHeap<int> Tip after 1k inserts");
    for (int i = 0; i < 999; ++i) pq2.RemoveTip();
    check(pq2.Tip() == 0, "PQHeap<int> Tip after removing all but one");
    pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<int> empty after removing all");
  }
  
  {
    lasd::PQHeap<int> pq2;
    for (int i = 0; i < 100; ++i) pq2.Insert(i);
    pq2.Change(0, -1000); // abbassa il massimo
    check(pq2.Tip() == 98, "PQHeap<int> Tip after decreasing max");
    pq2.Change(50, 2000); // aumenta un valore a metà
    check(pq2.Tip() == 2000, "PQHeap<int> Tip after increasing mid value");
  }

  {
    lasd::PQHeap<int> pq2;
    for (int i = 0; i < 50; ++i) pq2.Insert(i);
    for (int i = 0; i < 50; ++i) pq2.Change(i, 50 - i);
    check(pq2.Tip() == 50, "PQHeap<int> Tip after changing all priorities");
  }
  
  {
    lasd::PQHeap<int> pq2;
    for (int i = 0; i < 100; ++i) {
      pq2.Insert(i);
      if (i % 2 == 0) pq2.RemoveTip();
    }
    check(!pq2.Empty(), "PQHeap<int> not empty after alternating insert/remove");
    while (!pq2.Empty()) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<int> empty after removing all (alternating)");
  }

  {
    lasd::PQHeap<int> pq2;
    for (int i = 0; i < 50; ++i) pq2.Insert(42);
    check(pq2.Tip() == 42, "PQHeap<int> Tip with all duplicates");
    for (int i = 0; i < 50; ++i) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<int> empty after removing all duplicates");
  }

  {
    lasd::PQHeap<int> pq2;
    pq2.Insert(1);
    bool thrown2 = false;
    try { pq2.Change(1000, 5); } catch (const std::out_of_range&) { thrown2 = true; }
    check(thrown2, "PQHeap<int> Change out of range (stress)");
  }
}

// ----------------- PQHeap<double> MyTests -----------------

void MyTestPQHeapDouble() {
  cout << "\n--- MyTest PQHeap<double> ---" << endl;

  lasd::PQHeap<double> pq;
  check(pq.Empty(), "PQHeap<double> empty after default ctor");
  pq.Clear();
  check(pq.Empty(), "PQHeap<double> empty after Clear");

  pq.Insert(1.1);
  pq.Insert(2.2);
  pq.Insert(3.3);
  check(pq.Tip() == 3.3, "PQHeap<double> Tip is maximum");

  pq.RemoveTip();
  check(pq.Tip() == 2.2, "PQHeap<double> RemoveTip");

  pq.Insert(std::numeric_limits<double>::infinity());
  pq.Insert(-std::numeric_limits<double>::infinity());
  check(pq.Tip() == std::numeric_limits<double>::infinity(), "PQHeap<double> Tip with inf");

  pq.Change(0, std::numeric_limits<double>::quiet_NaN());
  check(std::isnan(pq.Tip()), "PQHeap<double> Change with NaN");

  pq.RemoveTip();
  check(pq.Tip() == 2.2, "PQHeap<double> RemoveTip after NaN");

  bool thrown = false;
  try { pq.Change(100, 1.1); } catch (const std::out_of_range&) { thrown = true; }
  check(thrown, "PQHeap<double> Change out of range index throws");

  // --- STRESS TESTS ---
  {
    lasd::PQHeap<double> pq2;
    for (int i = 0; i < 1000; ++i) pq2.Insert(i * 0.1);
    check(pq2.Tip() == 999 * 0.1, "PQHeap<double> Tip after 1k inserts");
    for (int i = 0; i < 999; ++i) pq2.RemoveTip();
    check(pq2.Tip() == 0.0, "PQHeap<double> Tip after removing all but one");
    pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<double> empty after removing all");
  }

  {
    lasd::PQHeap<double> pq2;
    for (int i = 0; i < 100; ++i) pq2.Insert(i * 0.1);
    pq2.Change(0, -1000.0); 
    check(pq2.Tip() == 9.8, "PQHeap<double> Tip after decreasing max");
    pq2.Change(50, 2000.0); 
    check(pq2.Tip() == 2000.0, "PQHeap<double> Tip after increasing mid value");
  }

  {
    lasd::PQHeap<double> pq2;
    for (int i = 0; i < 50; ++i) pq2.Insert(i * 0.1);
    for (int i = 0; i < 50; ++i) pq2.Change(i, 50.0 - i);
    check(pq2.Tip() == 50.0, "PQHeap<double> Tip after changing all priorities");
  }

  {
    lasd::PQHeap<double> pq2;
    for (int i = 0; i < 100; ++i) {
      pq2.Insert(i * 0.1);
      if (i % 2 == 0) pq2.RemoveTip();
    }
    check(!pq2.Empty(), "PQHeap<double> not empty after alternating insert/remove");
    while (!pq2.Empty()) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<double> empty after removing all (alternating)");
  }

  {
    lasd::PQHeap<double> pq2;
    for (int i = 0; i < 50; ++i) pq2.Insert(42.42);
    check(pq2.Tip() == 42.42, "PQHeap<double> Tip with all duplicates");
    for (int i = 0; i < 50; ++i) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<double> empty after removing all duplicates");
  }

  {
    lasd::PQHeap<double> pq2;
    pq2.Insert(1.1);
    bool thrown2 = false;
    try { pq2.Change(1000, 5.5); } catch (const std::out_of_range&) { thrown2 = true; }
    check(thrown2, "PQHeap<double> Change out of range (stress)");
  }
}

// ----------------- PQHeap<char> MyTests -----------------

void MyTestPQHeapChar() {
  cout << "\n--- MyTest PQHeap<char> ---" << endl;

  lasd::PQHeap<char> pq;
  check(pq.Empty(), "PQHeap<char> empty after default ctor");
  pq.Clear();
  check(pq.Empty(), "PQHeap<char> empty after Clear");

  pq.Insert('a');
  pq.Insert('z');
  pq.Insert('m');
  check(pq.Tip() == 'z', "PQHeap<char> Tip is maximum");

  pq.RemoveTip();
  check(pq.Tip() == 'm', "PQHeap<char> RemoveTip");

  bool thrown = false;
  try { pq.Change(100, 'x'); } catch (const std::out_of_range&) { thrown = true; }
  check(thrown, "PQHeap<char> Change out of range index throws");

  pq.Clear();
  thrown = false;
  try { pq.Tip(); } catch (const std::length_error&) { thrown = true; }
  check(thrown, "PQHeap<char> Tip on empty heap throws");

  // --- STRESS TESTS ---
  {
    lasd::PQHeap<char> pq2;
    for (int i = 0; i < 100; ++i) pq2.Insert((char)('a' + (i % 26)));
    check(pq2.Tip() == 'z', "PQHeap<char> Tip after 100 inserts");
    for (int i = 0; i < 99; ++i) pq2.RemoveTip();
    check(pq2.Tip() == 'a', "PQHeap<char> Tip after removing all but one");
    pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<char> empty after removing all");
  }
 
  {
    lasd::PQHeap<char> pq2;
    for (int i = 0; i < 26; ++i) pq2.Insert((char)('a' + i));
    pq2.Change(0, 'A');
    check(pq2.Tip() == 'y', "PQHeap<char> Tip after decreasing max");
    pq2.Change(10, 'z'); 
    check(pq2.Tip() == 'z', "PQHeap<char> Tip after increasing mid value");
  }

  {
    lasd::PQHeap<char> pq2;
    for (int i = 0; i < 10; ++i) pq2.Insert((char)('a' + i));
    for (int i = 0; i < 10; ++i) pq2.Change(i, (char)('z' - i));
    check(pq2.Tip() == 'z', "PQHeap<char> Tip after changing all priorities");
  }

  {
    lasd::PQHeap<char> pq2;
    for (int i = 0; i < 26; ++i) {
      pq2.Insert((char)('a' + i));
      if (i % 2 == 0) pq2.RemoveTip();
    }
    check(!pq2.Empty(), "PQHeap<char> not empty after alternating insert/remove");
    while (!pq2.Empty()) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<char> empty after removing all (alternating)");
  }

  {
    lasd::PQHeap<char> pq2;
    for (int i = 0; i < 20; ++i) pq2.Insert('x');
    check(pq2.Tip() == 'x', "PQHeap<char> Tip with all duplicates");
    for (int i = 0; i < 20; ++i) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<char> empty after removing all duplicates");
  }

  {
    lasd::PQHeap<char> pq2;
    pq2.Insert('a');
    bool thrown2 = false;
    try { pq2.Change(1000, 'b'); } catch (const std::out_of_range&) { thrown2 = true; }
    check(thrown2, "PQHeap<char> Change out of range (stress)");
  }
}

// ----------------- PQHeap<string> MyTests -----------------

void MyTestPQHeapString() {
  cout << "\n--- MyTest PQHeap<string> ---" << endl;

  lasd::PQHeap<string> pq;
  check(pq.Empty(), "PQHeap<string> empty after default ctor");
  pq.Clear();
  check(pq.Empty(), "PQHeap<string> empty after Clear");

  pq.Insert("a");
  pq.Insert("z");
  pq.Insert("m");
  check(pq.Tip() == "z", "PQHeap<string> Tip is maximum");

  pq.RemoveTip();
  check(pq.Tip() == "m", "PQHeap<string> RemoveTip");

  bool thrown = false;
  try { pq.Change(100, "x"); } catch (const std::out_of_range&) { thrown = true; }
  check(thrown, "PQHeap<string> Change out of range index throws");

  pq.Clear();
  thrown = false;
  try { pq.Tip(); } catch (const std::length_error&) { thrown = true; }
  check(thrown, "PQHeap<string> Tip on empty heap throws");

  // --- STRESS TESTS ---
  {
    lasd::PQHeap<string> pq2;
    for (int i = 0; i < 100; ++i) pq2.Insert(std::to_string(100 - i));
    check(pq2.Tip() == "99", "PQHeap<string> Tip after 100 inserts");
    for (int i = 0; i < 99; ++i) pq2.RemoveTip();
    check(!pq2.Empty(), "PQHeap<string> not empty after removing all but one");
    pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<string> empty after removing all");
  }
 
  {
    lasd::PQHeap<string> pq2;
    for (int i = 0; i < 50; ++i) pq2.Insert(std::to_string(i));
    pq2.Change(0, "zzzz"); 
    check(pq2.Tip() == "zzzz", "PQHeap<string> Tip after increasing max");
    pq2.Change(10, "aaaa");
    check(pq2.Tip() == "zzzz", "PQHeap<string> Tip after changing mid value");
  }

  {
    lasd::PQHeap<string> pq2;
    for (int i = 0; i < 10; ++i) pq2.Insert(std::to_string(i));
    for (int i = 0; i < 10; ++i) pq2.Change(i, std::string(10 - i, 'z'));
    check(pq2.Tip() == std::string(10, 'z'), "PQHeap<string> Tip after changing all priorities");
  }

  {
    lasd::PQHeap<string> pq2;
    for (int i = 0; i < 20; ++i) {
      pq2.Insert(std::to_string(i));
      if (i % 2 == 0) pq2.RemoveTip();
    }
    check(!pq2.Empty(), "PQHeap<string> not empty after alternating insert/remove");
    while (!pq2.Empty()) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<string> empty after removing all (alternating)");
  }

  {
    lasd::PQHeap<string> pq2;
    for (int i = 0; i < 20; ++i) pq2.Insert("foo");
    check(pq2.Tip() == "foo", "PQHeap<string> Tip with all duplicates");
    for (int i = 0; i < 20; ++i) pq2.RemoveTip();
    check(pq2.Empty(), "PQHeap<string> empty after removing all duplicates");
  }
 
  {
    lasd::PQHeap<string> pq2;
    pq2.Insert("a");
    bool thrown2 = false;
    try { pq2.Change(1000, "b"); } catch (const std::out_of_range&) { thrown2 = true; }
    check(thrown2, "PQHeap<string> Change out of range (stress)");
  }
}

// ----------------- MyTest comparison operators (== e !=) per HeapVec -----------------

void MyTestHeapVecCompOperators() {
  cout << "\n--- MyTest HeapVec Comparison operators ---" << endl;
  
  {
    lasd::SortableVector<int> v1(5);
    v1[0] = 10; v1[1] = 8; v1[2] = 6; v1[3] = 4; v1[4] = 2;
    lasd::HeapVec<int> h1(v1);
    
    lasd::SortableVector<int> v2(5);
    v2[0] = 2; v2[1] = 4; v2[2] = 6; v2[3] = 8; v2[4] = 10; 
    lasd::HeapVec<int> h2(v2);
    
    check(h1 != h2, "HeapVec<int> different internal layout are not equal");
    
    h1.Sort(); h2.Sort();
    check(h1 == h2, "HeapVec<int> equal after sorting both");
  }
  
  {
    lasd::SortableVector<double> v1(6);
    v1[0] = 5.5; v1[1] = 5.5; v1[2] = 3.3; v1[3] = 3.3; v1[4] = 1.1; v1[5] = 1.1;
    lasd::HeapVec<double> h1(v1);
    
    lasd::SortableVector<double> v2(6);
    v2[0] = 1.1; v2[1] = 3.3; v2[2] = 5.5; v2[3] = 1.1; v2[4] = 3.3; v2[5] = 5.5;
    lasd::HeapVec<double> h2(v2);
    
    check(h1 != h2, "HeapVec<double> with duplicates in different positions not equal");
    
    h1.Sort(); h2.Sort();
    check(h1 == h2, "HeapVec<double> with duplicates equal after sort");
  }
  
  {
    lasd::SortableVector<int> v1(4), v2(4);
    v1[0] = 1; v1[1] = 2; v1[2] = 3; v1[3] = 4;
    v2[0] = 1; v2[1] = 2; v2[2] = 3; v2[3] = 4;
    lasd::HeapVec<int> h1(v1);
    lasd::HeapVec<int> h2(v2);
    
    check(h1 == h2, "HeapVec<int> initially equal");
    
    // Modifica h1 manualmente per simulare MapPreOrder
    lasd::SortableVector<int> v1_modified(4);
    v1_modified[0] = 2; v1_modified[1] = 4; v1_modified[2] = 6; v1_modified[3] = 8;
    h1 = lasd::HeapVec<int>(v1_modified);
    
    check(h1 != h2, "HeapVec<int> not equal after modification on one");
    
    // Modifica h2 con gli stessi valori
    lasd::SortableVector<int> v2_modified(4);
    v2_modified[0] = 2; v2_modified[1] = 4; v2_modified[2] = 6; v2_modified[3] = 8;
    h2 = lasd::HeapVec<int>(v2_modified);
    
    check(h1 == h2, "HeapVec<int> equal after same modification on both");
  }
  
  {
    lasd::SortableVector<char> v1(1), v2(1), v3(1);
    v1[0] = 'a'; v2[0] = 'a'; v3[0] = 'b';
    
    lasd::HeapVec<char> h1(v1), h2(v2), h3(v3);
    
    check(h1 == h2, "HeapVec<char> single element equal");
    check(h1 != h3, "HeapVec<char> single element different values not equal");
    check(h2 != h3, "HeapVec<char> single element different values not equal (2)");
  }
  
  {
    lasd::HeapVec<string> h1, h2;
    check(h1 == h2, "HeapVec<string> empty heaps are equal");
    
    lasd::SortableVector<string> v(1);
    v[0] = "test";
    lasd::HeapVec<string> h3(v);
    
    check(h1 != h3, "HeapVec<string> empty vs non-empty not equal");
    check(h2 != h3, "HeapVec<string> empty vs non-empty not equal (2)");
    
    h3.Clear();
    check(h1 == h3, "HeapVec<string> empty after Clear equals other empty");
  }
  
  {
    lasd::SortableVector<int> v(5);
    v[0] = 15; v[1] = 10; v[2] = 8; v[3] = 6; v[4] = 3;
    lasd::HeapVec<int> h1(v);
    lasd::HeapVec<int> h2(v);
    
    check(h1 == h2, "HeapVec<int> initially equal after construction");
    
    h1.Sort();
    check(h1 != h2, "HeapVec<int> not equal after Sort on one");
    
    h2.Sort();
    check(h1 == h2, "HeapVec<int> equal after Sort on both");
    
    h1.Heapify();
    check(h1 != h2, "HeapVec<int> not equal after Heapify on one");
    
    h2.Heapify();
    check(h1 == h2, "HeapVec<int> equal after Heapify on both");
  }
  
  {
    lasd::SortableVector<int> v1(3), v2(3);
    v1[0] = 2147483647; v1[1] = 0; v1[2] = -2147483648; // INT_MAX e INT_MIN hardcoded
    v2[0] = -2147483648; v2[1] = 2147483647; v2[2] = 0; 
    lasd::HeapVec<int> h1(v1), h2(v2);
    
    check(h1 != h2, "HeapVec<int> extreme values different layout not equal");
    
    h1.Sort(); h2.Sort();
    check(h1 == h2, "HeapVec<int> extreme values equal after sort");
  }
  
  {
    lasd::SortableVector<double> v(3);
    v[0] = 2.5; v[1] = 1.5; v[2] = 3.5;
    lasd::HeapVec<double> h1(v);
    lasd::HeapVec<double> h2(h1);
    lasd::HeapVec<double> h3 = h2;
    
    check(h1 == h1, "HeapVec<double> reflexivity (h1 == h1)");
    check(h1 == h2, "HeapVec<double> copy constructor equality");
    check(h2 == h3, "HeapVec<double> copy assignment equality");
    check(h1 == h3, "HeapVec<double> transitivity (h1 == h2 && h2 == h3 => h1 == h3)");
  }
}

// ----------------- MyTests comparison operators (== e !=) per PQHeap -----------------

void MyTestPQHeapCompOperators() {
  cout << "\n--- MyTest PQHeap Comparison operators ---" << endl;
  
  {
    lasd::PQHeap<int> pq1, pq2;
    
    pq1.Insert(1); pq1.Insert(2); pq1.Insert(3); pq1.Insert(4);
    
    pq2.Insert(4); pq2.Insert(3); pq2.Insert(2); pq2.Insert(1);
    
    check(pq1 == pq2 || pq1 != pq2, "PQHeap<int> equality depends on internal layout");
    
    check(pq1.Size() == pq2.Size(), "PQHeap<int> same size after different insertion order");
    check(pq1.Tip() == pq2.Tip(), "PQHeap<int> same Tip after different insertion order");
  }
  
  {
    lasd::PQHeap<double> pq1, pq2;
    
    pq1.Insert(1.0); pq1.Insert(2.0); pq1.Insert(3.0);
    pq2.Insert(1.0); pq2.Insert(2.0); pq2.Insert(3.0);
    
    check(pq1 == pq2, "PQHeap<double> initially equal");
    
    pq1.Change(0, 5.0);
    pq2.Change(0, 5.0);
    
    check(pq1 == pq2, "PQHeap<double> equal after same Change operation");
    
    pq1.Change(1, 10.0);
    pq2.Change(1, 8.0);
    
    check(pq1 != pq2, "PQHeap<double> not equal after different Change operations");
  }
  
  {
  lasd::PQHeap<char> pq1, pq2, pq3;
  
  pq1.Insert('z'); pq1.Insert('z'); pq1.Insert('a'); pq1.Insert('a');
  pq2.Insert('a'); pq2.Insert('z'); pq2.Insert('a'); pq2.Insert('z');
  pq3.Insert('z'); pq3.Insert('a'); pq3.Insert('z'); pq3.Insert('a');
  
  check(pq1.Size() == pq2.Size() && pq2.Size() == pq3.Size(), "PQHeap<char> same size with duplicates");
  check(pq1.Tip() == pq2.Tip() && pq2.Tip() == pq3.Tip(), "PQHeap<char> same Tip with duplicates");
  
  bool equalityConsistent = true;
  
  bool eq12 = (pq1 == pq2);
  bool eq23 = (pq2 == pq3);
  bool eq13 = (pq1 == pq3);
  
  if (eq12 && eq23 && !eq13) {
    equalityConsistent = false;
  }

  check(equalityConsistent, "PQHeap<char> equality with duplicates is consistent");
}
  
  {
    lasd::SortableVector<string> v(4);
    v[0] = "delta"; v[1] = "alpha"; v[2] = "gamma"; v[3] = "beta";
    
    lasd::PQHeap<string> pq1(v); 
    
    lasd::PQHeap<string> pq2;
    pq2.Insert("delta"); pq2.Insert("alpha"); pq2.Insert("gamma"); pq2.Insert("beta");
    
    check(pq1.Size() == pq2.Size(), "PQHeap<string> same size: container vs manual");
    check(pq1.Tip() == pq2.Tip(), "PQHeap<string> same Tip: container vs manual");
    
    check(pq1 == pq2 || pq1 != pq2, "PQHeap<string> container vs manual construction equality");
  }
  
  {
    lasd::PQHeap<int> pq1, pq2;
    
    for (int i = 1; i <= 5; ++i) {
      pq1.Insert(i);
      pq2.Insert(i);
    }
    
    check(pq1 == pq2, "PQHeap<int> initially equal");
    
    pq1.RemoveTip(); pq2.RemoveTip(); 
    check(pq1 == pq2, "PQHeap<int> equal after same RemoveTip");
    
    pq1.Insert(10); pq2.Insert(10);
    check(pq1 == pq2, "PQHeap<int> equal after same Insert");
    
    pq1.Insert(15);
    pq2.Insert(12);
    check(pq1 != pq2, "PQHeap<int> not equal after different Insert");
  }
  
  {
    lasd::PQHeap<int> pq1, pq2, pq3;
    
    check(pq1 == pq2, "PQHeap<int> empty heaps are equal");
    
    pq3.Insert(42);
    check(pq1 != pq3, "PQHeap<int> empty vs single element not equal");
    check(pq2 != pq3, "PQHeap<int> empty vs single element not equal (2)");
    
    pq1.Insert(42);
    pq2.Insert(42);
    check(pq1 == pq2, "PQHeap<int> single same element equal");
    check(pq1 == pq3, "PQHeap<int> single same element equal (2)");
  }
  
  {
    lasd::PQHeap<double> pq1;
    pq1.Insert(3.14); pq1.Insert(2.71); pq1.Insert(1.41);
    
    lasd::PQHeap<double> pq2(pq1); 
    check(pq1 == pq2, "PQHeap<double> copy constructor equality");
    
    lasd::PQHeap<double> pq3;
    pq3 = pq1; 
    check(pq1 == pq3, "PQHeap<double> copy assignment equality");
    check(pq2 == pq3, "PQHeap<double> transitivity after copy operations");
    
    pq1.Insert(9.99);
    check(pq1 != pq2, "PQHeap<double> original != copy after modification");
    check(pq2 == pq3, "PQHeap<double> copies remain equal");
  }
  
  {
    lasd::PQHeap<string> pq1, pq2;
    
    pq1.Insert("test1"); pq1.Insert("test2");
    pq2.Insert("other1"); pq2.Insert("other2");
    
    check(pq1 != pq2, "PQHeap<string> different content not equal");
    
    pq1.Clear(); pq2.Clear();
    check(pq1 == pq2, "PQHeap<string> equal after Clear on both");
    
    lasd::PQHeap<string> pq3;
    check(pq1 == pq3, "PQHeap<string> cleared equals empty constructed");
  }
  
  {
    lasd::PQHeap<int> pq;
    
    check(pq == pq, "PQHeap<int> reflexivity on empty");
    
    pq.Insert(5);
    check(pq == pq, "PQHeap<int> reflexivity with one element");
    
    pq.Insert(10); pq.Insert(3);
    check(pq == pq, "PQHeap<int> reflexivity with multiple elements");
    
    pq.RemoveTip();
    check(pq == pq, "PQHeap<int> reflexivity after RemoveTip");
    
    pq.Change(0, 15);
    check(pq == pq, "PQHeap<int> reflexivity after Change");
  }
}

// ----------------- Stress Test HeapVec vs PQHeap confronto -----------------

void MyStressTestHeapVecVsPQHeap() {
  cout << "\n--- My Stress Test HeapVec vs PQHeap Comparison ---" << endl;
  
  {
    lasd::SortableVector<int> v(1000);
    for (int i = 0; i < 1000; ++i) v[i] = rand() % 500;
    
    lasd::HeapVec<int> heap(v);
    lasd::PQHeap<int> pq(v);
    
    check(heap.IsHeap(), "HeapVec constructed from large vector is heap");
    check(heap.Size() == pq.Size(), "HeapVec and PQHeap have same size after construction");
    
    check(heap.Front() == pq.Tip(), "HeapVec Front equals PQHeap Tip");
  }
  
  {
    lasd::SortableVector<int> v(100);
    for (int i = 0; i < 100; ++i) v[i] = 100 - i; 
    
    lasd::HeapVec<int> heap(v);
    lasd::PQHeap<int> pq(v);
    
    heap.Sort();
    
    lasd::SortableVector<int> pqResults(100);
    for (int i = 99; i >= 0; --i) {
      pqResults[i] = pq.TipNRemove();
    }
    
    bool equal = true;
    for (int i = 0; i < 100; ++i) {
      if (heap[i] != pqResults[i]) {
        equal = false;
        break;
      }
    }
    check(equal, "HeapVec Sort equals PQHeap TipNRemove sequence");
    check(pq.Empty(), "PQHeap empty after removing all elements");
  }
  
  {
    lasd::SortableVector<double> v(500);
    for (int i = 0; i < 500; ++i) v[i] = (double)(i % 50); 
    
    lasd::HeapVec<double> heap(v);
    lasd::PQHeap<double> pq(v);
    
    check(heap.IsHeap(), "HeapVec with duplicates is heap");
    check(heap.Front() == pq.Tip(), "HeapVec and PQHeap have same maximum with duplicates");
    
    for (int i = 0; i < 10; ++i) {
      double heapMax = heap.Front();
      double pqMax = pq.Tip();
      check(heapMax == pqMax, "HeapVec Front equals PQHeap Tip in loop");
      
      pq.RemoveTip();
      check(heap.IsHeap(), "HeapVec remains heap during PQ operations");
    }
  }
}

// ----------------- Test Access methods per HeapVec -----------------

void MyTestHeapVecAccessMethods() {
  cout << "\n--- MyTest HeapVec Access Methods (Front, Back, operator[]) ---" << endl;
  
  {
    lasd::SortableVector<int> v(10);
    for (int i = 0; i < 10; ++i) v[i] = i * 2; 
    lasd::HeapVec<int> heap(v);
    
    check(heap.Front() == heap[0], "HeapVec<int> Front equals operator[0]");
    check(heap.Back() == heap[heap.Size()-1], "HeapVec<int> Back equals operator[size-1]");
    
    bool accessOk = true;
    for (unsigned long i = 0; i < heap.Size(); ++i) {
      try {
        int val = heap[i];
        (void)val; 
      } catch(...) {
        accessOk = false;
        break;
      }
    }
    check(accessOk, "HeapVec<int> operator[] access to all valid indices");
    
    bool thrownOOR = false;
    try { heap[100]; } catch (const std::out_of_range&) { thrownOOR = true; }
    check(thrownOOR, "HeapVec<int> operator[] throws out_of_range");
  }
  
  {
    lasd::SortableVector<double> v(5);
    v[0] = 1.1; v[1] = 2.2; v[2] = 3.3; v[3] = 4.4; v[4] = 5.5;
    lasd::HeapVec<double> heap(v);
    
    check(heap.Front() >= 1.1, "HeapVec<double> Front is valid maximum");
    check(heap.Back() >= 1.1, "HeapVec<double> Back is valid element");
    
    double sum = 0.0;
    for (unsigned long i = 0; i < heap.Size(); ++i) {
      sum += heap[i];
    }
    check(sum > 15.0 && sum < 17.0, "HeapVec<double> sum of all elements correct");
  }
  
  {
    lasd::SortableVector<char> v(26);
    for (int i = 0; i < 26; ++i) v[i] = 'a' + i;
    lasd::HeapVec<char> heap(v);
    
    check(heap.Front() == 'z', "HeapVec<char> Front is maximum char");
    check(heap[0] == heap.Front(), "HeapVec<char> operator[0] equals Front");
    
    char mid = heap[heap.Size()/2];
    check(mid >= 'a' && mid <= 'z', "HeapVec<char> middle element is valid char");
  }
  
  {
    lasd::SortableVector<string> v(5);
    v[0] = "apple"; v[1] = "zebra"; v[2] = "banana"; v[3] = "orange"; v[4] = "grape";
    lasd::HeapVec<string> heap(v);
    
    check(heap.Front() == "zebra", "HeapVec<string> Front is lexicographically maximum");
    check(heap.Back().length() > 0, "HeapVec<string> Back is non-empty string");
    
    bool allValid = true;
    for (unsigned long i = 0; i < heap.Size(); ++i) {
      if (heap[i].empty()) {
        allValid = false;
        break;
      }
    }
    check(allValid, "HeapVec<string> all elements are non-empty strings");
  }
  
  {
    lasd::HeapVec<int> emptyHeap;
    
    bool thrownFront = false;
    try { emptyHeap.Front(); } catch (const std::length_error&) { thrownFront = true; }
    check(thrownFront, "HeapVec<int> Front throws on empty heap");
    
    bool thrownBack = false;
    try { emptyHeap.Back(); } catch (const std::length_error&) { thrownBack = true; }
    check(thrownBack, "HeapVec<int> Back throws on empty heap");
    
    bool thrownAccess = false;
    try { emptyHeap[0]; } catch (const std::out_of_range&) { thrownAccess = true; }
    check(thrownAccess, "HeapVec<int> operator[0] throws on empty heap");
  }
}

// ----------------- Test Access Methods PQHeap -----------------

void MyTestPQHeapAccessMethods() {
  cout << "\n--- Test PQHeap Access Methods (Front, Back, operator[]) ---" << endl;
  
  {
    lasd::PQHeap<int> pq;
    for (int i = 0; i < 10; ++i) pq.Insert(i * 3); // 0,3,6,9,12,15,18,21,24,27
    
    check(pq.Front() == pq[0], "PQHeap<int> Front equals operator[0]");
    check(pq.Back() == pq[pq.Size()-1], "PQHeap<int> Back equals operator[size-1]");
    check(pq.Front() == pq.Tip(), "PQHeap<int> Front equals Tip");
    
    unsigned long originalSize = pq.Size();
    for (int i = 0; i < 3; ++i) {
      int frontBefore = pq.Front();
      int tipBefore = pq.Tip();
      check(frontBefore == tipBefore, "PQHeap<int> Front equals Tip before removal");
      pq.RemoveTip();
    }
    check(pq.Size() == originalSize - 3, "PQHeap<int> size correct after removals");
  }
  
  {
    lasd::PQHeap<double> pq;
    pq.Insert(3.14); pq.Insert(2.71); pq.Insert(1.41); pq.Insert(9.99);
    
    check(pq.Front() == 9.99, "PQHeap<double> Front is maximum inserted");
    
    bool foundPi = false;
    for (unsigned long i = 0; i < pq.Size(); ++i) {
      if (pq[i] == 3.14) {
        foundPi = true;
        break;
      }
    }
    check(foundPi, "PQHeap<double> contains inserted pi value");
    
    pq.Change(0, 1.0); 
    check(pq.Front() < 9.99, "PQHeap<double> Front changed after Change operation");
  }

  {
    lasd::PQHeap<char> pq;
    string alphabet = "programming";
    for (char c : alphabet) pq.Insert(c);
    
    check(pq.Front() >= 'a' && pq.Front() <= 'z', "PQHeap<char> Front is valid char");
    
    bool allValidChars = true;
    for (unsigned long i = 0; i < pq.Size(); ++i) {
      char c = pq[i];
      if (c < 'a' || c > 'z') {
        allValidChars = false;
        break;
      }
    }
    check(allValidChars, "PQHeap<char> all elements are lowercase letters");
    
    char back = pq.Back();
    check(back >= 'a' && back <= 'z', "PQHeap<char> Back is valid char");
  }
  
  {
    lasd::PQHeap<string> pq;
    vector<string> words = {"hello", "world", "amazing", "zebra", "apple", "zoo"};
    for (const string& word : words) pq.Insert(word);
    
    check(pq.Front() >= "zebra", "PQHeap<string> Front is lexicographically large");

    unsigned long totalLength = 0;
    for (unsigned long i = 0; i < pq.Size(); ++i) {
      totalLength += pq[i].length();
    }
    check(totalLength > 20, "PQHeap<string> total length of all strings reasonable");
    

    pq.Insert("zzzz");
    check(pq.Front() == "zzzz", "PQHeap<string> Front updated after inserting max string");
  }
  
  {
    lasd::PQHeap<int> pq;
    
    pq.Insert(42);
    check(pq.Front() == 42, "PQHeap<int> Front with single element");
    check(pq.Back() == 42, "PQHeap<int> Back with single element");
    check(pq[0] == 42, "PQHeap<int> operator[0] with single element");
    
    bool thrownOOR = false;
    try { pq[10]; } catch (const std::out_of_range&) { thrownOOR = true; }
    check(thrownOOR, "PQHeap<int> operator[] throws out_of_range");
  }
}

// ----------------- Test casi limite -----------------

void MyTestEdgeCases() {
  cout << "\n--- Test Edge Cases ---" << endl;
  
  {
    lasd::SortableVector<int> v(5);
    v[0] = -10; v[1] = -5; v[2] = -1; v[3] = -20; v[4] = -3;
    lasd::HeapVec<int> heap(v);
    
    check(heap.IsHeap(), "HeapVec with negative numbers is heap");
    check(heap.Front() == -1, "HeapVec Front with negative numbers is correct max");
  }
  
  {
    lasd::PQHeap<double> pq;
    for (int i = 0; i < 100; ++i) pq.Insert(3.14159);
    
    check(pq.Size() == 100, "PQHeap accepts many duplicate values");
    check(pq.Tip() == 3.14159, "PQHeap Tip correct with all duplicates");
    
    for (int i = 0; i < 50; ++i) pq.RemoveTip();
    check(pq.Size() == 50, "PQHeap size correct after removing half duplicates");
    check(pq.Tip() == 3.14159, "PQHeap Tip still correct with remaining duplicates");
  }
  
  {
    lasd::SortableVector<char> v(10);
    for (int i = 0; i < 10; ++i) v[i] = 'a' + i;
    lasd::HeapVec<char> heap(v);
    
    char front1 = heap.Front();
    char back1 = heap.Back();
    
    heap.Sort();
    
    char front2 = heap.Front();
    char back2 = heap.Back();
    
    check(front1 != front2 || back1 != back2, "HeapVec Front/Back change after Sort");
    check(front2 == 'a', "HeapVec Front after Sort is minimum");
    check(back2 == 'j', "HeapVec Back after Sort is maximum");
  }
  
  {
    lasd::PQHeap<string> pq;
    pq.Insert("alpha"); pq.Insert("beta"); pq.Insert("gamma");
    
    pq.Change(0, "omega");
    check(pq.Tip() == "omega", "PQHeap Change at index 0 updates Tip");
    
    string oldTip = pq.Tip();
    pq.Change(pq.Size()-1, "zzzzz"); 
    check(pq.Tip() >= oldTip, "PQHeap Change at last index maintains or updates Tip");
  }
  
  {
    lasd::PQHeap<int> pq;
    
    for (int i = 0; i < 20; ++i) {
      pq.Insert(i);
      if (i % 3 == 0 && !pq.Empty()) {
        pq.RemoveTip();
      }
    }
    
    check(!pq.Empty(), "PQHeap not empty after mixed insert/remove operations");
    
    bool accessOk = true;
    try {
      for (unsigned long i = 0; i < pq.Size(); ++i) {
        int val = pq[i];
        (void)val;
      }
    } catch(...) {
      accessOk = false;
    }
    check(accessOk, "PQHeap operator[] works after mixed operations");
  }
  
  {
    lasd::HeapVec<double> heap;
    lasd::SortableVector<double> v(2);
    v[0] = 1.5; v[1] = 2.5;
    heap = lasd::HeapVec<double>(v);
    
    check(heap.Size() == 2, "HeapVec with 2 elements has correct size");
    check(heap.Front() == 2.5, "HeapVec with 2 elements has correct Front");
    check(heap.Back() == 1.5, "HeapVec with 2 elements has correct Back");
    check(heap[0] != heap[1], "HeapVec with 2 elements has different values");
  }
}

// ----------------- Fine Tests 2a Libreria ----------------

void mytest() {
  cout << "--------------------! Exercise 1 - 2 MyTests START !--------------------" << endl;
  totalMyTests = passedMyTests = 0;

  // Vector<Data> MyTests
  MyTestVectorInt();
  MyTestVectorDouble();
  MyTestVectorChar();
  MyTestVectorString();

  // List<Data> MyTests
  MyTestListInt();
  MyTestListDouble();
  MyTestListChar();
  MyTestListString();

  // SetVec<Data> MyTests
  MyTestSetVecInt();
  MyTestSetVecDouble();
  MyTestSetVecChar();
  MyTestSetVecString();

  // SetList<Data> MyTests
  MyTestSetLstInt();
  MyTestSetLstDouble();
  MyTestSetLstChar();
  MyTestSetLstString();

  // HeapVec<Data> MyTests
  MyTestHeapVecInt();
  MyTestHeapVecDouble();
  MyTestHeapVecChar();
  MyTestHeapVecString();

  // PQHeap<Data> MyTests
  MyTestPQHeapInt();
  MyTestPQHeapDouble();
  MyTestPQHeapChar();
  MyTestPQHeapString();

  // Comparisons operators MyTests
  MyTestHeapVecCompOperators();
  MyTestPQHeapCompOperators();

  // Stress MyTests
  MyStressTestHeapVecVsPQHeap();
  MyTestHeapVecAccessMethods();
  MyTestPQHeapAccessMethods();
  MyTestEdgeCases();

  cout << "--------------------! MyTests Exercise 1 - 2 END !-------------------" << endl;
  cout << "\nTotal MyTests: " << totalMyTests << endl;
  cout << "Passed MyTests: " << passedMyTests << endl;
  cout << "Failed MyTests: " << totalMyTests - passedMyTests << endl;

  cout << "---------------------------------------------------------------------" << endl;
  cout << "--------------------! Numero test Exercise 1: 128 !------------------" << endl;
  cout << "--------------------! Numero test Exercise 2: 360 !------------------" << endl;
  cout << "---------------------------------------------------------------------" << endl;
}





