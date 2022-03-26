typedef struct {
	unsigned int one : 1;
	unsigned int middle : 2;
	unsigned int eight : 1;
} bcd;

//using only one bit for 8 and 9

typedef struct {
	int sign :1;
	bcd val[];
} bcd_int;

static unsigned int binarise_single(const bcd call)
{
	return call.one + (call.eight) ? (call.eight << 3) : (call.middle << 1);
}

//bcd arrays are little endian, as all things should be.

int binarise(const bcd call[],const int len)
{
	if (len<=0)
		{return 0;}
	else
		{return 10*binarise(call+1,len-1) + (signed) binarise_single(*call);}
}

static bcd decimise_single(const int call)
{	
	if (call >7)
		return (bcd) {.eight = 1, .one = call % 8};
	else
		return (bcd) {.middle = call / 2, .one = call % 2};
}

bcd* decimise(const int call, bcd back[])
{
	if (!call) //call == NULL
		{*back = (bcd) {0,0};}
	else
	{	*back = decimise_single(call % 10); 
		decimise(call / 10, back+1);
	}	
	return back;
}

static bcd* normalise(bcd call, bcd back[])
{
	if (call.middle && call.eight)
	{	call.middle--, call.eight--;
		back[1].middle += back[1].one;
		back[1].one = !back[1].one;  //^= 1 is actually faster
		// {back[1].one = 0, back[1].middle++;} if (back[1].one) else {back[1].one = 1;} 
	}
	back[0]=call;
	return back;
}

bcd* add_single(const bcd adder, const bcd addand, bcd back[])
{
	int rsum, esum;
	
	esum =adder.eight + addand.eight;
	rsum = adder.rest + addand.rest;
	while (esum > 1 || rsum > 7)
	{	if (esum > 1)
			{back[1].rest++, (esum-=2), (rsum+=6);}
		else //if (rsum > 7)
			{rsum-=8, esum++;}
	}
	return (normalise((bcd) {rsum, esum},back));
}

bcd sub_single(const bcd minuend, const bcd subtrahend)
{	int rdif, edif;
	
	rdif = minuend.rest - subtrahend.rest;
	if ((edif = minuend.eight - subtrahend.eight) <= 0)
		{if (rdif < 0 || edif < 0)
			{return sub_single(subtrahend, minuend);}
		
	}
	else if (rdif<0) //don't need while since could only be 0 or 1 iterations
		{rdif+=8, edif--;}
	return (bcd) {rdif, edif};
}
