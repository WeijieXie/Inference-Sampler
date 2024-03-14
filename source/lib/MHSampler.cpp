#include "MHSampler.hpp"

template <typename REAL>
MHSampler<REAL>::MHSampler(std::string filePath, std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo, int numPoints, REAL stepSize) : Sampler<REAL>(filePath, modelFunc, paraInfo)
{
    this->name = "MHSampler";
    this->numPoints = numPoints;
    this->stepSize = stepSize;
}
template MHSampler<float>::MHSampler(std::string filePath, std::function<float(float, const std::vector<float> &)> modelFunc, std::vector<ParamInfo<float>> paraInfo, int numPoints, float stepSize);
template MHSampler<double>::MHSampler(std::string filePath, std::function<double(double, const std::vector<double> &)> modelFunc, std::vector<ParamInfo<double>> paraInfo, int numPoints, double stepSize);

template <typename REAL>
MHSampler<REAL>::MHSampler(std::string filePath, std::function<REAL(REAL, const std::vector<REAL> &)> modelFunc, std::vector<ParamInfo<REAL>> paraInfo) : Sampler<REAL>(filePath, modelFunc, paraInfo)
{
    this->name = "MHSampler";
    this->numPoints = 100000;
    this->stepSize = REAL(0.01);
}

template MHSampler<float>::MHSampler(std::string filePath, std::function<float(float, const std::vector<float> &)> modelFunc, std::vector<ParamInfo<float>> paraInfo);
template MHSampler<double>::MHSampler(std::string filePath, std::function<double(double, const std::vector<double> &)> modelFunc, std::vector<ParamInfo<double>> paraInfo);

template <typename REAL>
void MHSampler<REAL>::sample()
{

    for (auto iter = this->paraInfo.begin(); iter < this->paraInfo.end(); iter++)
    {
        this->paraMins.push_back(iter->min);
        this->paraMaxs.push_back(iter->max);
        this->paraScales.push_back(iter->max - iter->min);
        this->binWidths.push_back((iter->max - iter->min) / this->numBins);
    }

    // generate values from different probability distributions
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::normal_distribution<REAL> normalDist(0.0, this->stepSize);
    std::uniform_real_distribution<REAL> uniformDist(0.0, 1.0);

    std::vector<REAL> p(this->numParas);
    std::vector<REAL> pPre(this->numParas);

    std::vector<REAL> v(this->numParas);
    std::vector<REAL> vPre(this->numParas);
    REAL vi = 0;

    REAL intePart = 0.0;
    std::vector<REAL> chainElement;

    chainElement.clear();

    // generate the first sample point
    for (int j = 0; j < this->numParas; j++)
    {
        v.at(j) = uniformDist(eng);
        p.at(j) = this->paraMins.at(j) + v.at(j) * (this->paraScales.at(j));

        // add normalized value to the entry in marginal distribution matrix if the sample lands in the corresponding bin
        this->marDis[j].at(std::floor(v.at(j) / (1 / REAL(this->numBins)))) += 1 / REAL(this->numPoints);

        chainElement.push_back(p[j]); // record the coordinate
    }

    REAL likelihood = this->likelihood(p);
    REAL likelihoodPre = 0;

    // update the sampledChain
    chainElement.push_back(std::exp(likelihood));
    this->sampledChain.push_back(chainElement);

    for (int i = 0; i < this->numPoints - 1; i++)
    {
        // backup the previous point location for that the update may be rejected
        vPre = v;
        pPre = p;
        likelihoodPre = likelihood;

        for (int j = 0; j < this->numParas; j++)
        {
            vi = normalDist(eng);
            if (v.at(j) + vi > 1)
            {
                v.at(j) = std::modf(v.at(j) + vi, &intePart); // take the fraction part if is larger than 1
            }
            else if (v.at(j) + vi < 0)
            {
                v.at(j) = std::modf(v.at(j) + vi, &intePart) + 1; // take (fraction part + 1) if is larger than 1
            }
            else
            {
                v.at(j) += vi;
            }

            p.at(j) = this->paraMins.at(j) + v.at(j) * (this->paraScales.at(j));
        }

        likelihood = this->likelihood(p);

        if (likelihood <= likelihoodPre && likelihood - likelihoodPre <= log(uniformDist(eng)))
        {
            // take the backup value of the previous point when rejected
            v = vPre;
            p = pPre;
            likelihood = likelihoodPre;
        }

        chainElement.clear();
        for (int k = 0; k < this->numParas; k++)
        {
            // add normalized value to the entry in marginal distribution matrix if the sample lands in the corresponding bin
            std::modf(v.at(k) / (1 / REAL(this->numBins)), &intePart);
            this->marDis[k].at(intePart) += 1 / REAL(this->numPoints);

            chainElement.push_back(p[k]);
        }

        // update the sampledChain
        chainElement.push_back(std::exp(likelihood));
        this->sampledChain.push_back(chainElement);
    }
}

template void MHSampler<float>::sample();
template void MHSampler<double>::sample();