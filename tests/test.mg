func int_sum(list integers) : int {
	int out = 0;
	for i to len(integers) {
		out = out + integers[i];
	}
	return out;
}

func list_cat(list lists) : list {
	list out = [];
	for i to len(lists) {
		out = out + lists[i];
	}
	return out;
}

func flt_sum(list floats) : flt {
	flt out = 0.0;
	for i to len(floats) {
		out = out + floats[i];
	}
	return out;
}

func str_cat(list strings) : str {
	str out = "";
	for i to len(strings) {
		out = out + strings[i];
	}
	return out;
}

list a = [1, 2, 3, 4, 5];
list b = ['a', 'b', 'c', 'd', 'e'];
list c = [['a'], ['b'], [1], [5], [6.97]];
list d = [1.2, 2.3, 3.4, 4.5, 5.6, 6.7, 7.8, 8.9, 9];

print int_sum(a),  "\n";
print list_cat(c), "\n";
print str_cat(b),  "\n";
print flt_sum(d),  "\n";
