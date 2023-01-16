#include <iostream>
#include <string>
#include <assert.h>
#include "Line.h"
#include "Set.h"
#include "Cache.h"

//TO DO: most of this is incomplete
//       look for TODO throughout the file

Cache::Cache(int32_t associativity, int32_t blockOffsetBits, 
             int32_t setIndexBits, bool verbose)
{
   int32_t i, j;
   /* TODO: Calculate the number of sets from the setIndex bits */
   numSets = 1;  //1 isn't correct -- You need to fix this (Don't use POW function.)
                 //Writing the number of sets out in binary might help you figure it out

   //the rest of this is complete
   sets = new Set[numSets];  //create an array of Set objects
   for (i = 0; i < numSets; i++)
   {
       sets[i].initialize(i, associativity, verbose); //initialize each Set object
   }

   this->associativity = associativity;        //the way
   this->blockOffsetBits = blockOffsetBits;    //the number of bits for the block offset
   this->setIndexBits = setIndexBits;          //the number of bits for the set index
   this->verbose = verbose;                    //use this to turn on/off debugging print statements
}

/*
 * Destruct the dynamically allocated data.
 */
Cache::~Cache()
{
   //TODO 
}

/* 
 * isHit
 * Returns true if accessing the cache with the provided address results in
 * a hit. Calls isHit in the Set class.
 */
bool Cache::isHit(int64_t address)
{
   //TODO 
   //Hint: get the tag and the index from the address and call isHit 
   //in the Set class using the appropriate Set object 
   return false;
}

/*
 * isEvict
 * Returns true if accessing the cache with the provided address results in
 * an eviction because the Set is full. Calls isFull in the Set class.
 */
bool Cache::isEvict(int64_t address)
{
   //TODO 
   //Hint: get the tag and the index from the address and call isFull 
   //in the Set class using the appropriate Set object
   return false;
}

/*
 * update
 * Updates the set in which the tag of the address is to be stored
 * by calling the updateSet method using the appropriate Set object.
 */
void Cache::update(int64_t address)
{
   //TODO 
   //Hint: get the tag and the index from the address and call updateSet in
   //the Set class using the appropriate Set object
}

/*
 * getBits
 * Takes as input a source, a starting bit number, and an ending bit number
 * and returns those bits from the source.
 * For example, getBits(60, 62, 0x7000000000000000) returns 7
 */
int64_t Cache::getBits(int32_t start, int32_t end, int64_t source)
{
   //TODO
   //You wrote this for  your CS 3481 simulator.  You can use that code or
   //for good practice, try to write it from scratch.
   return 0;
}

/*
 * print
 * Output the contents of the cache.  This may be useful for debugging.
 * You can add a call to this in the Simulate run method.
*/
void Cache::print()
{
   std::cout << "Number of Sets: " << numSets << ", ";
   std::cout << "Associativity: " << associativity << "\n";

   int32_t i, j;
   for (i = 0; i < numSets; i++)
   {
      sets[i].print();   //call print method in Set class
   }
   std::cout << "\n";
}

