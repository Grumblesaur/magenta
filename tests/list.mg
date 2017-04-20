list first = [1, '37.9', 901, 886];
list second = ['abc', 123, 'easy', 7.5];
list c = first + second;

print first, "\n";
print second, "\n";
print c, "\n";

for x to len(c) {
	print c[x], " ";
}
print "\n";

print ('easy' in second) * "easy in second", "\n";
print ('hard' in second) * "hard in second\n";
