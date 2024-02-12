// HashTable.cpp
// Author: Matthew Martinez
// Description: File contains constructor for a HashTable and common 
// functions to interact with the HashTable.

#include <iostream>
#include <math.h>
#include "HashTable.h"
#include <vector>

using std::vector;
using std::string;

/*Description: Default constructor for HashTable class
  Parameters: N/A
  Returns: N/A
*/
HashTable::HashTable(){
  table.resize(11);
  p = 31;
  size = table.size();
  numElements = 0;
}

/*Description: Constructor for HashTable class. accepts parameters
  for size and multiple p.
  Parameters: int s, int mult
  Returns: N/A
*/
HashTable::HashTable(int s, int mult){
  table.resize(s);
  p = mult;
  size = table.size();
  numElements = 0;
}

/*Description: Function returns size variable of HashTable.
  Parameters: N/A
  Returns: int
*/
int HashTable::getSize(){ 
  return size;
}

/*Description: Function returns NumElements variable of Hashtable.
  Parameters: N/A
  Returns: int
*/   
int HashTable::getNumElements(){
  return numElements;
}

/*Description: Returns p variable(multiplier) for HashTable.
  Parameters: N/A
  Returns: int
*/
int HashTable::getP(){
  return p;
}

/*Description: Function traverses hash table and prints Hashtable contents.
  Parameters: N/A
  Returns: void
*/
void HashTable::printTable(){
  std::cout << "HASH TABLE CONTENTS" << std::endl;
  for (int i = 0; i < table.size(); i++){
    if (table[i].size() > 0){
      std::cout << i << ": ";
      for (int j = 0; j < table[i].size()-1; j++){
        std::cout << table[i][j] << ", ";
      }
      std::cout << table[i][table[i].size()-1] << std::endl;
    }
  }
}

/*Description: Function searches HashTable function for string parameter.
  Returns index if parameter is found, else returns -1;
  Parameters: string s;
  Returns: int
*/
int HashTable::search(std::string s){
  unsigned int index = hash(s);

  for (unsigned int i = 0; i < table[index].size(); i++) {
    if (table[index][i] == s) {
      return index;
    }
  }

  return -1;
}

/*Description: Function inserts string s into Hashtable.
  Parameters: string s
  Returns: void
*/
void HashTable::insert(std::string s){
  unsigned int index = hash(s);
  table[index].push_back(s);
  numElements = numElements + 1;
  size = table.size(); 
}

/*Description: Function removes first instance of parameter string
  found in hash table. Does nothing if string is not found.
  Parameters: string s
  Returns: void
*/
void HashTable::remove(std::string s){
  unsigned int index = hash(s);

  for (unsigned int i = 0; i < table[index].size(); i++) {
    if (table[index][i] == s) {
      table[index].erase(table[index].begin()+i);
      table[index].shrink_to_fit();
      numElements = numElements - 1;
      break;
    }
  }
}

/*Description: Function sets size of hashtable to size of 
  parameter s. Elements within hash table are rehashed and
  put into new indices.
  Parameters: int s
  Returns: void
*/
void HashTable::resize(int s){
  vector<vector<string>> table2(table.size());
  
  // copy old table to new table
  for (unsigned int i = 0; i < table.size(); i++) {
    table2[i] = table[i];
  }

  table.clear();

  table.resize(s);
  numElements = 0;

  for (unsigned int i = 0; i < table2.size(); i++) {
    if (table2[i].size() > 0) {
      for (unsigned int j = 0; j < table2[i].size(); j++) {
        insert(table2[i][j]);
      }
    }
  }
}

/*Description: Function takes string parameter runs string through
  hash function and returns an index to store the string in.
  Parameters: string s
  Returns: int
*/
int HashTable::hash(std::string s){
  unsigned int hashValue = 0;

  for (unsigned int i = 0; i < s.length(); i++) {
    hashValue = hashValue + ((int(s[i]))*pow(p,i));
  }
  
  hashValue = hashValue%table.size();

  return hashValue;

}