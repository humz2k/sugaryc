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