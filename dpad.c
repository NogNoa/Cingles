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
	int val :3;
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
	back.right = !(ang.val & 06) ||      !~ang.val;
	back.left  =  (ang.val & 04)  ^ (ang.val & 02);
	back.up    =  (ang.val & 04) && (ang.val & 03);
	back.down  = !(ang.val & 04) &&      (ang.val);
	return back;
}
