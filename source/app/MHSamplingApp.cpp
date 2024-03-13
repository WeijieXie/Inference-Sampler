#include "UniformSampler.hpp"
#include "MHSampler.hpp"
#include <memory>

template <typename REAL>
std::unique_ptr<Sampler<REAL>> createSampler(int maxNumSample, std::string filePath, std::function<REAL(REAL, const std::vector<REAL>&)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numBins) {
    int uniformNumSample = pow(numBins,paraInfo.size());
    if (uniformNumSample>maxNumSample) {
        std::cout<<"MHSampler created..."<<std::endl;
        return std::make_unique<MHSampler<REAL>>(filePath, modelFunc, paraInfo,maxNumSample,0.01);
    } else  {
        std::cout<<"UniformSampler created..."<<std::endl;
        return std::make_unique<UniformSampler<REAL>>(filePath, modelFunc, paraInfo);
    }
}

int main(int argc, char *argv[])
{
    std::function<double(double, const std::vector<double> &)> modelFunc = [](double x, const std::vector<double> &params) -> double
    {
        double result = params[0] * x*x*x + params[1] * x*x+ params[2] * x+ params[3]; // Example implementation
        return result;
    };
    const ParamInfo<double> paraInfo1=ParamInfo<double>(-3,3,"a");
    const ParamInfo<double> paraInfo2=ParamInfo<double>(-3,3,"b");
    const ParamInfo<double> paraInfo3=ParamInfo<double>(-3,3,"c");
    const ParamInfo<double> paraInfo4=ParamInfo<double>(-3,3,"d");
    const std::vector<ParamInfo<double>> paraVec_4d = {paraInfo1,paraInfo2,paraInfo3,paraInfo4};

    std::string filePath;
    int numBins=100;
    int maxNumSample=100;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h")
        {
            std::cout << "Usage: -f <file_path> -n <number_of_bins> -s <maximum_number_of_samples>" << std::endl;
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
        else if (arg == "-s" && i + 1 < argc)
        {
            maxNumSample = std::stoi(argv[++i]);
        }
        else
        {
            std::cout << "Unknown or incomplete argument: " << arg << std::endl;
            return 1;
        }
    }
    auto sampler =createSampler(maxNumSample,filePath,modelFunc,paraVec_4d,numBins);
    sampler->numBinsSetter(numBins);
    sampler->sample();
    sampler->summaryCalculator();

    return 0;
}