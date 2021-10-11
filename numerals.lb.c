typedef struct {
	unsigned int rest : 3;
	unsigned int eight : 1;
} bcd;

typedef struct {
	int sign :1;
	bcd val[];
} bcd_int;

int binarise_single(bcd call)
{
	return (signed) (call.eight) ? (call.rest ? 9 : 8) : call.rest;
}

//bcd arrays are little endian, as all things should be.

int binarise(bcd call[], int len)
{
	if (len<=0)
		return 0;
	else
	{	return 10*binarise(call+1,len-1) + binarise_single(*call);
	}
}

bcd decimise_single(int call)
{
	return (bcd) {.eight = (call > 7), .rest = call % 8};
}

bcd* decimise(int call, bcd back[])
{
	if (!call) //call == NULL
		*back = (bcd) {0,0};
	else
	{	*back = decimise_single(call % 10); 
		decimise(call / 10, back+1);
	}	

	return back;
}

bcd* normalise(bcd call, bcd back[])
{
	while (call.eight > 0 && call.rest > 1)
		(call.rest-=2), call.eight--, back[1].rest++;  

	*back=call;
	return back;
}

bcd* add_single(bcd adder, bcd addand, bcd back[])
{
	int rsum, esum;
	
	esum =adder.eight + addand.eight;
	rsum = adder.rest + addand.rest;
	while (esum > 1 || rsum > 7)
	{	if (esum > 1)
			back[1].rest++, (esum-=2), (rsum+=6);
		else //if (rsum > 7)
			rsum-=8, esum++;
	}
	return (normalise((bcd) {rsum, esum},back));
}

bcd sub_single(bcd minuend, bcd subtrahend)
{	int rdif, edif;
	
	rdif = minuend.rest - subtrahend.rest;
	if ((edif = minuend.eight - subtrahend.eight) <= 0)
	{	if (rdif < 0 || edif < 0)
			return sub_single(subtrahend, minuend);
	}
	else if (rdif<0) //don't need while since could only be 0 or 1 iterations
		rdif+=8, edif--;
	return (bcd) {rdif, edif};
}
