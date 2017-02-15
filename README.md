# magenta

# Types:

###num (int, float, bool)
  ```
  num i = 0;
  num f = 0.0;
  num b = true;
  ```
  
  str
  `str s = "hello world!"`
  
###func
  ```
  func add : int(int a, int b) {
    return a + b;
  }
  
  OR (still deciding)
  
  add : int(int a, int b) {
    return a + b;
  }
```

###compound
  

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
    \-   subtraction
```
 
## bool
```
    and  conjunction
    or   disjunction
    not  negation
    xor  exclusive disjunction
```

## bitwise (given Latin names for their obscurity and few use cases)
```
    et   bitwise and
    aut  bitwise or
    non  bitwise not
    xaut bitwise xor
```

# str
```
    .    concatenation,
    *   string multiplication,
    []   character access (substring of length 1 at a given character index)
```

# Compounds
```
    @    member access (e.g. y@x S.T. y belongs to x)
```
 
# arrays
```
    []   element access
```
