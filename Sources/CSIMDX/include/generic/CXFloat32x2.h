
/// Try using built-in vectors when available
#if __has_extension(attribute_ext_vector_type)
typedef Float32 CXFloat32x2 __attribute__((ext_vector_type(2)));
#else
typedef Float32[2] CXFloat32x2;
#endif
