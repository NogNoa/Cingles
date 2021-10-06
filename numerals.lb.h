typedef struct {
	unsigned int eight : 1;
	unsigned int rest : 3;
} bcd;

int binarise_single(bcd call);

int binarise(bcd call[], int len);

bcd decimise_single(int call);

bcd* decimise(int call, bcd back[]);

bcd* normalise(bcd call, bcd back[2]);

bcd* add_single(bcd adder, bcd addand, bcd back[2]);
