# Uniform Function Call Syntax (UFCS)

Imagine I have a type
```
struct my_type{
    int a;
    ...
};

struct my_type obj;
```
and a method
```
int my_method(struct my_type obj, int b){
    return obj.a + b;
}
```

I can call it like this:
```
my_method(obj,1);
```
Or, I can call it like this:
```
obj.my_method(1);
```

This means I can add \`methods\` wherever I want, and I can even add \`methods\` to built in types:
```
int add_1(int x){
    return x+1;
}
```
can be called
```
int my_x = 0;
my_x.add_1();
```

It also makes OOP a little less gross. For example, the code
```
struct my_struct{
    int a;
};

typedef struct my_struct* my_object;

int get_a(my_object obj){
    return obj->a;
}

void set_a(my_object obj, int a){
    obj->a = a;
}
```
lets you do stuff like this
```
my_object obj = (my_object)GC_malloc(sizeof(struct my_struct));
obj.set_a(10);
obj.get_a();
```

# Type Inference

Exactly like C++, use `auto`.

# Sugaryc Standard Library

There are some sugaryc-style data structures/algorithms that you can include.

## `lists.sgh`

`std.list<T>` is a 1D dynamic list. It allocates `10` items at a time, and does bounds checking so is slow. `print` and `println` will be correctly formatted.

### Initialization
```
std.list<T> my_list = std.make_list<T>();
```
### API
```
my_list.append(item) //appends item to the list
my_list.pop() //pops the last item
my_list.pop(idx) //pops the item at index idx
my_list.insert(idx,item) //inserts item at index idx
my_list[idx] //returns item at index idx
len(my_list) //returns the length of the list
my_list.destroy() //optionally manually delete the list
```

You can also iterate through a list with `foreach`:
```
foreach(auto i in my_list){
    do_something_with(i);
}
```

`print` and `println` will be correctly formatted.

## `vector.sgh`

`std.vector<T>` is a 1D dynamic array. It is more performant than a `std.list<T>`, but doesn't do bounds checking. It doubles in size on reallocation. `print` and `println` will be correctly formatted.

### Initialization
```
std.vector<T> my_vec = std.make_vector<T>();
```

### API
```
my_vec.push_back(item) //appends item to end of vector
my_vec.emplace_back(item) //removes last item
my_vec.pop_back(item) //pops last item
my_vec.reserve(n) //reserves n elements
my_vec.shrink_to_fit() //shrinks size to fit
my_vec.resize(n) //resizes vector to n elements
len(my_vec) //returns the length of the vector
my_vec.destroy() //optionally manually delete the vector
```

## `optional.sgh`

`std.optional<T>` is a container for optional values of the type `T`.

### Initialization
```
std.optional<T> my_opt = std.make_optional<T>(value);
std.optional<T> my_null_opt = std.nullopt<T>();
```

### API
```
my_opt.value_or(val) //returns value of my_opt if it exists, or val
my_opt.value(val) //returns value of my_opt if it exists, or errors out
my_opt.has_value() //returns true if my_opt has a value, or false if it doesn't
```

## `np/array.sgh`

Numpy style ndarrays. Fast rather than safe. Valid types `T` are: `T=float, double, short, int, long, long long, unsigned short, unsigned int, unsigned long, unsigned long long`. `print` and `println` will be correctly formatted.


### Initialization
```
np.ndarray<T> arr = np.array<T>(Shape(...));
np.ndarray<float> arr = np.array(Shape(...));
```
where `Shape(...)` is a list of dimensions, for example `Shape(10)`, `Shape(2,3)`.

#### Other initializers
```
np.ndarray<T> arr0 = np.ones<T>(Shape(...));
np.ndarray<T> arr1 = np.zeros<T>(Shape(...));
np.ndarray<T> arr2 = np.arange<T>(start=0,end,step=1);
np.ndarray<T> arr3 = np.linspace<T>(start,end,samples);
```

### Attributes
```
shape_t arr.shape //the shape of the array.
    - len(arr.shape) //gives the number of dimensions of the array.
    - arr.shape[i] //gives the ith dimension
int size //the number of elements in the array
T* raw //pointer to the raw memory in the array
```

### API
```
arr.as_type<T>() //casts arr to np.ndarray<T>
arr.reshape(Shape(...)) //reshapes arr
arr.reshape(shape) //given a shape_t, reshape arr
arr.flatten() //flattens arr
arr.destroy() //optionally manually delete arr
```

### Broadcasting
Broadcasting should (!!) work the same as in numpy. For example
```
auto arr3 = (arr + 0.5) * arr2
```

### Math
WIP, but for now:
```
np.sin(arr)
np.cos(arr)
np.tan(arr)
np.asin(arr)
np.acos(arr)
np.atan(arr)
```

# Operator Overloading

This works similar to in python. You overload a built in method for specific types. The method names and corresponding operators are:

```
+  -> __add__
-  -> __sub__
*  -> __mul__
/  -> __div__
<< -> __shl__
>> -> __shr__
%  -> __mod__
|  -> __or__
&  -> __and__
|| -> __lor__
&& -> __land__
^  -> __xor__
<  -> __lt__
>  -> __gt__
<= -> __le__
>= -> __ge__
== -> __eq__
!= -> __neq__
```

There is no awfulness like overloading `*` or `&` for pointers. Any memory allocated in an operator should be allocated using `GC_malloc`, rather than `malloc` (you really just shouldn't use `malloc` at all, if you want to free memory use `GC_free`).

For overloading the index operator, using `__index__`. `__index__` needs to return a pointer to the type that is getting returned (if it needs to be constant, return a `const` pointer). For example, if I am writing an `int` array struct,
```
struct int_array{
    int* array;
};

int* __index__(struct int_array arr, int idx){
    return arr.array + idx;
}
```
For up to `4` dimensions, I can overload:
```
T* __index__(my_type,int idx1);
T* __index__(my_type,int idx1, int idx2);
T* __index__(my_type,int idx1, int idx2, int idx3);
T* __index__(my_type,int idx1, int idx2, int idx3, int idx4);
```
For `n > 4` dimensions, I can overload:
```
T* __index__(my_type, int* idxs, int nidxs);
```
BUT, this will allocate `idxs` on the heap, so is probably a bad idea for performance.

There is no restriction on types used as indexes. If I had a `dictionary` object, it would be valid to have something like:
```
T* __index__(dictionary dict, string str);
```

# Modules

These aren't really modules, just more name mangling. You declare a module with `module module_name;`. Then, anywhere with `module_name.something` will be replaced with something like `module_name__something`. Nothing smarter than that.

# Iterator

Sugaryc has the syntax extension:
```
foreach(T item in my_iterator){
    do_something_with(item);
}
```

An iterator needs to have some overloaded functions. Imagine I'm implementing a wrapper on an `int*`:
```
struct int_ptr_wrapper{
    int* raw;
    int len;
};
```
and I want to be able to iterate though the elements with `foreach`.

I first need to define an `iterator` type:
```
struct int_ptr_iter_struct{
    int* raw;
    int cur;
    int length;
};

typedef struct int_ptr_iter_struct* int_ptr_iter;
```

Then I need to overload `__iter__` to take in a `struct int_ptr_wrapper` and return a `int_ptr_iter` (note that the returned iterator needs to be a pointer):

```
int_ptr_iter __iter__(struct int_ptr_wrapper ptr){
    int_ptr_iter out = (int_ptr_iter)GC_malloc(sizeof(struct int_ptr_iter_struct));
    out->raw = ptr.raw;
    out->length = ptr.length;
}
```

Then I need to overload some functions on `int_ptr_iter`. Firstly, I need to overload the `__start__` function, which should initialize my iterator, and return the first element.
```
int __start__(int_ptr_iter iter){
    iter->cur = 0;
    return iter->raw[iter->cur];
}
```
Then I need to overload `__done__`, which should return a bool if we are done iterating:
```
bool __done__(int_ptr_iter iter){
    return iter->cur >= iter->length;
}
```
And finally, I need to overload `__next__`, which gets the next element:
```
int __next__(int_ptr_iter iter){
    iter->cur++;
    return iter->raw[iter->cur];
}
```

Then, I can iterate through my `struct int_ptr_wrapper ptr` using a `foreach` loop:
```
struct int_ptr_warpper ptr = ...initialization_stuff...;
foreach(auto i in ptr){
    print(i);
}
```

See `range.sgh` and `lists.sgh` in `include` for examples.

# Generics

I like C++ templates, but they can get kind of confusing and a little too complicated. I also like the simplicity of the C preprocessor (simplicity in terms of understanding what it is doing under the hood).

Sugaryc implements generics as a souped up preprocessor. Everything is still dumb text substitution, but the new constructs make it (fairly) easy to write generic, reusable code.

There are two types of generics, `template`s and `generated`s. 

## Templates

These are very simple. They let you wrap an area of code, and then will substitute some string with values you provide. For example:

```
template<T=int,float>{
    T add2(T a, T b){
        return a + b;
    }
}
```

will (literally) be expanded to:
```
int add2(int a, int b){
    return a + b;
}
float add2(float a, float b){
    return a + b;
}
```

Note that each template can only take one parameter as input (although this may change). 

Inputs to templates don't need to be types. Its just text substitution, so you can do all kinds of terrible things. You can also multiple things inside one template block. For example:
```
template<T=int,float>{
    T add2(T a, T b){
        return a + b;
    }

    T sub2(T a, T b){
        return a - b;
    }
}
```
is perfectly valid. You should in theory be able to nest templates, but this can get weird. See `stdlib/np/array.sgc` for an example.

## Generateds

These are a little more complicated, and a little annoying for a few reasons. Essentially, a `generated` will generate some code if the compiler finds some string that we specify. For example:
```
generated my_type<T>{
    typedef struct{
        T a;
    } my_type<T>;
}
```
will generate a `my_type<T>` only if it sees the string `my_type<some T>`. You can specify multiple strings to match against. For example:
```
generated keyword1,keyword2,keyword3<T>{
    typedef struct{
        T a;
    } my_generated_type<T>;
}
```
will generate a `my_generated_type<T>` if any of `keyword1<T>`, `keyword2<T>` or `keyword3<T>` show up. Unlike `template`s, `generated`s can take multiple inputs. 

### Don't nest generated types. It might work, but it depends on the ordering of when things are expanded, and I'll likely change this in the future. Also, don't have a `generated` inside a `template`. Again, it may work, but things get weird.

One thing to note is that the generated code is placed in the same location as the original code. This is important. For example:

```
generated my_type<T>{
    typedef struct{
        T a;
    } my_type<T>;
}

struct my_struct{
    int a;
};

my_type<struct my_struct>;
```

will be expanded to:
```
typedef struct{
    struct my_struct a;
} my_type<struct my_struct>;

struct my_struct{
    int a;
};

my_type<struct my_struct>;
```

Because `struct my_struct` is not declared before `my_type<struct my_struct>`, the compiler will freak out. So for situations where you are including a `generated` (for example from the standard library), note that they need to be included AFTER any relevant declarations.

I know, this is annoying. But it makes it simple to implement, and also to reason about.

## What `thing<other thing>` actually does

Like everything else, `thing<other thing>` just substitutes this with text. So you can really have that anywhere, as another way to mangle names. You can also nest them. 

## Abuse

If you want some examples on how to abuse generics, see `filter_map_reduce.sgh` and `strong_types.sgh` in `include`.

# Function Overloading

This works the same as in C++. Actually, the compiler currently literally generates C++, so the name mangling is identical to C++. This will probably change, so don't count on that being the case.

Use the `extern` keyword to stop name mangling. For example, the header for `free` in `stdlib.sgh` is
```
extern void free(void*);
```

# Cuda Style Kernels

There is some experimental support for cuda style kernels. For example:
```
#include <stdlib.sgh>

__global__ void test(int* in, int* out){
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    out[idx] = in[idx];
}

int main(){
    return 0;
}
```
Currently, these are basically `openmp` `parallel for` constructs, but the goal is to eventually have native GPU support. If you want something a little better, see https://github.com/humz2k/FPC.

# C Standard Library

WIP. Eventually, all C standard library functions/headers will have corresponding `sgh` equivalents. If something is missing, see `math.sgh` for examples on how to write your own wrappers. For any architecture dependent things, see `stdlib_macros.c` and `time_macros.c` in `cstdlib` for examples on how to deal with that. PRs welcome and would be appreciated!

# Booleans

Use builtin type `bool` and `true/false`. `println` and `print` will format `bool`s correctly.