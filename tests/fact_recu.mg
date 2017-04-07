func fact (int x) : int {
	print x;
	if x == 1 
		return x;
	return x * fact(x - 1);
}

int x = 5;
print fact(x);
