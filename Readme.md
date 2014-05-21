ChickenFuck
===========
---

A simple [Brainfuck](http://en.wikipedia.org/wiki/Brainfuck) interpreter written in C.

Probably has bugs, missing some error checking in file loading, copies a commandline argument using strcpy, all due to laziness.

Usage
-----

To run the built-in 'Hello, World!' program:
```
chickenfuck
```
To run a program directly:

```
chickenfuck [your program here]
```

To run a Brainfuck file:

```
chickenfuck -f file.b
```

License
-------

ChickenFuck is released under the terms of the University of Illinois / NCSA Open
Source License and contains Brainfuck programs written by 
[Daniel B. Christofani](http://www.hevanet.com/cristofd/brainfuck/) in the tests/
subdirectory. These consist of tests derived from his test.b and his rot13.b program.
The built-in 'Hello, World!' program is taken from Wikipedia's article on Brainfuck.
