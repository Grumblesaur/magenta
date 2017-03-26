print "START for.mg TEST FILE";

for iter from 1 to 10 by 1 {
	print "I AM MAYOR";
}

for iter2 from 5 to 0 {
	print iter2 * '*';
}

for a from 0 to 10 by 1 {
	print "OUTER LOOP";
	for b from 0 to 10 by 1 {
		print "INNER LOOP";
	}
}

for c from 0 to 10 by 1 print c;
print "no loop";

int x = 0;

for rows from 0 by 2 {
	for cols from 0 to 10 {
		print '*' * cols;
	}
	if rows >= 20 break;
}

for inf_test {
	print 'I am the batman';
	x = x + 1;
	if x > 11 break;
}
