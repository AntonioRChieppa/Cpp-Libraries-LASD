
namespace lasd {

/* ************************************************************************** */

// Specific constructor

// Copy constructor (obtained from TraversableContainer)
template <typename Data>
SetLst<Data>::SetLst(const TraversableContainer<Data> &container){
    container.Traverse(
        [this](const Data &value){
            Insert(value);
        }
    );
}

// Move constructor (obtained from MappableContainer)
template <typename Data>
SetLst<Data>::SetLst(MappableContainer<Data> &&container) noexcept{
    container.Map(
        [this](Data &value){
            Insert(value);
        }
    );
}

/* ************************************************************************** */

// Destructor
template <typename Data>
SetLst<Data>::~SetLst(){
    Clear();
}

/* ************************************************************************** */

// Copy assigment 
template <typename Data>
SetLst<Data> & SetLst<Data>::operator=(const SetLst &sLst){
    List<Data>::operator=(sLst);
    return *this;
}

// Move assigment
template <typename Data>
SetLst<Data> & SetLst<Data>::operator=(SetLst &&sLst) noexcept{
    List<Data>::operator=(std::move(sLst));
    return *this;
}

/* ************************************************************************** */

// Comparisons operators

template <typename Data>
bool SetLst<Data>::operator==(const SetLst<Data> &sLst) const noexcept{
    return List<Data>::operator==(sLst);
}

template <typename Data>
bool SetLst<Data>::operator!=(const SetLst<Data> &sLst) const noexcept{
    return List<Data>::operator!=(sLst);
}

/* ************************************************************************** */

// Specific member functions (inherited from OrderedDictionaryContainer)

// Min()
template <typename Data>
const Data & SetLst<Data>::Min() const{
    if(head!=0)
        return List<Data>::Front();
    else
        throw std::length_error("Access to an empty SetList!");
}

// MinNRemove()
template <typename Data>
Data SetLst<Data>::MinNRemove(){
    return List<Data>::FrontNRemove();
}

// RemoveMin()
template <typename Data>
void SetLst<Data>::RemoveMin(){
    List<Data>::RemoveFromFront();
}

// Max()
template <typename Data>
const Data & SetLst<Data>::Max() const{
    if(head!=0)
        return List<Data>::Back();
    else
        throw std::length_error("Access to an empty SetList!");
}

// MaxNRemove()
template <typename Data>
Data SetLst<Data>::MaxNRemove(){
    return List<Data>::BackNRemove();
}

// RemoveMax()
template <typename Data>
void SetLst<Data>::RemoveMax(){
    List<Data>::RemoveFromBack();
}

// Predecessor()
template <typename Data>
const Data & SetLst<Data>::Predecessor(const Data &value) const{
    if (head == nullptr)
        throw std::length_error("Predecessor not found!");

    Node **pos = BinarySearch(value);

    if (pos == &head)
        throw std::length_error("Predecessor not found!");


    Node* curr = head;
    Node* predecessor = nullptr;
    while (curr != nullptr && &(curr->next) != pos) {
        curr = curr->next;
    }
    predecessor = curr;

    if (predecessor == nullptr)
        throw std::length_error("Predecessor not found!");

    return predecessor->element;
}

// PredecessorNRemove()
template <typename Data>
Data SetLst<Data>::PredecessorNRemove(const Data &value) {
    Data dat = Predecessor(value);
    Remove(dat);
    return dat;
}

// RemovePredecessor()
template <typename Data>
void SetLst<Data>::RemovePredecessor(const Data &value){
    Data dat =  Predecessor(value);
    Remove(dat);
}

// Successor()
template <typename Data>
const Data & SetLst<Data>::Successor(const Data &value) const{
    Node **pos = BinarySearch(value);

    if(*pos==nullptr || head==nullptr)
        throw std::length_error("Successor not found!");

    Node *successor = nullptr;
    if(*pos!=nullptr && (*pos)->element == value)
        successor = (*pos)->next;
    else
        successor = *pos;

    if(successor == nullptr)
        throw std::length_error("Successor not found!");

    return successor->element;
}

// SuccessorNRemove()
template <typename Data>
Data SetLst<Data>::SuccessorNRemove(const Data &value){
    Data dat = Successor(value);
    Remove(dat);
    return dat;

}

// RemoveSuccessor()
template <typename Data>
void SetLst<Data>::RemoveSuccessor(const Data &value){
    Data dat = Successor(value);
    Remove(dat);
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

// Insert (Copy)
template <typename Data>
bool SetLst<Data>::Insert(const Data &value){
    Node **pos = BinarySearch(value);

    if(*pos!=nullptr && (*pos)->element == value)
        return false; // è già presente
    
    Node *nodo = new Node(value);
    nodo->next = *pos;
    *pos = nodo;

    if(nodo->next == nullptr)
        tail = nodo;

    ++size;
    return true;
}

// Insert (move)
template <typename Data>
bool SetLst<Data>::Insert(Data &&value) noexcept{
    Node **pos = BinarySearch(value);

    if(*pos!=nullptr && (*pos)->element == value)
        return false; // è già presente
    
    Node *nodo = new Node(std::move(value));
    nodo->next = *pos;
    *pos = nodo;

    if(nodo->next == nullptr)
        tail = nodo;
    
    ++size;
    return true;
}

// Remove
template <typename Data>
bool SetLst<Data>::Remove(const Data &value){
    Node **pos = BinarySearch(value);

    if (!(*pos) || (*pos)->element != value)
        return false;

    Node * nodo = *pos;
    *pos = nodo->next;

    if(nodo == tail){
          
            tail = nullptr;
            Node *current = head;
            while(current != nullptr) 
                current = current->next;
            tail = current;
    }


    delete nodo;
    --size;

    return true;
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)
template <typename Data>
const Data & SetLst<Data>::operator[](unsigned long i) const{
    return List<Data>::operator[](i);
}

/* ************************************************************************** */

// Specific member function (inherited from TestableContainer)
template <typename Data>
bool SetLst<Data>::Exists(const Data &value) const noexcept{
    Node **pos = BinarySearch(value);

    if(*pos!=nullptr && (*pos)->element==value)
        return true;
    else 
        return false;
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)
template <typename Data>
void SetLst<Data>::Clear(){
    List<Data>::Clear();
}

/* ************************************************************************** */

// Auxiliary functions
template <typename Data>
typename SetLst<Data>::Node** SetLst<Data>::BinarySearch(const Data &value) const {
    if(head == nullptr)
        return const_cast<Node**>(&head);

    long left = 0;
    long right = size - 1;
    Node **result = const_cast<Node**>(&head);

    while(left <= right) {
        long mid = (left + right) / 2;

        Node *curr = head;
        Node **currPtr = const_cast<Node**>(&head);
        for(long i = 0; i < mid && curr != nullptr; ++i) {
            currPtr = &(curr->next);
            curr = curr->next;
        }

        if(curr == nullptr) {
            return result;
        }

        if(curr->element == value)
            return currPtr;
        else if(curr->element < value) {
            left = mid + 1;
            result = &(curr->next);
        } 
        else {
            right = mid - 1;
            result = currPtr;
        }
    }

    return result;
}



/* ************************************************************************** */

}
