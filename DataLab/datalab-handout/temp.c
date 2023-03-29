#include<stdio.h>
int equal(int x,int y)
{
  return (!(x^y));
}
int main()
{
  int x=4,y=4;
  printf("%#x",1073741824);
}

//  unsigned float_i2f(int x)
// {
//   long long lx=x;
//   int flag = (x <= 0), y;
//   unsigned ux = x;
//   int e = 0, m = 0;
//   unsigned E, M;
//   if (x == 0x80000000)
//     return 0xcf000000;
//   if (flag)
//     ux = -x;
//   y = ux;
//   while (ux > 1)
//   {
//     e++;
//     ux >>= 1;
//   }
//   m = y ^ (1 << e);
//   if (e < 23)
//     M = m << (23 - e);
//   else
//   {
//     M = m >> (e - 24);
//     M = (M + (!((M & 3) ^ 3))) >> 1;
//   }
//   E = e + 127;
//   if (y)
//     return ((flag << 31) | (E << 23) | M);
//   return 0;
// }