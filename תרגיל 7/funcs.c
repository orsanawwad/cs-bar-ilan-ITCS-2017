/*****************************************
* Student name: Orsan Awwad
* Student ID: *
* Course Exercise Group: 01
* Exercise name: Exercise 7 C Part
******************************************/

#include "funcs.h"

int bitAnd(int x, int y) {
    /**
     * We have (x^y)
     * We Apply DeMorgan twice
     * ⇒ ¬¬(x∧y) = (x^y)
     * ⇒ ¬(¬x∨¬y) = (x^y)
     * We managed to have an expression that only contains NOTs and ORs
     */
    return ~(~x|~y);
}

int bitCount(int x) {
    /**
     * The next five lines creates constant masks with the following value
     * - 0x55555555
     * - 0x33333333
     * - 0x0f0f0f0f
     * - 0x00FF00FF
     * - 0x0000FFFF
     */
    int fives = ((((((0x55<<8)+0x55)<<8)+0x55)<<8)+0x55);
    int threes = ((((((0x33<<8)+0x33)<<8)+0x33)<<8)+0x33);
    int zeroF = ((((((0x0f<<8)+0x0f)<<8)+0x0f)<<8)+0x0f);
    int twoFs = (((0xff)<<16)+0xff);
    int fourFs = ((0xff)<<8)+0xff;
    /**
     * The following 5 lines uses the divide and conquer method, each of
     * those steps adds neighboring bits in groups of 1, 2, 4, 8 (since
     * we're using 32 bit), then after the last step we'll have the
     * final count number in binary, converting that to decimals will
     * give us the correct value.
     */
    int c = (x & fives) + ((x >> 1) & fives);
    c = ((c >> 2) & threes) + (c & threes);
    c = ((c >> 4) + c) & zeroF;
    c = ((c >> 8) + c) & twoFs;
    c = ((c >> 16) + c) & fourFs;
    return c;
}

int bang(int x) {
    /**
     * What happens here is we combine the 1s in the number with its negated form, shift it 31 times to
     * the right, and add 1, using this method on any number other than zero, the result after shifting
     * the number will be 111...111111 (all ones), so adding 1 to it will give 0 for any x > 0, x < 0,
     * however if x was zero, the equation before adding 1 will always be zero, because 0 with its
     * negated value is and always will be zero, we can use this to then add one to it which will return
     * the correct result, because the bang operator only returns 1 if the number is 0, and returns 0 for
     * anything else than that.
     */
    return ((x | (~x+1)) >> 31 ) + 1;
}

int fitsBits(int x, int n) {
    // Calculate how many high order bits are remaining after using n low order bits.
    int a = (33 + (~n));
    // The next two lines fills the high order bits with the same value as the sign bit of x
    int b = (x << a);
    int c = (b >> a);
    // This is equivalent to c == x
    int e = !(c ^ x);
    return e;
}

int divpwr2(int x, int n) {
    /**
     * First have to compute the bias so rounds towards 0
     * We only add the bias if x < 0, so we can use its MSB as the start
     * If it is 0 we do nothing, if it is 1 we will add something
     */

    return (x + (((x >> 31 & 1) << n) + x >> 31)) >> n;
}

int negate(int x) {
    // Two's complement pretty much, run NOT on all the bits and add one in the end to get the negative value
    return ~x+1;
}

int isPositive(int x) {
    /* Create 0x80000000 constant aka 1000 0000 0000 0000 0000 0000 0000 0000 */
    int a = 1 << 31;

    /**
     * The goal of this equation is to check if the number is NOT zero AND its MSB is NOT 1
     * If one of the two conditions is true then the number is not positive,
     * We check the MSB using (x & a) >> 31 where a is 0x8000000 where it cancels everything
     * but the MSB and shift it 31 times to the right where if the MSB we get the number 0
     * and if its 1 we get 32 bits of 1s, if the value is anything other than zero, running !
     * (bang) on it will return 0 aka false, else it'll be 1 if MSB is 0.
     * Next we check if the number is zero by simply using ! (bang) operator on the original
     * number, if its anything other than zero, it'll return 0, else it'll return one.
     *
     * The condition is !isMSBEqualsOne & !isZero where if one of the conditions is true
     * then the number is positive
     *
     * NOTE:
     * !isMSBEqualsOne & !isZero is the same as !(isMSBEqualsOne | isZero) (using DeMorgan)
     * this way we compressed to one less operation
     *
     */
    int isZero = !x;
    int isMSBEqualsOne = (x & a) >> 31;
    return !(isMSBEqualsOne | isZero);
}

int isLessOrEqual(int x, int y) {
    /**
     * If x < y, then x - y < 0 (the value will be negative), x - y is the same as saying (y + (~x + 1)), if its
     * negative the MSB will be 1, else it'll be zero, but we want x <= y, not just x < y, so we negate it with !
     * and we get the result.
     */
    return !(((y + (~x + 1)) >> 31) & 1);
}
