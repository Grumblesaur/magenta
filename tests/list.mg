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

print ['a'] * 5, "\n";
print 3 * ['b'], "\n";
print;
print ['abc', '123'][true], '\n';

print second, '\n', second * -1, '\n';

print ['a', 'b', 'c'] / 'c', '\n';

list repeats = 6 * ['a'] + [3, 4, 5, 6, 7, 8];

while 'a' in repeats {
	repeats = repeats / 'a';
}
print repeats, "\n";
