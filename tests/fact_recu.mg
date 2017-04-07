func fact (int x) : int {
	print x;
	if x == 1 {
		return x;
	} else {
		return x + fact(x - 1);
	}
}

int x = 100;
print fact(x);