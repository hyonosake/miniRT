#include <stdio.h>
#define MIN	0.2
float			return_positive(float r1, float r2, float min_t)
{
	if (r1 > MIN && r1 < min_t)
		return (r1);
	else if (r2 > MIN && r2 < min_t)
		return (r2);
	return (min_t);
}

float			return_min_positive(float r1, float r2, float min_t)
{
	if (r1 < r2 && r1 > MIN && r1 < min_t)
		return (r1);
	else if (r2 < r1 && r2 > MIN && r2 < min_t)
		return (r2);
	return (min_t);
}

int main(void)
{
	float a;
	float b;
 
	printf("a = ");
	scanf("%f", &a);
	printf("\nb = ");
	scanf("%f", &b);
	if (a < 0 && b < 0)
		printf("%.2f\n", 1200.0);
	else if (a >= 0 && b >= 0)
		printf("%.2f\n", return_min_positive(a, b, 1200));
	else if (a > 0 || b > 0)
		printf("%.2f\n", return_positive(a, b, 1200));
	return 0;
	
}