#include <stdlib.h>
#include <stdio.h>

/*
typedef union
{
    float f;
    
    struct
    {
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
    } parts;
} float_cast;

int main (void)
{
    float_cast d1 = { .f = 0.55625 };
    
    printf("sign = %x\n", d1.parts.sign);
    printf("exponent = %x\n", d1.parts.exponent);
    printf("mantissa = %x\n", d1.parts.mantissa);
    
    return 0;
}
*/

void convert (unsigned long int value)
{
    unsigned int sign;
    unsigned int mantissa;
    unsigned int exponent;
    float decimal = 2.0;
    
    sign = (value & 0x8000000000000000) >> 63;
    exponent = (value & 0x7FE0000000000000) >> 53;
    mantissa = (value & 0x001FFFFFFFFFFFFF);
    
    printf ("Sign %d:", sign);
    printf ("Scientific Notation: ");
    
    if (sign == 1)
        printf ("-");
    
    printf ("1.%d x 2^(%d)", mantissa, exponent);
    
    for (int x = 0; x < exponent; x++)
        decimal *= 2.0;
        
    printf ("\n\nDecimal: %f", decimal);
    
    return;
}

int main ()
{
    convert(0x4029000000000000);
    puts("\n");
    convert(0x4529000000000000);
    puts("\n");
    convert(0x4029400000000000);
    return 0;
}