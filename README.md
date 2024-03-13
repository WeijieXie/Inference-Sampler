# Project Installation and Usage Guide

This guide provides instructions on how to compile and run the provided sample programs. Follow these steps to get started.

## Compilation

To compile the project, execute the following commands in the terminal from the current directory:

```bash  
cmake -B build  
cmake --build build  
```

Upon successful compilation, three executable files will be generated in the `build/bin` directory:

- `Sample2D`
- `Sample4D`
- `TestSampler`

## Testing

It is recommended to run the tests before using the sampling programs. Execute the following command to perform unit tests:

```bash  
./build/bin/TestSampler
```

In normal circumstances, all tests should pass. These tests are designed to verify the integrity of the sampling algorithms.

## Running the Sample Programs

### Sample2D

To run `Sample2D`, use the command:

```bash  
build/bin/Sample2D -f filepath -n numBins
```

This program performs sampling in a uniform manner for a model with two parameters ($y=a*x^b$). It works well with simpler models, but as the number of parameters increases, the average sampling overhead may grow.

### Sample4D

For improved efficiency, `Sample4D` utilizes the Markov Chain Monte Carlo (MCMC) method with Metropolis-Hastings Sampling. To run `Sample4D`, use the command:

```bash  
build/bin/Sample4D -f filepath -n numBins -s maxNumOfSampler
```


This program applies to a model with four parameters ($y=a*x^3+b*x^2+c*x+d$). It chooses the sampling method based on `numBins` and `maxNumOfSampler`. If `pow(numBins, number of parameters)` is less than the maximum number of samples, it opts for uniform sampling. Otherwise, it employs Metropolis-Hastings Sampling.

## Output Information

After running `Sample2D` and `Sample4D`, you will see output in the terminal similar to the following, which includes the best value for each parameter, along with its mean and standard deviation:

```bash  
For parameter "a": best_value = 2.5125; mean = 0.0125257; std_deviation = 2.5054
```


Additionally, `Sample4D` will output the current sampling type being used:

- If uniform sampling is used, you'll see:

```bash  
UniformSampler created...
``` 

- If Metropolis-Hastings Sampling is employed, it will display:
```bash  
MHSampler created...
``` 

## Generating Probability Distribution Plots

Running `Sample2D` and `Sample4D` with different parameters will create a new subfolder in the `plots` directory (which will be created if it doesn't exist already). This subfolder is named after the sampling method and parameter information (number of parameters, number_of_bins, maximum_number_of_samples). It contains a probability distribution graph for each parameter, annotated with the best value, mean, and standard deviation. These visualizations are designed to help better understand the sampling results.

## Conclusion

Follow these guidelines to compile and test the project successfully. Depending on the specific requirements, choose either `Sample2D` or `Sample4D` for sampling tasks. Pay attention to the terminal output and the generated plots in the `plots` folder to gain insights into the performance and results of the sampling process. Happy sampling!




