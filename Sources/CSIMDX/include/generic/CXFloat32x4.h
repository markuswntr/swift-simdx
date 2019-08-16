
/// Try using built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef float CXFloat32x4 __attribute__((ext_vector_type(4)));
#else
typedef float[4] CXFloat32x4;
#endif
