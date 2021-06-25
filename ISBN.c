#include <stdio.h>

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
	printf("Publisher code: %d\n", pub);
	printf("Item number: %d\n", item);
	printf("check digit: %d\n", chck);
	return 0;
}

