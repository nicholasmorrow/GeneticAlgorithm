/*************************************************************************
Title:    GeneticAlgorithm.h - Base Genetic Algorithm Object
Author:   Nicholas Morrow <nickhudspeth@gmail.com> http://www.nickhudspeth.com
File:     GeneticAlgorithm.h
Software: C Standard Libraries
Hardware: Independent
License:  GNU General Public License

DESCRIPTION:
    What does this module do? How does it work?

USAGE:
    See Doxygen manual

NOTES:
    None

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

*************************************************************************/

/**********************    INCLUDE DIRECTIVES    ***********************/
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

/**************    CONSTANTS, MACROS, & DATA STRUCTURES    ***************/
#define DEFAULT_POPULATION_SIZE 10
#define DEFAULT_MUTATION_PROBABILITY 5.0f
#define DEFAULT_SURVIVAL_PERCENTAGE 10.0f
#define DEFAULT_MUTATION_VARIANCE 1.0f
#define DEFAULT_PRINT_FREQUENCY 5
#define DEFAULT_GENOME_LENGTH 30

class Individual {
    public:
        Individual(int id = 0, int len = DEFAULT_GENOME_LENGTH);
        ~Individual() {};
        void  setGenome(const std::vector<float> &genome) { _genome = genome;}
        void  setScore(const float s) { _score = s;}
        float score(void)         { return _score;}
        std::vector<float> &genome() { return _genome;}
        int getID() { return ID;}
    private:
        int ID;
        float _score;
        std::vector<float> _genome;
};

class GeneticAlgorithm {
    public:
        GeneticAlgorithm(
            int population_size = DEFAULT_POPULATION_SIZE,
            int mutation_probability = DEFAULT_MUTATION_PROBABILITY,
            int mutation_variance = DEFAULT_MUTATION_VARIANCE,
            float target_fitness = 0,
            int survival_percentage = DEFAULT_SURVIVAL_PERCENTAGE,
            int print_frequency = DEFAULT_PRINT_FREQUENCY);
        virtual ~GeneticAlgorithm(){};
        Individual *evolvePopulation(const int max_iterations = 1000);
        /*************************************************************************
         * Function :    userFitnessFunction()
         * Purpose  :    Application-overridden function to evaluate the fitness of
         *               an individual. Function should use the setScore method of
         *               the Individual instance directly to set the fitness score
         *               within this function.
         * Input    :    Individual &ind
         * Returns  :    void
         *************************************************************************/
        virtual void userFitnessFunction(Individual *ind);
        void  setMutationProbability(const float val) {mutation_probability = val;}
        void  setMutationVariance(const float val)    {mutation_variance    = val;}
        void  setSurvivalPercentage(const float val)  {survival_percentage  = val;}
        unsigned int populationSize(void)   {return population.size();}
        float mutationProbability(void)     {return mutation_probability;}
        float mutationVariance(void)        {return mutation_variance;}
        float survivalPercentage(void)      {return survival_percentage;}
        void  bestFitnessScore(void);

    protected:
        int   iterations;
        float mutation_probability;
        float mutation_variance;
        float target_fitness;
        float survival_percentage;
        int   print_frequency;
        std::vector<Individual *> population;
        std::vector<Individual *> survivors;
        Individual *crossover();
        void fitness();
        void mutate(Individual *ind);
        void spawn(bool first, int fsize);
        void printResults(bool final, time_t start_time);
};
