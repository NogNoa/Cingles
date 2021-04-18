#include <stdio.h>

/*
int change(int *amnt, int deno)
{
	int bills;
	
	bills = *amnt / deno;
	*amnt -= deno * bills;
	return bills;
}
*/

int main(){

	int gsi, grpid, pub, item, chck;
	
		
	printf("Enter ISBN: ");
	scanf("%d -", &gsi);
	if (gsi > 970){
		scanf("%d -", &grpid);
		printf("GS1 prefix: %d\n", gsi);
	}
	else {
		grpid = gsi;
		printf("GS1 prefix: NA\n");
	}
	scanf("%d -%d -%d", &pub, &item, &chck);
	printf("Group identifier: %d\n", grpid);
	printf("Publicsher code: %d\n", pub);
	printf("Item number: %d\n", item);
	printf("check digit: %d\n", chck);
	return 0;
}

