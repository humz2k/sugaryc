# sugaryc
 
C, but with function overloading, operator overloading, modules, templates, and uniform function call syntax (and a garbage collector).

Add `bin` to path, then compile with `sgcc`. For example, `sgcc my_file.sgc -o a.out`.

`usage: sgcc [-h] [-o <output>] [-cxx <cxx>] [-c] [-O <opt>] [--echo] [-I <I> [<I> ...]] [-L <L> [<L> ...]] [-l <l> [<l> ...]] [--no-parallel] [--save-temps] <source> [<source> ...]`

```
struct my_struct{
 int a;
};

typedef struct my_struct* my_object;

void set_a(my_object obj, int a){
 obj->a = a;
}

int get_a(my_object obj){
 return obj->a;
}

int main(){
 my_object obj = (my_object)malloc(sizeof(struct my_struct));
 obj.set_a(10);
 int a = obj.get_a();
 free(obj);
 return 0;
}
