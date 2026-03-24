
namespace lasd {

/* ************************************************************************** */

//Specific constructor (Node)
template <typename Data>
List<Data>::Node::Node(const Data &info){
    element = info;
}


template <typename Data>
List<Data>::Node::Node(Data &&info) noexcept{
    element = std::move(info);
}

/* ************************************************************************** */

//Copy constructor (Node)
template <typename Data>
List<Data>::Node::Node(const Node& other){
    element = other.element;
    next = other.next;
}

//Move constructor (Node)
template <typename Data>
List<Data>::Node::Node(Node&& other) noexcept{
    std::swap(element,other.element);
    std::swap(next,other.next);
}

/* ************************************************************************** */

// Destructor (Node)
template <typename Data>
List<Data>::Node::~Node(){}

/* ************************************************************************** */

//Comparisons operators
template <typename Data>
bool List<Data>::Node::operator==(const Node &other) const noexcept{
    return (element == other.element) &&
           ((next == nullptr && other.next == nullptr) ||
            (next != nullptr && other.next != nullptr && (*next == *other.next)));
}

template <typename Data>
bool List<Data>::Node::operator!=(const Node &other) const noexcept{
    return !(*this==other);
}

/* ************************************************************************** */

// Specific constructor (List)

template <typename Data>
List<Data>::List(const TraversableContainer<Data> &container){
    container.Traverse(
        [this](const Data &dat){
            InsertAtBack(dat);
        }
    );
}

template <typename Data>
List<Data>::List(MappableContainer<Data> &&container) noexcept{
    container.Map(
        [this](Data &dat){
            InsertAtBack(std::move(dat));
        }
    );
}

/* ************************************************************************** */

// Copy constructor (List)
template <typename Data>
List<Data>::List(const List<Data> &lista) {
    head = tail = nullptr;
    size = 0;

    if(lista.size > 0){
        Node * current = lista.head;
        while(current!=nullptr){
            InsertAtBack(current->element);
            current = current->next;
        }
    }

}

// Move constructor (List)
template <typename Data>
List<Data>::List(List<Data> &&lista) noexcept{
    std::swap(head,lista.head);
    std::swap(tail,lista.tail);
    std::swap(size,lista.size);
}

/* ************************************************************************** */

// Destructor (List)
template <typename Data>
List<Data>::~List(){
    Clear();
}

/* ************************************************************************** */

// Copy assigment (List)
template <typename Data>
List<Data> & List<Data>::operator=(const List &lista){
    if(this != &lista) {
        Clear(); 

        Node * current = lista.head;
        while(current!=nullptr){
            InsertAtBack(current->element);
            current = current->next;
        }
    }
    return *this;

}

// Move assigment (List)
template <typename Data>
List<Data> & List<Data>::operator=(List &&lista) noexcept{
    std::swap(head, lista.head);
    std::swap(tail, lista.tail);
    std::swap(size, lista.size);
    return *this;
}

/* ************************************************************************** */

// Comparisons Operators
template <typename Data>
bool List<Data>::operator==(const List<Data> &lista) const noexcept{
    if(size!=lista.size){
        return false;
    }
    else{
        Node * oneList = head;
        Node * twoList = lista.head;
        while(oneList!=nullptr){
            if(!(oneList->element == twoList->element))
                return false;
            oneList = oneList->next;
            twoList = twoList->next;
        }
        return true;
    }
}

template <typename Data>
bool List<Data>::operator!=(const List<Data> &lista) const noexcept{
    return !(*this == lista);
}

/* ************************************************************************** */

// Specific member function (List)

// InsertAtFront() (Copy)
template <typename Data>
void List<Data>::InsertAtFront(const Data &info){
    Node *firstNode = new Node(info);
    AttachAtFront(firstNode);
}

// InsertAtFront() (Move)
template <typename Data>
void List<Data>::InsertAtFront(Data &&info){
    Node *firstNode = new Node(std::move(info));
    AttachAtFront(firstNode);
}

// RemoveFromFront() 
template <typename Data>
void List<Data>::RemoveFromFront(){
    delete DetachFront();                   
}

// FrontNRemove() 
template <typename Data>
Data List<Data>::FrontNRemove(){
    return DataNDelete(DetachFront());
}

// InsertAtBack() (Copy)
template <typename Data>
void List<Data>::InsertAtBack(const Data &info){
    Node * lastNode = new Node(info);
    AttachAtBack(lastNode);
}

// InsertAtBack() (Move)
template <typename Data>
void List<Data>::InsertAtBack(Data &&info){
    Node * lastNode = new Node(std::move(info));
    AttachAtBack(lastNode);
}

// RemoveFromBack()
template <typename Data>
void List<Data>::RemoveFromBack(){
    delete DetachBack();
}

// BackNRemove()
template <typename Data>
Data List<Data>::BackNRemove(){
    return DataNDelete(DetachBack());
}


/* ************************************************************************** */

// Specific member functions (inherited from MutableLinearContainer)

// Operator[]
template <typename Data>
Data & List<Data>::operator[](const unsigned long i){
    if(i >= size) //i va da 0 a size-1
        throw std::out_of_range("Access to a non-existing index: " + std::to_string(i) + "; List size: "+std::to_string(size)+".");

    Node * current = head;
    for(unsigned long pos = 0; pos < i; ++pos){
        current = current->next;
    }

    return current->element;
}

// Front()
template <typename Data>
Data & List<Data>::Front(){
    if(head==nullptr)
        throw std::length_error("Access to an empty List!");
    else
        return head->element;
}

// Back()
template <typename Data>
Data & List<Data>::Back(){
    if(tail != nullptr)
        return tail->element;
    else    
        throw std::length_error("Access to an empty List!");
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)

// Operator[]
template <typename Data>
const Data & List<Data>::operator[](const unsigned long i) const{
    if(i >= size) //i va da 0 a size-1
        throw std::out_of_range("Access to a non-existing index: " + std::to_string(i) + "; List size: "+std::to_string(size)+".");

    Node * current = head;
    for(unsigned long pos = 0; pos < i; ++pos){
        current = current->next;
    }

    return current->element;
}

// Front()
template <typename Data>
const Data & List<Data>::Front() const{
    if(head==nullptr)
        throw std::length_error("Access to an empty List!");
    else
        return head->element;
}

// Back()
template <typename Data>
const Data & List<Data>::Back() const{
    if(tail != nullptr)
        return tail->element;
    else    
        throw std::length_error("Access to an empty List!");
}

/* ************************************************************************** */

// Specific member function (inherited from MappableContainer)

// Map()
template <typename Data>
void List<Data>::Map(MapFun fun){
    PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderMappableContainer)

// PreOrderMap()
template <typename Data>
void List<Data>::PreOrderMap(MapFun fun){
    Node * current = head;
    while(current!=nullptr){
        fun(current->element);
        current = current->next;
    }
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderMappableContainer)

// PostOrderMap()
template <typename Data>
void List<Data>::PostOrderMap(MapFun fun){
    PostOrderMapR(fun,head);
}

/* ************************************************************************** */

// Specific member function (inherited from TraversableContainer)

// Traverse()
template <typename Data>
void List<Data>::Traverse(TraverseFun fun) const {
   PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderTraversableContainer)

// PreOrderTraverse()
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun) const{
    Node* current = head;
    while(current != nullptr) {
        fun(current->element);
        current = current->next;
    }
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderTraversableContainer)

// PostOrderTraverse()
template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun) const{
    PostOrderTraverseR(fun,head); //chiamata alla versione ricorsiva
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)

// Clear()
template <typename Data>
void List<Data>::Clear(){
    while(head!=nullptr){
        Node * temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

/* ************************************************************************** */

// Auxiliary functions (List)

// AttachAtFront() - Attacca un nodo in testa
template <typename Data>
void List<Data>::AttachAtFront(Node * First) noexcept{
    First -> next = head;
    head = First;
    if(tail == nullptr)
        tail = head;
    
    ++size;
}

// AttachAtBack() - Attacca un nodo in coda
template <typename Data>
void List<Data>::AttachAtBack(Node * Last) noexcept{
    if(head==nullptr)
        head = Last;
    else{
        tail->next = Last;
    }
        
    tail = Last;
    ++size;
    
}

// DetachFront() - Stacca un nodo in testa
template <typename Data>
typename List<Data>::Node * List<Data>::DetachFront(){
    if(head == nullptr)
        throw std::length_error("Access to an empty List!");
    else{
        Node * First = head;
        if(tail == head)
            tail = head = nullptr;
        else
            head = head->next;

        --size;
        First->next = nullptr;
        return First;
    } 
    
}

// DetachBack() - Stacca un nodo dalla coda
template <typename Data>
typename List<Data>::Node * List<Data>::DetachBack(){
    if(tail == nullptr)
        throw std::length_error("Access to an empty List!");
    else{
        Node * Last = tail;
        if(tail==head)
            head = tail = nullptr;
        else{
            Node * current = head;
            while(current->next!=tail)
                current = current->next; //trova il nodo prima della coda
            current->next = nullptr;
            tail = current;
        }

        --size;
        Last->next = nullptr;
        return Last;
    }
}

// DataNDelete() - Elimina un nodo e nè restituisce il valore
template <typename Data>
Data List<Data>::DataNDelete(Node *nodo){
    Data dat(std::move(nodo->element));
    delete nodo;
    return dat;
}

// PostOrderMapR() - Versione ricorsiva della map in post order
template <typename Data>
void List<Data>::PostOrderMapR(MapFun fun, Node * nodo){
    if(nodo!=nullptr){
        PostOrderMapR(fun,nodo->next); // scorre al contrario, salvando le chiamate ricorsive sullo stack di attivazione
        fun(nodo->element);
    }
}

// PostOrderTraverseR() - Versione ricorsiva della traverse in post order
template <typename Data>
void List<Data>::PostOrderTraverseR(TraverseFun fun, Node * nodo) const{
    if(nodo!=nullptr){
        PostOrderTraverseR(fun,nodo->next);
        fun(nodo->element);
    }
}
















}
