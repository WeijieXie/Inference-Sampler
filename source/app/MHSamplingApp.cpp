#include "MHSampler.hpp"

int main(int argc, char *argv[])
{
    std::function<double(double, const std::vector<double> &)> modelFunc = [](double x, const std::vector<double> &params) -> double
    {
        double result = params[0] * pow(x,params[1]); // Example implementation
        return result;
    };
    const ParamInfo<double> paraInfo1=ParamInfo<double>(0,5,"a");
    const ParamInfo<double> paraInfo2=ParamInfo<double>(0,5,"b");
    const std::vector<ParamInfo<double>> paraVec_2d = {paraInfo1,paraInfo2};

    std::string filePath;
    int numBins=100;
    int maxNumSample;

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
    std::unique_ptr<Sampler<double>> sampler = createSampler(maxNumSample,filePath,modelFunc,paraInfo,numBins);
    sampler.numBinsSetter(numBins);

    sampler.sample();
    sampler.summaryCalculator();

    return 0;
}

template <typename REAL>
std::unique_ptr<Sampler<REAL>> createSampler(int maxNumSample, std::string filePath, std::function<REAL(REAL, const std::vector<REAL>&)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numBins = 100) {
    int uniformNumSample = pow(numBins,paraInfo.size());
    if (uniformNumSample>maxNumSample) {
        std::cout<<"MHSampler created..."<<std::endl;
        return std::make_unique<MHSampler<REAL>>(filePath, modelFunc, paraInfo, numBins,maxNumSample,0.01);
    } else  {
        std::cout<<"UniformSampler created..."<<std::endl;
        return std::make_unique<UniformSampler<REAL>>(filePath, modelFunc, paraInfo);
    }
}