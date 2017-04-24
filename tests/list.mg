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

print [['a'], ['b', 'd'], ['c', 'e', 'f']], "\n";

print ['a'] * 5, "\n";
print 3 * ['b'], "\n";
print ['abc', '123'][true], '\n';

print second, '\n', second * -1, '\n';
