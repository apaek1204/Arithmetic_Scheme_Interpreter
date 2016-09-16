Project 01: uScheme
===================

This is a simple implementation of a [Scheme] interpreter that supports the
following syntax:

    <digit>         = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    <number>        = {<digit>}
    <op>            = - | + | * | /
    <expression>    = (<op> <expression> <expression>) | <number>

Examples
--------

    :::scheme
    1
    (+ 1 2)
    (+ 1 (- 2 3))
    (+ (* 1 2) (- 3 4))

[Scheme]:   https://en.wikipedia.org/wiki/Scheme_(programming_language)


Questions
---------

1. The complexity of the interpreter is O(n), where n is the number of elements. The largest size that the stack will ever reach is n because we're both pushing AND popping numbers from the stack. There is no need for reallocation of memory for more than n elements, so allocation of memory is O(1). Adding elements is O(n), so the total complexity is O(n).

2. uschemeSmart(127KB) is larger than uscheme(104KB). uschemeSmart(3.29MB) also uses more memory than uscheme(2.54MB).

	Smart pointers are convenient in that you don't have to worry about memory leaks.

	We prefer the smart pointer method because we don't have to do memory management, so there are less errors.

	Even though smart pointers are good, they take up more space and could be less efficient, but from a programmer's perspective, smart pointers are definitely better.

3. Let's say we're working with (+ 1 2 3 4 5)

	We would make the tree so that the leaves are the operands (1 2 3 4 5) and the nodes above are the operator (+). So this example would be a tree of depth 3.

'''
         +
      +     +
   +   3  4   5
 1   2

'''


	The parser would have to parse tokens (operands) until we reach ")". We also have to allocate enough memory for the right number of leaf nodes (the operands)

	The interpreter would look similar, with post-order traversal and stack operations.

Emily did the README and uschemeSmart.cpp, Andrew did the uscheme.cpp
