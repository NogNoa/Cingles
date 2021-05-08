#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc>=2) {
		printf("Knock, Knock, %s, err $USER\n",argv[1]);
	} else {
		fprintf(stderr, "'scuse me sir, I expect: %s <name>\n",argv[0]);
		return 1;
	}
	return 0;
}	

