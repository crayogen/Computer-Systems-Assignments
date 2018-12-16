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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, orit (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  return ~((~x) | (~y));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
// n<<3 is n*8, which is our mask
 int move_bits = n<<3;
 int a = 0xff;  //make a mask of 1111 1111, to get 1 byte
 int b = a<<move_bits;  //move by n*8 bits
 return (((x&b)>>(move_bits)))&a;  //shift number to right most bit and read only the last byte
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */

 int logicalShift(int x, int n) {
 int arth_shift = x>>n; //this will give leading ones
 int a = 1<<31;  //takes one to most sig bit
 int b = ~(a>>n<<1); //gets zeros in all the leading one positions
 int c = arth_shift&b; //uses b filter to remove leading ones
 return c;

}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
 int filter = 0x55; //filter 0101 0101
 int filter_2 = 0x33; //filter 0011 0011
 int filter_3 = 0xf; //filter 1111 

 int a = (x & filter) + (x>>1 & filter) + (x>>8 & filter);
// we ran 0101 0101 filter over the first 8 bits and then shifted by 8 to get the next 8 bits, reading only alternating ones
//this is because while adding the filtered results we can only store up to 3 (filter size), to avoid carry. This is so we can later on count the number of bits accumilated
 int b = (x>>9 & filter) + (x>>16 & filter) + (x>>17 & filter);
//similarly here
 int c = (x>>24 & filter) + (x>>25 & filter); 
//and here


//we now run a 0011 0011 filter on each of a, b, and c
//in a similar way by stacking bits together after shifting and then adding them
//here we can store up to 16, in the 4 bits which is our filter size
 int a1 = (a & filter_2) + (a>>2 & filter_2) +
	(b & filter_2) + (b>>2 & filter_2)  + (c>>2 & filter_2);

 int b1 = (c & filter_2);

//similarly here we read the bytes which now store the count of bits accumilated by them
//we read each byte by using the filter 1111, and add
//we didnt have to use filter on a1, and b1 since we dont expect sign bits which would cause trouble if carried over
 int count = (a1 & filter_3) + (a1>>4) + (b1 & filter_3) + (b1>>4);
 return count;
}

/* 
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */

int anyOddBit(int x) {
 int filter = 0xaa; //using filter 0101 0101 to capture odd bits and get rid of even
 int a = (x | x>>8 | x>>16 | x>>24) & filter; //stacking number moved by 8 bits and 16 and 24 on itself and performing or to accumilate 1s
 return (!!a); //if there is any 1, in a then it is odd so return 1
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  int first_bits_mask = ~(1<<31>>(31 +~n+1)); //~(1<<31>>(31-n)) //to capture the first n bits

// first bits are moved to the end and x is truncated (shifted forward) and shifted back after which its last n bits become 0

  int first_bits = ( x>>(32+~n+1) ) &first_bits_mask; //(x>>(32-n))
  int x_truncated = (x<<n);
  return x_truncated | first_bits;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return (1<<31); //using formulas 2^(w-1) and 2^n = 1<<n;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int rem_bits = x>>(n+~0); //remove the first n-1 bits, the rest of the bits should either be all 1s or 0s in order for the number to fit in the last n bits
  int all_zeros = (!rem_bits); //1 iff 0000
  int all_ones = !(~rem_bits); //1 iff 1111
  return (all_ones|all_zeros);
}

/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  int not_x = ~x; //~x+1 returns the twos comlpliment which leads to a 1 in the position of the least significant shift
//eg 00110101000, 2s comp: 11001011000
//and with x leads to 0s in all other positions because of ~x
  return x&(not_x+1);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  int first_bit = (x>>31);
  int neg_filter = ((!!first_bit)<<n) + first_bit; //filter that adds one to the last n bits of negative numbers to compute carry
  return (x + neg_filter) >> n;
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  //x is not zero or negative and x contains only only 1
  //(x-1) which will convert all the zeros on the right of the only 1 to ones should & with x to give zeros
  int first_bit = (x>>31);
  int all_zeros = !x;
  int all_ones_on_right = (x-1);
  return !( first_bit | (all_zeros) | (all_ones_on_right & x) );
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { //two compliment
  int neg = ~x + 1;
  return neg;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  //return 1 of eother all zeros or first bit is one
  int first_bit_one = (x>>31)&1;
  int zeros_everywhere = !x;
  int a = !(first_bit_one | zeros_everywhere);
  return a;

//1 -> -ve
//0 -> +ve or 0
}

/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  //using the difference and tehn covering all possible scenarios
  int one_neg_one_pos = ( (x>>31) ^ (y>>31) ) & 1;
  int y_minus_x = (y + ~x + 1)>>31;
  int x_neg_y_pos = one_neg_one_pos & !(y>>31); //means y>x
  int both_pos_or_neg = !one_neg_one_pos; //needs a y-x check
  return ( both_pos_or_neg & ! y_minus_x ) | x_neg_y_pos; //
}

/*
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) {
  int mult_by_two = x<<1;
  int first_bit = x<<31;
  int mask_1 = 1<<31;
  int mask_2 = ~mask_1;
  return 2;
    }
