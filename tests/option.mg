int x = 0;

#false
#true
option x {
	case 0:
		print "false";
	case 0:
		print "true";
		break;
}

#false
option x {
	case 0:
		print "false";
		break;
	case 0:
		print "true";
		break;
}

#true
option x {
	case 100000:
		print "false";
		break;
	case 0:
		print "true";
		break;
}

#only numbers
option x {
	case 1-1:
		print 1;
	case 2-2:
		print 2;
	case 3-3:
		print 3;
	case 4-4:
		print 4;
	case 3:
		print "nope";
}

option x {
	case 0:
		x = x - 1;
}
