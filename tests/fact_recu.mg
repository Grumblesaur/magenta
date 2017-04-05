func fact (int x) : int {
	print x;
	if x == 0 {
		return 1;
	} else {
		return x * fact(x - 1);
	}
}

int x = 6;
print fact(x);
