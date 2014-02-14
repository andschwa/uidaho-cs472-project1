/* Copyright 2014 Andrew Schwartzmeyer
 *
 * Source file for derived hill-climbing algorithm class
 */

#include <iostream>

#include "hill_climbing_algorithm.hpp"

const Individual HillClimbing::solve() const {
  Individual potential;
  Individual neighbor;
  parameter fitness;
  do {
    // random restart
    potential = problem.potential();
    neighbor = potential;
    fitness = problem.fitness(potential);
    if (fitness > problem.filter) {
      // work with "lucky" values
      for (long i = 0; i < problem.iterations; i++) {
	// actual hill-climbing algorithm
	const Individual neighbor = mutate(potential);
	parameter n_fitness = problem.fitness(neighbor);
	if (n_fitness > fitness) {
	  // keep track of best potential solution
	  potential = neighbor;
	  fitness = n_fitness;
	  // one of the few legitimate modern uses of goto!
	  if (fitness > problem.goal) goto finished;
	}
      }
      std::cout << "Neighbors exhausted, fitness was: " << fitness << "\n";
    }
  } while (fitness < problem.goal);
 finished:
  return potential;
}
