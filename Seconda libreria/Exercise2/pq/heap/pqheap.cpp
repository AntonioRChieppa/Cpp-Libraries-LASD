
namespace lasd {

/* ************************************************************************** */

// Default constructors
template <typename Data>
PQHeap<Data>::PQHeap(){
    capacity = 4;
    Elements = new Data[capacity]();
    size = 0;
}

// Specific constructors

// Constructor from TraversableContainer
template <typename Data>
PQHeap<Data>::PQHeap(const TraversableContainer<Data> &container) : HeapVec<Data>(container) {
    if(size > 1)
        capacity = size;
    else    
        capacity = 4;
}

// Constructor from MappableContainer
template <typename Data>
PQHeap<Data>::PQHeap(MappableContainer<Data> &&container) noexcept : HeapVec<Data>(std::move(container)) {
    if(size > 1)
        capacity = size;
    else    
        capacity = 4;
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
PQHeap<Data>::PQHeap(const PQHeap<Data> &pqHeap) : HeapVec<Data>(pqHeap){
    capacity = pqHeap.capacity;
}

// Move constructor
template <typename Data>
PQHeap<Data>::PQHeap(PQHeap<Data> &&pqHeap) noexcept : HeapVec<Data>(std::move(pqHeap)){
    std::swap(capacity, pqHeap.capacity);
}

/* ************************************************************************** */

// Copy assigment
template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(const PQHeap<Data> &pqHeap){
    HeapVec<Data>::operator=(pqHeap);
    return *this;
}

// Move assigment
template <typename Data>
PQHeap<Data> & PQHeap<Data>::operator=(PQHeap<Data> &&pqHeap) noexcept{
    HeapVec<Data>::operator=(std::move(pqHeap));
    return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool PQHeap<Data>::operator==(const PQHeap &pqHeap) const noexcept{
    return HeapVec<Data>::operator==(pqHeap);
}

template <typename Data>
bool PQHeap<Data>::operator!=(const PQHeap &pqHeap) const noexcept{
    return !(*this==pqHeap);
}

/* ************************************************************************** */

// Specific member functions (inherited from PQ)

// Tip()
template <typename Data>
const Data & PQHeap<Data>::Tip() {
    if(size==0)
        throw std::length_error("Access to an empty PQ Heap!");
    else    
        return Elements[0];
}

// RemoveTip()
template <typename Data>
void PQHeap<Data>::RemoveTip() {
    if(size==0)
        throw std::length_error("Access to an empty PQ Heap!");
    else{

        std::swap(Elements[0], Elements[size - 1]);
        --size;

        HeapifyDown(0, size);

        if(size < capacity/4 && capacity > 10)
            Resize(capacity / 2);
    }
}

// TipNRemove()
template <typename Data>
Data PQHeap<Data>::TipNRemove(){
    if(size==0)
        throw std::length_error("Access to an empty PQ Heap!");
    else{
        Data tip = std::move(Elements[0]);
        std::swap(Elements[0], Elements[size - 1]);
        --size;

        HeapifyDown(0, size);

        if(size < capacity/4 && capacity > 10)
            Resize(capacity / 2);

        return tip;
    }
}

// Insert (Copy) 
template <typename Data>
void PQHeap<Data>::Insert(const Data &value){
    if(size==capacity)
        Resize(capacity * 2);
    
    Elements[size] = value;
    HeapifyUp(size);
    size++;
}

// Insert (Move)
template <typename Data>
void PQHeap<Data>::Insert(Data &&value) noexcept{
    if(size==capacity)
        Resize(capacity * 2);
    
    Elements[size] = std::move(value);
    HeapifyUp(size);
    size++;
}

// Change (Copy)
template <typename Data>
void PQHeap<Data>::Change(unsigned long index, const Data &value){
    if(index >= size)
        throw std::out_of_range("Access to a non-existing index: " + std::to_string(index) + "; PQHeap size: "+std::to_string(size)+".");

    Data oldValue = Elements[index];
    Elements[index] = value;
    if(value > oldValue)
        HeapifyUp(index);
    else if(value < oldValue)
        HeapifyDown(index, size);
}

// Change (move)
template <typename Data>
void PQHeap<Data>::Change(unsigned long index, Data &&value){
    if(index >= size) 
        throw std::out_of_range("Access to a non-existing index: " + std::to_string(index) + "; PQHeap size: "+std::to_string(size)+".");

    Data oldValue = Elements[index];
    Elements[index] = std::move(value);
    if(value > oldValue)
        HeapifyUp(index);
    else if(value < oldValue)
        HeapifyDown(index, size);  
    
}

/* ************************************************************************** */

// Specific member functions (inherited from ResizableContainer)
template <typename Data>
void PQHeap<Data>::Resize(unsigned long newCapacity){
    if(newCapacity==0){
        Clear();
        return;
    }

    unsigned long minSize = 0;
    if(size < newCapacity)
        minSize = size;
    else if(size > newCapacity)
        minSize = newCapacity;

    if(capacity != newCapacity){
        Data * tPQHeap = new Data[newCapacity] {};
        for(unsigned long i = 0; i < minSize; ++i){
            tPQHeap[i] = std::move(Elements[i]);
        }

        delete[] Elements;
        Elements = tPQHeap;
        capacity = newCapacity;
        if(size > capacity)
            size = capacity;
    }
}

/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer)
template <typename Data>
void PQHeap<Data>::Clear(){
    delete[] Elements;
    Elements = new Data[4]();
    capacity = 4;
    size = 0;
}

/* ************************************************************************** */

// Auxiliary functions

// HeapifyDown()
template <typename Data>
void PQHeap<Data>::HeapifyDown(unsigned long index, unsigned long PQHeapSize){
    HeapVec<Data>::RecursiveHeapify(index, PQHeapSize); // conviene sistemare solo la radice
}

// HeapifyUp()
template <typename Data>
void PQHeap<Data>::HeapifyUp(unsigned long index){
    while(index > 0){
        if(Elements[(index-1)/2]<Elements[index]){
            std::swap(Elements[(index-1)/2], Elements[index]);
            index = (index - 1)/2;
        }
        else{
            break;
        } 
    } 
}


/* ************************************************************************** */

}
