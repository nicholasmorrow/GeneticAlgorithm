/************************************************************************
Title:    Base Genetic Algorithm Object
Author:   Nicholas Morrow <nickhudspeth@gmail.com> http://www.nickhudspeth.com
File:     GeneticAlgorithm.cpp
Software: C Standard Libraries
Hardware: Independent
License:  GNU General Public License
Usage:    Refer to the header file GeneticAlgorithm.hpp for a description of the routines.
    See also example test_GeneticAlgorithm.cpp, if available.
LICENSE:
    Copyright (C) 2015 Nicholas Morrow

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

************************************************************************/

/**********************    INCLUDE DIRECTIVES    ***********************/

#include "GeneticAlgorithm.h"


/*********************    CONSTANTS AND MACROS    **********************/
#define DEBUG 1
#define DEFAULT_POPULATION_SIZE 10
#define DEFAULT_MUTATION_PROBABILITY 5.0f
#define DEFAULT_SURVIVAL_PERCENTAGE 10.0f

/***********************    GLOBAL VARIABLES    ************************/


/*******************    FUNCTION IMPLEMENTATIONS    ********************/
using namespace std;
GeneticAlgorithm::GeneticAlgorithm(
    int _population_size ,
    int _mutation_probability,
    int _mutation_variance,
    float _target_fitness,
    int _survival_percentage,
    int _print_frequency)
{
    mutation_probability = _mutation_probability;
    mutation_variance = _mutation_variance;
    target_fitness = _target_fitness;
    survival_percentage = _survival_percentage;
    print_frequency = _print_frequency;
    spawn(1, _population_size);
    #ifndef NDEBUG
    cout << "Created new GeneticAlgorithm object with population size: " <<
         population.size() << endl;
    #endif
}

Individual *GeneticAlgorithm::evolvePopulation(int max_iterations)
{
    time_t start;
    time(&start);
    //float elapsed;
    if (max_iterations == 0) {
        assert(target_fitness > 0);
        while (survivors.back()->score() < target_fitness) {
            spawn(0, 0);
            fitness();
            if (iterations % print_frequency == 0) {printResults(0, start);}
            iterations++;
        }
    }
    else {
        for (int i = 0; i < max_iterations; i++) {
            spawn(0, 0);
            fitness();
            if (iterations % print_frequency == 0) {printResults(0, start);}
            iterations++;
        }
    }
    printResults(1, start);
    return survivors.back();
}

void GeneticAlgorithm::userFitnessFunction(Individual *ind)
{
    /*  GeneticAlgorithm::mutate does not perform range checking on written
        mutation values. Exploit this and kill an individual if its genome
        contains invalid values. */
    cout <<
         "GeneticAlgorithm::userFitnessFunction should be overridden in derived implementation."
         << endl;
}


Individual *GeneticAlgorithm::crossover()
{
    assert(survivors.size() > 0);
    srand(time(NULL));
    static Individual *a = (Individual *) new Individual(rand(), 30);
    static Individual *b = (Individual *) new Individual(rand(), 30);
    Individual *c = (Individual *) new Individual(rand(), 30);
    int index = 0, glen = 0;
    float temp;
    a = survivors.at((int)(rand() % survivors.size()));
    b = survivors.at((int)(rand() % survivors.size()));
    glen = a->genome().size();
    assert(glen == b->genome().size());
    assert(glen > 0);
    int pos = rand() % glen;
    for (int i = 0; i < pos; i++) {
        c->genome().at(i) = a->genome().at(i);
    }
    for (int i = pos; i < glen; i++) {
        c->genome().at(i) = b->genome().at(i);
    }
    return c;
}


void GeneticAlgorithm::fitness()
{
    assert(population.size() > 0);
    assert(survivors.size() > 0);
    /* Populate survivors vector with the fittest candidates*/
    for (int i = 0; i < population.size(); i++) {
        Individual *cand = population.at(i);
        userFitnessFunction(cand);
        for (int j = (survivors.size() - 1); j > -1; j--) {
            if (cand->score() > survivors.at(j)->score()) {
                survivors.at(j) = cand;
                break;
            }
        }
    }
}

void GeneticAlgorithm::mutate(Individual *ind)
{
    srand(time(NULL));
    int glen = ind->genome().size();
    for (int j = 0; j < glen; j++) {
        if ((rand() % 100) < mutation_probability) {
            ind->genome().at(j) += (float)(rand()) / ((float)(RAND_MAX /
                                   mutation_variance));
        }
    }
}


void GeneticAlgorithm::spawn(bool first, int fsize)
{
    int len = 0, surv_size = 0;
    srand(time(NULL));
    /* Initialize population and survivor vectors on first run */
    if (first) {
        for (int i = 0; i < fsize; i++) {
            population.emplace_back(new Individual(rand(), 30));
        }
        surv_size = (int)((float)population.size() * (float)(
                              survival_percentage / 100));
        for (int i = 0; i < surv_size; i++) {
            survivors.emplace_back(new Individual(rand(), 30));
        }
    }
    else {
        assert(survivors.size() > 0);
        surv_size = (int)((float)population.size() * (float)(
                              survival_percentage / 100));
        len = population.size() - survivors.size();
        assert(len > 0);
        population.clear();
        population = survivors;
        for (int i = 0; i < len; i++) {
            Individual *ind = crossover();
            mutate(ind);
            population.emplace_back(ind);
        }
        // for (int i = 0; i < population.size(); i++)
        // {
        //     mutate(population.at(i));
        // }
    }
}
void GeneticAlgorithm::printResults(bool final, time_t start_time)
{
    time_t now;
    time(&now);
    if (final) {cout << "DONE." << endl;}
    cout << "Leading Individual ID: " << survivors.back()->getID() << endl;
    cout << "Leading Individual Score: " << survivors.back()->score() << endl;
    cout << "Number of Trial Iterations: " << iterations << endl;
    cout << "Time Elapsed: " << difftime(now, start_time) << endl;
    int size = survivors.back()->genome().size();
    cout << "Leading Genome: " << endl;
    for (int i = 0; i < size; i ++) {
        cout << survivors.back()->genome().at(i) <<", ";
    }
    cout << " \n" << endl;
}

Individual::Individual(int id, int len)
{
    srand(time(NULL));
    ID = id;
    for (int i = 0; i < len; i++) {
        _genome.push_back((float)(rand() % 100));
    }
}