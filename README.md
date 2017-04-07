# magenta
https://trello.com/b/LEAOTeYg/magenta

# Types:

### num (int, float, bool)
  ```
  int i = 0;
  flt f = 0.0;
  
  str s = "hello world!";
  str z = 'single quotes are also legal';

  # type
 
  # this is a feature yet to be implemented
  type Person {
    str name;
    int age;
  }
  
  ```
  
  
### func & meth
  ```
  # this is a feature yet to be implemented
  
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
    ~     logarithm (e.g. log base 2 of 3 is 2~3),
    //    integer division,
    *     multiplication,
    /     division,
    %     modulo,
    +     addition,
    -     subtraction,
    
    >     greater than,
    <     less than,
    ==    equal,
    !=    not equal,
    >=    greater equal,
    <=    less equal,
    ?:    ternary or null-coalescing
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
    !   bitwise not
    &   bitwise and
    |   bitwise or
    ^   bitwise xor
```

# str
```
     +    concatenation,
     *    string multiplication (with an integer),
    []    character access (substring of length 1 at a character index)
           (slice operations to come later?)
```

# Compounds
```
     # This will be implemented with user-defined types
     .    member access (e.g. x.y S.T. y belongs to x)
```
 
# arrays
```
    # This will be implemented with containers
    []   element access
```
