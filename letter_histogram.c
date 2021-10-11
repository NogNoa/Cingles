#include <stdio.h>
#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int main()
{
	int c, i, j;
	int hest[26];
	
	for (i = 0; i<26; ++i)
		hest[i] = 0;
	
	while ((c = getchar()) != EOF) {
		if ('Z' >= c && c >= 'A')
			++hest[c-'A'];
		else if ('z' >= c && c >= 'a'){
			++hest[c-'a'];
		}
	}
	
	for (i=0; i<26; ++i){
		putchar('A'+i);putchar(' ');putchar(' ');
		for (j=0; j<=hest[i]; ++j)
			putchar('|');
		putchar('\n');
	}
	return 0;
}

//todo: add count len
// transpose
