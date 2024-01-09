
#include <type_traits>

template <typename T, typename T2>
static inline typename std::common_type<T, T2>::type __add__(T t, T2 t2) {
    return t + t2;
}

template <typename T>
static inline T* __add__(T* t, int t2) {
    return t + t2;
}

template <typename T>
static inline T* __add__(int t, T* t2) {
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

template <typename T, typename T2>
static inline int __eq__(T* t, T2 t2) {
    return t == t2;
}

template <typename T, typename T2>
static inline int __neq__(T* t, T2 t2) {
    return t != t2;
}

template <typename T>
static inline T* __index__(T* t, int* idx, int nidx) {
    return &t[idx[0]];
}

//Yes, this is gross and bad but I like syntax sugar. If you want performance, just do *(ptr + idx).

static inline int _n_var_args(){
    return 0;
}

template <typename T, typename... Args>
static inline int _n_var_args(T i, Args... args){
    return 1 + _n_var_args(args...);
}

extern "C" void* GC_malloc(int);

template <typename T>
static inline void _vaptr_helper(T* out, int n){

}

template <typename T, typename... Args>
static inline void _vaptr_helper(T* out, int n, T i, Args... args){
    out[n] = i;
    _vaptr_helper(out,n+1,args...);
}

template <typename T, typename... Args>
static inline T* _var_args_to_ptr(T i, Args... args){
    int n = _n_var_args(i,args...);
    T* out = (T*)GC_malloc(sizeof(T) * n);
    _vaptr_helper(out,0,i,args...);
    return out;
}

//#define __index_wrapper__(var,...) (*__index__(var,(int[]){__VA_ARGS__},_n_var_args(__VA_ARGS__)))
#define __index_wrapper__(var,...) (*__index__(var,_var_args_to_ptr(__VA_ARGS__),_n_var_args(__VA_ARGS__)))

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

//#ifndef NULL

//#endif
