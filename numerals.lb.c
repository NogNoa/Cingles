typedef struct {
	unsigned int eight : 1;
	unsigned int rest : 3;
} bcd;

int binarise_single(bcd call)
{
	return (signed) (call.eight) ? (call.rest ? 9 : 8) : call.rest;
}

//bcd arrays are little endian, as all things should be.

int binarise_wraped(bcd call[], int len, int iter)
{
	if (iter>=len)
		return 0;
	else
	{	return 10*binarise_wraped(call+1,len,iter+1) + binarise_single(*call);
	}
}

int binarise(bcd call[], int len)
{
	return binarise_wraped(call, len, 0);
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

bcd* normalise(bcd call, bcd back[2])
{
	while (call.eight > 0 && call.rest > 1)
		back[1].rest++, call.eight--, (call.rest-=2); 

	return (back = (bcd []) { {call.eight, call.rest}, back[1]});
}

bcd* add_single(bcd adder, bcd addand, bcd back[2])
{
	int rsum, esum;
	esum =adder.eight + addand.eight;
	rsum = adder.rest + addand.rest;
	while (esum > 1 || rsum > 7)
	{	if (esum > 1)
			back[1].rest++, (esum-=2),(rsum+=6);
		else //if (rsum > 7)
			esum++,rsum -= 8;
	}
	return (back = normalise((bcd) {esum, rsum},back));
}
