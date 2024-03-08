#include "Sampler.hpp"
template<typename REAL>
Sampler<REAL>::Sampler(std::string filePath,std::function<REAL(REAL, const std::vector<REAL>&)> modelFunc)
{
    Observations<REAL> observation;
    this->observation = observation;
    this->observation.loadData(filePath);
    
    this->modelFunc = modelFunc;
}
template Sampler<float>::Sampler(std::string filePath,std::function<float(float, const std::vector<float>&)> modelFunc);
template Sampler<double>::Sampler(std::string filePath,std::function<double(double, const std::vector<double>&)> modelFunc);

template<typename REAL>
void Sampler<REAL>::paraInfoSetter(std::string name, REAL min, REAL max)
{
    paraInfo.push_back(ParamInfo(min,max,name));
}
template void Sampler<float>::paraInfoSetter(std::string name, float min, float max);
template void Sampler<double>::paraInfoSetter(std::string name, double min, double max);

template <typename REAL>
void Sampler<REAL>::modelFuncSetter(std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc)
{
    this->modelFunc = modelFunc;
}
template void Sampler<float>::modelFuncSetter(std::function<float(float, const std::vector<float> &)> modelFunc);
template void Sampler<double>::modelFuncSetter(std::function<double(double, const std::vector<double> &)> modelFunc);

