#include "GeneticAlgorithm.h"
#include <math.h>

#define DEFAULT_POPULATION_SIZE 10
#define DEFAULT_MUTATION_PROBABILITY 5.0f
#define DEFAULT_SURVIVAL_PERCENTAGE 10.0f
#define DEFAULT_MUTATION_VARIANCE 1.0f
#define DEFAULT_PRINT_FREQUENCY 5

class GenAlg : public GeneticAlgorithm
{
public:
    using GeneticAlgorithm::GeneticAlgorithm;
    void userFitnessFunction(Individual *ind);
};

void GenAlg::userFitnessFunction(Individual *ind)
{
    float len = (float)ind->genome().size();
    float sum = 0;
    for (unsigned int i = 0; i < ind->genome().size(); i++)
    {
        sum += ind->genome().at(i);
    }
    float s = 1.0f - fabs((((100.0f * len) - sum) /
                           (100.0f * len)));
    assert (s < 1);
    ind->setScore(s);
}

int main(int argc, char const *argv[])
{
    GenAlg *ga = new GenAlg(1000, 5, 5, 0.9999f, 20, 100);
    ga->evolvePopulation(0);
    return 0;
}
