#include <stdio.h>

int main(){

	int magic[16], i, sum, sumtoo;
	
	
	printf("Enter the numbers from 1 to 16 in any order: ");
	for (i=0;i<16;++i)
		scanf("%d", &magic[i]);
	for (i=0;i<16;++i){	
		printf("%2d", magic[i]);
		if ((i + 1) % 4)
			putchar(' ');
		else
			putchar('\n');
	}
	printf("Row sums:");
	for (i=0;i<4;++i){
		sum = magic[4*i +0] + magic[4*i + 1] + magic[4*i +2] + magic[4*i + 3];
		printf("%4d", sum);
	}
	printf("\nColumn sums:");
	for (i=0;i<4;++i){
		sum = magic[i] + magic[4 + i] + magic[8 + i] + magic[12 + i];
		printf("%4d", sum);
	}
	printf("\nDiagonal sums:");
	sum = magic[0] + magic[5] + magic[10] + magic[15];
	sumtoo = magic[3] + magic[6] + magic[9] + magic[12];
	printf("%4d%4d\n", sum, sumtoo);
	return 0;
}

