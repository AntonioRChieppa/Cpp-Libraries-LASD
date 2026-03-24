
namespace lasd {

/* ************************************************************************** */

// Specific member function (DictionaryContainer)

// InsertAll (Copy, TraversbleContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> &container){
    bool allInserted = true;
    container.Traverse(
        [&allInserted, this](const Data &dat){
            if(!Insert(dat))
                allInserted = false;
        }
    );
    return allInserted;
}

// InsertAll (Move, MappableContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertAll(MappableContainer<Data> && container) noexcept{
    bool allInserted = true;
    container.Map(
        [&allInserted, this](Data &dat){
            if(!Insert(std::move(dat)))
                allInserted = false;
        }
    );
    return allInserted;
}

// InsertSome (Copy, TraversableContainer)
template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> &container){
    bool someInserted = false;
    container.Traverse(
        [&someInserted,this](const Data &dat){
            if(Insert(dat))
                someInserted = true;
        }
    );
    return someInserted;
}

// InsertSome (Move, MappableContainer)
template <typename Data>
inline bool DictionaryContainer<Data>::InsertSome(MappableContainer<Data> &&container) noexcept{
    bool someInserted = false;
    container.Map(
        [&someInserted,this](Data &dat){
            if(Insert(std::move(dat)))
                someInserted = true;
        }
    );
    return someInserted;
}

// RemoveAll
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> &container){
    bool allRemoved = true;
    container.Traverse(
        [&allRemoved,this](const Data &dat){
            if(!Remove(dat))
                allRemoved = false;
        }
    );
    return allRemoved;
}

// RemoveSome
template <typename Data>
inline bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> &container){
    bool someRemoved = false;
    container.Traverse(
        [&someRemoved,this](const Data &dat){
            if(Remove(dat))
                someRemoved = true;
        }
    );
    return someRemoved;
}

/* ************************************************************************** */

}
