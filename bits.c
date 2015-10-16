/* 
 * CS:APP Data Lab 
 * 
 * <Zhen Feng >
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
    int sign, samecase, bit, sum, zocase, nonzeocase, final;
        sign=x>>31;  // get sign of x
        samecase=sign^x; // just make positive and negative number into the same 			 // case
   // since the number of bit N  can not exceed 32 so it binary representation
   // will not exceed 5 bit, so we can just divide the x  by 2^16,2^8
   // 2^4,2^2,2^1 to get each bit of N
        bit=!!(samecase>>16);
        bit= bit<<4;
        sum=bit;
	//printf("sum=: %d\n ",sum);
	bit=!!((samecase>>sum)>>8);
	bit=bit<<3;
	sum+=bit;
 	bit=!!((samecase>>sum)>>4);
	bit=bit<<2;
	sum+=bit;
	//printf("sum=: %d\n ",sum);
	bit=!!((samecase>>sum)>>2);
	bit=bit<<1;
	sum+=bit;
	bit=!!((samecase>>sum)>>1);
 	sum+=bit;

   // since sign bit has extra 1 bit and this algorithm rounds down so we should   // add 2 finally.
       sum+=2; 
   // 0 and -1 are special case 
       zocase=!samecase;
   // create a helper number nonzeocase retrun -1 if x is not 0 or 1
   // return 0 if x is 0 or 1
       nonzeocase=!!(((x+1)>>1)<<1);
         nonzeocase=(nonzeocase<<31)>>31;
      final=(nonzeocase&sum)|zocase;
     return final;
        

}     
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
   int m,sign,plus,k;
       m=(~((~0)<<31))&x; // create a speacial number
       sign=x>>31;  // get sign bit
       plus=(x>>31)&1;// and sign bit with 1 to make sure we only add 1 when 
                      // sign is 1, plus =0 otherwise 
       k=(sign^m)+plus; // the special number xor m means ~m if x is negative 
                        // and means m if x is positive. Then we add plus
   return k ;
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
   x= x>>31;  
  return !(x); // just shift it right 31 bit to get sign bit and not it to make                // sure ouput 0 when sign is 1 and ouput 1 otherwise.
}

/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  int m, p, k;
      m=x<<(32+((~n)+1)); // get the section that needs to be put at front
      p=~((~0)<<(32+((~n)+1))); // get the special number p
      k=x>>n;
      k=k&p;// shift x right n bit and and it with special number to make 
            // it has n number of zeros at the front 
      return (k+m);  // add k and m to get the final number
      
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
   int sign,bitdiv;
       sign=x>>31; // get the sign of the x
       bitdiv=1<<n;// get the divider of the function 
  return ((((bitdiv+(~0))&sign)+x)>>n) ; // if x is positive then we just
                                         // divide it by bitdiv, if x is 
                                         // negative, we just add the 
                                         // corresponding complent at first 
                                         // and then divided by bitdiv
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int m, k;
      m=(0xAA<<8)+0xAA;
      m=(m<<16)+m; // create a number m with each bytes is A
      k=m&x; // and the number m with x and we will get m again if x has all 
             //0 odd bits 
  return !(k^m); // just xor m and k, only m will make this output 0, then not
                 // it to get 1, which means only x with all 0 odd bits can 
                 // ouput 1 
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
    return ((~(x&y))&(~((~x)&(~y)))); // basic boolean argebra
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
   int m, y;
       m=0; 
       y=x+(~m); //use ~0 to represent -1
   return ((!(~(y^x)))&(!!(x+0))); // only x=0 or Tmin will  let !(~(y^x)))
                                   // get 1 so we just kick 0 out, which and it
                                   // with (!!(x+0) ) to make sure only Tmin 
                                   // return 1.
}
