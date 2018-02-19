/*
    ICS 51, Lab #2

    --------------------------------------------------------------------
 
    IMPORTATNT NOTES:
    
    - To test your code use the tests in lab2-tester.cpp
    
    - Write your assembly code only in the marked areas.
    
    - You are not allowed to change anything in this file except for adding your assembly code 
    between the lines marked with "YOUR CODE STARTS HERE" and "YOUR CODE ENDS HERE".

    - This lab has to be done individually.

    - Remember to fill in your name, student ID below.

    - Two test images are provided to you (lena.png and authoritah.png)
    
    - Submit ONLY your completed lab2.cpp for grading.
*/

char *yourName = "Paramdeep Singh Atwal";
char *yourStudentID = "91166595";


/***********************************************************************************************

    PART 1: Image Thresholding

    - This function takes in a square sized grayscale image and applies thresholding on each pixel.
      i.e. it should change pixel values according to this formula:
                        0xFF       if x >= threshold
                        0x00       if x <  threshold
    - The width and height of the image are equal to dim. 
    - You are not allowed to define additional variables.

************************************************************************************************/
void imageThresholding(unsigned char* image, int dim, unsigned char threshold) {
    __asm 
    {
        // YOUR CODE STARTS HERE
		mov eax, dim
		imul eax, eax
		mov ebx, 0
		mov ecx, image
		mov dl, threshold

		ENDING:
			cmp ebx, eax
			je END
			mov ecx, image
			add ecx, ebx
			jmp THRESH
		THRESH:
			cmp [ecx], dl
			jb MIN
			cmp [ecx], dl
			jae MAX
		MIN:
			mov [ecx], 0x00
			inc ebx
			jmp ENDING
		MAX:
			mov [ecx], 0xFF
			inc ebx
			jmp ENDING
		END:

        // YOUR CODE ENDS HERE
    }
}
/***********************************************************************************************

    PART 2: Image Rotation

    - This function rotates a square sized color image:
      90 degress clockwise if direction > 0
      90 degress counterclockwise if direction < 0
    - If direction == 0, the image is not rotated.
    - The width and height of the image are both equal to dim.
    - Four variables (a0, a90, a180, a270) are defined that you may use in your implementation for
    temporary data storage. You are not allowed to define additional variables.

************************************************************************************************/
void imageRotation(unsigned int* image, int dim, int direction) {
    unsigned int a0, a90, a180, a270;
    __asm 
    {
		// YOUR CODE STARTS HERE

		mov ecx, image
		mov ebx, 0
		mov esi, 0


		BEGIN_R: // 0 to dim/2 + 1
			mov edx, dim
			shr edx, 1
			inc edx
			cmp esi, edx
			jge END_R

			mov edi, ebx

		BEGIN_C : // n to dim - n -1 
			mov edx, dim
			sub edx, ebx
			dec edx
			cmp edi, edx
			jge END_C

		//a0= base + 4 * (row *dim + col)
			
			mov eax, esi
			mov edx, dim
			mul edx
			add eax, edi
			shl eax, 2
			add eax, ecx
			mov a0, eax

		//a90 = base + 4 * (col * dim + dim - row - 1)

			mov eax, edi
			mov edx, dim
			mul edx
			add eax, dim
			sub eax, esi
			dec eax
			shl eax, 2
			add eax, ecx
			mov a90, eax

		//a180 = base + 4 *(dim * (dim - row) - col - 1)

			mov eax, dim
			sub eax, esi
			mov edx, dim
			mul edx
			sub eax, edi
			dec eax
			shl eax, 2
			add eax, ecx
			mov a180, eax

		// a270 = base + 4 *(dim * (dim - col) - dim + row)

			mov eax, dim
			sub eax, edi
			mov edx, dim
			mul edx
			sub eax, dim
			add eax, esi
			shl eax, 2
			add eax, ecx
			mov a270, eax


		//swap
		cmp direction, 0
		jl SWAP_TWO

		cmp direction, 0
		je END_R

			
			mov edx, a0
			mov edx, [edx]

			mov eax, a0
			mov ecx, a270
			mov ecx, [ecx]
			mov [eax], ecx
			
			mov eax, a270
			mov ecx, a180
			mov ecx, [ecx]
			mov [eax], ecx

			mov eax, a180
			mov ecx, a90
			mov ecx, [ecx]
			mov [eax], ecx

			mov eax, a90
			mov [eax], edx

			mov ecx, image
			inc edi
			jmp BEGIN_C

		SWAP_TWO: //if direction is less
			mov edx, a0
			mov edx, [edx]

			mov eax, a0
			mov ecx, a90
			mov ecx, [ecx]
			mov[eax], ecx

			mov eax, a90
			mov ecx, a180
			mov ecx, [ecx]
			mov[eax], ecx

			mov eax, a180
			mov ecx, a270
			mov ecx, [ecx]
			mov[eax], ecx

			mov eax, a270
			mov[eax], edx

			mov ecx, image
			inc edi
			jmp BEGIN_C


		END_C:
			inc esi
			inc ebx
			jmp BEGIN_R

		END_R:
			mov image, ecx
        // Jump to the end (i.e, return) if direction == 0

        // Iterate over the red triangle (row by row starting from top left)

            // compute index of pixel p0, find the corresponding memory address and store it in a0

            // compute index of pixel p90, find the corresponding memory address and store it in a90

            // compute index of pixel p180, find the corresponding memory address and store it in a180

            // compute index of pixel p270, find the corresponding memory address and store it in a270

            // rotationaly swap pixel values
            // direction > 0 : p0 -> p90 -> p180 -> p270 -> p0
            // direction < 0 : p0 -> p270 -> p180 -> p90 -> p0

        // YOUR CODE ENDS HERE
	
    }
}