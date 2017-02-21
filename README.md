# magenta
https://trello.com/b/LEAOTeYg/magenta

# Types:

### num (int, float, bool)
  ```
  int i = 0;
  float f = 0.0;
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
    print a + b;
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
    elif
    else
    option
    case
    
    while
    for
    
    print
    input
```


# Operators:
  
# num
```
    ()   grouping,
    **  exponentiation,
    //   natural log,
    *   multiplication,
    /    division,
    %    modulo,
    \+   addition,
    -   subtraction
    
    >   greater than
    <   less than
    ==  equal
    !=  not equal
    >=  greater equal
    <=  less equal
```
 
## bool
```
    and   conjunction
    or    disjunction
    not   negation
    xor   exclusive disjunction
    then  material implication
```

## bitwise (given Latin names for their obscurity and few use cases)
```
    et   bitwise and
    aut  bitwise or
    non  bitwise not
    xaut bitwise xor
    imp  bitwise then (I know, weird, right?)
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
