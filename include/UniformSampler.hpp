#pragma once

#include "Sampler.hpp"

#include <cmath>

template <typename REAL>
class UniformSampler:public Sampler<REAL>
{
public:
    UniformSampler(std::string filePath,std::function<REAL(REAL, const std::vector<REAL>&)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo):Sampler<REAL>(filePath,modelFunc, paraInfo){}
    UniformSampler():Sampler<REAL>(){}
    void sample();
};