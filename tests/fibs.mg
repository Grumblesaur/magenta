# generate the first n fibonacci numbers

#int n = num(input("Number of fibonacci numbers?"));
int n = 8;
int a = 0;
int b = 1;
int f = 1;

#print(f);
while n > 1 {
	f = a + b;
	a = b;
	b = f;
	n = n - 1;
}

print f;
