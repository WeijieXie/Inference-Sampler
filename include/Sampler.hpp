#pragma once

#include "Observations.hpp"

#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <iostream>
#include <filesystem>
#include <sstream>

#include <matplot/matplot.h>
using namespace matplot;

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
    std::string name = "UniformSampler";

    Observations<REAL> observations;
    std::vector<ParamInfo<REAL>> paraInfo;
    std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc;
    int numParas;
    int numBins = 100;

    std::vector<REAL> paraMins;
    std::vector<REAL> binWidths;

    std::vector<std::vector<REAL>> sampledChain;
    std::vector<std::vector<REAL>> marDis;
    std::vector<std::vector<REAL>> paraVals;
    // std::function<REAL(REAL, std::vector<REAL>&)> : modelFunc(std::move(f)){};

    std::vector<REAL> peaks;
    std::vector<REAL> means;
    std::vector<REAL> stdDevs;

    REAL likelihood(const std::vector<REAL> &paras);

public:
    Sampler() = default;
    Sampler(std::string filePath, std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numBins = 100);
    ~Sampler(){};

    void paraInfoSetter(std::string name, REAL min, REAL max);
    void modelFuncSetter(std::function<REAL(REAL x, const std::vector<REAL> &)> paras);
    void numBinsSetter(int numBins);
    std::vector<std::vector<REAL>> sampledChainGetter();
    std::vector<std::vector<REAL>> marDisGetter();

    std::vector<REAL> peaksGetter();
    std::vector<REAL> meansGetter();
    std::vector<REAL> stdDevsGetter();

    void summaryCalculator();
    void marDisPlotter(int maxSamples = 0);

    virtual void sample() = 0;
};
