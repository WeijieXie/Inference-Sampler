#include "UniformSampler.hpp"

#include <iostream>
#include <string>

template <typename REAL>
void UniformSampler<REAL>::sample()
{
    int numParas = this->paraInfo.size();
    int numSample = pow(this->numBins, numParas);
    int index;

    REAL paraValue;
    REAL likeliHood;

    std::vector<REAL> sample;
    std::vector<int> indexes;
    std::vector<REAL> normSum(numParas);

    this->sampledChain.clear();

    for (auto iter = this->paraInfo.begin(); iter < this->paraInfo.end(); iter++)
    {
        this->paraMins.push_back(iter->min);
        this->binWidths.push_back((iter->max - iter->min) / this->numBins);
    }

    for (int i = 0; i < numSample; i++)
    {
        sample.clear();
        indexes.clear();
        for (int j = 0; j < numParas; j++)
        {
            // Treat the index as the j-th digit of a number in "numBins-base" with "number of parameters" digits,
            // Convert i to this base to update the number, which updates the index
            index = (i % int(pow(this->numBins, j + 1))) / (int(pow(this->numBins, j)));

            paraValue = this->paraMins.at(j) + (index + 0.5) * this->binWidths.at(j); // use the index to get corresponding value of para j

            sample.push_back(paraValue);
            indexes.push_back(index);
        }
        likeliHood = this->likelihood(sample);
        sample.push_back(likeliHood);

        for (int k = 0; k < numParas; k++)
        {
            this->marDis.at(k).at(indexes.at(k)) += std::exp(likeliHood);
            normSum.at(k) += std::exp(likeliHood);
        }

        this->sampledChain.push_back(sample);
    }

    // normalize the marginal distribution
    for (int i = 0; i < numParas; i++)
    {
        for (int j = 0; j < this->numBins; j++)
        {
            this->marDis.at(i).at(j) = this->marDis.at(i).at(j) / normSum.at(i);
        }
    }
}

template void UniformSampler<float>::sample();
template void UniformSampler<double>::sample();