#include "data.h"

const std::vector<double> test_data::sample_likelihoods = {0.575187, 0.846482, 0.985531, 0.889452, 1, 0.889452, 0.985531, 0.846482, 0.575187};

const std::vector<std::vector<double>> test_data::sample_points_2d = {{1.0/6, 1.0/6}, {0.5, 1.0/6}, {5.0/6, 1.0/6},
                                                                      {1.0/6, 0.5}, {0.5, 0.5}, {5.0/6, 0.5},
                                                                      {1.0/6, 5.0/6}, {0.5, 5.0/6}, {5.0/6, 5.0/6}};

const std::vector<std::vector<double>> test_data::sample_points_3d = {{1.0/6, 1.0/6,1.0/6}, {0.5, 1.0/6,1.0/6}, {5.0/6, 1.0/6,1.0/6},
                                                                      {1.0/6, 0.5,1.0/6}, {0.5, 0.5,1.0/6}, {5.0/6, 0.5,1.0/6},
                                                                      {1.0/6, 5.0/6,1.0/6}, {0.5, 5.0/6,1.0/6}, {5.0/6, 5.0/6,1.0/6},
                                                                      {1.0/6, 1.0/6, 0.5}, {0.5, 1.0/6, 0.5}, {5.0/6, 1.0/6, 0.5},
                                                                      {1.0/6, 0.5, 0.5}, {0.5, 0.5, 0.5}, {5.0/6, 0.5, 0.5},
                                                                      {1.0/6, 5.0/6, 0.5}, {0.5, 5.0/6, 0.5}, {5.0/6, 5.0/6, 0.5},
                                                                      {1.0/6, 1.0/6, 5.0/6}, {0.5, 1.0/6, 5.0/6}, {5.0/6, 1.0/6, 5.0/6},
                                                                      {1.0/6, 0.5, 5.0/6}, {0.5, 0.5, 5.0/6}, {5.0/6, 0.5, 5.0/6},
                                                                      {1.0/6, 5.0/6, 5.0/6}, {0.5, 5.0/6, 5.0/6}, {5.0/6, 5.0/6, 5.0/6}};

const std::vector<std::vector<double>> test_data::marginal_distribution_2d = {{(0.575187+0.889452+0.985531)/(0.575187+0.889452+0.985531+0.846482+1+0.846482+0.985531+0.889452+0.575187),(0.846482+1+0.846482)/(0.575187+0.889452+0.985531+0.846482+1+0.846482+0.985531+0.889452+0.575187),(0.985531+0.889452+0.575187)/(0.575187+0.889452+0.985531+0.846482+1+0.846482+0.985531+0.889452+0.575187)},
                                                                              {(0.575187+0.846482+0.985531)/(0.575187+0.846482+0.985531+0.889452+1+0.889452+0.985531+0.846482+0.575187),(0.889452+1+0.889452)/(0.575187+0.846482+0.985531+0.889452+1+0.889452+0.985531+0.846482+0.575187),(0.985531+0.846482+0.575187)/(0.575187+0.846482+0.985531+0.889452+1+0.889452+0.985531+0.846482+0.575187)}};

const std::function<double(double, const std::vector<double>&)> test_data::modelFunc = [](double x, const std::vector<double>& params) -> double {
                                                                                        double result =  params[0]*x + params[1]; // Example implementation
                                                                                        return result;
                                                                                    };

const ParamInfo<double> test_data::paraInfo1=ParamInfo<double>(0,1,"para1");
const ParamInfo<double> test_data::paraInfo2=ParamInfo<double>(0,1,"para2");
const ParamInfo<double> test_data::paraInfo3=ParamInfo<double>(0,1,"para3");

const std::vector<ParamInfo<double>> test_data::paraVec_2d = {paraInfo1,paraInfo2};
const std::vector<ParamInfo<double>> test_data::paraVec_3d = {paraInfo1,paraInfo2,paraInfo3};