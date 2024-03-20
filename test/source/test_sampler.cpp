#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <stdexcept>
#include <iostream>

#include "data.h"
#include "Observations.hpp"
#include "UniformSampler.hpp"
#include "MHSampler.hpp"
using namespace Catch::Matchers;
template <typename REAL>
void checkFileContents(Observations<REAL> &obs)
{
    REQUIRE(obs.inputs.size() == 3);
    REQUIRE(obs.outputs.size() == 3);
    REQUIRE(obs.sigmas.size() == 3);
    REQUIRE_THAT(obs.inputs[0], WithinRel(0.94907, 0.0001));
    REQUIRE_THAT(obs.inputs[1], WithinRel(0.49062, 0.0001));
    REQUIRE_THAT(obs.inputs[2], WithinRel(0.98349, 0.0001));
    REQUIRE_THAT(obs.outputs[0], WithinRel(0.97454, 0.0001));
    REQUIRE_THAT(obs.outputs[1], WithinRel(0.74531, 0.0001));
    REQUIRE_THAT(obs.outputs[2], WithinRel(0.99174, 0.0001));
    for (auto sig : obs.sigmas)
    {
        REQUIRE_THAT(sig, WithinRel(1.0, 0.0001));
    }
}
TEST_CASE("Test file reader (double)", "[File Read]")
{
    Observations<double> obs;
    obs.loadData("test/test_data/testing_data_2D.txt");
    checkFileContents(obs);
}
TEST_CASE("Test file reader (exceptions)", "[File Read]")
{
    Observations<double> obs_double;
    REQUIRE_THROWS_AS(obs_double.loadData("test/test_data/loading_data_exception.txt"), std::invalid_argument);
}
TEST_CASE("Test UniformSampler constructor", "[Constructor]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    UniformSampler<double> uniformSamplerA(filePath, test_data::modelFunc, test_data::paraVec_2d);
    REQUIRE(uniformSamplerA.marDisGetter().size() == 2);
    REQUIRE(uniformSamplerA.marDisGetter()[0].size() == 100);

    UniformSampler<double> uniformSamplerB(filePath, test_data::modelFunc, test_data::paraVec_3d, 13);
    REQUIRE(uniformSamplerB.marDisGetter().size() == 3);
    REQUIRE(uniformSamplerB.marDisGetter()[0].size() == 13);
}
TEST_CASE("Test UniformSampler constructor (exceptions)", "[Constructor]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    REQUIRE_THROWS_AS(UniformSampler<double>(filePath, test_data::modelFunc, test_data::paraVec_2d, 0), std::domain_error);

    std::string filePathE("test/test_data/loading_data_exception.txt");
    REQUIRE_THROWS_AS(UniformSampler<double>(filePathE, test_data::modelFunc, test_data::paraVec_2d, 10), std::invalid_argument);
}
TEST_CASE("Test sample points 2D", "[Data Process]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    UniformSampler<double> uniformSampler(filePath, test_data::modelFunc, test_data::paraVec_2d);
    uniformSampler.numBinsSetter(3);
    uniformSampler.sample();
    std::vector<std::vector<double>> mat = uniformSampler.sampledChainGetter();
    REQUIRE(mat.size() == test_data::sample_points_2d.size());
    REQUIRE(mat[0].size() == test_data::sample_points_2d[0].size() + 1);
    // std::cout<<uniformSampler.sampledChainGetter().size()<<std::endl;
    // std::vector<std::vector<double>> mat_t = {{1,2,3},{4,5,6},{7,8,9}};
    double val = 0;
    for (int i = 0; i < int(mat.size()); i++)
    {
        for (int j = 0; j < int(test_data::sample_points_2d[0].size()); j++)
        {
            val = test_data::sample_points_2d[i][j];
            REQUIRE_THAT(mat[i][j], WithinRel(val, 0.0001));
        }
    }
}

TEST_CASE("Test sample points 3D", "[Data Process]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    UniformSampler<double> uniformSampler(filePath, test_data::modelFunc, test_data::paraVec_3d);
    uniformSampler.numBinsSetter(3);
    uniformSampler.sample();
    std::vector<std::vector<double>> mat = uniformSampler.sampledChainGetter();
    REQUIRE(mat.size() == test_data::sample_points_3d.size());
    REQUIRE(mat[0].size() == test_data::sample_points_3d[0].size() + 1);
    double val = 0;
    for (int i = 0; i < int(mat.size()); i++)
    {
        for (int j = 0; j < int(test_data::sample_points_3d[0].size()); j++)
        {
            val = test_data::sample_points_3d[i][j];
            REQUIRE_THAT(mat[i][j], WithinRel(val, 0.0001));
        }
    }
}

TEST_CASE("Test likelihood 2D", "[Data Process]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    UniformSampler<double> uniformSampler(filePath, test_data::modelFunc, test_data::paraVec_2d);
    uniformSampler.numBinsSetter(3);
    uniformSampler.sample();
    std::vector<std::vector<double>> mat = uniformSampler.sampledChainGetter();

    double likeliHood = 0;
    double val = 0;

    for (int i = 0; i < int(mat.size()); i++)
    {
        likeliHood = std::exp(mat[i].back());
        val = test_data::sample_likelihoods[i];
        REQUIRE_THAT(likeliHood, WithinRel(val, 0.01));
    }
}
TEST_CASE("Test Marginal Distribution 2D", "[Data Process]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    UniformSampler<double> uniformSampler(filePath, test_data::modelFunc, test_data::paraVec_2d);
    uniformSampler.numBinsSetter(3);
    uniformSampler.sample();
    std::vector<std::vector<double>> mat = uniformSampler.marDisGetter();
    REQUIRE(mat.size() == test_data::marginal_distribution_2d.size());
    REQUIRE(mat[0].size() == test_data::marginal_distribution_2d[0].size());

    double val = 0;

    for (int i = 0; i < int(mat.size()); i++)
    {
        for (int j = 0; j < int(mat[0].size()); j++)
        {
            val = test_data::marginal_distribution_2d[i][j];
            REQUIRE_THAT(mat[i][j], WithinRel(val, 0.0001));
        }
    }
}

TEST_CASE("Test Summary Calculator", "[Data Process]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    std::function<double(double, const std::vector<double> &)> modelFunc = [](double x, const std::vector<double> &params) -> double
    {
        double result = params[0] * params[1] * x; // Example implementation
        return result;
    };
    UniformSampler<double> uniformSampler(filePath, modelFunc, test_data::paraVec_2d);
    uniformSampler.numBinsSetter(3);
    // uniformSampler.sample();
    // uniformSampler.summaryCalculator();

    std::vector<double> paraPeaks;
    std::vector<double> paraMeans;
    std::vector<double> paraStdDevs;
    paraPeaks = uniformSampler.peaksGetter();
    paraMeans = uniformSampler.meansGetter();
    paraStdDevs = uniformSampler.stdDevsGetter();
    // REQUIRE(paraPeaks[0] == paraPeaks[1]);
    // REQUIRE(paraMeans[0] == paraMeans[1]);
    // REQUIRE(paraStdDevs[0] == paraStdDevs[1]);
}

TEST_CASE("Test MHSampler (2 paras)", "[Data Process]")
{
    std::string filePath("data/problem_data_4D.txt");
    std::function<double(double, const std::vector<double> &)> modelFunc = [](double x, const std::vector<double> &params) -> double
    {
        // double result = params[0] * (1 / x) - params[1] * x; // Example implementation
        double result = params[0] * x*x + params[1] * x+ params[2];
        return result;
    };

    const ParamInfo<double> paraInfo1 = ParamInfo<double>(0, 5, "a");
    const ParamInfo<double> paraInfo2 = ParamInfo<double>(0, 5, "b");
    const ParamInfo<double> paraInfo3 = ParamInfo<double>(0, 5, "c");
    const std::vector<ParamInfo<double>> paraVec_3d = {paraInfo1, paraInfo2,paraInfo3};

    // UniformSampler<double> uniformSampler(filePath, modelFunc, paraVec_2d);
    // uniformSampler.numBinsSetter(3);
    // uniformSampler.sample();
    // uniformSampler.summaryCalculator();

    MHSampler<double> mhSampler(filePath, modelFunc, paraVec_3d);
    mhSampler.numBinsSetter(500);
    mhSampler.sample();
    mhSampler.summaryCalculator();
    mhSampler.marDisPlotter(200);

    // REQUIRE(mhSampler.peaksGetter().size() == uniformSampler.peaksGetter().size());

    // for (int i = 0; i < int(mhSampler.peaksGetter().size()); i++)
    // {
    //     REQUIRE(mhSampler.peaksGetter()[i] == uniformSampler.peaksGetter()[i]);
    // }
}

// TEST_CASE("Test MHSampler (4 paras)", "[Data Process]")
// {
//     std::string filePath("test/test_data/testing_data_2D.txt");
//     std::function<double(double, const std::vector<double> &)> modelFunc = [](double x, const std::vector<double> &params) -> double
//     {
//         double result = params[0] * x * x * x + params[1] * x * x + params[2] * x + params[3];
//         return result;
//     };

//     const ParamInfo<double> paraInfo1 = ParamInfo<double>(-3, 3, "a");
//     const ParamInfo<double> paraInfo2 = ParamInfo<double>(-3, 3, "b");
//     const ParamInfo<double> paraInfo3 = ParamInfo<double>(-3, 3, "c");
//     const ParamInfo<double> paraInfo4 = ParamInfo<double>(-3, 3, "d");
//     const std::vector<ParamInfo<double>> paraVec_4d = {paraInfo1, paraInfo2, paraInfo3, paraInfo4};

//     UniformSampler<double> uniformSampler(filePath, modelFunc, paraVec_4d);
//     uniformSampler.numBinsSetter(3);
//     uniformSampler.sample();
//     uniformSampler.summaryCalculator();

//     MHSampler<double> mhSampler(filePath, modelFunc, paraVec_4d);
//     mhSampler.numBinsSetter(3);
//     mhSampler.sample();
//     mhSampler.summaryCalculator();

//     REQUIRE(mhSampler.peaksGetter().size() == uniformSampler.peaksGetter().size());

//     for (int i = 0; i < int(mhSampler.peaksGetter().size()); i++)
//     {
//         REQUIRE(mhSampler.peaksGetter()[i] == uniformSampler.peaksGetter()[i]);
//     }
// }