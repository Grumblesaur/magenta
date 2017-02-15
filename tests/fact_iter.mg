# calculate a factorial

func fact : int (int x) {
	int out = 1;
	while (x) {
		out = out * x;
		x = x - 1;
	}
	return out;
}

int x = int(input("Find factorial for: "));
print(fact(x));
