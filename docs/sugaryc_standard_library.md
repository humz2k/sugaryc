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