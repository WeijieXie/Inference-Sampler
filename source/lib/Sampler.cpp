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

template <typename REAL>
REAL Sampler<REAL>::likelihood(const std::vector<REAL> &paras)
{
    std::vector<REAL> inputs = observation.inputs;
    std::vector<REAL> outputs = observation.outputs;
    std::vector<REAL> sigmas = observation.sigmas;
    auto it_inputs = inputs.begin();
    auto it_outputs = outputs.begin();
    auto it_sigmas = sigmas.begin();
    REAL pred = 0;
    REAL L = 0;
    REAL Li = 0;
    REAL err = 0;
    while (it_inputs != inputs.end() && it_outputs != outputs.end() && it_sigmas != sigmas.end()) {
        // Perform your operations with *it_inputs, *it_outputs, and *it_sigmas
        pred = modelFunc(*it_inputs,paras);
        err = pred-*it_outputs;
        Li = -(err*err)/(2**it_sigmas**it_sigmas);
        L = L + Li;
        ++it_inputs;
        ++it_outputs;
        ++it_sigmas;
    }
    
    return L;
}
template float Sampler<float>::likelihood(const std::vector<float> &paras);
template double Sampler<double>::likelihood(const std::vector<double> &paras);
