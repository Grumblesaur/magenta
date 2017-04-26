for iter from 1 to 10 by 1 {
	print "I AM MAYOR\n";
}

for iter2 from 5 to 0 {
	print iter2 * '*', '\n';
}

for a from 0 to 10 by 1 {
	print "OUTER LOOP\n";
	for b from 0 to 10 by 1 {
		print "\tINNER LOOP\n";
	}
}

for c from 0 to 10 by 1 print c, '\n';
print "no loop\n";

int x = 0;

for rows from 0 by 2 {
	for cols from 0 to 10 {
		print '*' * cols, '\n';
	}
	if rows >= 20 break;
}

for inf_test {
	print 'I am the batman\n';
	x = x + 1;
	if x > 11 break;
}

for x from 10 to 1 by -1 {
	print "help me\n";
}
