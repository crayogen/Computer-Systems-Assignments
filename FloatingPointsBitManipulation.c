/* 
 * CS:APP Data Lab 
 * 
 * Hajira Zaman 21100057
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
   version 2.1 of the License, or (at your option) any later version.

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
 * float_f2i - Return bit-level equivalent of expression (int) f
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
int float_f2i(unsigned uf) {
/*first seperate the sign, exp and fractional parts, and remove bias from the exponent 
  3 different cases handled
	NaN or Inf case
	denormalised number or negative exponent
	exp so large it causes overflow
   in case it isnt one of these special cases
	first add implicit bit to the fractional part (24th bit should be one)
	then if exp is bigger than 23, shift frac left by the appropriate amount
	if its less than 23, shift frac right by the appropriate amount
	then check of the sign is negative
		if negative then return 2s compliment
		else just return the number
*/
  int bias = 127;
  unsigned sign = ( uf >> 31 ) & 1;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned frac =  (uf & 0x7FFFFF) | 0x800000; //frac part plus 1 in the 24th place (implicit bit)
  signed unbiased_exp = exp - bias;

  unsigned int_uf;

  if (~exp == 0) //if it is NaN or inf
    return(0x80000000u);
  if (exp == 0 || unbiased_exp < 0) { //if denormalized or exp is less than zero
    return (0);
  }
  if (unbiased_exp >= 0) { //if positive or zero exp
    if (unbiased_exp > 31) //in case of overflow
      return (0x80000000u);
    
    //if not special case
    if (unbiased_exp > 23)
        int_uf = frac << (unbiased_exp - 23);
    else int_uf = frac >> (23 - unbiased_exp);
    if (sign) //if it is a negative number then return 2s compliment
      return (~int_uf+1);
  }
  return (int_uf); //if it falls under no other special case then just return the converted number
}

/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
/* cases:
     positive int x:
	significant bits of number > 23
	  round number to even and truncate frac
	    if frac is all 1s then rounding causes increment of in exp
	    and frac becomes all zeros
	  add bias to exp
	significant bits of number < 23
	  no rounding needed
     negative int x:
	get 2s compliment of x
        do the same as above
     zero x
	return 0;
*/
  int bias = 127;
  int sign = x & 0x80000000;
  int exp_iter, exp, frac_filter, frac, frac_with_round_bit, discarded_frac;
  int rounding_bit; //determines whether to round up (filter)
  int discarded_in_middle, frac_odd;
  int frac_discard_len, frac_discard_len_1;
  //case zero x
  if (x);
  else return x;
  
  //case negative x, then make x twos compliment
  if (sign)
    x = -x;
  
  for (exp_iter=0; exp_iter<32; exp_iter++) {
    if ( (1<<exp_iter) & x ) //if x has a 1 in the ith position
      exp = exp_iter;
  }

  frac_filter = ~(0xffffffff << exp);
  frac = x & frac_filter;
  discarded_frac = x & (frac_filter>>23);
  frac_discard_len = exp - 24;
  frac_discard_len_1 = exp - 23; //to reduce ops

  //if significant bits if number > 23 then rounding
  
  //rounding
  if (exp > 23) {
    rounding_bit = 0x1 << frac_discard_len;
    discarded_in_middle = (discarded_frac == rounding_bit);
    frac_with_round_bit = (frac >> frac_discard_len);
    frac_odd = frac_with_round_bit & 0x2;
    //if not discarded part is right in the middle (edge case) and even number
    if (frac_odd || !discarded_in_middle)
    {
      if ( frac_with_round_bit == 0xffffff ) //if frac is all ones, overflow
        exp=exp+1;
      frac = frac_with_round_bit + 1;
      frac_discard_len_1 = 1;
    }
    
    frac = ( frac >> frac_discard_len_1 ) & 0x7fffff;
  }

  else
    frac = frac << -frac_discard_len_1;

  exp = (exp+bias)<<23;
  return (sign|exp|frac);
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
/* fliped the sign bit, called it op_sign (opposite_sign)
   if number is NaN then returned the input argument
   otherwise return the number with flipped sign bit
*/
   unsigned exp = (uf >> 23);
   unsigned frac =  uf & 0x7FFFFF;
   unsigned op_sign = ~uf & 0x80000000; // opposite sign
   unsigned neg_uf = (uf & 0x7fffffff) | op_sign;
   if ((~exp & 0xff) == 0) {
     if (frac != 0) //if exp is all ones and fraction isn't zero (NaN and not inf)
     return uf;
   }
   return neg_uf;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
/* Here I have handled 3 case:
     1) the NaN or infinity case in which I have just returned the input argument
        since (2 x infinity) = infinity
     2) the denormalised number case with exp of all zeros
        -> if there is no overflow when shifting the frac to the left then just did that
        -> in that case if there is an overflow, then i incremented the exp, essentially 
           just made the exponent bit 1 since its zero to begin with. I implimented this
           by masking with 0x800000.
     3) in case the number is not denormalised or NaN/inf, i just incremented the exp by 1
*/
  unsigned sign = ( uf >> 31 ) & 1;
  int sign_in_place = sign << 31;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned exp_twice = ( (exp + 1) ) & 0xFF;
  unsigned frac =  (uf & 0x7FFFFF);

  if ( (~exp & 0xff) == 0 ) // NaN or inf
    return uf;

  if (exp == 0) //denormalised
  {
    if (!(!(frac & 0x400000))) //if overflow
      return ( 0x800000|(frac<<1)|sign_in_place );

    return (frac << 1)| sign_in_place;
  }

  return ((exp_twice)<<23)|frac|sign_in_place;
}
