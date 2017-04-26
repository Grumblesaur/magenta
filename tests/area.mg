# pi is a language constant

func area_circle (flt radius) : flt {
	flt pi = 3.14;
	return pi * radius ** 2;
}

flt x = 3;
print area_circle(x), '\n';
