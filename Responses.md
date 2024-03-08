# Responses

Use this file for responding to questions in the assignment. 

## Section 1.1
1. `std::vector` has dynamic size while the size of `std::array` is fixed. The size of data here is not fixed thus `std::vector` is more suitable to store them. In addition, `std::vector` has more built-in methods which make it easier to manipulate the data.
2.  - Error 'undifined referrence' wiil be raised without these 2 lines, for that:  
        - the `Observations.cpp` cannot define the implementation because it doesn't have the intended type  when compliling to the object
        - when compiling `observation` in other .cpp file say `usage.cpp`, though `observation` knows what type should it be used for, it doesn't have the templated impletation  
    - To avoid this, the implementation of `observation` can be moved into the header file `Observations.h`
## Section 1.2

## Section 4

## Section 6