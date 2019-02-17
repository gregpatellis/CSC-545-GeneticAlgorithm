#pragma once

#include "Individual.h"
#include "Map.h"
#include <vector>

/**
 * Class representing a population of individuals
 */
class Population : public std::vector<Individual>
{
private:
  const Map* map; // the map

public:
  /**
   * Standard ctor.
   * @param map The map.
   * @param initialSize The initial size of the population.
   */
  Population(const Map& map, const int initialSize = 0);

  /**
   * Assignment operator. Assigns the contents of another
   * population to this one.
   * @param other The population to be assigned.
   * @return This population after assignment.
   */
  Population& operator=(const Population& other);

  /**
   * Randomly selects an individual out of the population
   * proportionally to its fitness.
   * @return The selected individual.
   */
  Individual& randomSelection();
};
