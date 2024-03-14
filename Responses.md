# Responses

Use this file for responding to questions in the assignment. 

## Section 1.1
1. `std::vector` has dynamic size while the size of `std::array` is fixed. The size of data here is not fixed thus `std::vector` is more suitable to store them. In addition, `std::vector` has more built-in methods which make it easier to manipulate the data.
2.  - Error 'undifined referrence' wiil be raised without these 2 lines, for that:  
        - the `Observations.cpp` cannot define the implementation because it doesn't have the intended type  when compliling to the object
        - when compiling `observation` in other .cpp file say `usage.cpp`, though `observation` knows what type should it be used for, it doesn't have the templated impletation  
    - To avoid this, the implementation of `observation` can be moved into the header file `Observations.h`
## Section 1.2
- The `sample` function is declared as pure virtual within the base class to ensure that derived classes implement their unique sampling methodologies (polymorphism). And the base class doesn't need to be initialized at all. It works like an interface.  
- I use vector to reprsent and pass the parameter. Because vectors can be easily access by its indexes which make it easier to create relationship with the elements in other vectors (e.g. dealing several vectors together in a single iteration). This capability greatly facilitates operations that involve complex relationships between different sets of parameters, enhancing both the flexibility and efficiency of the implementation.
- I made the member variabes to be `protected` in the base class thus protecting them from external modifications (ensure integrity) but enable derived class to access and modify them easily. When trying to access or change them outside the class, setter and getter must be used which are made `public`. The extra variables which are introduced in the derived classes are made `private` to encapsulate specific details irrelevant to other classes. I also made those functions which output information to be `public` to provide users with valuable insights, like  `summaryCalculator()` and `marDisPlotter()`. Specially, I set `likelihood()` to be `protected` which is only used in the class. 
## Section 4
1. `input(invalid)`: build/bin/Sample2D -f data/problem_data_2D.txt-n 100  
`output`: Usage: -f <file_path> -n <number_of_bins>  
2. `input`: build/bin/Sample2D -f data/problem_data_2D.txt -n 100  
`output`:  
For parameter"a": best_value = 2.525; mean = 0.0250513; std_deviation = 2.50531  
For parameter"b": best_value = 4.125; mean = 0.0413374; std_deviation = 4.13513  
3. `input`: build/bin/Sample2D -f data/problem_data_2D.txt -n 200  
`output`:  
For parameter"a": best_value = 2.5125; mean = 0.0125257; std_deviation = 2.5054  
For parameter"b": best_value = 4.1375; mean = 0.0206687; std_deviation = 4.13528   
4. `input`: build/bin/Sample2D -f data/problem_data_2D.txt -n 50  
`output`:  
For parameter"a": best_value = 2.55; mean = 0.0501668; std_deviation = 2.50833  
For parameter"b": best_value = 4.15; mean = 0.0828066; std_deviation = 4.14154    

## Section 6
1. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 20 -s 200000  
`output`:  
UniformSampler created...  
For parameter"a": best_value = 2.85; mean = 0.136238; std_deviation = 2.72539  
For parameter"b": best_value = 0.45; mean = 0.0266435; std_deviation = 0.571635  
For parameter"c": best_value = -1.05; mean = -0.050382; std_deviation = 1.0118  
For parameter"d": best_value = 0.15; mean = 0.0075; std_deviation = 0.149812  
2. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 100 -s 200000  
`output`:  
MHSampler created...  
For parameter"a": best_value = 2.97; mean = 0.0286394; std_deviation = 2.87092  
For parameter"b": best_value = 0.03; mean = 0.0013085; std_deviation = 0.334134  
For parameter"c": best_value = -0.75; mean = -0.00757557; std_deviation = 0.779731  
For parameter"d": best_value = 0.15; mean = 0.0012425; std_deviation = 0.131892  

3. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 200 -s 20000000     
`output`:  
MHSampler created...  
For parameter"a": best_value = 2.985; mean = 0.0144371; std_deviation = 2.88944  
For parameter"b": best_value = 0.045; mean = 0.000530563; std_deviation = 0.237992  
For parameter"c": best_value = -0.735; mean = -0.00375533; std_deviation = 0.767757  
For parameter"d": best_value = 0.135; mean = 0.00061515; std_deviation = 0.127761  

4. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 100 -s 200000000  
`output`:   
UniformSampler created...  
For parameter"a": best_value = 2.97; mean = 0.0288434; std_deviation = 2.88621  
For parameter"b": best_value = 0.15; mean = 0.00109992; std_deviation = 0.242766  
For parameter"c": best_value = -0.87; mean = -0.0075202; std_deviation = 0.769807  
For parameter"d": best_value = 0.15; mean = 0.001231; std_deviation = 0.127761    
5. `input`:  build/bin/Sample4D -f data/problem_data_2D.txt -n 10 -s 20000    
`output`:   
UniformSampler created...  
For parameter"a": best_value = 2.7; mean = 0.269947; std_deviation = 2.68605  
For parameter"b": best_value = 0.9; mean = 0.09008; std_deviation = 0.897088  
For parameter"c": best_value = -1.5; mean = -0.150027; std_deviation = 1.4928  
For parameter"d": best_value = 0.3; mean = 0.03; std_deviation = 0.298496   
 
- All the plots are generated from the commands above. The title of the graphs tells the best value, mean, standard deviation of each parameter, together with the auguments specified in the subfolder's name.
- There is a difference between the result produced by **uniform sampling** and **MH sampling**. Take a look into [**plot1**](plots/UniformSampler_numParas4_numbins100_maxSamples200000000/distribution_c.png) and [**plot2**](plots/MHSampler_numParas4_numbins100_maxSamples200000/distribution_c.png) : both of them is the distribution of parameter *c*. While **plot1** is generated by **uniform sampling** and **plot2** is by **MH sampling**. **plot1** is more continuous while **plot2** is quite rough around the best value, which may imply that **MH sampling** is more reliable to find a best value. In addition, with a number of bins to be 100, **uniform sampling** takes much more time than **MH sampling**.
- As the number of bins increases in **uniform sampling** and the number of samples increases in **MH sampling**, the difference in their results decreases.