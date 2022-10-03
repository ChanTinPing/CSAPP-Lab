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
/* Idea: We must use &, so the result should be (f(x,y) & g(x,y)) or ~(f(x,y) & g(x,y)). 
 * It seems impossible to create f or g without &. Hence, assume f and g are combination of x, y with &, ~. 
 * The remaining is brutal force by consider inputs 00 10 01 11.
 *
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int f = ~(x & y);
  int g = ~(~x & ~y);
  int c = (f & g);
  return c;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return (1<<31);

}
//2
/* Idea: ! map 0 to 1, and map others to 0. Hence, the main idea is map Tmax to 0, which is the use of 2+x+x.
 * However, 2+x+x also map -1 to 0. Hence, we need x+1 to distinguish -1 and Tmax.
 *
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  int a = !(2+x+x);
  int b = !(x+1);
  int c = a ^ b;
  return c;
}
/* Idea: First, create a=0xAAAAAAAA which is 1 in odd bits and 0 in even bits. Then, (a & ~x) map all 1 odd bits to 0, others to 1.
 *
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int a = (0xAA << 8) + 0xAA;
  a = (a << 16) + a;
  return !(a & (~x));
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x+1);
}
//3
/* Idea: AsciiDigit bits first 28 bits is 3, last 4 bits is 0 to 9. 
 * int a is map first 28 bits to 0 iff the first 28 bits of input is 3.
 * int b (with int a) map AsciiDigit bits to 0. However, it also map 0x3A-0x3F to 0.
 * so we need other operation to distinguish 0x30-0x39 and 0x3A-0x3F. a+6 will make 0x3A-0x3F first 28 bits into non-zero.
 *
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int a = x ^ 0x30;
  int b = a >> 4;
  int c = (a + 6) >> 4;
  return ! (b | c);
}
/* Idea: First use ! to distinguish =0 and not=0. t is such that all bits are same (0x00000000 or 0xFFFFFFFF).
 * Consider all combination of y, z, t and use Boolean algebra.
 *
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int neqx = !x;
  int t = ~neqx + 1;
  int ans = (z & t) | (y & ~t);
  return ans;
}
/* Idea: Let z = y-x = y+(~x+1). Consider the first bit (the leftest bit) of x,y,z.
 * If x=1, y=0, then result is 1. If x=0, y=1, result is 0. If x and y have same first bit, the result is first bit of ~z.
 * Consider all combinations of x,y,z first bit and corresponding results, and then build the function. Then extract the first digit.
 *
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int z = y + ~x + 1;  // z = y-x
  int a = (~(y|z)) | (x&(y^z));  // Function which its first bit is the result
  return (a>>31) & 1;  // Extract first bit
}
//4
/* Idea: The main core is use the carry of addition.
 *
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int a = ~0;  // a = 0xFFFFFFFF
  int y = (x>>1) | x;  // if x=0, then last 31 bits of y are zeros, otherwise last 31 bits of y is at least 1.
  int t = y + a;  // Hence, if x=0, then there is no carry at the first bit. Otherwise there is a carry on first bit.
  int d = (t ^ y) >> 31;  // If x=0, then first bit of t is 1 (=~0), otherwise it is the same. So use ^ to extract the information.
  return (d & 1);
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
  int a16, a8, a4, a2, a1 = 0;  // Binary system, answer = 16*(1-a16) + 8*(1-a8) + 4*(1-a4) + 2*(1-a2) + 1*(1-a1) + 1. 
  int ans = 0;
  int c1, c2 = 0;
  int y = (x>>1) ^ x;  // The mission change to find the position of the leftest 1 of y.
  c2 = (0xFF << 8);  // constant 0x0000FF00
  c1 = c2 + 0xFF;  // constant 0x0000FFFF
  
  // clean y such that its digits are 00...00100...00
  y = (y>>1) | y;
  y = (y>>2) | y;
  y = (y>>4) | y;
  y = (y>>8) | y;
  y = (y>>16) | y;  // y becomes 00...0011...11
  y = y + 1;  // Cleaning end. Now y has only one bit has value 1. Its position is the answer.
  
  // Use binary system to calculate the position of bit 1.
  a16 = !(y & ~c1);  y = ((y>>16) + y) & c1;  // y=(y>>16 + y)&c means y=y>>16 if ans >= 16, otherwise y=y.
  a8  = !(y & c2) ;  y = ((y>>8)  + y) & 0xFF;
  a4  = !(y & 0xF0);
  a2  = !(y & 0xCC);
  a1  = !(y & 0xAA);
  
  // Calculate answer
  ans = (a16<<4) + (a8<<3) + (a4<<2) + (a2<<1) + a1;
  ans = ~ans + 33;  
  
  return ans;
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
  unsigned two31 = 0x80000000;  // 2^31
  unsigned two23 = 0x00800000;  // 2^23
  unsigned ans = uf;
  unsigned s = 0;  // corresponds to sign bit in floating representation
  unsigned no_s = uf % two31;  // without sign bit
  if (uf >= two31) { s = two31; }
  
  if (no_s >= 0x7F800000)  { ans = ans; }  // NaN or inf
  else if (no_s >= 0x7F000000) {  // too much, result (floating value) become inf
    ans = 0x7F800000 + s;
  }
  else if (no_s < two23) {  // denormalized case, just <<1 and add the sign bit (which disappear when <<1)
    ans = (2*ans) + s;
  }
  else {  // normalized case, the exp part bit just add 1
    ans = uf + two23;
  }
  return ans;
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
  unsigned ans = 0;  
  unsigned two31 = 0x80000000;
  unsigned u_no_s = uf % two31;  // discard sign bit
  unsigned neg = uf / two31;  // neg==1 means it is negative
  int no_s = u_no_s;  // int type, suitable for comparison and subtraction
  int two23 = 0x00800000;
  int two_power = 1;  // << or >> bit by * or / 2^n
  int exp = (no_s / two23) - 127;  
  int frac = (no_s % two23) + two23;  // fraction part with implied leading 1
  int cnt = 0;  // use for counting in while statement
  
  if (exp < -1) { ans = 0; }  // answer round to zero
  else if (exp >= 31) { ans = 0x80000000; }  // too big or -2^31
  
  // normal case
  else {
  	if (exp <= 22) {  // >> frac bits
  		while (cnt < 23-exp) { 
  			two_power = two_power * 2; 
  			cnt = cnt + 1;
  		}
  		ans = frac / two_power;  // same as >> bits
  	}
  	else {  // << frac bits, no need rounding
  		while (cnt < exp-23) { 
  			two_power = two_power * 2; 
  			cnt = cnt + 1;
  		}
  		ans = frac * two_power;
  	}
  	
  	if (neg) {  // if it is negative, ans become ~ans+1, which is also 2^32-ans = (2^32-1)-ans+1
  		ans = 0 - ans;
  	}
  }
  
  return ans;
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
	unsigned ans = 1;
	unsigned bias = 0x3F800000;
	unsigned two23 = 0x00800000;
	int cnt = 0;
	
	if (x > 127) { ans = 0x7F800000; }
	
	else if (x >= -126) {
		ans = (x * two23) + bias;
	}
	
	else if (x >= -149) {
		while (cnt > -149-x) {
			ans = ans * 2;
			cnt = cnt - 1;
		}
	}
	
	else { ans = 0; }
	
    return ans;
}







