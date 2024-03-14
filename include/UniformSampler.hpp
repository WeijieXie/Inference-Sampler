#pragma once

#include "Sampler.hpp"

template <typename REAL>
class UniformSampler:public Sampler<REAL>
{
public:
    UniformSampler(std::string filePath,std::function<REAL(REAL, const std::vector<REAL>&)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo,int numBins=100):Sampler<REAL>(filePath,modelFunc, paraInfo,numBins){}
    UniformSampler():Sampler<REAL>(){}
    void sample();
};