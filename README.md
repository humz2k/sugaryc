# sugaryc
 
C, but with function overloading, operator overloading, modules (kind of), templates (kind of), and uniform function call syntax (and a garbage collector - https://github.com/ivmai/bdwgc).

Sugaryc is (almost) a strict superset of C, with extra features that try to make C prettier while keeping overhead relatively low.

See `docs` (https://github.com/humz2k/sugaryc/tree/main/docs) for documentation.

## Getting Started

### Building
You need `python3` and a C++ compiler installed (preferably `gcc-13/g++-13`). Set the environment variable `SGCC_CXX` to your C++ compiler of choice (e.g. `export SGCC_CXX="g++-13"`).

First, build the gc with `chmod +x build_gc.sh; ./build_gc.sh`.

Then, run `chmod +x build.sh; ./build.sh` to build the standard library, header files and pycparser scripts.

### Using the compiler

Add `bin` to path, then compile with `sgcc`. For example, `sgcc my_file.sgc -o a.out`. If you don't have `g++-13`, then specify another C++ compiler with `sgcc my_file.sgc -o a.out -cxx my_compiler`. `sgcc` uses some `gcc` extensions, so you will probably need to use some version of `gcc`.

`usage: sgcc [-h] [-o <output>] [-cxx <cxx>] [-c] [-O <opt>] [--echo] [-I <I> [<I> ...]] [-L <L> [<L> ...]] [-l <l> [<l> ...]] [--no-parallel] [--save-temps] <source> [<source> ...]`

### Hello world
In C, hello world looks like:
```
#include <stdlib.h>
#include <stdio.h>

int main(){
    printf("Hello, World!\n");
    return 0;
}
```
Ew. I don't feel like typing `\n` everywhere. Enter sugaryc:
```
#include <stdlib.sgh>

int main(){
    println("Hello, World!");
    return 0;
}
```
If this is in the file `helloworld.sgc`, we can compile it with `sgcc helloworld.sgc -o helloworld.o`, and run with `./helloworld.o`.

#### WTF

`println` (and its friend `print`) are cool for a few reasons. Firstly, no formatting strings. We can print any number of arguments, and they will be formatted correctly. For example:
```
#include <stdlib.sgh>
#include <string.sgh>

int main(){
    println("These are some numbers:",0,1,2,2.5);
    return 0;
}
```
will print `These are some numbers: 0 1 2 2.5`. Secondly, we can overload the `__str__` function for our own types, which `println` and `print` will use to print them. For example:
```
#include <stdlib.sgh>
#include <string.sgh>

struct my_struct{
    int a;
};

string __str__(struct my_struct input){
    return "struct my_struct{" + to_str(input.a) + "}";
}

int main(){
    struct my_struct thing;
    thing.a = 5;
    println(thing);
    return 0;
}
```
will print `struct my_struct{5}`. You also probably noticed that the `+` operator concatenates strings, and there is a `string` type. `string`s are still just a `const char*` (really, `typedef const char* string;`), but the overloaded operators return a garbage collected `const char*` (and there is no more need to use `strcat` and friends, although you can if you really want to).

The idea is to hide the complexity, while still giving you the control you get in normal C.

#### Ok, I guess that's kind of cool
It is. Here's some other cool stuff (that might make you angry, C people seem angry a lot).
##### Lists and iterators
```
#include <stdlib.sgh>
#include <lists.sgh>
#include <range.sgh>

int main(){
    auto my_list = std.make_list<int>();
    foreach(auto i in range(10)){
        my_list.append(i);
    }
    println(my_list);
    return 0;
}
```
##### Optionals
```
#include <stdlib.sgh>
#include <optional.sgh>

int main(){
    std.optional<int> i = std.make_optional<int>(10);
    println(i.value_or(0));
    std.optional<int> j = std.nullopt<int>();
    println(j.value_or(0));
    return 0;
}
```
##### Strong types
```
#include <stdlib.sgh>
#include <strong_types.sgh>

typedef std.strong_type<int, val % 2 == 0> even;
static inline even make_even(int val){
    return std.make_strong<int,val%2==0>(val);
}

int main(){
    even my_even_int = make_even(2);
}
```
##### Memory safety
```
#include <stdlib.sgh>

typedef struct {
    int a;
} my_struct;

#include <safe_ptr.sgh>

int main(){
    auto safe_array = std.alloc_safe<int>(10);
    safe_array[0] = 1;
    auto safe_object = std.alloc_safe<my_struct>();
    return 0;
}
```
##### N-D arrays
```
#include <stdlib.sgh>
#include <np/array.sgh>

int main(){
    auto array = np.zeros(Shape(2,5));
    auto array2 = np.ones(Shape(10));
    println(array);
    println(array2);
    println(array + array2.reshape(Shape(2,5)));
    return 0;
}
```
##### And more that I have forgotten.

### Examples

See `examples` for code samples.

## FAQs

### Why?
Idk.

### Why not just use C++?
I don't like C++ very much.

### Why garbage collection?
It makes things easy.

### Who is this for?
Me. If you like C, maybe you too.

### Is this just regex and macro abuse?
Yes.
