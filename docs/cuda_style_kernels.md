# Cuda Style Kernels

There is some experimental support for cuda style kernels. For example:
```
#include <stdlib.sgh>

__global__ void test(int* in, int* out){
    int idx = blockDim.x * blockIdx.x + threadIdx.x;
    out[idx] = in[idx];
}

int main(){
    return 0;
}
```
Currently, these are basically `openmp` `parallel for` constructs, but the goal is to eventually have native GPU support. If you want something a little better, see https://github.com/humz2k/FPC.