
namespace lasd {

/* ************************************************************************** */

//specific member function(MappableContainer)

// ...

/* ************************************************************************** */

// Specific member function (PreOrderMappableContainer)

// Override Map
template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun){
    PreOrderMap(fun);
}

/* ************************************************************************** */

// Specific member function (PostOrderMappableContainer)

// Override Map
template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun){
    PostOrderMap(fun);
}

/* ************************************************************************** */

}
