#ifndef __LIBAEDS_ARRAY_H__
#define __LIBAEDS_ARRAY_H__

#include <stddef.h>


// Short macro for writing for loops iterating an index.
// `var` must be a valid unused variable name in the context of the calling site.
// `from` must be an expression of type size_t. It is evaluated only once.
// `size` must be an expression of type size_t. It is evaluated once for each iterarion.
// Complexity: O(n) where n is the size.
#define foreach_ix(var, from, size) for (size_t var = (from); var < (size); var++)

// Fill an array of pointers with the given value. O(size) complexity.
// A for loop with a assignment is used. This guarantees the correct pointer
// representation is assigned, opposed to using memset.
// Complexity: O(n) where n is the size of the supplied array.
void array_fill(void** restrict array, size_t size, void* value);


// Indexing for void* arrays.
// array_get(a, elem_size, index) is equivalent to `a + (elem_size * index)`.
void* array_get(void*, size_t elem_size, size_t index);


#endif /* __LIBAEDS_ARRAY_H__ */
