# Responses

Use this file for responding to questions in the assignment. 

## Section 1.1
1. `std::vector` has dynamic size while the size of `std::array` is fixed. The size of data here is not fixed thus `std::vector` is more suitable to store them. In addition, `std::vector` has more built-in methods which make it easier to manipulate the data.
2.  - Error 'undifined referrence' wiil be raised without these 2 lines, for that:  
        - the `Observations.cpp` cannot define the implementation because it doesn't have the intended type  when compliling to the object
        - when compiling `observation` in other .cpp file say `usage.cpp`, though `observation` knows what type should it be used for, it doesn't have the templated impletation  
    - To avoid this, the implementation of `observation` can be moved into the header file `Observations.h`
## Section 1.2
- `sample` is pure virtual for that the derived classes of the base need different methods to implement it. And the base class doesn't need to be initialized at all. It works like an interface.
- I use vector to reprsent and pass the parameter. Because vectors can be easily access by its indexes which make it easier to create relationship with the elements in other vectors (e.g. dealing several vectors together in a single iteration).
- I made the member variabes to be `protected` in the base class thus protecting them from those actions outside the class but enable derived class to access them. When trying to access or change them outside the class, setter and getter must be used which are made public. The extra variables which are added in the derived classes are made `private`. `protected` also made easier for the derived class to access the base data. I also made those functions which output information to be `public`, like  `summaryCalculator()` and `marDisPlotter()`. And I set `likelihood()` to be `protected` which is only used in the class. 
## Section 4
1. `input(invalid)`: build/bin/Sample2D -f data/problem_data_2D.txt-n 100  
`output`: Usage: -f <file_path> -n <number_of_bins>  
2. `input`: build/bin/Sample2D -f data/problem_data_2D.txt -n 100  
`output`:  
For parameter"a": peak_value = 2.525; mean = 0.0250513; std_deviation = 2.50531  
For parameter"b": peak_value = 4.125; mean = 0.0413374; std_deviation = 4.13513
3. `input`: build/bin/Sample2D -f data/problem_data_2D.txt -n 20  
`output`:  
For parameter"a": peak_value = 2.625; mean = 0.127794; std_deviation = 2.55512  
For parameter"b": peak_value = 4.375; mean = 0.21192; std_deviation = 4.23924

## Section 6
1. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 20 -s 200000  
`output`:  
UniformSampler created...  
For parameter"a": peak_value = 2.85; mean = 0.136238; std_deviation = 2.72539  
For parameter"b": peak_value = 0.45; mean = 0.0266435; std_deviation = 0.571635  
For parameter"c": peak_value = -1.05; mean = -0.050382; std_deviation = 1.0118  
For parameter"d": peak_value = 0.15; mean = 0.0075; std_deviation = 0.149812
2. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 100 -s 200000  
`output`:  
MHSampler created...  
For parameter"a": peak_value = 2.97; mean = 0.0289268; std_deviation = 2.89412  
For parameter"b": peak_value = 0.03; mean = 0.000897591; std_deviation = 0.238198  
For parameter"c": peak_value = -0.75; mean = -0.00741517; std_deviation = 0.763692  
For parameter"d": peak_value = 0.15; mean = 0.00122397; std_deviation = 0.129187

3. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 40 -s 20000  
`output`:  
MHSampler created...  
For parameter"a": peak_value = 2.925; mean = 0.0660321; std_deviation = 2.75851  
For parameter"b": peak_value = 0.075; mean = 0.00855019; std_deviation = 0.84896  
For parameter"c": peak_value = -0.675; mean = -0.0194036; std_deviation = 0.859467  
For parameter"d": peak_value = 0.075; mean = 0.00251044; std_deviation = 0.14061  
4. `input(with very few points)`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 3 -s 100  
`output`: UniformSampler created...  
For parameter"a": peak_value = 2; mean = 0.666667; std_deviation = 1.88562  
For parameter"b": peak_value = 0; mean = 6.38703e-111; std_deviation = 1.9576e-55  
For parameter"c": peak_value = 0; mean = -2.60253e-228; std_deviation = 3.95161e-114  
For parameter"d": peak_value = 0; mean = 0; std_deviation = 0  
5. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 200 -s 10000000  
`output`:  
MHSampler created...  
For parameter"a": peak_value = 2.985; mean = 0.0144332; std_deviation = 2.88868    
For parameter"b": peak_value = 0.045; mean = 0.000541455; std_deviation = 0.238426  
For parameter"c": peak_value = -0.735; mean = -0.0037633; std_deviation = 0.7694  
For parameter"d": peak_value = 0.135; mean = 0.000616688; std_deviation = 0.12804  
6. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 20 -s 1000000   
`output`:  
UniformSampler created...  
For parameter"a": peak_value = 2.85; mean = 0.136238; std_deviation = 2.72539  
For parameter"b": peak_value = 0.45; mean = 0.0266435; std_deviation = 0.571635  
For parameter"c": peak_value = -1.05; mean = -0.050382; std_deviation = 1.0118  
For parameter"d": peak_value = 0.15; mean = 0.0075; std_deviation = 0.149812  
 
- all the plots are labeled with mean, standard deviation together with the auguments specified in the folder's name
- there is difference between the result which may due to the random of the MH method
- from the distribution plot of MH method, it can be seen that the distribution is more concentrated than that if the uniform sample method.
