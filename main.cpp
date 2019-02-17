#include "Individual.h"
#include "Individual.cpp"
#include "Map.h"
#include "Population.cpp"
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

void initMap(Map& map)
{
  map.states.push_back("North Carolina");
  map.states.push_back("South Carolina");
  map.states.push_back("Virginia");
  map.states.push_back("Tennessee");
  map.states.push_back("Kentucky");
  map.states.push_back("West Virginia");
  map.states.push_back("Georgia");
  map.states.push_back("Alabama");
  map.states.push_back("Mississippi");
  map.states.push_back("Florida");

  map.borders.push_back(Border(0, 1));
  map.borders.push_back(Border(0, 2)); 
  map.borders.push_back(Border(0, 3));
  map.borders.push_back(Border(0, 6));
  map.borders.push_back(Border(1, 6));
  map.borders.push_back(Border(2, 3));
  map.borders.push_back(Border(2, 4));
  map.borders.push_back(Border(2, 5));
  map.borders.push_back(Border(3, 4));
  map.borders.push_back(Border(3, 6));
  map.borders.push_back(Border(3, 7));
  map.borders.push_back(Border(3, 8));
  map.borders.push_back(Border(4, 5));
  map.borders.push_back(Border(6, 7));
  map.borders.push_back(Border(6, 9));
  map.borders.push_back(Border(7, 8));
  map.borders.push_back(Border(7, 9));
}

int main(int argc, char* argv[])
{
  Map map;
  initMap(map);

  srand((unsigned)time(NULL));
  const int populationSize = 20; // TODO find reasonable value
  Population population(map, populationSize);

  const int maxIterations = 100; // TODO find reasonable value
  int currentIteration = 0;
  bool goalFound = false;
  Individual bestIndividual(map); // to hold the individual representing the goal, if any

  while(currentIteration < maxIterations && !goalFound)
  {
    Population newPopulation(map);
    newPopulation.reserve(populationSize); // just to improve efficiency
    for(int i = 0; i < populationSize; ++i)
    {
      Individual x = population.randomSelection();
      Individual y = population.randomSelection();
      Individual child = Individual::reproduce(x, y,map);
      if(1 == (rand() % (5+1))) // TODO use small probability instead
      {
        child.mutate(map);
      }
      if(child.isGoal(map))
      {
        goalFound = true;
        bestIndividual = child;
      }
      newPopulation.push_back(child);
    }
    population = newPopulation;
    ++currentIteration;
  }

  if(goalFound)
  {
    printf("Found a solution after %d iterations\n", currentIteration);
    bestIndividual.print(map);
  }
  else
  {
    printf("Did not find a solution after %d iterations\n", currentIteration);
  }

}
