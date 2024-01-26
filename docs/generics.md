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
is perfectly valid.

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

## Abuse

If you want some examples on how to abuse generics, see `filter_map_reduce.sgh` and `strong_types.sgh` in `include`.