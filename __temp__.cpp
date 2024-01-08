
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
extern "C" void *malloc(int);
extern "C" void free(void *);
extern "C" int printf(const char *format, ...);
int main()
{
  printf("%f\n", __sub__(__add__(1.0, __div__(__mul__(1.0, 5), 2)), 2));
  return 0;
}

