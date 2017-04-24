func fact (int x) : int {
	if x == 1 {
		return x;
	} else {
		return x * fact(x - 1);
	}
}

int z = 5;

print fact(z), "\n";
