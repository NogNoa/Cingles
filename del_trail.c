#include <stdio.h>
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */
	// that's a tab

int main()
{	
	int c, state = IN, i = 0;
	char blank[0x20];

	
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\r'){
			state = OUT;
			blank[i] = c;
			blank[++i] = '\0';
		}	
		else{
			if (c == '\n') {
				state = OUT;
				blank[0] = '\n';
				blank[i = 1] = '\0';
            }
			else{ 
				if (state == OUT){
					state = IN;
					printf("%s",blank);
					blank[i = 0] = '\0'; 
				}
				putchar(c);
			}
		}	
	}	
	return 0;	
}			
