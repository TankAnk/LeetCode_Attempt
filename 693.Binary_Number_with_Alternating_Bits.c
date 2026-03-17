#include <stdio.h>
#include <stdbool.h>
/* 1st attempt
bool hasAlternatingBits(int n) {
    int remainder;
	while (n > 0)
    {
    	remainder = n % 2;
    	n/=2;
    	if (remainder == n % 2) return false;
    }
    
    return true;
}
*/

/*2nd attempt with ChatGPT recommendation
Solution:
	- Number with alternating bits n = 101010... if >> 1 --> n = 010101...
	- Therefore n XOR (n >> 1) = 1111...
	- Number with all 1s if +1 --> 0000... --> 1111... AND (1111... + 1) = 0
*/
bool hasAlternatingBits(int n) {
	n = n ^ (n >> 1);
    return ((n & (n + 1)) == 0);
}

int main()
{
	int arr[5] = {2147483647, 2147483646, 2147483645, 1431655765, 1431655766};
	for (int i = 0; i < 5; i++)
		printf("%d\n", hasAlternatingBits(arr[i]));
	
	return 0;
}
