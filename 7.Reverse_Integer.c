#include <stdio.h>
#include <limits.h>

int reverse(int x)
{
	int result = 0, sign = 1;
	if (x < 0)
	{
		x = (unsigned) x * -1;
		sign = -1;
	}

	while (x > 0)
	{
		//result * 10 + x%10 <= INT_MAX
		if (result > ((INT_MAX - x%10)/10)) return 0;
		result*=10;
		result += x%10;
		x/=10;
	} 
	
	return result*sign;
}

int main()
{
	int n;
	scanf("%d", &n);
	printf("%d", reverse(n));
	
	return 0;
}
