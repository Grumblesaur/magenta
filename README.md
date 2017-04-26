# magenta
https://trello.com/b/LEAOTeYg/magenta

# Types:

### num (int, float, bool)
  ```
  int i = 0;
  flt f = 0.0;
  
  str s = "hello world!";
  str z = 'single quotes are also legal';

  list x = ['abc', 1, 3.6, [1, 3, 4], 5];
  
  ```
  
  
### func & meth
  ```
  # func-declared procedures have no side effects
  func add(int a, int b) : int {
    return a + b;
  }
  
```
  

# Types
```
    func  declare a function
    int   declare an integer
    str   declare a string
    flt   declare a floating point number
    type  describe a new data structure
    list  declare a container which may hold any of the above
```


# flow control
```
    # conditionals which only execute a single statement don't
    # require curly braces
    if (condition)
        print "success";

    
    if (condition) {
        # statement(s)
    } else if (other_condition) {
        # statement(s)
    } else {
        # statement(s)
    }

    # case expressions don't have to be constants, so the option-case block
    # can be used as a more condensed if-else if-else block
    option (expression) {
        # use "break" keyword to avoid fallthrough
        case expression1:
            # statement(s)
        case expression2:
            # statement(s)
            break;
        case expression3:
            # statement(s)
            break;
    }
    
    while (condition) {
        # statement(s)
    }
    
    # when a from-clause is not specified, "var" begins at 0
    # when a to-clause is not specified, "var" will have no upper bound
    # when a by-clause is not specified, "var" will increment by 1
    # "var" is local to the for-loop block, and is removed after execution
    for var [from x] [to y] [by z] {
        # statements
    }
    
    break   # exits the current loop or breaks out of a switch statement
    next    # skips to the next iteration of the current loop
    
    return  # outputs a value from a function
```


# Operators:
  
# numeric
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
```

# any types
```
    and   conjunction
    or    disjunction
    not   negation
    xor   exclusive disjunction
    then  material implication

    >     greater than,
    <     less than,
    ==    equal,
    !=    not equal,
    >=    greater equal,
    <=    less equal,
    ?:    ternary or null-coalescing
```

## bitwise (applicable to integers only)
```
    !   bitwise not
    &   bitwise and
    |   bitwise or
    ^   bitwise xor
```

# str
```
     +    string concatenation: combines left operand and right head-to-tail
     *    string repetition: combines left operand with itself right times
    []    character access: returns string of length one with char at index
```
 
# arrays
```
    []   element access: returns object with value of element at index
    in   element presence: true if value of left operand present in right
     *   list repetition: combines left operand with itself right times
     +   list concatenation: combines left operand with right head-to-tail
     /   element removal: removes first element with value of right operand
```
