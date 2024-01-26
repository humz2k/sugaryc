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