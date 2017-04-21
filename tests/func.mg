func divmod(int dividend, int divisor) : list {
	return[dividend / divisor, dividend % divisor];
}

for x from 1 to 10+1 {
	for y from 1 to 10+1 {
		print (y-1) * " ", divmod(x, y), "\n";
	}
}
