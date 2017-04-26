# calculate a factorial

func fact (int x) : int {
	int out = 1;
	while (x) {
		out = out * x;
		x = x - 1;
	}
	return out;
}

int x = 5;
print fact(x), '\n';
