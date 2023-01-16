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
   numSets = 1<<setIndexBits;  //1 isn't correct -- You need to fix this (Don't use POW function.)
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
	delete [] sets;
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
	//gets the tag and index to see if the set contains it
	int64_t tag = getBits((blockOffsetBits+setIndexBits), 63, address);
	int64_t index = getBits(blockOffsetBits, (blockOffsetBits + setIndexBits - 1), address);
	return sets[index].isHit(tag);
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
	
	//get the index of the set then push it down for sets to check if its full or not
	int64_t tag = getBits((blockOffsetBits+setIndexBits), 63, address);
   	int64_t index = getBits(blockOffsetBits, (blockOffsetBits + setIndexBits - 1), address);
	if(isHit(address))
	{
		return false;	
	}
	else
	{
		return sets[index].isFull();
	}

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
	//gets tag and index from the address and pushes it to sets to deal with
	int64_t tag = getBits((blockOffsetBits+setIndexBits), 63, address);
	int64_t index = getBits(blockOffsetBits, (blockOffsetBits + setIndexBits - 1), address);
	sets[index].updateSet(tag);

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
   assert(start >= 0 && end <= 63 && start <= end);
   if((end >= 0) && (start >= 0)){
        
        if((end < 64) && (start < 64)){
        
            //    
            uint64_t helper = 0; //I need a variable to hold my value to be returned
            uint64_t ammout_of_bits = end - start; //Find out how many bits I will be working with

            //I want to identify how many bits I need to shift off the left hand side...
            //... They should shift back as zeros
            helper = source << (63 - end); 

            //Now I want to identify how many bits I need to shift back to the right to...
            //get the acutal sequence of bits that was desired 
            helper = helper >> (63 - ammout_of_bits);
    
            return helper; //Return the desired bits                       
        }
        else{
            
            return 0x00; //Return 0x00 if input is out of range    
        }

    }
    else{
        
        return 0x00; //Return 0x00 if input is out of range    
    }
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

