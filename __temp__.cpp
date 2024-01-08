

static inline int __add__(int l, int r){
    return l + r;
}extern "C" void *malloc(int);
extern "C" void free(void *);
extern "C" int printf(const char *format, ...);
int main()
{
  __add__(1, 1);
  return 0;
}

