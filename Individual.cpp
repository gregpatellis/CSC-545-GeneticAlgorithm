#include "Individual.h"
#include <cstdlib>
#include <iostream>
using namespace std;

Individual::Individual(const Map& map) : map(&map)
{
  int stateNum = map.states.size();
  
  for(int i = 0;i < stateNum;i++) 
  {
	int color = (rand() % ( 3 + 1 ) );     // 0-R | 1-B | 2-G | 3-Y	
	stateColor[i] = color;
  }
  updateFitness(map);
}

Individual Individual::reproduce(const Individual& x, const Individual& y,const Map& map)
{
  Individual child(*x.map);
  int geneSize = map.states.size();
  int spliceIndex = 1+(rand() % ((geneSize-1)-1 + 1 ) );
  int spliceLen = (geneSize - 1) - (spliceIndex);
  int spliceX[spliceLen];
  int spliceY[spliceLen];
  for(int i = 0; i < spliceLen; i++)
	spliceX[i] = x.stateColor[i+spliceIndex+1];
  for(int j = 0;j < spliceLen; j++)
	spliceY[j] = y.stateColor[j+spliceIndex+1];
  int whichSplice = (rand() % (1+1));

  if(whichSplice == 1)
  {
	for(int j = 0;j <= spliceIndex;j++)
		child.stateColor[j] = x.stateColor[j]; 

	for(int i = 0; i < spliceLen; i++)
		child.stateColor[spliceIndex + i + 1] = spliceY[i];

  }   

  if(whichSplice == 0)
  {
	for(int j = 0;j <= spliceIndex;j++)
	        child.stateColor[j] = y.stateColor[j];

        for(int i = 0; i < spliceLen; i++)
                child.stateColor[spliceIndex + i + 1] = spliceX[i];

  }
  // TODO generate child from parent individuals x and y

  child.updateFitness(map);
  return child;
}

bool Individual::isGoal(const Map& map) const
{
  // TODO implement goal test
 
  for(int i = 0; i < map.borders.size();i++)
  {
	  if(stateColor[map.borders[i].index1] == stateColor[map.borders[i].index2])
	  	return false;
  }
  return true;
}

double Individual::getFitness() const
{
  return fitness;
}

void Individual::updateFitness(const Map& map)
{
  // TODO implement fitness function
  // set member fitness to computed fitness value

  int counter = 0;
  for(int j = 0;j < map.borders.size();j++)
  {
        if(stateColor[map.borders[j].index1] != stateColor[map.borders[j].index2])
        {
		counter++;
        }
  }

  fitness = counter;
}

void Individual::mutate(const Map& map)
{
  // TODO implement random mutation 
  
  int genePool = sizeof(map.states.size());
  int index = (rand() % (genePool + 1 ));
  int colorAssign;
  if(stateColor[index] == 0)
  {
	colorAssign = 1+(rand() % (3-1+1));
	stateColor[index] = colorAssign;
  }
 
  if(stateColor[index] == 1)
  {
	bool notValid = true;
	while(notValid)
	{
		colorAssign = (rand() % (3+1));
		if(colorAssign == 1)
			notValid = true;
		else
			notValid = false;
	}  
	
	stateColor[index] = colorAssign;
  }

  if(stateColor[index] == 2)
  {
        bool notValid = true;
        while(notValid)
        {
                colorAssign = (rand() % (3+1));
                if(colorAssign == 2)
                        notValid = true;
                else
                        notValid = false;
        }  

        stateColor[index] = colorAssign;
  }
   
  if(stateColor[index] == 3)
  {
	colorAssign = (rand() % (2+1));
        stateColor[index] = colorAssign;
  }   

  updateFitness(map);
}

void Individual::print(const Map& map) 
{
  cout << "fitness: " << getFitness() << endl;
  for(int i = 0; i < map.states.size();i++)
	cout << map.states[i] << ": " << stateColor[i] << endl;

 // cout << map.states.size() << endl;
  //cout << sizeof(stateColor); 
 // TODO implement printing function
  // it should print the genom in the following form:
  // fitness: 15
  // North Carolina: 0
  // South Carolina: 3
  // ...
}
