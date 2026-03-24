#include <iostream>
#include <stdexcept>
#include <string>


#include "../container/container.hpp"
#include "../container/traversable.hpp"
#include "../container/testable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

#include "../vector/vector.hpp"
#include "../list/list.hpp"
#include "../set/set.hpp"

#include "../set/lst/setlst.hpp"
#include "../set/vec/setvec.hpp"

/* ************************************************************************** */

using namespace std;

/* ************************************************************************** */
int totalTests = 0;
int passedTests = 0;

void check(bool condition, const string& message) {
  ++totalTests;
  if (condition) {
    ++passedTests;
    cout << "[PASSED] " << message << endl;
  } else {
    cout << "[FAILED] " << message << endl;
  }
}

// ----------------- Vector<int> Tests -----------------

void TestVectorInt() {
  cout << "--- Test Vector<int> ---" << endl;
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

// ----------------- Vector<Double> Tests -----------------

void TestVectorDouble() {
  cout << "\n--- Test Vector<double> ---" << endl;
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

// ----------------- Vector<char> Tests -----------------

void TestVectorChar() {
  cout << "\n--- Test Vector<char> ---" << endl;
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

// ----------------- Vector<String> Tests -----------------

void TestVectorString() {
  cout << "\n--- Test Vector<string> ---" << endl;
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

// ----------------- List<Int> Tests -----------------

void TestListInt() {
  cout << "\n--- Test List<int> ---" << endl;
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

// ----------------- List<Double> Tests -----------------

void TestListDouble() {
  cout << "\n--- Test List<double> ---" << endl;
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

// ----------------- List<Char> Tests -----------------

void TestListChar() {
  cout << "\n--- Test List<char> ---" << endl;
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

// ----------------- List<String> Tests -----------------

void TestListString() {
  cout << "\n--- Test List<string> ---" << endl;
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

// ----------------- SetVec<int> Tests -----------------

void TestSetVecInt() {
  cout << "\n--- Test SetVec<int> ---" << endl;
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

//----------------- SetVec<Double> Tests -----------------

void TestSetVecDouble() {
  cout << "\n--- Test SetVec<double> ---" << endl;
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

//----------------- SetVec<Char> Tests -----------------

void TestSetVecChar() {
  cout << "\n--- Test SetVec<char> ---" << endl;
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

//----------------- SetVec<String> Tests -----------------

void TestSetVecString() {
  cout << "\n--- Test SetVec<string> ---" << endl;
  lasd::SetVec<string> s;

  s.Insert("hello");
  s.Insert("world");
  s.Insert("test");
  check(s.Exists("world"), "SetVec<string> contains 'world'");

  s.Remove("test");
  check(!s.Exists("test"), "'test' removed from SetVec<string>");

  lasd::SetVec<string> sCopy(s);
  lasd::SetVec<string> sMoved = std::move(sCopy);
  check(sMoved.Exists("hello"), "Moved SetVec<string> retains 'hello'");
  check(sCopy.Empty(), "Moved-from SetVec<string> empty");

  sMoved.Clear();
  check(sMoved.Empty(), "SetVec<string> empty after Clear()");
}

//----------------- SetLst<Int> Tests -----------------

void TestSetLstInt() {
  cout << "\n--- Test SetLst<int> ---" << endl;
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

//----------------- SetLst<Double> Tests -----------------

void TestSetLstDouble() {
  cout << "\n--- Test SetLst<double> ---" << endl;
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

//----------------- SetLst<Char> Tests -----------------

void TestSetLstChar() {
  cout << "\n--- Test SetLst<char> ---" << endl;
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

//----------------- SetLst<String> Tests -----------------

void TestSetLstString() {
  cout << "\n--- Test SetLst<string> ---" << endl;
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


void mytest() {
  cout << "==================== MY TESTS START ====================" << endl;
  // Vector<Data> Tests
  TestVectorInt();
  TestVectorDouble();
  TestVectorChar();
  TestVectorString();

   // List<Data> Tests
  TestListInt();
  TestListDouble();
  TestListChar();
  TestListString();

  // SetVec<Data> Tests
  TestSetVecInt();
  TestSetVecDouble();
  TestSetVecChar();
  TestSetVecString();

  // SetList<Data> Tests
  TestSetLstInt();
  TestSetLstDouble();
  TestSetLstChar();
  TestSetLstString();

  cout << "==================== MY TESTS END ======================" << endl;
  cout << "\nTotal tests: " << totalTests << endl;
  cout << "Passed tests: " << passedTests << endl;
  cout << "Failed tests: " << totalTests - passedTests << endl;
}
  

