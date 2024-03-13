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
void MHSampler<REAL>::sample()
{

    for (auto iter = this->paraInfo.begin(); iter < this->paraInfo.end(); iter++)
    {
        this->paraMins.push_back(iter->min);
        this->paraMaxs.push_back(iter->max);
        this->paraScales.push_back(iter->max - iter->min);
        // std::cout<<"min: "<<iter->min<<std::endl;j
        this->binWidths.push_back((iter->max - iter->min) / this->numBins);
        // std::cout<<"width: "<<width<<std::endl;
    }

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::normal_distribution<REAL> normalDist(0.0, this->stepSize);
    std::uniform_real_distribution<REAL> uniformDist(0.0, 1.0);

    // std::vector<std::vector<REAL>> marDisPre = this->marDis;

    std::vector<REAL> p(this->numParas);
    std::vector<REAL> pPre(this->numParas);

    std::vector<REAL> v(this->numParas);
    std::vector<REAL> vPre(this->numParas);
    REAL vi = 0;

    REAL intePart = 0.0;
    // std::vector<REAL> paraLikelihood;

    for (int j = 0; j < this->numParas; j++)
    {
        v.at(j) = uniformDist(eng);
        p.at(j) = this->paraMins.at(j) + v.at(j) * (this->paraScales.at(j));

        this->marDis[j].at(std::floor(v.at(j) / (1 / REAL(this->numBins)))) += 1 / REAL(this->numPoints);

        // std::cout << v.at(j) << std::endl;
    }

    REAL likelihood = this->likelihood(p);
    REAL likelihoodPre = 0;

    // this->sampledChain.push_back(p);

    for (int i = 0; i < this->numPoints - 1; i++)
    {
        // marDisPre = this->marDis;
        vPre = v;
        pPre = p;
        likelihoodPre = likelihood;
        for (int j = 0; j < this->numParas; j++)
        {
            vi = normalDist(eng);
            if (v.at(j) + vi > 1)
            {
                // p.at(j) = p.at(j) + vi - 1;
                v.at(j) = std::modf(v.at(j) + vi, &intePart);
                // std::cout << v.at(j) << " 1111111111111111" << std::endl;
            }
            else if (v.at(j) + vi < 0)
            {
                v.at(j) = std::modf(v.at(j) + vi, &intePart) + 1;
                // v.at(j) = intePart + 1;
                // std::cout << v.at(j) << " 2222222222222222" << std::endl;
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
            // this->marDis = marDisPre;
            v = vPre;
            p = pPre;
            likelihood = likelihoodPre;
        }

        for (int k = 0; k < this->numParas; k++)
        {
            std::modf(v.at(k) / (1 / REAL(this->numBins)),&intePart);
            // this->marDis[k].at(std::floor(v.at(k) / (1 / REAL(this->numBins)))) += 1 / REAL(this->numPoints);
            this->marDis[k].at(intePart) += 1 / REAL(this->numPoints);
        }

        // paraLikelihood = p;
        // paraLikelihood.push_back(likelihood)
        // this->sampledChain.push_back(p);
    }
}

template void MHSampler<float>::sample();
template void MHSampler<double>::sample();