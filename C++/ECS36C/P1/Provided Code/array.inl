// TODO: Implement the methods of class Array here or in the header file.
template <typename T, std::size_t Length>
Array<T, Length>& Array<T, Length>::operator=(const Array<T, Length>& other){
    for (int i = 0; (unsigned)i <= (Length-1); ++i){
        this->array[i] = other.array[i];
    }
    return *this;
}

template <typename T, std::size_t Length>
Array<T, Length>::Array(const Array<T, Length>& other)
{
    for (int i = 0; (unsigned)i <= (Length-1); ++i){
        this->array[i] = other.array[i];
    }
}

template <typename T, std::size_t Length>
T& Array<T, Length>::at(std::size_t index){
    if (index <= (Length-1))
    {
        return this->array[index];
    }
    else
    {
        throw std::out_of_range("Index must be in range.");
    }
}

template <typename T, std::size_t Length>
const T& Array<T, Length>::at(std::size_t index) const{
    if (index <= (Length-1))
    {
        return this->array[index];
    }
    else
    {
        throw std::out_of_range("Index must be in range.");
    }
}

// For your convenience, I show you a bit of what the definition of the size()
// method looks like below.
template <typename T, std::size_t Length>
std::size_t Array<T, Length>::size() const
{
    // TODO: Implement.
    return Length;
}

/**
 * Here, Index must come before T and Length in the `template < ... >` line.
 * I'm not sure why; I just know the compiler wants it that way.
 */
template <std::size_t Index, typename T, std::size_t Length>
T& get(Array<T, Length>& array)
{
    // TODO: Provide a static assertion that causes compilation to fail
    // if the given index is out of range.
    static_assert(Index < Length, "Index out of range");
    // TODO: Retrieve the element.
    return array.at(Index);

}



template <std::size_t Index, typename T, std::size_t Length>
const T& get(const Array<T, Length>& array)
{
    // TODO: Provide a static assertion that causes compilation to fail
    // if the given index is out of range.
    static_assert(Index < Length, "Index out of range");
    // TODO: Retrieve the element.
    return array.at(Index);
}


// TODO: Implement the const overload of get(), either here or in the header
// file.

// TODO: Implement operator<<, either here or in the header file.
template <typename T, std::size_t Length>
std::ostream& operator<<(std::ostream& os, const Array<T, Length>& array)
{
    for (int i = 0; (unsigned)i <= (Length-1); ++i)
    {
        os<<array.at(i) << ' ';
    }
    os<<std::endl;
    return os;
}

