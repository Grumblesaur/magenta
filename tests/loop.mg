int i = 0;
int j = 0;
while i < 100 {
	j = i ** 2;
	if j == 16 {
		break;
	}
	i = i + 1;
}
print j;

i = 0;
while i < 10 {
	i = i + 1;
	if i % 2 == 0 {
		next;
	}
	print i;
}