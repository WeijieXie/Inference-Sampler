#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>
#include <stdexcept>
#include <iostream>

#include "data.h"
#include "Observations.hpp"
#include "UniformSampler.hpp"
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
// TEST_CASE("Test file reader (double)", "[File Read]")
// {
//     Observations<double> obs;
//     obs.loadData("test/test_data/testing_data_2D.txt");
//     checkFileContents(obs);
// }
TEST_CASE("Test file reader (not a number)", "[File Read]")
{
    Observations<double> obs_double;
    REQUIRE_THROWS_AS(obs_double.loadData("test/test_data/loading_data_exception.txt"), std::invalid_argument);
    // Observations<double> obs_double;
    // REQUIRE_THROWS_AS(obs_double.loadData("test/test_data/loading_data_exception.txt"),std::invalid_argument);
}
// TEST_CASE("Test constructor", "[Data Process]")
// {
//     Observations<double> obs_double;
//     REQUIRE_THROWS_AS(obs_double.loadData("test/test_data/loading_data_exception.txt"),std::invalid_argument);
//     // Observations<double> obs_double;
//     // REQUIRE_THROWS_AS(obs_double.loadData("test/test_data/loading_data_exception.txt"),std::invalid_argument);
// }
// TEST_CASE("Test setters and getters", "[Data Process]")
// {
//     Observations<double> obs_double;
//     REQUIRE_THROWS_AS(obs_double.loadData("test/test_data/loading_data_exception.txt"),std::invalid_argument);
//     // Observations<double> obs_double;
//     // REQUIRE_THROWS_AS(obs_double.loadData("test/test_data/loading_data_exception.txt"),std::invalid_argument);
// }
TEST_CASE("Test sample points 2D", "[Data Process]")
{
    // std::vector<double> params = {1.0, 2.0, 3.0};
    // double x = 5.0;

    // std::function<double(double, const std::vector<double>&)> modelFunc;
    // modelFunc = [](double x, const std::vector<double>& params) -> double {
    //     double result =  params[0]*x + params[1]; // Example implementation
    //     return result;
    // };

    // std::vector<ParamInfo<double>> paraVec;
    // ParamInfo<double> paraInfo1(0,1,"para1");
    // ParamInfo<double> paraInfo2(0,1,"para2");
    // paraVec.push_back(paraInfo1);
    // paraVec.push_back(paraInfo2);

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
    // for (const auto &row : mat) {
    //     for (double val : row) {
    //         // REQUIRE_THAT(obs.outputs[0], WithinRel(0.97454, 0.0001));

    //         std::cout << val << " ";
    //     }
    //     std::cout << '\n';
    // }
    // std::cout<<uniformSampler.sampledChainGetter()<<std::endl;
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
    // std::cout<<uniformSampler.sampledChainGetter().size()<<std::endl;
    // std::vector<std::vector<double>> mat_t = {{1,2,3},{4,5,6},{7,8,9}};
    double val = 0;
    for (int i = 0; i < int(mat.size()); i++)
    {
        for (int j = 0; j < int(test_data::sample_points_3d[0].size()); j++)
        {
            val = test_data::sample_points_3d[i][j];
            REQUIRE_THAT(mat[i][j], WithinRel(val, 0.0001));
        }
    }
    // std::cout<<uniformSampler.sampledChainGetter()<<std::endl;
}

TEST_CASE("Test likelihood 2D", "[Data Process]")
{
    // std::vector<double> params = {1.0, 2.0, 3.0};
    // double x = 5.0;

    // std::function<double(double, const std::vector<double>&)> modelFunc;
    // modelFunc = [](double x, const std::vector<double>& params) -> double {
    //     double result =  params[0]*x + params[1]; // Example implementation
    //     return result;
    // };

    // std::vector<ParamInfo<double>> paraVec;
    // ParamInfo<double> paraInfo1(0,1,"para1");
    // ParamInfo<double> paraInfo2(0,1,"para2");
    // paraVec.push_back(paraInfo1);
    // paraVec.push_back(paraInfo2);

    std::string filePath("test/test_data/testing_data_2D.txt");
    UniformSampler<double> uniformSampler(filePath, test_data::modelFunc, test_data::paraVec_2d);
    uniformSampler.numBinsSetter(3);
    uniformSampler.sample();
    std::vector<std::vector<double>> mat = uniformSampler.sampledChainGetter();
    // std::cout<<uniformSampler.sampledChainGetter().size()<<std::endl;
    // std::vector<std::vector<double>> mat_t = {{1,2,3},{4,5,6},{7,8,9}};

    double likeliHood = 0;
    double val = 0;

    // std::cout<<std::endl;
    for (int i = 0; i < int(mat.size()); i++)
    {
        likeliHood = std::exp(mat[i].back());
        val = test_data::sample_likelihoods[i];
        REQUIRE_THAT(likeliHood, WithinRel(val, 0.01));
        // std::cout << std::exp(mat[i].back()) << " ";
    }
    // std::cout<<std::endl;
    // for (double val : test_data::sample_likelihoods) {
    //     // REQUIRE_THAT(obs.outputs[0], WithinRel(0.97454, 0.0001));
    //     std::cout << val << " ";
    // }
    // for (const auto &row : mat) {
    //     for (double val : row) {
    //         // REQUIRE_THAT(obs.outputs[0], WithinRel(0.97454, 0.0001));

    //         std::cout << val << " ";
    //     }
    //     std::cout << '\n';
    // }
    // std::cout<<uniformSampler.sampledChainGetter()<<std::endl;
}
TEST_CASE("Test Marginal Distribution 2D", "[Data Process]")
{
    std::string filePath("test/test_data/testing_data_2D.txt");
    UniformSampler<double> uniformSampler(filePath, test_data::modelFunc, test_data::paraVec_2d);
    uniformSampler.numBinsSetter(3);
    uniformSampler.sample();
    std::vector<std::vector<double>> mat = uniformSampler.marDisGetter();
    // std::cout << mat.size() << std::endl;
    REQUIRE(mat.size() == test_data::marginal_distribution_2d.size());
    REQUIRE(mat[0].size() == test_data::marginal_distribution_2d[0].size());

    double val = 0;

    // std::cout<<std::endl;
    for (int i = 0; i < int(mat.size()); i++)
    {
        for (int j = 0; j < int(mat[0].size()); j++)
        {
            val = test_data::marginal_distribution_2d[i][j];
            REQUIRE_THAT(mat[i][j], WithinRel(val, 0.0001));
        }
    }
    // std::cout<<std::endl;
    // for (double val : test_data::sample_likelihoods) {
    //     // REQUIRE_THAT(obs.outputs[0], WithinRel(0.97454, 0.0001));
    //     std::cout << val << " ";
    // }
    // for (const auto &row : mat) {
    //     for (double val : row) {
    //         // REQUIRE_THAT(obs.outputs[0], WithinRel(0.97454, 0.0001));

    //         std::cout << val << " ";
    //     }
    //     std::cout << '\n';
    // }
    // std::cout<<uniformSampler.sampledChainGetter()<<std::endl;
}
