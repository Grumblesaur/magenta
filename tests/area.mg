# pi is a language constant

func area_circle (float radius) : flt {
	return pi * (radius ** 2);
}

radius = flt(input("Radius of a circle: "))
print(area_circle(radius));
