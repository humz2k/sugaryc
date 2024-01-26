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

This means I can add \`methods\` whereever I want to, and I can even add \`methods\` to built in types:
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