
#include <type_traits>

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __add__(T t, T2 t2) {
    return t + t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __sub__(T t, T2 t2) {
    return t - t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __mul__(T t, T2 t2) {
    return t * t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __div__(T t, T2 t2) {
    return t / t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __shl__(T t, T2 t2) {
    return t << t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __shr__(T t, T2 t2) {
    return t >> t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __mod__(T t, T2 t2) {
    return t % t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __or__(T t, T2 t2) {
    return t | t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __and__(T t, T2 t2) {
    return t & t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __lor__(T t, T2 t2) {
    return t || t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __land__(T t, T2 t2) {
    return t && t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __xor__(T t, T2 t2) {
    return t ^ t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __lt__(T t, T2 t2) {
    return t < t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __gt__(T t, T2 t2) {
    return t > t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __le__(T t, T2 t2) {
    return t <= t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __ge__(T t, T2 t2) {
    return t >= t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __eq__(T t, T2 t2) {
    return t == t2;
}

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __neq__(T t, T2 t2) {
    return t != t2;
}

template <typename T>
static inline T* __index__(T* t, int* idx, int nidx) {
    return &t[idx[0]];
}

#define __index_wrapper__(var,...) (*__index__(var,(int[]){__VA_ARGS__},sizeof((int[]){__VA_ARGS__})/sizeof(int)))

/*template <typename T, typename... Args>
static inline auto __index_wrapper__(T* t, Args... args) -> decltype(*__index__(t,args...)) {
    return *__index__(t,args...);
}*/


/*template<typename T>
struct _ndarray{
    T* raw;
    int* dims;
    int ndims;
};

template <typename... Args>
static inline int _get_index(int* dims, int ndims, int out, int i, Args... args) {
    if (ndims == 1){
        return out + i;
    }
    int this_idx = i;
    for (int i = 1; i < ndims; i++){
        this_idx *= dims[i];
    }
    return _get_index(dims,ndims-1,out + this_idx, args...);
}

template<typename T, typename... Args>
static inline T* __index__(struct _ndarray<T>* arr, Args... args){
    int idx = _get_index(arr->dims,arr->dims,0,args...);
    
}

typedef struct _ndarray<double>* _DoubleArray;
typedef struct _ndarray<float>* _FloatArray;
typedef struct _ndarray<int>* _IntArray;
typedef struct _ndarray<long int>* _LongIntArray;*/