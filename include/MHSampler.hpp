#pragma once

#include "Sampler.hpp"

template <typename REAL>
class MHSampler : public Sampler<REAL>
{
protected : 
    int numPoints = 100000;
    REAL stepSize = 0.01;

public:
    MHSampler(std::string filePath, std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numBins, int numPoints, REAL stepSize);
    MHSampler() : Sampler<REAL>(){};
    void sample();
};
