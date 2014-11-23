#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#define NEGATIVE 1
#define POSITIVE 0

double number(int bits, int sign, int exp);

double number(int bits, int sign, int exp)
{
    double res,frac,y;
    double i;
    frac = 0.0;
    for (i=1.0; i<=bits-1; i++)
    {
        y = pow(2,-i);   // Y = 2^-i
        frac = frac + y;      // Fraction = Fraction + Y
    }                   // leaving only the hidden bit (1) to add and to multiply by the sign.
    res = pow(-1.0, sign) * (1.0 + frac) * pow(2,exp-1);   // res = (-1)^S * (1.0 + Fraction) + (2)^exp
    return res;
}


int main()
{
    int k = 2;
    int l = 3;
    printf("%d to the power of %d-1 is: %f\n", k, l, pow(k,l-1));
//    printf("The range of char is between %d and %d and the number of bits is %d\n", CHAR_MIN, CHAR_MAX, CHAR_BIT);
//    printf("The range of int is between %d and %d and the number of bits is %d\n", INT_MIN, INT_MAX, log2f(32.0));
//    printf("The range of short int is between %d and %d\n", SHRT_MIN, SHRT_MAX);
//    printf("The range of long int is between %d and %d\n", LONG_MIN, LONG_MAX);
//    printf("The range of unsigned char is between 0 and %d\n", UCHAR_MAX);
//    printf("The range of unsigned int is between 0 and %u\n", UINT_MAX);
//    printf("The range of unsigned short int is between 0 and %u\n", USHRT_MAX);
//    printf("The range of unsigned long int is between 0 and %lu\n", ULONG_MAX);
//    printf("Radix of exponent (b) in float is %d\n", FLT_RADIX);
    printf("The radix of the base (p) in float is %d\n", FLT_MANT_DIG);
    printf("The radix of the base (p) in double float is %d\n", DBL_MANT_DIG);
    printf("The minimun exponent number for a representable number in float is %d\n", FLT_MIN_EXP);
    printf("The minimun exponent number for a representable number in double is %d\n", DBL_MIN_EXP);
    printf("The maximum exponent number for a representable number in float is %d\n", FLT_MAX_EXP);
    printf("The maximum exponent number for a representable number in double is %d\n", DBL_MAX_EXP);
//    printf("Number of decimal digits q such that any floating-point number with q decimal\n"
//           "digits can be rounded into a floating-point number with p radix b digits and\n"
//           "back again without change to the q decimal digits %d\n",FLT_DIG);
//    printf("Minimum int x such that FLT_RADIX**(x-1) is a normalized float, emin:  %d\n", FLT_MIN_EXP);
//    printf("Maximun representable finite floating point number %f\n", FLT_MAX);
//    printf("Minimum normalized positive floating point number %f\n", FLT_MIN);
    printf("The biggest number in single precision is %f\n", number(FLT_MANT_DIG, POSITIVE, FLT_MAX_EXP));
    printf("The biggest number in double precision is %f\n", number(DBL_MANT_DIG, POSITIVE, DBL_MAX_EXP));
    printf("The smallest number in single precision is %f\n", number(FLT_MANT_DIG, POSITIVE, FLT_MIN_EXP));
    printf("The smallest number in single precision is %0.25f\n", number(DBL_MANT_DIG, POSITIVE, DBL_MIN_EXP));
    return 0;
}
