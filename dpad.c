/* takes a 3-bit value that gives an angle in increments of 45deg = π/4, 
	and return a 4-bit value of flags for each cardinal direction.
	The angle start from the right and goes clockwise.
	The direction flags go UDLR (left significant)
	so 
	00 = 000 =  R
	01 = 001 = DR
	02 = 010 = D
	03 = 011 = DL
	04 = 100 =  L
	05 = 101 = UL
	06 = 110 = U
	07 = 111 = UR
*/

typedef struct {
	unsigned int val :3;
} angle;

typedef struct {
	_Bool right :1;
	_Bool left  :1;
	_Bool down  :1;
	_Bool up	:1;
} dirmask;

dirmask dir_decode(angle ang)
{
	dirmask back;
	back.right = ! (ang.val & 06)     ||       !~ang.val;
	back.left  = ((ang.val & 06) == 04) || (ang.val == 03);
	back.down  = ! (ang.val & 04)     &&         ang.val;
	back.up    =   (ang.val & 04)     &&  (ang.val & 03);
	return back;
}

#include <stdio.h>
#include <string.h>

void test(int i)
{	dirmask dir = dir_decode((angle){i});
	char right  = (dir.right) ? 'R' : ' ';
	char left   = (dir.left)  ? 'L' : ' ';
	char down   = (dir.down)  ? 'D' : ' ';
	char up     = (dir.up)    ? 'U' : ' ';
	printf("%c%c%c%c\n",up,down,left,right);
}

int main(int argc, char** argv)
{
	if (argc > 1 && !strcmp(argv[1],"test"))
	{	for (int i=0;i<8;i++)
		{	test(i);	}
	}
	return 0;
}