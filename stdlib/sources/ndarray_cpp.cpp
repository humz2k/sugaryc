#include <stdlib.h>
#include <stdio.h>

#include <assert.h>

extern "C" void* GC_malloc(int);

#include <stdarg.h>

template<typename T>
struct _ndarray{
    T* raw;
    int* dims;
    int ndims;
};

template<typename T>
struct _ndarray<T>* _make_ndarray(int* dims, int ndims){
    struct _ndarray<T>* out = (struct _ndarray<T>*)GC_malloc(sizeof(struct _ndarray<T>));

    out->dims = (int*)GC_malloc(sizeof(int) * ndims);
    out->ndims = ndims;

    int sz = 1;
    for (int i = 0; i < ndims; i++){
        sz *= dims[i];
        out->dims[i] = dims[i];
    }

    out->raw = (T*)GC_malloc(sizeof(T) * sz);
    
    return out;
}

struct _ndarray<double>* _make_double_array(int* dims, int ndims){
    return _make_ndarray<double>(dims, ndims);
}

struct _ndarray<float>* _make_float_array(int* dims, int ndims){
    return _make_ndarray<float>(dims, ndims);
}

struct _ndarray<int>* _make_int_array(int* dims, int ndims){
    return _make_ndarray<int>(dims, ndims);
}

struct _ndarray<long int>* _make_long_int_array(int* dims, int ndims){
    return _make_ndarray<long int>(dims, ndims);
}

template<typename T>
static inline T* _index_ndarray(struct _ndarray<T>* arr, int* idxs, int nidx){
    assert(arr->ndims == nidx);

    int index = 0;
    for (int i = 0; i < nidx; i++){
        int this_idx = idxs[i];
        for (int j = 0; j < (arr->ndims - i) - 1; j++){
            this_idx *= arr->dims[j];
        }
        index += this_idx;
    }

    return &arr->raw[index];
    
}

extern "C" int* _index_int_array(struct _ndarray<int>* arr, int* idxs, int nidx){
    return _index_ndarray(arr,idxs,nidx);
}

extern "C" long int* _index_long_int_array(struct _ndarray<long int>* arr, int* idxs, int nidx){
    return _index_ndarray(arr,idxs,nidx);
}

extern "C" float* _index_float_array(struct _ndarray<float>* arr, int* idxs, int nidx){
    return _index_ndarray(arr,idxs,nidx);
}

extern "C" double* _index_double_array(struct _ndarray<double>* arr, int* idxs, int nidx){
    return _index_ndarray(arr,idxs,nidx);
}