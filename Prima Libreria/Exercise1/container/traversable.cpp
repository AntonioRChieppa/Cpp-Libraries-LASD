
namespace lasd {

/* ************************************************************************** */

// Specific member function (TraversableContainer)
template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun, Accumulator acc) const{
    Traverse(
        [fun,&acc](const Data &dat){
            acc = fun(dat,acc);
        }
    );
    return acc;
}

// Exists override
template <typename Data>
bool TraversableContainer<Data>::Exists(const Data & val) const noexcept{
    bool exists = false;
    Traverse(
        [val, &exists](const Data & dat){
            if(dat == val)
                exists = true;
        }
    );
    return exists;
}


/* ************************************************************************** */

// Specific member function (PreOrderTraversableContainer)

template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    PreOrderTraverse(
        [fun,&acc](const Data &dat){
            acc = fun(dat,acc);
        }
    );
    return acc;
}

// Traverse override
template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const{
    PreOrderTraverse(fun);
}

/* ************************************************************************** */

// Specific member function (PostOrderTraversableContainer)

template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    PostOrderTraverse(
        [fun, &acc](const Data &dat){
            acc = fun(dat,acc);
        }
    );
    return acc;
}

// Traverse override
template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const{
    PostOrderTraverse(fun);
}

/* ************************************************************************** */

}
