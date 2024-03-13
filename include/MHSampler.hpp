#pragma once

#include "Sampler.hpp"

#include <random>

template <typename REAL>
class MHSampler : public Sampler<REAL>
{
protected : 
    int numPoints = 100000;
    REAL stepSize = 0.01;

    std::vector<REAL> paraMaxs;
    std::vector<REAL> paraScales;

public:
    MHSampler(std::string filePath, std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numPoints, REAL stepSize);
    // MHSampler() : Sampler<REAL>(){};
    void sample();
};
