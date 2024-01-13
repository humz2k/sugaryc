# sugaryc
 
C, but with function overloading, operator overloading, and uniform function call syntax.

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
 return 0;
}
