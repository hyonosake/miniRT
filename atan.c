#include <math.h>
#include <stdio.h>


int main(void)
{
	for (int x = -1000;x < 1000;x++)
		printf("%d\t%.2f\n", x, (atan(x)) * M_PI);
	return 0;
}