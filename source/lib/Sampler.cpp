#include "Sampler.hpp"
template <typename REAL>
Sampler<REAL>::Sampler(std::string filePath, std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numBins)
{
    Observations<REAL> observations;
    this->observations = observations;
    this->observations.loadData(filePath);

    this->modelFunc = modelFunc;

    this->paraInfo = paraInfo;
    this->numParas = paraInfo.size();

    if (numBins <= 0)
        throw std::domain_error("number of bins should be positive, instead of" + numBins);
    this->numBins = numBins;

    this->marDis = std::vector<std::vector<REAL>>(paraInfo.size(), std::vector<REAL>(numBins));
    this->paraVals = std::vector<std::vector<REAL>>(paraInfo.size(), std::vector<REAL>(numBins));

    this->peaks = std::vector<REAL>(this->numParas);
    this->means = std::vector<REAL>(this->numParas);
    this->stdDevs = std::vector<REAL>(this->numParas);
}
template Sampler<float>::Sampler(std::string filePath, std::function<float(float, const std::vector<float> &)> modelFunc, std::vector<ParamInfo<float>> paraInfo, int numBins);
template Sampler<double>::Sampler(std::string filePath, std::function<double(double, const std::vector<double> &)> modelFunc, std::vector<ParamInfo<double>> paraInfo, int numBins);

template <typename REAL>
void Sampler<REAL>::paraInfoSetter(std::string name, REAL min, REAL max)
{
    paraInfo.push_back(ParamInfo(min, max, name));
    this->marDis = std::vector<std::vector<REAL>>(paraInfo.size(), std::vector<REAL>(numBins));
    this->paraVals = std::vector<std::vector<REAL>>(paraInfo.size(), std::vector<REAL>(numBins));
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
void Sampler<REAL>::numBinsSetter(int numBins)
{
    this->numBins = numBins;
    this->marDis = std::vector<std::vector<REAL>>(paraInfo.size(), std::vector<REAL>(numBins));
    this->paraVals = std::vector<std::vector<REAL>>(paraInfo.size(), std::vector<REAL>(numBins));
}
template void Sampler<float>::numBinsSetter(int numBins);
template void Sampler<double>::numBinsSetter(int numBins);

template <typename REAL>
std::vector<std::vector<REAL>> Sampler<REAL>::sampledChainGetter()
{
    return this->sampledChain;
}
template std::vector<std::vector<float>> Sampler<float>::sampledChainGetter();
template std::vector<std::vector<double>> Sampler<double>::sampledChainGetter();

template <typename REAL>
std::vector<std::vector<REAL>> Sampler<REAL>::marDisGetter()
{
    return this->marDis;
}
template std::vector<std::vector<float>> Sampler<float>::marDisGetter();
template std::vector<std::vector<double>> Sampler<double>::marDisGetter();

template <typename REAL>
std::vector<REAL> Sampler<REAL>::peaksGetter()
{
    return this->peaks;
}
template std::vector<float> Sampler<float>::peaksGetter();
template std::vector<double> Sampler<double>::peaksGetter();

template <typename REAL>
std::vector<REAL> Sampler<REAL>::meansGetter()
{
    return this->means;
}
template std::vector<float> Sampler<float>::meansGetter();
template std::vector<double> Sampler<double>::meansGetter();

template <typename REAL>
std::vector<REAL> Sampler<REAL>::stdDevsGetter()
{
    return this->stdDevs;
}
template std::vector<float> Sampler<float>::stdDevsGetter();
template std::vector<double> Sampler<double>::stdDevsGetter();

template <typename REAL>
REAL Sampler<REAL>::likelihood(const std::vector<REAL> &paras)
{
    std::vector<REAL> inputs = observations.inputs;
    std::vector<REAL> outputs = observations.outputs;
    std::vector<REAL> sigmas = observations.sigmas;
    auto it_inputs = inputs.begin();
    auto it_outputs = outputs.begin();
    auto it_sigmas = sigmas.begin();
    REAL pred = 0;
    REAL L = 0;
    REAL Li = 0;
    REAL err = 0;
    while (it_inputs != inputs.end() && it_outputs != outputs.end() && it_sigmas != sigmas.end())
    {
        pred = modelFunc(*it_inputs, paras);
        err = pred - *it_outputs;
        Li = -(err * err) / (2 * *it_sigmas * *it_sigmas);
        L = L + Li;
        ++it_inputs;
        ++it_outputs;
        ++it_sigmas;
    }

    return L;
}
template float Sampler<float>::likelihood(const std::vector<float> &paras);
template double Sampler<double>::likelihood(const std::vector<double> &paras);

template <typename REAL>
void Sampler<REAL>::summaryCalculator()
{
    int numParas = this->numParas;
    int numBins = this->numBins;

    REAL paraMin = 0;
    REAL binWidth = 0;

    REAL marDis = 0;
    REAL maxMarDis = 0;
    REAL paraVal = 0;
    REAL mean = 0;
    REAL stdDev = 0;

    REAL peakParaValue = 0;
    REAL sum = 0;
    REAL sumForDev = 0;

    this->peaks.clear();
    this->means.clear();
    this->stdDevs.clear();

    for (int i = 0; i < numParas; i++)
    {
        sum = 0;
        sumForDev = 0;
        maxMarDis = 0;
        paraMin = this->paraMins.at(i);
        binWidth = this->binWidths.at(i);
        for (int j = 0; j < numBins; j++)
        {
            marDis = this->marDis[i][j];

            // update the paraVal (the mid of the bin) to facilitate the following marDisPlotter
            paraVal = paraMin + (j + 0.5) * binWidth;
            this->paraVals[i][j] = paraVal;

            sum += marDis * paraVal;
            sumForDev += marDis * paraVal * paraVal;

            // find the best value of the para
            if (marDis > maxMarDis)
            {
                maxMarDis = marDis;
                peakParaValue = paraVal;
            }
        }

        mean = sum / numBins;
        stdDev = sqrt(sumForDev - pow(mean, 2));

        this->peaks.push_back(peakParaValue);
        this->means.push_back(mean);
        this->stdDevs.push_back(stdDev);

        std::cout << "For parameter"
                  << "\"" << this->paraInfo[i].name << "\": "
                  << "best_value = " << peakParaValue
                  << "; mean = " << mean
                  << "; std_deviation = " << stdDev
                  << std::endl;
    }
}
template void Sampler<float>::summaryCalculator();
template void Sampler<double>::summaryCalculator();

template <typename REAL>
void Sampler<REAL>::marDisPlotter(int maxSamples)
{
    for (int i = 0; i < this->numParas; i++)
    {
        std::vector<REAL> x_values = this->paraVals[i];
        std::vector<REAL> probabilities = this->marDis[i];

        std::string title_str = "para " + this->paraInfo[i].name + ", best value = " + std::to_string(this->peaks[i]) + ", mean = " + std::to_string(this->means[i]) + ", std deviation = " + std::to_string(this->stdDevs[i]);
        std::string x_str = "para value";
        std::string y_str = "Possibility";

        bar(x_values, probabilities);
        title(title_str);
        xlabel(x_str);
        ylabel(y_str);

        std::string maxSamples_str = "";
        if (maxSamples != 0)
        {
            maxSamples_str = "_maxSamples" + std::to_string(maxSamples);
        }

        std::string folder_path_1 = "plots";
        std::string folder_path_2 = this->name + "_numParas" + std::to_string(this->numParas) + "_numbins" + std::to_string(this->numBins) + maxSamples_str;
        std::string full_folder_path = folder_path_1 + "/" + folder_path_2;

        std::string file_name = "distribution_" + this->paraInfo[i].name + ".png";
        std::string full_path = full_folder_path + "/" + file_name;

        if (!std::filesystem::exists(folder_path_1))
        {
            std::filesystem::create_directories(folder_path_1);
        }

        if (!std::filesystem::exists(full_folder_path))
        {
            std::filesystem::create_directories(full_folder_path);
        }

        save(full_path);
        // show();
    }
}
template void Sampler<float>::marDisPlotter(int maxSamples);
template void Sampler<double>::marDisPlotter(int maxSamples);