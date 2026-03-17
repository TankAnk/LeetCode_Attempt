#include <stdio.h>

/*Attempt:
	- Declare the result = 0;
	- Repeat 32 times:
		+ Shift left the result 1
		+ Add the lsb of the original number to the result
		+ Shift right the original number 1
*/

int reverseBits(int n) {
	int result = 0;
    for (int i = 0; i < 32; i++)
    {
    	result = result << 1;
    	//lsb = n & 1;
    	result = result | (n & 1);
    	n = n >> 1;
    }
    
    return result;
}

int main()
{
	int n = 43261596;
	
	printf("%d\n%d\n", n, reverseBits(n));
		
	return 0;
}
