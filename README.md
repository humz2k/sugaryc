# sugaryc
 
C, but with function overloading, operator overloading, modules, templates, and uniform function call syntax (and a garbage collector).

## Building
Run `chmod +x build.sh; ./build.sh` to build the standard library, header files and pycparser scripts, OR run `make clean; make all` in `cstdlib`, `make clean; make libsgc.a` in `stdlib` and `python3 _build_tables.py` in `pycparser`.

## Using the compiler

Add `bin` to path, then compile with `sgcc`. For example, `sgcc my_file.sgc -o a.out`.

`usage: sgcc [-h] [-o <output>] [-cxx <cxx>] [-c] [-O <opt>] [--echo] [-I <I> [<I> ...]] [-L <L> [<L> ...]] [-l <l> [<l> ...]] [--no-parallel] [--save-temps] <source> [<source> ...]`

## Examples

See `examples` for code samples.

Sneak peak:

```
#include <stdlib.sgh>
#include <string.sgh>
#include <assert.sgh>
#include <lists.sgh>
#include <safe_ptr.sgh>
#include <range.sgh>

int main(){

    auto my_list = std.make_list<int>();
    my_list.append(1);
    my_list.append(2);
    println(my_list);

    foreach(int i in my_list){
        println(i);
    }

    foreach(auto i in range(10)){
        println(i);
    }

    auto my_safe_ptr = std.alloc_safe<float>(10);
    my_safe_ptr[0] = 0;
    my_safe_ptr[1] = 1;
    my_safe_ptr[2] = 2;
    println(my_safe_ptr[0],my_safe_ptr[1],my_safe_ptr[2]);

    return 0;
}
```

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