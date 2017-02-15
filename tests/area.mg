# pi is a language constant

func area_circle : float (float radius) {
	return pi * (radius ** 2);
}

radius = float(input("Radius of a circle: "))
print(area_circle(radius));
