
namespace lasd {

/* ************************************************************************** */

// Specific constructors 

// Constructor from TraversableContainer
template <typename Data>
HeapVec<Data>::HeapVec(const TraversableContainer<Data> &container) : SortableVector<Data>(container){
    Heapify();
}

// Constructor from MappableContainer
template <typename Data>
HeapVec<Data>::HeapVec(MappableContainer<Data> &&container) noexcept: SortableVector<Data>(std::move(container)) {
    Heapify();
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
HeapVec<Data>::HeapVec(const HeapVec<Data> &hVec) : SortableVector<Data>(hVec){}

// Move constructor
template <typename Data>
HeapVec<Data>::HeapVec(HeapVec<Data> &&hVec) noexcept : SortableVector<Data>(std::move(hVec)){}

/* ************************************************************************** */

// Copy assigment
template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(const HeapVec<Data> &hVec) {
    SortableVector<Data>::operator=(hVec);
    return *this;
}

// Move assigment
template <typename Data>
HeapVec<Data> & HeapVec<Data>::operator=(HeapVec<Data> &&hVec) noexcept{
    SortableVector<Data>::operator=(std::move(hVec));
    return *this;
}

/* ************************************************************************** */

// Comparison operators

template <typename Data>
bool HeapVec<Data>::operator==(const HeapVec<Data> &hVec) const noexcept{
    return SortableVector<Data>::operator==(hVec);
} 

template <typename Data>
bool HeapVec<Data>::operator!=(const HeapVec<Data> &hVec) const noexcept {
    return !(*this==hVec);
}

/* ************************************************************************** */

// Specific member function (inherited from LinearContainer)

template <typename Data>
const Data & HeapVec<Data>::operator[](unsigned long i) const{
    return Vector<Data>::operator[](i);
}

template <typename Data>
const Data & HeapVec<Data>::Front() const{
    return Vector<Data>::Front();
}

template <typename Data>
const Data & HeapVec<Data>::Back() const{
    return Vector<Data>::Back();
}

/* ************************************************************************** */

// Specific member functions (inherited from Heap)

// IsHeap()
template <typename Data>
bool HeapVec<Data>::IsHeap() const{

    for(unsigned long i = 0; i < size; ++i){
        unsigned long leftChild = 2*i+1;
        unsigned long rightChild = 2*i+2; 

        if(leftChild < size && Elements[i] < Elements[leftChild])
            return false;
        
        if(rightChild < size && Elements[i] < Elements[rightChild])
            return false;
    }
    return true;
}

// Heapify() - DownHeapify
template <typename Data>
void HeapVec<Data>::Heapify(){
    if(size == 0)
        return;

    for(unsigned long index = size / 2; index > 0; index--){
        RecursiveHeapify(index - 1, size); // (root)
    }

}

/* ************************************************************************** */

// Specific member function (inherited from SortableLinearContainer)
template <typename Data>
void HeapVec<Data>::Sort() noexcept{
    HeapSort();
}

/* ************************************************************************** */

// Auxiliarity functions

// RecursiveHeapify()
template <typename Data>
void HeapVec<Data>::RecursiveHeapify(unsigned long root, unsigned long HeapSize){
    unsigned long max = root;
    unsigned long left = 2 * root + 1;
    unsigned long right = 2 * root + 2;

    if(left < HeapSize && Elements[max] < Elements[left])
        max = left;

    if(right < HeapSize && Elements[max] < Elements[right])
        max = right;

    if(max != root){
        std::swap(Elements[max], Elements[root]);
        RecursiveHeapify(max, HeapSize);
    }
}

// HeapSort()
template <typename Data>
void HeapVec<Data>::HeapSort() noexcept{
    Heapify(); //costruzione Max-Heap

    for(unsigned long HeapSize = size; HeapSize > 1; --HeapSize){
        std::swap(Elements[0], Elements[HeapSize - 1]);
        RecursiveHeapify(0, HeapSize - 1);
    }

}

/* ************************************************************************** */

}
