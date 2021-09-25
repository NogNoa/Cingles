// Ritchie, D.M. and Kernighan, B.W. (1988) p86
#ifndef printf
	#include <stdio.h>
#endif
#ifndef isdigit
	#include <ctype.h>
#endif

static int getch(void);
static void ungetch(int);

int getint(int *pn)
{   /* getint: get next integer from input into *pn */
	signed char c, s=0, sign;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{	s=c;
		c = getch();
	}
	if (!isdigit(c))
	{	if (c!= EOF)
			ungetch(c);
		if (s)
			ungetch(s);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

//original

int getfloat(double *pn)
{   /* getfloat: get next float from input into *pn */
	signed char c, s=0, sign;
	int i=0;
	while (isspace(c = getch())) /* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c!= '.') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
	{	s=c;
		c = getch();
		if (!isdigit(c))
		{	if (c!= EOF)
				ungetch(c);
			if (s)
				ungetch(s);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	if (c == '.')
	{	c = getch();
		if (!isdigit(c))
		{	if (c!= EOF)
				ungetch(c);
			if (s)
				ungetch('.');
			return 0;
		}
		for (;isdigit(c); c = getch(), i++)
			*pn = 10 * *pn + (c - '0');
	}
	for (int j=0;j<i;j++)
		*pn /= 10;
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

// Ritchie, D.M. and Kernighan, B.W. (1988) p69

#include <string.h> /* for strlen() */
#define BUFSIZE 100
static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0; /* next free position in buf */

static int getch(void) 
{	/* get a (possibly pushed-back) character */
	return (bufp > 0) ? buf[--bufp] : getchar();
}

static void ungetch(int c) 
{	/* push character back on input */
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else if (c != EOF)
		buf[bufp++] = c;
}

//original

void unget(char s[])
{
	int l;

	if (bufp + (l=strlen(s)) > BUFSIZE )
		printf("unget: too long string %s\n",s);
	else
		for (int i=0;i<l;++i)
			buf[bufp++] = s[i];
}

// Ritchie, D.M. and Kernighan, B.W. (1988) p91

#define ALLOCSIZE 10000 /* size of available space */
static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

char *alloc(int n) /* return pointer to n characters */
{
	if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
		allocp += n;
		return allocp - n; /* old p */
	} else /* not enough room */
		return 0;
}

void afree(char *p) /* free storage pointed to by p */
{
	if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
	allocp = p;
}

#include "dcl.h"

// Ritchie, D.M. and Kernighan, B.W. (1988) p111

int gettoken(void) 
{ /* return next token */
	int type, getch(void);
	void ungetch(int);
	char *p = token, c;
	while (isspace(c = getch()) && c != '\n')
		;
	if (c == '(') 
	{	if ((c = getch()) == ')') 
		{	strcpy(token, "()");
			type = PARENS;
		} else 
		{	ungetch(c);
			type = '(';
		}
	} else if (c == '[') 
	{	for (*p++ = c; (*p++ = getch()) != ']'; )
			;
		*p = '\0';
		type = BRACKETS;
	} else if (isalpha(c)) 
	{	for (*p++ = c; isalnum(c = getch()); )
			*p++ = c;
		*p = '\0';
		ungetch(c);
		type = NAME;
	} else
		type = c;
	return type;
}

void ungettoken(int tokentype)
{	
	ungetch(tokentype);
}

/*if tokentype that is either NAME, PARENS, BRACKETS it pushed back on the stack 
than with gettoken it will be pulled again as the type, 
and the token is supposed to still be there since the stack is very shallow
(only used for one token + a charecter after reading a new string token)
*/

// Ritchie, D.M. and Kernighan, B.W. (1988) p121

int getword(char *word, size_t lim)
{ /* getword: get next word or character from input */
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c)) 
	{	for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') 
			{	ungetch(*w);
				break;
			}
	}
	*w = '\0';
	return c;
}

//original

char ig_getword(char *word, size_t lim)
{ /* ig_getword: get next word or character from input 
	 ignores preprocessor, strings constants and comments*/
	char *w = word, c;

	while (isspace(c = getch()))
		;
	for (;"ever";c = getch())
	{	if (c == '/')
		{	if ((c = getch()) == '/')
				while ((c = getch()) != '\n' && c != EOF)
					;
			else if (c == '*')
				while (!((c = getch()) == '*' && (c = getch()) == '/') && c != EOF)
					;	
		}
		else if (c == '#')
			while ((c = getch()) != '\n' && c != EOF)
				;
		else if (c == '\"')
			while ((c = getch()) != '\"' && c != EOF)
				;
		else
		{	break;
		}
	}
	if (c != EOF)
		*w++ = c;
	if (isalpha(c)) 
	{	for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') 
			{	ungetch(*w);
				break;
			}
	}
	*w = '\0';
	return c;
}

int lngetword(char *word, size_t lim)
{ /* getword: get next word or character from input, including newline*/
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	
	while (isspace(c = getch()) && !(c == '\n'))
		;
	if (c != EOF)
		*w++ = c;
	if (isalpha(c)) 
	{	for ( ; --lim > 0; w++)
			if (!isalnum(*w = getch()) && *w != '_') 
			{	ungetch(*w);
				break;
			}
	}
	*w = '\0';
	return c;
}

char get_directive(char *direct, size_t lim)
{ /* if at or just before start of line with # put line in direct and returns last char, 
     else eats whitespace and returns 0 */

	char c;
	while(isspace(c=getch()))
		;
	if (c == '#')
		{	while ((c=getch()) != '\n' && c != '\r' && c != EOF && --lim > 0)
				*direct++ = c;
			*direct = '\0';
			return c;
		}
	else
	{	if (c != EOF)
			ungetch(c);
		return '\0';
	}
	/* success: if return != 0 */
}


_Bool ex_isspace(char c)
{
	if (c =='\r' || c == ')' || 
	    c == ']' || c == '}' ||
	    c == '+' || c == '-' ||
	    c == ',' || c == ';' ||
	    c == '*' || c == '(' || 
	    c == '[' || c == '{' ||
	    c == '&' || c == '!' ||
	    isspace(c))
		return 1;
	else
		return 0;
}

char uni_getword(char *word, size_t lim)
{ /* get every token between whitespace, 
     and every sequence of whitespace */
	char *w = word;
	_Bool b_space;

	if(ex_isspace( *w++ = getch() ))
		b_space=1;
	else
		b_space=0;	

	for ( ; --lim > 0 && *w != EOF; w++)
	{	if ((ex_isspace( *w = getch() )) ^ b_space) 
		{	ungetch(*w);
			break;
		}
	}
	*w--='\0';
	return *w;
}


/* fgets: get at most n chars from iop */
char *KnR_fgets(char *s, int n, FILE *iop)
{
	register int c;
	register char *cs;
	
	cs = s;
	while (--n > 0 && (c = getc(iop)) != EOF)
		if ((*cs++ = c) == '\n')
			break;
	*cs = '\0';
	return (c == EOF && cs == s) ? NULL : s;
}

#ifndef va_list
	#include <stdarg.h>
#endif

void minscanf(char *fmt, ...)
{  /* minscanf: minimal scanf with variable argument list */
	va_list arg_pnti; /* points to each unnamed arg in turn */
	char *p, *sval, minfmt[3],c;
	int *ival;
	unsigned *uval;
	double *dval;
		
	for(c=getch();isspace(c);c=getch())
		;
	
	va_start(arg_pnti, fmt); /* make ap point to 1st unnamed arg */
	for (p = fmt; *p; p++) {
		
		for(;isspace(*p);p++)
		{	while(isspace(c))
			{	c=getch();
			}
		}
		
		for (;*p && *p != '%' && *p == c;p++,c=getch())
			;
		
		if (*p != '%')
			continue;

		switch (*++p)
		{case 'd':
		case 'i':
		case 'x':
		case 'X':
		case 'o':
			ival = va_arg(arg_pnti, int*);
			sprintf(minfmt,"%%%c",*p);
			scanf(minfmt, ival);
			break;
		case 'u':
			uval = va_arg(arg_pnti, unsigned*);
			scanf("%u", uval);
			break;
		case 'f':
		case 'e':
		case 'E':
		case 'g':
		case 'G':
			dval = va_arg(arg_pnti, double*);
			sprintf(minfmt,"%%%c",*p);
			scanf(minfmt, dval);
			break;
		case 'p':
			scanf("%p", va_arg(arg_pnti, void **));
			break;
		case 's':
			sval = va_arg(arg_pnti, char*);
			scanf("%s",sval);
			break;
		case '%':
			if (c=='%')
				p++, c=getch();
			break;
		default:
			break;
		}
	}
	va_end(arg_pnti); /* clean up when done */
}
