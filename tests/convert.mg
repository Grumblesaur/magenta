func dtoc(int d) : str {
	str out = '';
	option d {
		case 0: out = '0'; break;
		case 1: out = '1'; break;
		case 2: out = '2'; break;
		case 3: out = '3'; break;
		case 4: out = '4'; break;
		case 5: out = '5'; break;
		case 6: out = '6'; break;
		case 7: out = '7'; break;
		case 8: out = '8'; break;
		case 9: out = '9'; break;
	}
	return out;
}

func ctod(str c) : int {
	int out = -1;
	option c {
		case '0': out = 0; break;
		case '1': out = 1; break;
		case '2': out = 2; break;
		case '3': out = 3; break;
		case '4': out = 4; break;
		case '5': out = 5; break;
		case '6': out = 6; break;
		case '7': out = 7; break;
		case '8': out = 8; break;
		case '9': out = 9; break;
	}
	return out;
}

func itos(int i) : str {
	str s = '';
	while i {
		s = s + dtoc(i % 10);
		i = i / 10;
	}
	return s*-1;
}

func stoi(str s) : int {
	int out = 0;
	int order = len(s)-1;
	int index = 0;
	while order >= 0 {
		out = out + (10 ** order) * ctod(s[index]) ;
		index = index + 1;
		order = order - 1;
	}
	return out;
}

print [stoi("1234")], "\n";
print [itos(9000)], "\n";
