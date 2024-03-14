#include "UniformSampler.hpp"

int main(int argc, char *argv[])
{
    std::function<double(double, const std::vector<double> &)> modelFunc = [](double x, const std::vector<double> &params) -> double
    {
        double result = params[0] * pow(x, params[1]); // Example implementation
        return result;
    };
    const ParamInfo<double> paraInfo1 = ParamInfo<double>(0, 5, "a");
    const ParamInfo<double> paraInfo2 = ParamInfo<double>(0, 5, "b");
    const std::vector<ParamInfo<double>> paraVec_2d = {paraInfo1, paraInfo2};

    std::string filePath;
    int numBins = 100;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h")
        {
            std::cout << "Usage: -f <file_path> -n <number_of_bins>" << std::endl;
            return 0;
        }
        else if (arg == "-f" && i + 1 < argc)
        {
            filePath = argv[++i];
        }
        else if (arg == "-n" && i + 1 < argc)
        {
            numBins = std::stoi(argv[++i]);
        }
        else
        {
            std::cout << "Usage: -f <file_path> -n <number_of_bins>" << std::endl;
            return 0;
        }
    }

    UniformSampler<double> uniformSampler(filePath, modelFunc, paraVec_2d);
    uniformSampler.numBinsSetter(numBins);
    uniformSampler.sample();
    uniformSampler.summaryCalculator();
    uniformSampler.marDisPlotter();

    return 0;
}