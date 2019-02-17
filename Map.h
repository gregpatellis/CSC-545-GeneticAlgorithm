#pragma once

#include <vector>

/**
 * A class representing a border between two states.
 */
class Border
{
public:
  int index1, index2; // indices of the states having this border in common

  Border(int index1, int index2) : index1(index1), index2(index2) {}
};

/**
 * A class representing a political map.
 */
class Map
{
public:
  std::vector<const char*> states; // names of the states
  std::vector<Border> borders; // borders between the states
};
