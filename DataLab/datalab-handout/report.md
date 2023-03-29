# datalab实验报告
## bitXor
```c
int bitXor(int x, int y) {
     return ~(x&y)&~(~x&~y);
}
```
异或：将析取范式中的$ \lor $ 用  $ \land 和 \lnot $表示

$\lnot ((x \land y) \lor (\lnot x \land \lnot y))= \lnot (x \land y) \land \lnot(\lnot x \land \lnot y)$
## thirdBits
```c
int thirdBits(void) 
{
  int x=0x49;
  x^=x<<9;
  x^=x<<18;
  return x;
}
```
从(1001001)b 开始，累次左移

## fitsShort
```c
int fitsShort(int x) 
{
  x+=1<<15;
  return!(x>>16);
}
```
首先给x加上(1>>15),将负数映射成整数，若x可用short表示，则映射后的范围在0~0xffff内，否则前16位不全为零，这一判断
可用右移操作符清掉后16位后取！实现

## isTmax
```c
int isTmax(int x) 
{
  int v1 = x + 1;
  int v2 = v1 + v1;
  return !(v2 | (!v1));
}
```
考虑x0=0x7fffffff的特殊性质，y0=x0+1=0x80000000,y0<<1后为零，满足该条件的只有x0和x1=0xffffffff，故可取|(!y0)排除x1即可判断。

## fitsBits
```c
int fitsBits(int x, int n)
{
  int v = x >> (n + (~0));
  //printf("%#x\n", v);
  return !((v+1)>>1);
}
```
若$−2^{n-1}≤x<2^{n-1}$，则x若为正数，则高32−(n-1)位均为0，若为负数，则高32−(n-1)位均为1。故考虑右移n-1位，若结果全零或全一则为真。

## upperbit
```c
int upperBits(int n) 
{
   return ((!!n)<<31)>>(n+(~0)) ;
}
```
我们可以通过将0x8000左移n-1位来实现，但n=0时需要单独考虑，故用(!!n)<<31 来表示 0x8000 ，当n=0时，整个表达式为0

## anyOddBit
```c
int anyOddBit(int x) {
    int mask=0xaa;
    mask|=mask<<8;
    mask|=mask<<16;
    return !!(x&mask);
}
```
首先构造掩码(1010...)b(三十二位)，之后取!!(x&mask)即可

## byteSwap
```c
int byteSwap(int x, int n, int m)
{
    int shift_n=n<<3;
    int shift_m=m<<3;
    int n_byte = (x>>shift_n)& 0xff;
    int m_byte = (x>>shift_m) & 0xff;
    int mask=(0xff<<shift_m)|(0xff<<shift_n);
    x=(x&(~(mask)))|((n_byte<<shift_m)|(m_byte<<shift_n));
    return x;
}
```
原始思路：
首先计算对应的位移shift_n和shift_m，得到nth和mth字节的内容，最后清空x的m,n_th字节的内容，通过 或运算 交换字节。
```c
int byteSwap(int x, int n, int m)
{
    int shift_n=n<<3;
    int shift_m=m<<3;
    int c=((x>>shift_m)^(x>>shift_n))&0xff;
    return x^(c<<shift_n)^(c<<shift_m);
}
```
考虑到交换可以通过异或进行，我们可以用异或操作优化运算符。
## absVal
初始代码
```c
  int is_naga=x>>31;
  return (x&~is_naga)+((~x+1)&is_naga);
```
x为负数时，可以通过~x+1算出-x，~x=x^(111...),
由于x>>31=111...(x<0),000...(x>=0)
为了保证x为正时，值不发生变换，可以通过x^(x>>31)+(x>>31)&1来实现。

注意到取反加一等价与减一取反，故可以进一步优化为`return (x+is_na)^is_na;`
## divpwr2
```c
int divpwr2(int x, int n)
{
    //int flag = (x >> 31) & ((1 << n)+~0);
    int sign=x>>31;
    int flag=~(sign<<n);
    return( x + (sign&flag)) >> n;
}
```
原思路：
由于x>>0是向下取整，故对于x>=0,直接返回x>>n，当x<0时，需要加上$2^n-1$作为修正因子。故可设flag=(x >> 31) & ((1 << n)+~0),返回( x + flag) >> n即可

修改后：
修正因子可以考虑通过sign左移n位取反得到。

## float_neg
```c
unsigned float_neg(unsigned uf) 
{
  unsigned u=uf<<1;
  return uf^((u<=(0xFF000000))<<31);
}
```
首先去除符号位得到u，然后通过比较u和0xFF000000判断是否为规范数，若为规范数，则对符号位与1取异或，否则对零取异或。
## logicalNeg
```c
int logicalNeg(int x) 
{
  return ((x|(~x+1))>>31)+1;
}
```
注意到这样一个特性，除零之外，所有数和它的相反数中必有一个符号位为1

|表达式  |0|非零|
|:---|:---:|:---:|
|(x\|(~x+1))>>31)|000...|111...|

对(x|(~x+1))>>31) 加一即可实现

## bitMask
```c
int bitMask(int highbit, int lowbit) 
{
  int mask = ~0;
  int m1 = mask << highbit<<1;
  int m2 = mask << lowbit;
  return( m1 ^ m2)&m2;
}
```
记 mask = ~0，当highbit>=lowbit时，分别将mask左移highbit+1位，lowbit位后取异或，即可得到对应的值,当0，当highbi < lowbit时，异或后的值与mask << lowbit与操作归零，由此即可实现
## isGreater
```c
int isGreater(int x, int y)//x>y <->x>=y+1
{
  // int x_sign = x >> 31;
  // int y_sign = y >> 31;
  // int y_x = y + ~x+1;
  // int y_x_sign = y_x >> 31;
  // int is_dif = x_sign ^ y_sign;
  // return ((is_dif & y_sign) | ((~is_dif) & y_x_sign)) & 1;
  int dif_sig=x^y; //same 0... else 1...
  int z=x+~y;//x-y-1 x>y :0... else 1...
  int judge1=dif_sig&x;
  int judge2=~dif_sig&z;
  return ((judge1|judge2)>>31)+1;

}
```
该题比较两个数字的大小，首先我们明确正数是比负数大的，而负数比正数小

利用该性质我们可以先由该性质判断，随后利用两数相减再减一为非负数数时返回1性质写出表达式

## logicalShift
```c
int logicalShift(int x, int n) 
{
  return (x>>n)&(~(1<<31>>n<<1));
}
```
本题需要实现逻辑移位，通过算术移位再与做与运算消去左边可能出现的1即可
## satMul2
```c
int satMul2(int x) 
{
  int ret=x<<1;
  int Tmin=1<<31;
  int is_dif=(ret^x)>>31;
  return (ret&~is_dif)|(is_dif&(Tmin^(ret>>31)));
}
```
记ret=2*x，当x和ret同号时，此时未溢出，否则根据ret的符号返回Tmin或Tmax。

## subOK
```c
int subOK(int x, int y) {
int z=x+~y+1;
int dif_sig=x^y;
int over_flow=z^x;
return ((dif_sig&over_flow)>>31)+1;
}
```
 分类讨论，当x,y同号时，肯定不会溢出，当x,y符号不同时，记z=x-y,若z与x同号，则未溢出，否则溢出。

## trueThreeFourths 
```c
int trueThreeFourths(int x)
{
  int flag=~(x>>31)&3;
  int y=((x+flag)>>2)&(~(flag<<30));
  return x+~y+1;
}
```
欲求$\frac{3}{4}x$向零取整，只需求出$\frac{1}{4}x$向两边取整的值再做差即可。x为负，x>>2已经满足向下取整,x>=0,对应的值应该是$\frac{x+3}{4}$向下取整,由于可能的overflow，用>>2对整数操作时还要对~0xC0000000做与操作。可以用flag=~(x>>31)&3,x>=0时flag=3,<0时为零，~0xC0000000也可用~(flag<<30)表示。

## isPower2
```c
int isPower2(int x) 
{
  int y=x+~0;
  return !((x&y)|(y>>30));
}
```
当x=$2^n,n>=0且n!=31$时,x=00..01000..(由一个1和31个零组成),x-1=00..001111..
有x&x-1为0,可以证明这一性质仅在x由一个1和31个零组成或x=0时成立。为了排除0和0x80000000，可以用(x&(x-1))与((x-1)>>30)求并，后者会在x=0和0x80000000为1，再对整体取非即可。

## float_i2f
```c
unsigned float_i2f0(int x)
{
    long long lx = x;
    int flag = (lx < 0);
    int e = 0;
    unsigned m;
    unsigned abs_x;
    long long cop_abs_x;
    unsigned tail;
    int add_1 = 0;
    unsigned tmp_x;
    if (flag)
        abs_x = -lx;
    else
        abs_x = lx;
    cop_abs_x = abs_x;
    while (cop_abs_x)
    {
        e++;
        cop_abs_x >>= 1;
    }
    tmp_x = abs_x;
    if (e <= 24)
        m = ((tmp_x << (33 - e))) >> 9;
    else
    {
        tail = (abs_x << (55 - e));
        add_1 = (tail & 0x40000000) && (tail ^ 0x40000000);
        m = ((abs_x >> (e - 24))) & 0x7fffff;
    }
    if (x)
        return ((flag << 31) + ((e + 126) << 23) + m) + add_1;
    else
        return 0;
}
```
最初的思路：首先判断符号位，用flag记录，然后算出x绝对值abs_x，拷贝副本tmp_x，不断将tmp_x右移，得到指数e，然后根据e与24的大小分类讨论，算出小数部分，同时考虑进位。进位的条件为有效位下一位为一，且有效位和有效位下一位右的数不全为零。之后各部分移位叠加即可。
然而小数部分计算的讨论比较麻烦，为了简化，优化的版本如下：
```c
unsigned float_i2f(int x)
{
    int flag = (x < 0);
    unsigned abs_x, carry;
    unsigned tmp, left_0 = 0, E;
    if (x)
    {
        if (flag)
            abs_x = -x;
        else
            abs_x = x;
        tmp = abs_x;

        while (!(tmp & (0x80000000)))
        {
            tmp <<= 1;
            left_0++;
        }
        tmp <<= 1;
        E = 158 - left_0;
        if ((tmp & 0x100) && (tmp & 0x2ff))
            carry = 1;
        else
            carry = 0;
        return ((flag << 31) | (E << 23) | (tmp >> 9)) + carry;
    }
    else
        return 0;
}
```
绝对值和符号位的思路不变，但小数部分的计算我们不再将原数右移，而是左移到底，间接算出指数部分E，同时也能方便地省略首位的1，固定之后右移的位数，简化分类讨论。
## howManyBits
```c

int howManyBits(int x) 
{
  int b16,b8,b4,b2,b1;
  x ^= (x<<1);
  b16=((!!(x>>16))<<4);
  x>>=b16;
   b8=(!!(x>>8))<<3;
  x>>=b8;
   b4=(!!(x>>4))<<2;
  x>>=b4;
   b2=(!!(x>>2))<<1;
  x>>=b2;
  b1=(x>>1)&1;
  return b16+b8+b4+b2+b1+1;
}
```
欲求表示x的最小位数，只需找出非负数最左边的1或负数最左边的0的位置，再加一（符号位）就能得到答案。首先可以用x^=(x<<1),将符号位设为1，符号位前的位设为零，之后利用二分法得到符号位的bit位。

## float_half
最初版本：
```c
unsigned float_half(unsigned uf)
{
    unsigned sign_bit = (uf & 0x80000000);
    unsigned abs_f = uf - sign_bit;
    unsigned carry,shift;
    int add;
    if (abs_f >= 0x7f800000)
        return uf;
    else if (abs_f >= 0x900000)
        return sign_bit + abs_f - 0x800000;
    else
    {
        carry = ((abs_f & 3) == 3);
        return sign_bit + (abs_f >> 1) + carry;
    }
}
```
首先提出符号位，得到uf的绝对值abs_f，然后根据uf的指数位分类讨论
1. uf为NAN，此时指数位为11111111,abs_f >= 0x7f800000，返回uf
2. uf除二后仍为规格数,此时指数位>=00000002,abs_f >= 0x900000,uf/2只需将原指数位减一，其余部分不变，故返回sign_bit + abs_f - 0x800000。
3. 其他情况，uf除二后为非规格数,uf/2的绝对值等于abs_f >> 1再加上可能的进位，由IEEE向偶数舍入的规则，当且仅当abs_f最后两位均为1时方可进位，故返回sign_bit + (abs_f >> 1) + carry，其中carry = ((abs_f & 3) == 3)
注意到返回的结构很有特点，都是符号位+指数位+小数位，故可以考虑统一不同的情况，减少一个运算符
```c
unsigned float_half(unsigned uf)
{
    unsigned sign_bit = (uf & 0x80000000);
    unsigned abs_f = uf - sign_bit;
    unsigned carry,shift;
    int add;
    if (abs_f >= 0x7f800000)
    {
        shift = 0;
        add = 0;
    }
    else if (abs_f >= 0x900000)
    {
        shift = 0;
        add = -0x800000;
    }
    else
    {
        shift = 1;
        carry = ((abs_f & 3) == 3);
        add = carry;
    }
    return sign_bit + (abs_f >> shift) + add;
}
```