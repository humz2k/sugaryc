# sugaryc
 
C, but with function overloading, operator overloading, modules, templates, and uniform function call syntax (and a garbage collector).

Add `bin` to path, then compile with `sgcc`. For example, `sgcc my_file.sgc -o a.out`.

`usage: sgcc [-h] [-o <output>] [-cxx <cxx>] [-c] [-O <opt>] [--echo] [-I <I> [<I> ...]] [-L <L> [<L> ...]] [-l <l> [<l> ...]] [--no-parallel] [--save-temps] <source> [<source> ...]`

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