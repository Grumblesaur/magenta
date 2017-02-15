# calculate factorials recursively

func fact : int (int x) {
	if x == 0 {
		return 1;
	} else {
		return x * fact(x - 1);
	}
}

int x = int(input("Find factorial of: "));
print(fact(x));
