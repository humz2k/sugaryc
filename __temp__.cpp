extern "C" void *malloc(int);
extern "C" void free(void *);
extern "C" int printf(const char *format, ...);
struct my_struct
{
  int a;
  int b;
};
typedef struct my_struct *MY_OBJECT;
int get_a(MY_OBJECT self)
{
  return self->a;
}

int get_b(MY_OBJECT self)
{
  return self->b;
}

void set_a(MY_OBJECT self, int a)
{
  self->a = a;
}

MY_OBJECT __add__(MY_OBJECT left, MY_OBJECT right)
{
  return left;
}

int main()
{
  MY_OBJECT test = (MY_OBJECT) malloc(sizeof(struct my_struct));
  return 0;
}

