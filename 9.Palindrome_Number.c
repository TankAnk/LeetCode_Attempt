#include <stdio.h>
#include <stdbool.h>

/*Attempt:
	- Check until the reverse x == reversed || x == reversed / 10
	- For example: x = 1239321
		+ Until x = 1239 and 123 check if (123 == 1239) or (123 == 1239/10);
*/
bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x % 10 == 0 && x != 0) return false;

    int reversed = 0;

    while (x > reversed) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
    }

    return (x == reversed || x == reversed / 10);
}


int main()
{
	int arr[5] = {121, 10, 2002, 1991, 999999999};
	for (int i = 0; i < 5; i++)
		printf("%d\n", isPalindrome(arr[i]));

	return 0;
}
