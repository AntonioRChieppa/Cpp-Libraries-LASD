
namespace lasd {

/* ************************************************************************** */

// Specific constructors

// Copy constructor (obtained from TraversableContainer)
template <typename Data>
SetVec<Data>::SetVec(const TraversableContainer<Data> &container) : SetVec(container.Size()){
    container.Traverse(
        [this](const Data &dat){
            Insert(dat); // uso dell'Insert per evitare duplicati
        }
    );
}

// Move constructor (obtained from MappableContainer)
template <typename Data>
SetVec<Data>::SetVec(MappableContainer<Data> &&container) noexcept : SetVec(container.Size()) {
    container.Map(
        [this](Data &dat){
            Insert(std::move(dat));
        }
    );
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
SetVec<Data>::SetVec(const SetVec<Data> &sVec) {
    capacity = sVec.capacity;
    Elements = new Data[capacity]();
    size = sVec.size;
    head = sVec.head;
    
    for(unsigned long i = 0; i < capacity; ++i) {
        Elements[i] = sVec.Elements[i];
    }
}

// Move constructor
template <typename Data>
SetVec<Data>::SetVec(SetVec<Data> &&sVec) noexcept {
    std::swap(size, sVec.size);
    std::swap(Elements, sVec.Elements);
    std::swap(capacity, sVec.capacity);
    std::swap(head, sVec.head);
}

/* ************************************************************************** */

// Destructor
template <typename Data>
SetVec<Data>::~SetVec(){
    delete[] Elements;
    Elements = nullptr;
    size = capacity = head = 0;
}

/* ************************************************************************** */

// Copy assigment 
template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(const SetVec<Data> &sVec){
    if(this != &sVec){
        delete[] Elements;
        capacity = sVec.capacity;
        Elements = new Data[capacity]();
        size = sVec.size;
        head = sVec.head;

    for(unsigned long i = 0; i < capacity; ++i) {
            Elements[i] = sVec.Elements[i];
    }
    
    }
    return *this;
}

// Move assigment
template <typename Data>
SetVec<Data> & SetVec<Data>::operator=(SetVec<Data> &&sVec) noexcept{
    std::swap(size, sVec.size);
    std::swap(Elements, sVec.Elements);
    std::swap(capacity, sVec.capacity);
    std::swap(head,sVec.head);
    return *this;
}

/* ************************************************************************** */

// Comparisons operators
template <typename Data>
bool SetVec<Data>::operator==(const SetVec<Data> &sVec) const noexcept{
    if(size!=sVec.size)
        return false;
    else{
        for(unsigned long i=0;i < size; ++i){
            if((*this)[i] != sVec[i])
                return false;
        }
        return true;
    }
}

template <typename Data>
bool SetVec<Data>::operator!=(const SetVec<Data> &sVec) const noexcept{
    return !(*this==sVec);
}

/* ************************************************************************** */

// Specific member functions (inherited from OrderedDictionaryContainer)

// Min()
template <typename Data>
const Data & SetVec<Data>::Min() const{
    if(size==0)
        throw std::length_error("Access to an empty SetVec!");
    else   
        return Elements[head];
}

// MinNRemove()
template <typename Data>
Data SetVec<Data>::MinNRemove(){
    if(size==0)
        throw std::length_error("Access to an empty SetVec!");
    else{
        Data minValue = std::move(Elements[head]);
        head = (head + 1) % capacity; // aggiorno la testa
        --size;

        if(size < capacity/4 && capacity > 10) // ridimensiona se lo spazio vuoto è in eccesso
            Resize(capacity / 2);

        return minValue;
    }
}

// RemoveMin()
template <typename Data>
void SetVec<Data>::RemoveMin(){
    if(size==0)
        throw std::length_error("Access to an empty SetVec!");
    else{
        head = (head + 1) % capacity; // aggiorno la testa 
        --size;

        if(size < capacity/4 && capacity > 10) // ridimensiona se lo spazio vuoto è in eccesso
            Resize(capacity / 2);

    }
}

// Max()
template <typename Data>
const Data & SetVec<Data>::Max() const{
    if(size==0)
        throw std::length_error("Access to an empty SetVec!");
    else   
        return Elements[CircularIndex(size - 1)];
}

// MaxNRemove()
template <typename Data>
Data SetVec<Data>::MaxNRemove(){
    if(size==0)
        throw std::length_error("Access to an empty SetVec!");
    else{
        Data maxValue = std::move(Elements[CircularIndex(size - 1)]);
        --size;

        if(size < capacity/4 && capacity > 10) // ridimensiona se lo spazio vuoto è in eccesso
            Resize(capacity / 2);

        return maxValue;
    }
}

// RemoveMax()
template <typename Data>
void SetVec<Data>::RemoveMax(){
    if(size==0)
        throw std::length_error("Access to an empty SetVec!");
    else{
        --size;

        if(size < capacity/4 && capacity>10) 
            Resize(capacity / 2);
    }
}

// Predecesssor()
template <typename Data>
const Data & SetVec<Data>::Predecessor(const Data &value) const{
    if(size==0)
        throw std::length_error("Access to an empty SetVec!"); 
    unsigned long pos = 0;
    BinarySearch(pos,value);
    if(pos == 0)
        throw std::length_error("Predecessor not found!"); 
    else
        return Elements[CircularIndex(pos - 1)]; 
        
}

// PredecessorNRemove()
template <typename Data>
Data SetVec<Data>::PredecessorNRemove(const Data &value){
    if(size==0)
        throw std::length_error("Access to an empty SetVec!"); 
    unsigned long pos = 0;
    BinarySearch(pos, value);
    if(pos == 0)
        throw std::length_error("Predecessor not found!");
    pos--;
    Data predOut = Elements[CircularIndex(pos)];
    if(pos < size - pos){
        // Shift verso sinistra
        for(unsigned long i = pos; i > 0; --i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i - 1)]);
        head = (head + 1) % capacity;
    }
    else{
        // Shift verso destra
        for(unsigned long i = pos; i < size - 1; ++i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);

    }

    size--;
    if(size < capacity/4 && capacity > 10)
            Resize(capacity / 2);

    return predOut;
}

// RemovePredecessor()
template <typename Data>
void SetVec<Data>::RemovePredecessor(const Data &value){
    if(size==0)
        throw std::length_error("Access to an empty SetVec!"); 
    unsigned long pos = 0;
    BinarySearch(pos, value);
    if(pos == 0)
        throw std::length_error("Predecessor not found!");
    pos--;
    if(pos < size - pos){
        // Shift verso sinistra
        for(unsigned long i = pos; i > 0; --i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i - 1)]);
        head = (head + 1) % capacity; 
    }
    else{
        // Shift verso destra
        for(unsigned long i = pos; i < size - 1; ++i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);
    }

    size--;
    if(size < capacity/4 && capacity > 10) 
        Resize(capacity / 2);
}

// Successor()
template <typename Data>
const Data & SetVec<Data>::Successor(const Data &value) const{
    if(size==0)
        throw std::length_error("Access to an empty SetVec!"); 
    unsigned long pos = 0;
    bool found = BinarySearch(pos,value);
    if((found && pos == size - 1) || (!found && pos==size))
        throw std::length_error("Successor not found!"); 
    if(found)
        return Elements[CircularIndex(pos + 1)]; 
    else
        return Elements[CircularIndex(pos)];
}

// SuccessorNRemove()
template <typename Data>
Data SetVec<Data>::SuccessorNRemove(const Data &value){
    if(size==0)
        throw std::length_error("Access to an empty SetVec!"); 
    unsigned long pos = 0;
    bool found = BinarySearch(pos, value);
    if((found && pos == size - 1) || (!found && pos==size))
        throw std::length_error("Successor not found!");

    unsigned long succPos = found ? pos + 1 : pos;
    Data succOut = Elements[CircularIndex(succPos)];
    if(succPos < size - succPos){
        // Shift verso sinistra
        for (unsigned long i = succPos; i > 0; --i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i - 1)]);
        head = (head + 1) % capacity; 
    }
    else{
        // Shift verso destra
        for(unsigned long i=succPos; i < size - 1; ++i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);
    }
    --size;

    if(size < capacity/4 && capacity > 10)
        Resize(capacity / 2);

    return succOut;
}

// RemoveSuccessor()
template <typename Data>
void SetVec<Data>::RemoveSuccessor(const Data &value) {
    unsigned long pos = 0;
    bool found = BinarySearch(pos, value);

    if ((found && pos == size - 1) || (!found && pos == size))
        throw std::length_error("Successor not found!");

    unsigned long succPos = found ? pos + 1 : pos;

    // Rimuoviamo l'elemento in succPos
    if (succPos < size - succPos) {
        // Shift verso sinistra 
        for (unsigned long i = succPos; i > 0; --i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i - 1)]);

        head = (head + 1) % capacity; 
    } else {
        // Shift verso destra
        for (unsigned long i = succPos; i < size - 1; ++i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);
    }

    --size;

    if (size < capacity / 4 && capacity > 10)
        Resize(capacity / 2);
}


/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

// Insert (copy)
template <typename Data>
bool SetVec<Data>::Insert(const Data &value){
    if(size == capacity)
        Resize(capacity * 2); 

    unsigned long pos = 0;
    bool found = BinarySearch(pos,value);
    if(found){
        return false; // elemento già presente
    }

    if (pos < size - pos) {
        // Shift verso sinistra
        head = (head == 0) ? capacity - 1 : head - 1; //sposto la testa indietro per far spazio 
        for (unsigned long i = 0; i < pos; ++i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);

        Elements[CircularIndex(pos)] = value;
    } 
    else {
        // Shift verso destra
        for (unsigned long i = size; i > pos; --i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i - 1)]);

        Elements[CircularIndex(pos)] = value;
    }

    ++size;
    return true;
}

// Insert (move)
template <typename Data>
bool SetVec<Data>::Insert(Data &&value) noexcept{
    if(size == capacity)
        Resize(capacity * 2); 

    unsigned long pos = 0;
    bool found = BinarySearch(pos,value);
    if(found){
        return false; // elemento già presente
    }

    if (pos < size - pos) {
        // Shift verso sinistra
        head = (head == 0) ? capacity - 1 : head - 1;
        for (unsigned long i = 0; i < pos; ++i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);

        Elements[CircularIndex(pos)] = std::move(value);
    } 
    else {
        // Shift verso destra
        for (unsigned long i = size; i > pos; --i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i - 1)]);

        Elements[CircularIndex(pos)] = std::move(value);
    }

    ++size;
    return true;
}

// Remove
template <typename Data>
bool SetVec<Data>::Remove(const Data &value){
    if(size==0)
        return false;
    unsigned long pos = 0;
    bool found = BinarySearch(pos, value);

    if(!found)
        return false; // l'elemento non è presente all'interno del set
    else if(found && pos < size - pos){
        for (unsigned long i = pos; i > 0; --i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i - 1)]);
        
        head = (head + 1) % capacity;
    }
    else{
        for (unsigned long i = pos; i < size - 1; ++i)
            Elements[CircularIndex(i)] = std::move(Elements[CircularIndex(i + 1)]);
    }

    --size;

    if(size < capacity/4 && capacity > 1)
        Resize(capacity / 2);

    return true;
}

/* ************************************************************************** */

// Specific member function (inherited from LinearContainer)
template <typename Data>
const Data & SetVec<Data>::operator[](const unsigned long i) const{
    if(i < size && capacity > 0)
        return Elements[CircularIndex(i)];
    else
        throw std::out_of_range("Access to a non-existing index: " + std::to_string(i) + "; SetVec size: "+std::to_string(size)+".");

}

/* ************************************************************************** */

// Specific member function (inherited from ResizableContainer)
template <typename Data>
void SetVec<Data>::Resize(unsigned long newCapacity){
    if(newCapacity==0){
        Clear();
        return;
    }
        
    if(capacity != newCapacity){
        Data * tempSVec = new Data[newCapacity] {};
        for(unsigned long i = 0; i < size; ++i){
            tempSVec[i] = std::move(Elements[CircularIndex(i)]);
        }

        delete[] Elements;
        Elements = tempSVec;
        capacity = newCapacity;
        head = 0;
    }
}

/* ************************************************************************** */

// Specific member function (inherited from TestableContainer)
template <typename Data>
bool SetVec<Data>::Exists(const Data &value)const noexcept{
    unsigned long pos = 0;
    return BinarySearch(pos,value);
}

/* ************************************************************************** */

// Specific member functions (inherited from ClearableContainer)
template <typename Data>
void SetVec<Data>::Clear(){
    delete[] Elements;
    Elements = new Data[4]();
    capacity = 4;
    size = head = 0;
}

/* ************************************************************************** */

// Specific constructors
template <typename Data>
SetVec<Data>::SetVec(const unsigned long newCapacity) {
    if(newCapacity > 0)
        capacity = newCapacity;
    else
        capacity = 4;
    
    Elements = new Data[capacity]();
    size = head = 0;
}

// Auxiliary functions

// CircularIndex()
template <typename Data>
unsigned long SetVec<Data>::CircularIndex(unsigned long i) const noexcept{ 
    return (head + i) % capacity;
}


// BinarySearch
template <typename Data>
bool SetVec<Data>::BinarySearch(unsigned long &pos, const Data &value) const{
    
    long left = 0;
    long right = size - 1;

    while(left<=right){
        long mid = (left+right) / 2;

        if(Elements[CircularIndex(mid)] == value){
            pos = mid;
            return true;
        }
        else if(Elements[CircularIndex(mid)]<value)
            left = mid + 1;
        else
            right = mid - 1;
    }

    // pos restituisce la posizione dell'elemento se è presente, altrimenti restituisce la posizione in cui andrebbe inserito
    pos = left;
    return false;
}


/* ************************************************************************** */

}
