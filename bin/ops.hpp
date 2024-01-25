
#include <type_traits>

#include <stdbool.h>

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __add__(T t, T2 t2) {
    return t + t2;
}

template <typename T>
static inline __attribute__((always_inline)) T* __add__(T* t, int t2) {
    return t + t2;
}

template <typename T>
static inline __attribute__((always_inline)) T* __add__(int t, T* t2) {
    return t + t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __sub__(T t, T2 t2) {
    return t - t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __mul__(T t, T2 t2) {
    return t * t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __div__(T t, T2 t2) {
    return t / t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __shl__(T t, T2 t2) {
    return t << t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __shr__(T t, T2 t2) {
    return t >> t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __mod__(T t, T2 t2) {
    return t % t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __or__(T t, T2 t2) {
    return t | t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __and__(T t, T2 t2) {
    return t & t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __lor__(T t, T2 t2) {
    return t || t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __land__(T t, T2 t2) {
    return t && t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __xor__(T t, T2 t2) {
    return t ^ t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __lt__(T t, T2 t2) {
    return t < t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __gt__(T t, T2 t2) {
    return t > t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __le__(T t, T2 t2) {
    return t <= t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __ge__(T t, T2 t2) {
    return t >= t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __eq__(T t, T2 t2) {
    return t == t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) typename std::common_type<T, T2>::type __neq__(T t, T2 t2) {
    return t != t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) int __eq__(T* t, T2 t2) {
    return t == t2;
}

template <typename T, typename T2>
static inline __attribute__((always_inline)) int __neq__(T* t, T2 t2) {
    return t != t2;
}

template <typename T>
static inline __attribute__((always_inline)) T* __index__(T* t, int* idx, int nidx) {
    return &t[idx[0]];
}

//Yes, this is gross and bad but I like syntax sugar. If you want performance, just do *(ptr + idx).

static inline __attribute__((always_inline)) int _n_var_args(){
    return 0;
}

template <typename T, typename... Args>
static inline __attribute__((always_inline)) int _n_var_args(T i, Args... args){
    return 1 + _n_var_args(args...);
}

extern "C" void* GC_malloc(int);
extern "C" void* GC_realloc(void*,int);
extern "C" void GC_free(void*);

template <typename T>
static inline __attribute__((always_inline)) void _vaptr_helper(T* out, int n){

}

template <typename T, typename... Args>
static inline __attribute__((always_inline)) void _vaptr_helper(T* out, int n, T i, Args... args){
    out[n] = i;
    _vaptr_helper(out,n+1,args...);
}

template <typename T, typename... Args>
static inline __attribute__((always_inline)) T* _var_args_to_ptr(T i, Args... args){
    int n = _n_var_args(i,args...);
    T* out = (T*)GC_malloc(sizeof(T) * n);
    _vaptr_helper(out,0,i,args...);
    return out;
}

//#define __index_wrapper__(var,...) (*__index__(var,(int[]){__VA_ARGS__},_n_var_args(__VA_ARGS__)))
#define __index_wrapper__(var,...) (*__index__(var,_var_args_to_ptr(__VA_ARGS__),_n_var_args(__VA_ARGS__)))

static inline const char* __str__(_Bool i){
    if (i == false)return "false";
    return "true";
}

template <typename T>
static inline const char* __str__(T a){
    return "NULL";
}

template<typename T>
static inline const char* to_str(T in);

extern "C" int printf(const char* format, ... );

static inline void print(){

}

template <typename T, typename... Args>
static inline void print(T t, Args... args) {
    printf("%s ",to_str(t));
    print(args...);
}

#define println(...) print(__VA_ARGS__);printf("\n")

extern "C" void exit(int);

#define __global__ 

#define __generate(...) 

#define warpsize 32

#define LAUNCH_KERNEL(func,numBlocks,blockSize,...) \
{\
    for (int _bidx = 0; _bidx < numBlocks; _bidx++){\
        _Pragma("omp parallel for")\
        for (int _warpidx = 0; _warpidx < blockSize/(warpsize/2); _warpidx++){\
            for (int _modid = 0; _modid < (warpsize/2); _modid++){\
                func(make_int3(_bidx,0,0),make_int3(blockSize,1,1),make_int3(_warpidx * (warpsize/2) + _modid,0,0), __VA_ARGS__);\
            }\
        }\
    }\
}

 
#define __bool_true_false_are_defined 1

#define NULL nullptr

//#ifndef NULL

//#endif
