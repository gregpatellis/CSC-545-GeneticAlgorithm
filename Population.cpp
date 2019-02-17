#include "Population.h"

Population::Population(const Map& map, int initialSize) : map(&map)
{
  for(int i = 0; i < initialSize; ++i)
  {
    push_back(Individual(map));
  }
}

Population& Population::operator=(const Population& other)
{
  assign(other.begin(), other.end());
  map = other.map;
  return *this;
}

Individual& Population::randomSelection()
{
  // return an individual of the population
  // with a probability proportional to its fitness

  int sum = 0;
  for(int i = 0; i < size(); i++)
  {
	sum = sum + at(i).getFitness();
  }
  int chanceNum = 10+(rand() % ((sum-1)-10+1));
  int index = 0;    

  for(int j = 0;j < size();j++)
  {
	if(at(j).getFitness() > chanceNum)
	{	
		index = j;	
		return at(index);
	}
	chanceNum -= at(j).getFitness();
  } 
}
