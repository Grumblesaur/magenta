type poo{
	int r
}

type point {
	int a, int b, str c, flt d, poo e
}

func at(): int {
	return 7;
}

print at();

poo t = {5};

point x = {0, 1, 'taylor', 7.654321, nil};

print x.a;
print x.b;
print x.c[5];
print x.d;
print x.e;
print t.r;
