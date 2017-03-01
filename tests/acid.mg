#tests operator precedence with a bunch of flt operations

flt real_87_varNAME = 2.0 * (12.0 - 6.0) + 4.5;
flt X2222 = (real_87_varNAME - 1/2) / 4.0;

if 3 < 4 and 5 != 6 {
  flt _a = 5;
} else {
  flt _a = 17;
}

if 3 >= 3.01 or 5 == 7 {
  X2222 = X2222 + 10;
}

#     V------------- here is where we are segfaulting currently
if _a > X2222 {
	flt NUM = X2222 * _a;
}

flt i = 70;

while i > 0 {
  NUM = NUM + 1;
  i = i - 7;
}

if not not not(i != 0) {
	NUM = NUM + 2;
}
	
while NUM < 10 {
	 NUM = NUM + 1;
}

if NUM > 20 {
  if NUM > 30 {
    if NUM > 40 {
      NUM = NUM - 10;
	} else {
      NUM = NUM + 5;
	}
  } else {
    NUM = real_87_varNAME - NUM;
  }
}
NUM = NUM - .5;
{
  a = 0-2;
  a = a + 3;
NUM = NUM + a;
}
print NUM + (6 - 1 - 1) + .5;
