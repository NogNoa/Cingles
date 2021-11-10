#include <stdio.h>

int main(){

	float amnt;
		
	printf("Enter an amount: ");
	scanf("%f", &amnt);
	amnt *= 1.05;
	printf("With tax added: $%.2f\n", amnt);
	return 0;
}

