
#include <type_traits>

#include <stdbool.h>

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
extern "C" void* GC_realloc(void*,int);

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

//#ifndef NULL

//#endif
extern "C" void *malloc(long unsigned int);
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
int __eq__(string left, string right);
int __neq__(string left, string right);
int len(string str);
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

struct list_struct__template__int
{
  int *raw;
  int length;
  int n_allocated;
};
typedef struct list_struct__template__int *std__list__template__int;
inline static std__list__template__int std__make_list__template__int(void)
{
  std__list__template__int out = (std__list__template__int) GC_malloc(sizeof(struct list_struct__template__int));
  if (!__neq__(out, nullptr))
  {
    printf("%s: FAILED\n", "out != NULL");
    exit(1);
  }
  ;
  out->length = 0;
  out->n_allocated = 10;
  out->raw = (int *) GC_malloc(__mul__(sizeof(int), 10));
  if (!__neq__(out->raw, nullptr))
  {
    printf("%s: FAILED\n", "out->raw != NULL");
    exit(1);
  }
  ;
  return out;
}

inline static void append(std__list__template__int lst, int val)
{
  if (!__neq__(lst, nullptr))
  {
    printf("%s: FAILED\n", "lst != NULL");
    exit(1);
  }
  ;
  if (!__ge__(lst->length, 0))
  {
    printf("%s: FAILED\n", "lst->length >= 0");
    exit(1);
  }
  ;
  if (!__lt__(lst->length, lst->n_allocated))
  {
    lst->n_allocated = __add__(lst->n_allocated, 10);
    lst->raw = (int *) GC_realloc(lst->raw, __mul__(sizeof(int), lst->n_allocated));
    if (!__neq__(lst->raw, nullptr))
    {
      printf("%s: FAILED\n", "lst->raw != NULL");
      exit(1);
    }
    ;
  }
  if (!__lt__(lst->length, lst->n_allocated))
  {
    printf("%s: FAILED\n", "lst->length < lst->n_allocated");
    exit(1);
  }
  ;
  __index_wrapper__(lst->raw, lst->length) = val;
  lst->length++;
  return;
}

inline static int pop(std__list__template__int lst, int idx)
{
  if (!__neq__(lst, nullptr))
  {
    printf("%s: FAILED\n", "lst != NULL");
    exit(1);
  }
  ;
  if (!__lt__(idx, lst->length))
  {
    printf("%s: FAILED\n", "idx < lst->length");
    exit(1);
  }
  ;
  int out = __index_wrapper__(lst->raw, idx);
  for (int i = idx; __lt__(i, __sub__(lst->length, 1)); i++)
  {
    __index_wrapper__(lst->raw, i) = __index_wrapper__(lst->raw, __add__(i, 1));
  }

  lst->length--;
  if (__gt__(__sub__(lst->n_allocated, lst->length), 10))
  {
    lst->n_allocated = __sub__(lst->n_allocated, 10);
    if (!__gt__(lst->n_allocated, 0))
    {
      printf("%s: FAILED\n", "lst->n_allocated > 0");
      exit(1);
    }
    ;
    if (!__ge__(lst->n_allocated, lst->length))
    {
      printf("%s: FAILED\n", "lst->n_allocated >= lst->length");
      exit(1);
    }
    ;
    lst->raw = (int *) GC_realloc(lst->raw, __mul__(sizeof(int), lst->n_allocated));
  }
  return out;
}

inline static int pop(std__list__template__int lst)
{
  if (!__neq__(lst, nullptr))
  {
    printf("%s: FAILED\n", "lst != NULL");
    exit(1);
  }
  ;
  if (!__gt__(lst->length, 0))
  {
    printf("%s: FAILED\n", "lst->length > 0");
    exit(1);
  }
  ;
  return pop(lst, __sub__(lst->length, 1));
}

inline static int len(std__list__template__int lst)
{
  if (!__neq__(lst, nullptr))
  {
    printf("%s: FAILED\n", "lst != NULL");
    exit(1);
  }
  ;
  return lst->length;
}

inline static void insert(std__list__template__int lst, int idx, int value)
{
  if (!__neq__(lst, nullptr))
  {
    printf("%s: FAILED\n", "lst != NULL");
    exit(1);
  }
  ;
  if (!__lt__(idx, lst->length))
  {
    printf("%s: FAILED\n", "idx < lst->length");
    exit(1);
  }
  ;
  if (!__lt__(__add__(lst->length, 1), lst->n_allocated))
  {
    lst->n_allocated = __add__(lst->n_allocated, 10);
    lst->raw = (int *) GC_realloc(lst->raw, __mul__(sizeof(int), lst->n_allocated));
    if (!__neq__(lst->raw, nullptr))
    {
      printf("%s: FAILED\n", "lst->raw != NULL");
      exit(1);
    }
    ;
  }
  for (int i = __sub__(lst->length, 1); __ge__(i, idx); i--)
  {
    __index_wrapper__(lst->raw, __add__(i, 1)) = __index_wrapper__(lst->raw, i);
  }

  __index_wrapper__(lst->raw, idx) = value;
  lst->length++;
}

inline static int *__index__(std__list__template__int lst, int *idxs, int n)
{
  if (!__neq__(lst, nullptr))
  {
    printf("%s: FAILED\n", "lst != NULL");
    exit(1);
  }
  ;
  if (!__eq__(n, 1))
  {
    printf("%s: FAILED\n", "n == 1");
    exit(1);
  }
  ;
  int idx = __index_wrapper__(idxs, 0);
  if (!__lt__(idx, lst->length))
  {
    printf("%s: FAILED\n", "idx < lst->length");
    exit(1);
  }
  ;
  if (!__neq__(lst->raw, nullptr))
  {
    printf("%s: FAILED\n", "lst->raw != NULL");
    exit(1);
  }
  ;
  return &__index_wrapper__(lst->raw, idx);
}

inline static string __str__(std__list__template__int lst)
{
  string out = "[";
  for (int i = 0; __lt__(i, __sub__(lst->length, 1)); i++)
  {
    out = __add__(out, __add__(to_str(__index_wrapper__(lst->raw, i)), ", "));
  }

  if (__gt__(lst->length, 0))
  {
    out = __add__(out, to_str(__index_wrapper__(lst->raw, __sub__(lst->length, 1))));
  }
  out = __add__(out, "]");
  return out;
}

int main()
{
  auto my_list = std__make_list__template__int();
  println(my_list);
  for (int i = 0; __lt__(i, 5); i++)
  {
    append(my_list, i);
    println(my_list, len(my_list));
  }

  insert(my_list, 1, 10);
  println(my_list, len(my_list));
  return 0;
}


template<typename T>
static inline const char* to_str(T in){
    return __str__(in);
}
