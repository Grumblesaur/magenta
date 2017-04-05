# pi is a language constant

func area_circle (flt radius) : flt {
	flt pi = 3.14;
	return pi * radius ** 2;
}

#radius = flt(input("Radius of a circle: "))
flt x = 3;
print area_circle(x);