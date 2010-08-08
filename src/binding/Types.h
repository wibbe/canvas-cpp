#ifndef V8_SCRIPT_TYPES_HPP
#define V8_SCRIPT_TYPES_HPP
  
/**
* Servs as a null marker for types.
*/
class NullType { };

/**
* Serves as a default ("don't care") type for templates.
*/
struct EmptyType { };

/**
* Class that generates a distinct type for each distinct constant
* integral value passed.
*/
template <int v>
struct Int2Type
{
 enum { value = v };
};


#endif