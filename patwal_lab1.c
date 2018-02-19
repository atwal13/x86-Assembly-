/*
    ICS 51, Lab #1
    
    --------------------------------------------------------------------

    IMPORTATNT NOTES:
    
    - To test your code see function testcode() in lab1-tester.c
        
    - For part 2, you are NOT allowed to use any version of the 
      MULTIPLY instruction.

    - You are not allowed to change anything in this file except for adding your assembly code 
    between the lines marked with "YOUR CODE STARTS HERE" and "YOUR CODE ENDS HERE".

    - This lab has to be done individually.
    
    - Remember to fill in your name, student ID below.
    
    - Submit ONLY your completed lab1.c for grading.
*/

char *yourName = "Paramdeep Singh Atwal";
char *yourStudentID = "91166595";


/***********************************************************************************************

    PART 1: 

    Given a 32-bit integer, swap all odd bits with even bits. 
    For example, if the given number is 23 (00010111), it should be 
    converted to 43 (00101011). Every even position bit is swapped 
    with adjacent bit on right side, and every odd position bit is 
    swapped with adjacent on left side.

    Implementation details:
    The input integer is stored in registers ecx. You need to store the 
    answer into register eax.

    Hint: 
    You only need a half-dozen instructions to do this. 
    Think about "clearing" odd (even) bits and using shift (shl, shr) 
    instructions.
    
    If we have an 8-bit number 00010111, the expected output is 00101011.
    Clearing (zeroing) odd bits (7, 5, 3, 1) of 00010111 would make it 
    00010101. Now if we shift it to the left by one bit, it becomes 
    00101010. The odd bits of 00101010 are equal to the odd bits of the 
    expected output. They are "0 1 1 1".

    Using the same technique, generate the even bits of the expected 
    output and then figure out a way for combining generated odd and 
    even bits. 

************************************************************************************************/
int swapBits(int x)
{
    int result;

    __asm 
    {
        mov eax, -1
        mov ecx, x

        // YOUR CODE STARTS HERE
		and ecx, 0x55555555
		shl ecx, 1
		mov ebx, x
		and ebx, 0xAAAAAAAA
		shr ebx, 1
		or ecx, ebx
		mov eax, ecx

        // YOUR CODE ENDS HERE
 
        mov result, eax
    }
    return result;

}

/***********************************************************************************************

    PART 2: 
    
    You are given three 32-bit signed integers. You need to add the 
    smallest number to the largest number and multiply that sum by 2017. 
    You cannot use mul/imul instructions. Instead decompose the multiplier
    into powers of two and use the shift and add instructions to do the
    multiplication. Read about "ancient Egyptian multiplication" here:
    https://en.wikipedia.org/wiki/Ancient_Egyptian_multiplication

    Implementation details:
    The three integers are stored in registers ebx, ecx, and edx. You 
    need to store the answer into register eax.

    Hint:
    One way of finding minimum and maximum number is to sort the numbers.

************************************************************************************************/
void minMax(int a, int b, int c, int *result)
{
    __asm 
    {
		mov eax, -1
		mov esi, result

		mov ebx, a
		mov ecx, b
		mov edx, c

		// YOUR CODE STARTS HERE

		//Compare a and b to find the larger one 
		mov edi, ebx //put a in edi
		cmp ecx, edi // compare b and a
		jle IF //if a bigger jump to iF
		mov edi, ecx // if not move b to edi since it is larger

		IF:

		//Larger between aorb and c -> max goes into edi 
		cmp edx, edi // compare c and a 
		jle ELSEIF // if a bigger then go to elseif
		mov edi, edx // if not then move c to edi

		ELSEIF:

		//Compare a and b and find the smaller one 
		cmp ecx, ebx // compare b and a
		jge ELSEIFTWO // if b bigger then a go to elseiftwo
		mov ebx, ecx // if not then move b to edi

		ELSEIFTWO:

		//Compare a or b and c to find the smaller one which is stored in ebx
		cmp edx, ebx
		jge ELSEIFTHREE
		mov ebx, edx

		ELSEIFTHREE:
		//Add the min and max and multiply it by 2017
		add ebx, edi
		mov ecx, ebx
		mov eax, ebx 
		shl eax, 1
		add eax, ecx
		shl eax, 1
		add eax, ecx
		shl eax, 1
		add eax, ecx
		shl eax, 1
		add eax, ecx
		shl eax, 1
		add eax, ecx
		shl eax, 5
		add eax, ecx
		
        // YOUR CODE ENDS HERE

        mov [esi][0], eax
    }
}

/***********************************************************************************************

    PART 3:

    Implement a function that determines if a number is a power of two or not. It 
    takes a positive integer n as an argument, and returns 1 if n is a power of two, 
    and otherwise 0.

    Implementation details:
    The input integer is stored in registers ecx. You need to store the result into register eax.

    Hint:
    The integer n is a power of two if (n & (n-1)) == 0 (Why?)

************************************************************************************************/
int isPowerOfTwo(unsigned int n)
{
    __asm
    {
        mov ecx, n

        // YOUR CODE STARTS HERE
		mov edx, n
		dec edx
		and edx, ecx
		cmp edx, 0
		jne else1
		if1:
			mov eax, 1
			jmp endIf
		else1:
			mov eax, 0
		endIf:

        // YOUR CODE ENDS HERE
    }
}