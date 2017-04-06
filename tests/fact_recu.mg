func fact (int x) : int {
	if x == 0 {
		return 1;
	} else {
		return x * fact(x - 1);
	}
}

int x = 5;
print fact(x);
