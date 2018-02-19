/*
    ICS 51, Lab #3

    --------------------------------------------------------------------

    IMPORTATNT NOTES:

    - This lab has five parts. The description of each part is given below.

    - Noramally, the compiler adds the prologue/epilogue code for the callee. However, when the 
    __declspec(naked) attribute is used, it is the programmer's responsibility to write the 
    prologue/epilogue code. In this lab you need to write prologue/epilogue code sections only 
    for the functions that have been declared with the naked attribute, namely:

       + findMinIndex
       + isPalindrome
       + performOperation
       + gcd

    - You cannot define any local variable in the C code. If you need additional variables in your
    assembly code, you have to allocate space for them in the prologue of the function. 

    - You are not allowed to change anything in this file except for adding your assembly code 
    between the lines marked with "YOUR CODE STARTS HERE" and "YOUR CODE ENDS HERE".

    - This lab has to be done individually.

    - Remember to fill in your name, student ID below.

    - Submit ONLY your completed lab3.c for grading.
*/

char *yourName = "Paramdeep Singh Atwal";
char *yourStudentID = "91166595";

#define RANDOMIZE_CALLEE_REGISTERS __asm mov ebx, 0xAFAFAFAF \
                                   __asm mov esi, 0xAFAFAFAF \
                                   __asm mov edi, 0xAFAFAFAF 
#define RANDOMIZE_CALLER_REGISTERS __asm mov eax, 0xAFAFAFAF \
                                   __asm mov ecx, 0xAFAFAFAF \
                                   __asm mov edx, 0xAFAFAFAF

/***********************************************************************************************

    PART 1: Change Letter Case

    You are given a string (null-terminated array of characters) that may contain numbers,
    upper and lower case letters, punctuations symbols, etc. Implement a function to convert all
    uppercase letters to lowercase and vice versa.
    For example "ThisIsTheFinalLabOf51" should be converted to "tHISiStHEfINALlABoF51".
    The string should be modifed in place. There is no explicit output for this function.

    Tips:

    - Note that each element of the arrays is a char (1 byte). You can NOT use a 32-bit register
    to read/write from/to a memory location. Instead you should use the 8-bit version of the x86
    general-purpose registers.

    - The link to the ASCII codes is here: http://www.asciitable.com/

************************************************************************************************/
void changeCase(char *string) {

    RANDOMIZE_CALLEE_REGISTERS
    RANDOMIZE_CALLER_REGISTERS

    __asm
    {
        // YOUR CODE STARTS HERE
		//start off with copying the string into a register
		//and use an indexer which will be ecx so it starts from 0

		mov eax, string
		mov ecx, 0

		cmp ecx, 0x00
			je HOW_LONG

		//essentially computes the length of the string
		HOW_LONG:

			cmp byte ptr [eax + ecx], 0
				je END

			mov bl, byte ptr [eax + ecx]
			cmp bl, 65
				jge CHECK_UPPER


			inc ecx
				jmp HOW_LONG


		//this loop is used to check for lower_case values
		CHECK_LOWER:

			cmp bl, 122
				jle CHANGE_LOWER

			inc ecx
				jmp HOW_LONG

		//this loop is used to check for the upper_case values
		CHECK_UPPER :

			cmp bl, 90
				jle CHANGE_UP

			cmp bl, 97
				jge CHECK_LOWER

			inc ecx
				jmp HOW_LONG
		
		//now revert the lower_case to upper_case
		CHANGE_LOWER:

			sub bl, 32
			mov byte ptr[eax + ecx], bl
			inc ecx
				jmp HOW_LONG


		//now revert the upper_case to lower_case
		CHANGE_UP :

			add bl, 32
			mov byte ptr[eax + ecx], bl
			inc ecx
				jmp HOW_LONG

		//end code if nothing to continue
		END:


        // YOUR CODE ENDS HERE
    }
}

/***********************************************************************************************

    PART 2: Selection Sort

    Selection sort is an in-place comparison sort algorithm that works by dividing the input list 
    into two parts: the sublist of items already sorted, which is built up from left to right of 
    the list, and the sublist of items remaining to be sorted that occupy the rest of the list. 
    Initially, the sorted sublist is empty and the unsorted sublist is the entire input list. 
    The algorithm proceeds by finding the smallest element in the unsorted sublist, exchanging it 
    with the leftmost unsorted element (putting it in sorted order), and moving the sublist 
    boundaries one element to the right. To learn more, read: 
    https://en.wikipedia.org/wiki/Selection_sort#Example

    Our implementation here uses a function called "findMinIndex" to find the index of smallest
    element between ith index and jth index of the array. The function "selectionSort" uses
    this function to find the smallest number and exchanges it with the leftmost unsorted element
    in each iteration. You need to implement the behavior of both functions in x86 assembly.

************************************************************************************************/
__declspec(naked) 
int findMinIndex (int integer_array[], int i, int j)
{

// C code to be converted to x86 assembly
/*
    int iMin = i;
    // test against elements after i and before j to find the smallest 
    for ( i ; i < j; i++) {
        // if this element is less, then it is the new minimum   
        if (integer_array[i] < integer_array[iMin]) {
            // found new minimum; remember its index 
            iMin = i;
        }
    }

    return iMin;
*/

    RANDOMIZE_CALLER_REGISTERS

    __asm
    {
        // YOUR CODE STARTS HERE
		//pop all the necessary values into the stack
		push ebp
		mov ebp, esp
		push edi
		push esi
		push ebx

		//get the necessary values from the stack *by getting the right location*

		mov eax, 0x00000000
		shl eax, 1
		mov ebx, eax
		mov eax, [ebp + 8]
		//mov the appropriate values into ecx
		mov ebx, 0x00000000
		shl ebx, 1
		mov ecx, ebx
		mov edx, [ebp + 12]
		//mov the appropriate values into ecb
		mov ecx, 0x0000000
		shl ecx, 1
		xor ecx, ecx
		mov ecx, [ebp + 16]

		mov ebx, edx

		jmp FOR_LOOP
		//for loop to determine when i < j and to increment i after to find the smallest
		FOR_LOOP:
			cmp edx, ecx
				jge EXIT

		jmp MOVING
		MOVING:
			mov esi, [eax + 4*edx]
			mov edi, [eax + 4*ebx]
			cmp esi, edi
				jge IF_LOOP

			mov ebx, edx

		jmp IF_LOOP
		//if statement that finds the minimum 
		IF_LOOP:
			inc edx
				jmp FOR_LOOP

		// exit statement that finally pops all the values from the stack
		// additionally moves the answer into the appropriate registers
				EXIT:

			mov eax, ebx
			pop ebx
			pop esi
			pop edi
			mov esp, ebp
			pop ebp

        // YOUR CODE ENDS HERE
        ret
    }

}

void selectionSort (int integer_array[], int array_size)
{

// C code to be converted to x86 assembly
/*  
    int j;
    int iMin;
    int temp;

    // advance the position through the entire array //
    // (could do j < n-1 because single element is also min element) //
    for (j = 0; j < array_size-1; j++) {

        // find the index of min element in the unsorted a[j .. n-1] //
        iMin = findMinIndex (integer_array, j, array_size);
 
        if(iMin != j) { // swap values
            temp = integer_array[iMin];
            integer_array[iMin] = integer_array [j];
            integer_array[j] = temp;    
        }
    }
*/

    RANDOMIZE_CALLEE_REGISTERS
    RANDOMIZE_CALLER_REGISTERS

    __asm
    {
        // YOUR CODE STARTS HERE
		// store the variables' values into registers
		mov esi, integer_array
		mov edx, array_size
		// subtract 1 from 
		sub edx, 1
		xor edi, edi

	jmp FOR_LOOP
	//for loop 	
	FOR_LOOP:

		cmp edi, edx
			jge EXIT //go to the end if the value that's in edi is greater than that in edx


		// do all the necessary pushing so the proper stack is created
		push eax
		push ecx
		push edx
		mov ebx, array_size
		push ebx
		push edi
		push esi

		call findMinIndex

		add esp, 12
		mov ebx, eax
		pop edx
		pop ecx
		pop eax
		cmp ebx, edi
			je IF_LOOP

		// move the corresponding values into eax and ecx
		mov eax, [esi + 4 *ebx]
		mov ecx, [esi + 4 *edi]

		// xor so that the difference in the alues is moved into eax
		xor eax, ecx
		xor ecx, eax
		xor eax, ecx

		mov [esi + 4 * ebx], eax
		mov [esi + 4 * edi], ecx

	jmp IF_LOOP
	//increments the value of edi and then starts the loop again
	IF_LOOP:

		inc edi
			jmp FOR_LOOP

	EXIT:

		mov integer_array, esi

        // YOUR CODE ENDS HERE
    }

}

/***********************************************************************************************

    PART 3: Palindrome

    Given a string, complete the implementation of the recursive function isPalindrome() to check 
    if the string is palindrome or not. A string is said to be palindrome if reverse of the 
    string is same as string. For example, “abba” is palindrome, but “abbc” is not palindrome.

************************************************************************************************/
__declspec(naked)
int isPalindrome(char *input_string, int left_index, int right_index)
{

// C code to be converted to x86 assembly
/*
    // Input Validation
    if (NULL == input_string || left_index < 0 || right_index < 0){
        return -1;
    }
    // Recursion termination condition
    if (left_index >= right_index)
        return 1;
    if (input_string[left_index] == input_string[right_index]){
        return isPalindrome(input_string, left_index + 1, right_index - 1);
    }
    return -1;
*/

    RANDOMIZE_CALLER_REGISTERS

    __asm
    {
        // YOUR CODE STARTS HERE

		push ebp
		//does the necessary pushing and transferring of the values
		mov ebp, 0x00000000
		mov ebp, esp
		mov ebx, 0x00000000

		mov ebx, input_string
		mov ecx, 0x00000000
		mov edx, 0x00000000

		mov edx, left_index
		mov ecx, right_index
		jmp COMPARE
		
		//compares all the values so that it can evaluate to TRUE/FALSE depending on the conditions
		COMPARE:
			cmp ebx, 0
				je FALSE
		
			cmp edx, 0
				jl FALSE

			cmp ecx, 0
				jl FALSE

			cmp edx, ecx
				jge TRUE

			mov al, [ebx + edx]
			cmp al, [ebx + ecx]
				je RECUR

			jmp FALSE

	//The recursive loop that calls isPalindrome so get the appropriate values
	RECUR:
		dec ecx
		push ecx
		inc edx
		push edx
		push ebx

		call isPalindrome

		// pops the values from the stack and then jumps to the end
		pop ebx
		pop edx
		pop ecx
		jmp END
	// when it's true this is evaluated
	TRUE:
		mov eax, 1
		jmp END
	// when it's false this is evaluated
	FALSE:
		mov eax, -1
		jmp END

	END: 
		mov esp, ebp
		pop ebp
		
        // YOUR CODE ENDS HERE
        ret
    }
}

/***********************************************************************************************

    PART 4: Vector Operation

    The vectorOperations function gets as parameters 4 arrays of the same length and
    the number of elements in those arrays. 

    For each pair of elements in first_array and second_array, it calls performOperation
    and stores the returned result in the same index of output_array.

    output_array[index] = performOperation(operation_array[index], first_array[index], second_array[index]).

    You also need to implement the body of performOperation function according to the provided
    C code.
  
************************************************************************************************/
__declspec(naked) 
int performOperation (int operation, int first, int second)
{

// C code to be converted to x86 assembly
/*
    if (operation==0) 
        return first - second;
    else if (operation==1)
        return first + second;
    else if (operation==2)
        return (first < second)? first : second;
    else if (operation==3)
        return (first > second)? first : second;
    else
        return first;
*/

    RANDOMIZE_CALLER_REGISTERS

    __asm
    {
        // YOUR CODE STARTS HERE

		//moves the appropriate values into the registers
		push ebp
		mov ebp, 0x0000000
		mov eax, 0x0000000
		mov ebx, 0x0000000
		mov ebp, esp
		cmp eax, ebx
			je COMPARISONS
		// the loop that makes the necessary comparisons
		COMPARISONS:
			mov edx, operation
			mov ebx, second

			cmp edx, 0
				je SUBTRACT
			cmp edx, 1
				je ADDITION
			cmp edx, 2
				je IF_THREE
			cmp edx, 3
				je IF_FOUR

			jmp OTHER
		//evaluates to this loop if subtraction is necessary
		SUBTRACT:
			sub first, ebx
			mov eax, first
			jmp END
		//evaluates to this loop if addition is necessary
		ADDITION:
			add first, ebx
			mov eax, first
			jmp END


		//the third if statement/condition
		IF_THREE:
			cmp first, ebx
				jl ONE
			jmp TWO
		// the fourth if statement/condition
		IF_FOUR:
			cmp first, ebx
				jg ONE
			jmp TWO
		
		ONE:
			mov eax, first
			jmp END

		TWO:
			mov eax, second
			jmp END

		OTHER:
			mov eax, first
			jmp END


		END:
			mov esp, ebp
			pop ebp



        // YOUR CODE ENDS HERE
        ret
    }
}

void vectorOperations (int number_of_elements, int *first_array, int *second_array, 
                       int *operation_array, int *output_array)
{
// C code to be converted to x86 assembly
/*
    int i;
    for (i=0; i<number_of_elements; i++)
    {
        output_array[i] = performOperation(operation_array[i], first_array[i], second_array[i]);
    }
*/

    RANDOMIZE_CALLEE_REGISTERS
    RANDOMIZE_CALLER_REGISTERS

    __asm 
    {
        // YOUR CODE STARTS HERE
		mov edi, output_array
		xor esi, esi
		// the for loop that does the evaluation and performs the calling to performOperation
		FOR_LOOP:
			cmp esi, number_of_elements
				jge END

			push eax
			push ecx
			push edx


			mov eax, 0x00000000
			mov eax, second_array
			mov eax, [eax + 4 * esi]

			mov ebx, 0x00000000
			mov ebx, first_array
			mov ebx, [ebx + 4 * esi]

			mov ecx, 0x00000000
			mov ecx, operation_array
			mov ecx, [ecx + 4 * esi]

			push eax
			push ebx
			push ecx

			call performOperation

			add esp, 12

			mov [edi + 4 * esi], eax
			//pops the values from the stack as appropriate and increments esi
			pop edx
			pop ecx
			pop eax

			inc esi
			// jumps back to the loop to restart the process
			jmp FOR_LOOP

		END:
			mov output_array, edi

        // YOUR CODE ENDS HERE
    }
}

/***********************************************************************************************

    PART 5: Dijkstra's Algorithm to calculate GCD.

    Implement a recursive function in assembly that calculates the greatest common divisor of 
    two unsigned integers.

    Given two unsigned integers n and m, we can define GCD(m , n) as:

           GCD(m , n) = n                       ,    if (m % n) == 0
           GCD(m , n) = GCD(n , m % n)          ,    if (m % n) >  0

************************************************************************************************/
__declspec(naked) 
unsigned int gcd(unsigned int m, unsigned int n) {

// C code to be converted to x86 assembly
/*
    if ((m % n) == 0)
        return n;
    else
        return gcd(n, m % n);
*/

    RANDOMIZE_CALLER_REGISTERS
    
    __asm
    {
        // YOUR CODE STARTS HERE
		push ebp
		mov ebp, esp
		//moves the necessary values into the registers
		mov eax, 0x000000
		mov ebx, 0x000000
		shl eax, 1

		mov eax, m
		mov edi, n
		cdq
		idiv edi 
		cmp edx, 0
			je DONE

		// the foor loop that calls itself recursively and evalutes the GCD
		jmp FOR_LOOP
		FOR_LOOP:
			push edx
			mov edi, n
			push edi
			call gcd
			pop edi
			pop edx
				jmp END

		DONE:
			mov eax, n
				jmp END
		// moves the answer into the appropriate register 
		// also pops ebp for the value
		END:
			mov esp, ebp
			pop ebp


        // YOUR CODE ENDS HERE
        ret
    }
}