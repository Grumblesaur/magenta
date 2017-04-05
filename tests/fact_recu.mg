func fact int x : int {
	if x == 0 {
		return 1;
	} else {
		return x * fact(x - 1);
	}
}

int x = int(input);
print(fact(x));
