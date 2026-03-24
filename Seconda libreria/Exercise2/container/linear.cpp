
namespace lasd {
/* ************************************************************************** */

// Comparison operators (LinearContainer)

template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer<Data> &container) const noexcept{
    if(size == container.size){
        for(unsigned long i=0;i < size; ++i){
            if(operator[](i) != container.operator[](i))
                return false;
        }
        return true;
    }
    else
        return false;
}

template <typename Data>
inline bool LinearContainer<Data>::operator!=(const LinearContainer<Data> &container) const noexcept{
    return !(*this == container);
}

/* ************************************************************************** */

// Specific member function (LinearContainer)

template <typename Data>
inline const Data & LinearContainer<Data>::Front() const{
    return operator[](0);
}

template <typename Data>
inline const Data & LinearContainer<Data>::Back() const{
    return operator[](this->size - 1);
}

/* ************************************************************************** */

// Specific member function (inherited from TraversableContainer)

template <typename Data>
inline void LinearContainer<Data>::Traverse(const TraverseFun fun) const{
    PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderTraversableContainer)

template <typename Data>
inline void LinearContainer<Data>::PreOrderTraverse(const TraverseFun fun) const{
    for(unsigned long i=0; i<this->size; ++i){
        fun(operator[](i));
    }
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderTraversableContainer)
template <typename Data>
inline void LinearContainer<Data>::PostOrderTraverse(const TraverseFun fun) const{
    for(unsigned long i=this->size; i > 0;){
         fun(operator[](--i));
    }
}

/* ************************************************************************** */

// Specific member function (MutableLinearContainer)
template <typename Data>
inline Data & MutableLinearContainer<Data>::Front(){
    return operator[](0);
}

template <typename Data>
inline Data & MutableLinearContainer<Data>::Back(){
    return operator[](this->size - 1);
}

/* ************************************************************************** */

// Specific member function (inherited from MappableContainer)
template <typename Data>
inline void MutableLinearContainer<Data>::Map(MapFun fun){
    PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member function (inherited from PreOrderMappableContainer)
template <typename Data>
inline void MutableLinearContainer<Data>::PreOrderMap(MapFun fun){
    for(unsigned long i=0;i<this->size;i++){
        fun(operator[](i));
     }
    
}

/* ************************************************************************** */

// Specific member function (inherited from PostOrderMappableContainer)
template <typename Data>
inline void MutableLinearContainer<Data>::PostOrderMap(MapFun fun){
    for(unsigned long i = this->size; i > 0;){
        fun(operator[](--i));
    }
}

/* ************************************************************************** */

// Specific member function (SortableLinearContainer)

template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept{
    InsertionSort();
}

// InsertionSort()
template <typename Data>
void SortableLinearContainer<Data>::InsertionSort() noexcept{
    for(unsigned long i = 1; i < this->size; ++i){
        Data x = std::move(this->operator[](i));
        long j = i - 1;
        while(j>=0 && x < this->operator[](j)){
            this->operator[](j+1) = std::move(this->operator[](j));
            --j;
        } 
        this->operator[](j+1) = std::move(x);
    }
}

/* ************************************************************************** */

}
