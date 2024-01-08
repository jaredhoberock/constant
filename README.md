# constant

`constant<value>` is a compile-time value like `std::integral_constant<T,value>` with additional arithmetic operators.

It is intended for use cases where it is important to treat values known at compile time uniformly with dynamic values.

For example, `constant<1024>` could encode the the size of a CUDA block:

    constant<1024> block_size;

A user-defined literal operator is included to make it convenient to spell these constants.

    // these two spellings are equivalent:
    constant<1024> block_size_1;
    auto block_size_2 = 1024_c;

We can use `constant` to index tuple-like types without needing to treat the index like a template parameter:

    std::tuple<int,char,std::string> my_tuple = ...
    char element_2 = element(my_tuple, 2_c);

This is sometimes convenient.

