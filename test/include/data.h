#pragma once 

#include "Sampler.hpp"
#include <vector>

class test_data
{
public:
    static const std::vector<double> sample_likelihoods;

    static const std::vector<std::vector<double>> sample_points_2d;

    static const std::vector<std::vector<double>> sample_points_3d;

    static const std::vector<std::vector<double>> marginal_distribution_2d;

    static const std::function<double(double, const std::vector<double>&)> modelFunc;

    static const ParamInfo<double> paraInfo1;
    static const ParamInfo<double> paraInfo2;
    static const ParamInfo<double> paraInfo3;

    static const std::vector<ParamInfo<double>> paraVec_2d;

    static const std::vector<ParamInfo<double>> paraVec_3d;

    // static UniformSampler<double> uniformSampler;

};