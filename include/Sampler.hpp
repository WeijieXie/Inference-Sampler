#pragma once

#include "Observations.hpp"

#include <vector>
#include <string>
#include <functional>
/**
 * @brief Class for holding / passing information about parameters to be sampled
 *
 * @tparam REAL: type representing real numbers; usually float or double.
 */
template <typename REAL>
class ParamInfo
{
public:
    ParamInfo() = default;
    ParamInfo(REAL min, REAL max, std::string name) : min(min), max(max), name(name)
    {
        width = max - min;
    }
    REAL min = 0;
    REAL max = 1;
    REAL width = max - min;
    std::string name;
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
template <typename REAL>
class Sampler
{
protected:
    Observations<REAL> observation;
    std::vector<ParamInfo<REAL>> paraInfo;
    std::vector<REAL> sampledChain;
    std::function<REAL(REAL, const std::vector<REAL>&)> modelFunc;
    int numBins = 100;
    // std::function<REAL(REAL, std::vector<REAL>&)> : modelFunc(std::move(f)){};
public:
    Sampler() = default;
    Sampler(std::string filePath,std::function<REAL(REAL, const std::vector<REAL>&)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo);
    ~Sampler(){};

    virtual void sample() = 0;
    void paraInfoSetter(std::string name, REAL min, REAL max);
    void modelFuncSetter(std::function<REAL(REAL x, const std::vector<REAL>&)> paras);
    REAL likelihood(const std::vector<REAL>& paras);
};
