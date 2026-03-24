
namespace lasd {

/* ************************************************************************** */

// Specific constructors (Vector)

template <typename Data>
Vector<Data>::Vector(const unsigned long newSize){
    size = newSize;
    Elements = new Data[size] {};
}

template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> &container) : Vector(container.Size()){
    unsigned long i = 0;
    container.Traverse(
        [&i, this](const Data &dat){
            Elements[i++] = dat;
        }
    );
    
}

template <typename Data>
Vector<Data>::Vector(MappableContainer<Data> &&container) noexcept : Vector(container.Size()){
    unsigned long i = 0;
    container.Map(
        [&i, this](Data &dat){
            Elements[i++] = std::move(dat);
        }
    );
}

/* ************************************************************************** */

// Copy constructor (Vector)
template <typename Data>
Vector<Data>::Vector(const Vector<Data> &vec) : Vector(vec.size){
    std::copy(vec.Elements, vec.Elements + size, Elements);
}

// Move constructor (Vector)
template <typename Data>
Vector<Data>::Vector(Vector<Data> &&vec) noexcept{
    std::swap(size, vec.size);
    std::swap(Elements, vec.Elements);
}

/* ************************************************************************** */

// Destructor (Vector)
template <typename Data>
Vector<Data>::~Vector(){
    delete[] Elements;
    size = 0;
}

/* ************************************************************************** */


// Copy assigment (Vector)
template <typename Data>
Vector<Data> & Vector<Data>::operator=(const Vector<Data> &vec){
    if(this!=&vec){
        Vector<Data> tempvec{vec}; //copy-and-swap idiom 
        std::swap(*this, tempvec);
    }
    
    return *this;
}

// Move assigment (Vector)
template <typename Data>
Vector<Data> & Vector<Data>::operator=(Vector<Data> &&vec) noexcept{
    std::swap(size,vec.size);
    std::swap(Elements,vec.Elements);
    return *this;
}

/* ************************************************************************** */

// Comparisons operators (Vector)

template <typename Data>
bool Vector<Data>::operator==(const Vector<Data> &vec) const noexcept{
    if(size!=vec.size)
        return false;
    else{
        for(unsigned long i = 0; i < size; ++i){
            if(Elements[i] != vec[i])
                return false;
        }
    }
    return true;
}

template <typename Data>
bool Vector<Data>::operator!=(const Vector<Data> &vec) const noexcept{
    return !(*this == vec);
}


/* ************************************************************************** */

// Specific member functions (Vector, inherited from MutableLinearContainer)

// Operator[]
template <typename Data>
Data & Vector<Data>::operator[](const unsigned long i){
    return const_cast<Data &>(static_cast <const Vector<Data> *>(this)->operator[](i));
}

// Front()
template <typename Data>
Data & Vector<Data>::Front(){
    return const_cast<Data &>(static_cast <const Vector<Data> *>(this)->Front());
}

// Back() 
template <typename Data>
Data & Vector<Data>::Back(){
    return const_cast<Data &>(static_cast<const Vector<Data> *>(this)->Back());
}

/* ************************************************************************** */

// Specific member functions (Vector, inherited from LinearContainer)

// Operator[]
template <typename Data>
const Data & Vector<Data>::operator[](const unsigned long i) const{
    if(i < size){
        return Elements[i];
    }
    else{
        throw std::out_of_range("Access to a non-existing index: " + std::to_string(i) + "; Vector size: "+std::to_string(size)+".");
    }
}

// Front() (non-Mutable)
template <typename Data>
const Data & Vector<Data>::Front() const{
    if(size != 0){
        return Elements[0];
    }
    else
        throw std::length_error("Access to an empty vector!");
}

// Back() (non-Mutable)
template <typename Data>
const Data & Vector<Data>::Back() const{
    if(size!=0){
        return Elements[size - 1];
    }
    else
        throw std::length_error("Access to an empty vector!");
}

/* ************************************************************************** */

// Specific member function (inherited from ResizableContainer)

// Resize
template <typename Data>
void Vector<Data>::Resize(unsigned long newSize){
    if(newSize==0)
        Clear();
    else if(size != newSize){
        Data * tempvec = new Data[newSize] {};
        unsigned long min;
        if(size < newSize)
            min = size;
        else  
            min = newSize;
        for(unsigned long i = 0; i < min; ++i){
            tempvec[i] = std::move(Elements[i]);
        }
        
        delete[] Elements;
        Elements = tempvec;
        size = newSize;
    }
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)

// Clear
template <typename Data>
void Vector<Data>::Clear(){
    delete[] Elements;
    Elements = nullptr;
    size = 0;
}

/* ************************************************************************** */

// Specific constructors (SortableVector)

template <typename Data>
SortableVector<Data>::SortableVector(const unsigned long newSize) : Vector<Data>(newSize) {}

template <typename Data>
SortableVector<Data>::SortableVector(const TraversableContainer<Data> &container) : Vector<Data>(container){}

template <typename Data>
SortableVector<Data>::SortableVector(MappableContainer<Data> &&container) noexcept : Vector<Data>(std::move(container)) {}

/* ************************************************************************** */

// Copy constructor (SortableVector)
template <typename Data>
SortableVector<Data>::SortableVector(const SortableVector<Data> &sortVec) : Vector<Data>(sortVec){}

// Move constructor (SortableVector)
template <typename Data>
SortableVector<Data>::SortableVector(SortableVector<Data> &&sortVec) noexcept : Vector<Data>(std::move(sortVec)){}

/* ************************************************************************** */

// Copy assigment (SortableVector)
template <typename Data>
SortableVector<Data> & SortableVector<Data> :: operator=(const SortableVector &sortVec){
    Vector<Data>::operator=(sortVec);
    return *this;
}

// Move assigment (SortableVector)
template <typename Data>
SortableVector<Data> & SortableVector<Data> :: operator=(SortableVector &&sortVec) noexcept{
    Vector<Data>::operator=(std::move(sortVec));
    return *this;
}

/* ************************************************************************** */

}
