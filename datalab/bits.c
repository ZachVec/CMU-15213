/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~x & ~y) & ~(x & y);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
/* TMax = 0x7FFFFFFF
 * obviously we got ~((TMax << 1) + 1) = 0, but ~((TMin << 1) + 1) also equals to 0
 * and << is illeagal, which could be replaced with x + x
 * then the question would be how do we distinguish TMin and TMax
 * TMax + 1 = TMin; TMin + 1 = 0
 */
  int flag1 = !~(x + x + 1); // 1 if x is TMin, TMax, otherwise 0
  int flag2 = !(x + 1);      // 1 if x is TMin, other wise 0
  return flag1 & !flag2;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int mask = 0xaa | 0xaa << 8 | 0xaa << 16 | 0xaa << 24;
  return !((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x)+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*
   * 0x30(00110000) ~ 0x39(00111001)
   */
  int flag1 = !((x >> 4) ^ 0x03); // 1 if 0x0000003x, 0 otherwise
  int flag2_1 = !(x & 0x08);      // 1 if 4th bit 0, 0 otherwise
  int flag2_2 = !(x & 0x06);
  return flag1 & (flag2_1 | flag2_2);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  x = (((!!x) << 31) >> 31);
  return (x & y) | (~x & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*
   * x <= y under 2 conditions:
   * 1. x, y have different sign bit and x's sign bit is 1
   * 2. x, y have same sign bit and y-x >= 0
   *  - when x != TMin, y-x = ~x + 1 + y, if sign bit of y-x is 0, return 1; 1 otherwise;
   *  - when x == TMin, ~x + 1 = x, so ~x + 1 + y = x + y, which would overflow, and sign bit would be 0
   */
  int xsign = (x >> 31) & 0x01;
  int ysign = (y >> 31) & 0x01;
  int diffSign = xsign ^ ysign; // diffSign = 1 if sign bits are different, or 0 otherwise
  int flag1 = diffSign & xsign; // different sign & x's sign bit is 1
  int flag2 = !diffSign & !((~x + 1 + y) >> 31);
  return flag1 | flag2;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  /*
  lowbit16 = x >> 16 | x;
  lowbit8 = lowbit16 >> 8 | lowbit8;
  lowbit4 = lowbit8 >> 4 | lowbit8;
  lowbit2 = lowbit4 >> 2 | lowbit4;
  lowbit1 = lowbit2 >> 1 | lowbit2;
  return lowbit1 & 0x01;
  */
  /*
   * 1. x = 0, ~x + 1 = 0
   * 2. x = TMin, ~x + 1 = TMin
   * 3. x ≠ 0, x ≠ TMin, ~x + 1 = -x
   * So, the conclusion above divide x | ~x+1 into 2 cases:
   *     - x = 0, sign bit of x | ~x+1 = 0, return 1;
   *     - x ≠ 0, sign bit of x | ~x+1 = 1, return 0;
   */
  return ((x | (~x + 1)) >> 31) + 1;

}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /* For positives, we find first 1 bit and plus 1;
   * For negatives, we find first 0 bit and plus 1;
   * So we ~ negatives only, and find first 1 bit and plus 1;
   * The whole process is:
   *  1. process the number: ~negatives
   *  2. find the first bit being 1
   *  3. output the wight of that bit we find above and plus 1
   */
  int flag1, flag2, flag3, flag4, flag5, flag6;
  x = (x >> 31) ^ x;
  flag1 = !!(x >> 16) << 4;
  x = x >> flag1;
  flag2 = !!(x >> 8) << 3;
  x = x >> flag2;
  flag3 = !!(x >> 4) << 2;
  x = x >> flag3;
  flag4 = !!(x >> 2) << 1;
  x = x >> flag4;
  flag5 = !!(x >> 1);
  x = x >> flag5;
  flag6 = x;
  return flag1 + flag2 + flag3 + flag4 + flag5 + flag6 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exp_mask = 0xFF << 23;
  int exp_flip = ~exp_mask;
  int sign = uf & 0x80000000;
  int exp = (uf & exp_mask) >> 23;
  if (exp == 0)
    return sign | (uf << 1);
  if (exp == 0xFF)
    return uf;
  exp++;
  if (exp == 0xFF)
    return sign | exp_mask;
  return (uf & exp_flip) | (exp << 23);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int exp = ((uf & 0xFF << 23) >> 23) - 127; // true exponent
  int sig = (uf & 0x3fffff) | 0x800000;    // sig = 1xxx...x, x - 23 bits
  int sign = (uf & 0x80000000);            // positive or negative

  // the number now is actually
  // s000...01.xxx...x(23 bits significand),
  // where s is the sign bit, 000...0 is 0 of 30 bits, 

  // if exp < 0, then the number would be in (-1, 1)
  // which would be 0 if casted into int
  if (exp < 0) return 0;

  // if exp >= 31, then left shift would overflow
  // which means the number would be inf
  if (exp >= 31) return 0x80000000u;

  // now the uf can be casted into int

  // sig now is 1xxx...x rather than 1.xxx...x
  // so the true value is sig * 2 ^ (exp - 23),
  if (exp <= 23) sig >>= (23 - exp);
  else sig <<= (exp - 23);
  if(sign) return ~sig + 1;
  else return sig;

}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // 2.0^x ange of different segments:
    // denormalized: x < -126, exp < 1
    //  - min: 0 00000000 00000000000000000000001 = 0x00000001 = 2 ^ (-149)
    //  - max: 0 00000000 10000000000000000000000 = 0x00400000 = 2 ^ (-127)
    // normalized: x in [-126, 127]
    //  - min: 0 00000001 00000000000000000000000 = 0x80000000 = 2 ^ (-126)
    //  - max: 0 11111110 00000000000000000000000 = 0x7f000000 = 2 ^ 127
    // inf/NaN x > 127: return +inf = 0x7f800000
    if(x > 127) return 0x7f800000;
    else if(x < -126) {  // denormalized
        if(x >= -149) return 0x01 << (149+x);
        else return 0;
    }
    else return (x+127) << 23;
}
