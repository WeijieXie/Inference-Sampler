#include "MHSampler.hpp"

template <typename REAL>
MHSampler<REAL>::MHSampler(std::string filePath, std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numBins, int numPoints, REAL stepSize) : Sampler<REAL>(filePath, modelFunc, paraInfo,numBins)
{
    this->numPoints = numPoints;
    this->stepSize = stepSize;
}

template MHSampler<float>::MHSampler(std::string filePath, std::function<float(float, const std::vector<float> &)> modelFunc, std::vector<ParamInfo<float>> paraInfo, int numBins, int numPoints, float stepSize);
template MHSampler<double>::MHSampler(std::string filePath, std::function<double(double, const std::vector<double> &)> modelFunc, std::vector<ParamInfo<double>> paraInfo, int numBins, int numPoints, double stepSize);
