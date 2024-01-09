
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
extern "C" void *malloc(int);
extern "C" void free(void *);
const char *__str__(const char *s);
const char *__str__(float f);
const char *__str__(double f);
const char *__str__(short a);
const char *__str__(int a);
const char *__str__(long int a);
const char *__str__(long long int a);
struct _int_tuple;
typedef struct _int_tuple *int_tuple;
int_tuple make_int_tuple(int *raw, int length);
const int *__index__(int_tuple t, int *idx, int nidx);
int len(int_tuple t);
const char *__str__(int_tuple t);
typedef const char *string;
string __add__(string left, string right);
string __mul__(string left, int right);
string __mul__(int left, string right);
typedef struct 
{
  float x;
  float y;
} float2;
inline static float2 make_float2(float x, float y)
{
  float2 out;
  out.x = x;
  out.y = y;
  return out;
}

inline static string __str__(float2 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__("float2", "{"), to_str(vec.x)), ", "), to_str(vec.y)), "}");
  return out;
}

typedef struct 
{
  float x;
  float y;
  float z;
} float3;
inline static float3 make_float3(float x, float y, float z)
{
  float3 out;
  out.x = x;
  out.y = y;
  out.z = z;
  return out;
}

inline static string __str__(float3 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__("float3", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), "}");
  return out;
}

typedef struct 
{
  float x;
  float y;
  float z;
  float w;
} float4;
inline static float4 make_float4(float x, float y, float z, float w)
{
  float4 out;
  out.x = x;
  out.y = y;
  out.z = z;
  out.w = w;
  return out;
}

inline static string __str__(float4 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__("float4", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), ", "), to_str(vec.w)), "}");
  return out;
}

typedef struct 
{
  double x;
  double y;
} double2;
inline static double2 make_double2(double x, double y)
{
  double2 out;
  out.x = x;
  out.y = y;
  return out;
}

inline static string __str__(double2 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__("double2", "{"), to_str(vec.x)), ", "), to_str(vec.y)), "}");
  return out;
}

typedef struct 
{
  double x;
  double y;
  double z;
} double3;
inline static double3 make_double3(double x, double y, double z)
{
  double3 out;
  out.x = x;
  out.y = y;
  out.z = z;
  return out;
}

inline static string __str__(double3 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__("double3", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), "}");
  return out;
}

typedef struct 
{
  double x;
  double y;
  double z;
  double w;
} double4;
inline static double4 make_double4(double x, double y, double z, double w)
{
  double4 out;
  out.x = x;
  out.y = y;
  out.z = z;
  out.w = w;
  return out;
}

inline static string __str__(double4 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__("double4", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), ", "), to_str(vec.w)), "}");
  return out;
}

typedef struct 
{
  short x;
  short y;
} short2;
inline static short2 make_short2(short x, short y)
{
  short2 out;
  out.x = x;
  out.y = y;
  return out;
}

inline static string __str__(short2 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__("short2", "{"), to_str(vec.x)), ", "), to_str(vec.y)), "}");
  return out;
}

typedef struct 
{
  short x;
  short y;
  short z;
} short3;
inline static short3 make_short3(short x, short y, short z)
{
  short3 out;
  out.x = x;
  out.y = y;
  out.z = z;
  return out;
}

inline static string __str__(short3 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__("short3", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), "}");
  return out;
}

typedef struct 
{
  short x;
  short y;
  short z;
  short w;
} short4;
inline static short4 make_short4(short x, short y, short z, short w)
{
  short4 out;
  out.x = x;
  out.y = y;
  out.z = z;
  out.w = w;
  return out;
}

inline static string __str__(short4 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__("short4", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), ", "), to_str(vec.w)), "}");
  return out;
}

typedef struct 
{
  int x;
  int y;
} int2;
inline static int2 make_int2(int x, int y)
{
  int2 out;
  out.x = x;
  out.y = y;
  return out;
}

inline static string __str__(int2 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__("int2", "{"), to_str(vec.x)), ", "), to_str(vec.y)), "}");
  return out;
}

typedef struct 
{
  int x;
  int y;
  int z;
} int3;
inline static int3 make_int3(int x, int y, int z)
{
  int3 out;
  out.x = x;
  out.y = y;
  out.z = z;
  return out;
}

inline static string __str__(int3 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__("int3", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), "}");
  return out;
}

typedef struct 
{
  int x;
  int y;
  int z;
  int w;
} int4;
inline static int4 make_int4(int x, int y, int z, int w)
{
  int4 out;
  out.x = x;
  out.y = y;
  out.z = z;
  out.w = w;
  return out;
}

inline static string __str__(int4 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__("int4", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), ", "), to_str(vec.w)), "}");
  return out;
}

typedef struct 
{
  long x;
  long y;
} long2;
inline static long2 make_long2(long x, long y)
{
  long2 out;
  out.x = x;
  out.y = y;
  return out;
}

inline static string __str__(long2 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__("long2", "{"), to_str(vec.x)), ", "), to_str(vec.y)), "}");
  return out;
}

typedef struct 
{
  long x;
  long y;
  long z;
} long3;
inline static long3 make_long3(long x, long y, long z)
{
  long3 out;
  out.x = x;
  out.y = y;
  out.z = z;
  return out;
}

inline static string __str__(long3 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__("long3", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), "}");
  return out;
}

typedef struct 
{
  long x;
  long y;
  long z;
  long w;
} long4;
inline static long4 make_long4(long x, long y, long z, long w)
{
  long4 out;
  out.x = x;
  out.y = y;
  out.z = z;
  out.w = w;
  return out;
}

inline static string __str__(long4 vec)
{
  string out = __add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__(__add__("long4", "{"), to_str(vec.x)), ", "), to_str(vec.y)), ", "), to_str(vec.z)), ", "), to_str(vec.w)), "}");
  return out;
}

struct _int_array;
struct _long_int_array;
struct _float_array;
struct _double_array;
typedef struct _int_array *int_array;
typedef struct _long_int_array *long_array;
typedef struct _float_array *float_array;
typedef struct _double_array *double_array;
double_array _make_double_array(int *dims, int ndims);
float_array _make_float_array(int *dims, int ndims);
int_array _make_int_array(int *dims, int ndims);
long_array _make_long_int_array(int *dims, int ndims);
int *__index__(int_array arr, int *idxs, int nidx);
long int *__index__(long_array arr, int *idxs, int nidx);
float *__index__(float_array arr, int *idxs, int nidx);
double *__index__(double_array arr, int *idxs, int nidx);
int ndims(int_array arr);
int ndims(long_array arr);
int ndims(float_array arr);
int ndims(double_array arr);
int_tuple dims(int_array arr);
int_tuple dims(long_array arr);
int_tuple dims(float_array arr);
int_tuple dims(double_array arr);
extern "C" double sin(double x);
extern "C" double cos(double x);
extern "C" double tan(double x);
extern "C" double asin(double x);
extern "C" double acos(double x);
extern "C" double atan(double x);
extern "C" double atan2(double y, double x);
extern "C" double sinh(double x);
extern "C" double cosh(double x);
extern "C" double tanh(double x);
extern "C" double asinh(double x);
extern "C" double acosh(double x);
extern "C" double atanh(double x);
extern "C" double exp(double x);
extern "C" double frexp(double x, int *exp);
extern "C" double ldexp(double x, int exp);
extern "C" double log(double x);
extern "C" double log10(double x);
extern "C" double modf(double x, double *iptr);
extern "C" double exp2(double x);
extern "C" double expm1(double x);
extern "C" int ilogb(double x);
extern "C" double log1p(double x);
extern "C" double log2(double x);
extern "C" double logb(double x);
extern "C" double scalbn(double x, int n);
extern "C" double scalbln(double x, long int n);
extern "C" double pow(double x, double y);
extern "C" double sqrt(double x);
extern "C" double cbrt(double x);
extern "C" double hypot(double x, double y);
extern "C" double erf(double x);
extern "C" double erfc(double x);
extern "C" double tgamma(double x);
extern "C" double lgamma(double x);
extern "C" double ceil(double x);
extern "C" double floor(double x);
extern "C" double fmod(double x, double y);
extern "C" double trunc(double x);
extern "C" double round(double x);
extern "C" long int lround(double x);
extern "C" long long int llround(double x);
extern "C" double rint(double x);
extern "C" long int lrint(double x);
extern "C" long long int llrint(double x);
extern "C" double nearbyint(double x);
extern "C" double remainder(double x, double y);
extern "C" double remquo(double x, double y, int *quo);
extern "C" double copysign(double x, double y);
extern "C" double nan(const char *tagp);
extern "C" double nextafter(double x, double y);
extern "C" double nexttoward(double x, long double y);
extern "C" double fdim(double x, double y);
extern "C" double fmax(double x, double y);
extern "C" double fmin(double x, double y);
extern "C" double fabs(double x);
extern "C" double abs(double x);
extern "C" double fma(double x, double y, double z);
extern "C" const double M_PI;
extern "C" const double M_E;
extern "C" float sinf(float x);
extern "C" float cosf(float x);
extern "C" float tanf(float x);
extern "C" float asinf(float x);
extern "C" float acosf(float x);
extern "C" float atanf(float x);
extern "C" float atan2f(float y, float x);
extern "C" float sinhf(float x);
extern "C" float coshf(float x);
extern "C" float tanhf(float x);
extern "C" float asinhf(float x);
extern "C" float acoshf(float x);
extern "C" float atanhf(float x);
extern "C" float expf(float x);
extern "C" float frexpf(float x, int *exp);
extern "C" float ldexpf(float x, int exp);
extern "C" float logf(float x);
extern "C" float log10f(float x);
extern "C" float modff(float x, float *iptr);
extern "C" float exp2f(float x);
extern "C" float expm1f(float x);
extern "C" int ilogbf(float x);
extern "C" float log1pf(float x);
extern "C" float log2f(float x);
extern "C" float logbf(float x);
extern "C" float scalbnf(float x, int n);
extern "C" float scalblnf(float x, long int n);
extern "C" float powf(float x, float y);
extern "C" float sqrtf(float x);
extern "C" float cbrtf(float x);
extern "C" float hypotf(float x, float y);
extern "C" float erff(float x);
extern "C" float erfcf(float x);
extern "C" float tgammaf(float x);
extern "C" float lgammaf(float x);
extern "C" float ceilf(float x);
extern "C" float floorf(float x);
extern "C" float fmodf(float x, float y);
extern "C" float truncf(float x);
extern "C" float roundf(float x);
extern "C" long int lroundf(float x);
extern "C" long long int llroundf(float x);
extern "C" float rintf(float x);
extern "C" long int lrintf(float x);
extern "C" long long int llrintf(float x);
extern "C" float nearbyintf(float x);
extern "C" float remainderf(float x, float y);
extern "C" float remquof(float x, float y, int *quo);
extern "C" float copysignf(float x, float y);
extern "C" float nanf(const char *tagp);
extern "C" float nextafterf(float x, float y);
extern "C" float nexttowardf(float x, long double y);
extern "C" float fdimf(float x, float y);
extern "C" float fmaxf(float x, float y);
extern "C" float fminf(float x, float y);
extern "C" float fabsf(float x);
extern "C" float absf(float x);
extern "C" float fmaf(float x, float y, float z);
float sin(float x);
float cos(float x);
float tan(float x);
float asin(float x);
float acos(float x);
float atan(float x);
float atan2(float y, float x);
float sinh(float x);
float cosh(float x);
float tanh(float x);
float exp(float x);
float log(float x);
float log10(float x);
float pow(float x, float y);
float sqrt(float x);
float cbrt(float x);
float ceil(float x);
float floor(float x);
float fmod(float x, float y);
float fabs(float x);
int main()
{
  auto a = make_long4(1, 2, 3, 4);
  println(a);
  return 0;
}


template<typename T>
static inline const char* to_str(T in){
    return __str__(in);
}
