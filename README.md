# aoc-2024
Advent of code 2024 - C++ - `Can be used as a boiler plate`

# Instructions
You can create your test in `tests` folder make sure 
it has either `.cc` or `.cpp` extension.

Now run cmake , with your own choice of generator
```
    mkdir build
    cd build
    cmake .. -G<GENERATOR>
``` 
This will create an input file `.in` with the name of 
the test case added. You can modify the input and while
writing your test you can simply use the filename without
caring about the path. Example is already in : `tests/filereadtest.cc`