# magenta
https://trello.com/b/LEAOTeYg/magenta

# Types:

### num (int, float, bool)
  ```
  int i = 0;
  flt f = 0.0;
  ```
  
  str
  `str s = "hello world!"`
  
  type
  ```
  type Person {
    str name;
    int age;
  }
  
  ```
  
  
### func & meth
  ```
  # func-declared procedures have no side effects
  func add(int a, int b) : int {
    return a + b;
  }
  
  # meth-declared procedures can have side effects
  meth add_debug(int a, int b) : int {
    print(a + b);
    return a + b;
  }
  
```

###type
  

# Keywords
```
	func  declare a function
    int   declare an integer
    str   declare a string
    flt   declare a floating point number
    type  describe a new data structure
    
    if
    else
    option
    case
    
    while
    for
    
    return
```


# Operators:
  
# num
```
    ()    grouping,
    **    exponentiation,
    ~     logarithm e.g. log base 2 of 3 is 2~3,
    //    integer division,
    *     multiplication,
    /     division,
    %     modulo,
    +     addition,
    -     subtraction
    
    >     greater than
    <     less than
    ==    equal
    !=    not equal
    >=    greater equal
    <=    less equal
```
 
## bool
```
    and   conjunction
    or    disjunction
    not   negation
    xor   exclusive disjunction
    then  material implication
```

## bitwise
```
    &    bitwise and
    |   bitwise or
    !   bitwise not
    ^  bitwise xor
```

# str
```
     +    concatenation,
     *    string multiplication,
    []    character access (substring of length 1 at a character index)
           (slice operations to come later?)
```

# Compounds
```
    @    member access (e.g. y@x S.T. y belongs to x)
```
 
# arrays
```
    []   element access
```
