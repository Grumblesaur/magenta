func add(int a, int b) : int {
	return a + b;
}

func add(int c, int b) : int {
	return c + b;
}

func p(int x) : int {
	print x;
	return 0;
}

p(p(add(add(3,4),2)));

int x = 1;
int x = 3;
print x;