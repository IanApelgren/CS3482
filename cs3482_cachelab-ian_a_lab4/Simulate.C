#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include "Line.h"
#include "Set.h"
#include "Cache.h"
#include "Simulate.h"

//TO DO: implement run and accessCache functions
//Look for TODO 

/* Simulator constructor
 * Dynamically create a Cache object and initialize the Simulator object.
 */

Simulate::Simulate(int32_t associativity, int32_t blockOffsetBits, 
                   int32_t setIndexBits, bool verbose)
{
   hits = misses = evictions = 0;
   cacheP = new Cache(associativity, blockOffsetBits, setIndexBits, verbose);
   this->verbose = verbose;
}

/*
 * Destroy the Simulator object.
 */
Simulate::~Simulate()
{
   delete cacheP;
}

void Simulate::run(std::string filename)
{
   std::fstream fs;
   fs.open(filename, std::fstream::in);
   
   //TODO
   //Loop, reading lines from the file.
   //From each line, get the type and the address.
   //Depending upon the type (L or S), you'll pass it to the
   //accessCache method. (See assignment.)
   //If the verbose flag is true, print out the input line (see csim-ref).

	std::string type, data;
	long addr;
	int64_t compL, compS, compM;
	while (fs >> type) //type gets set to "I", "L", or "S"
	{
    		fs >> data;
		addr = stol(data,nullptr,16);

		//accounting for verbose flag being set
		if (verbose == true)
		{
			std::cout << type << data << std::endl;
		}
		
		//check if its L S or M
		compL = type.compare("L");
		compS = type.compare("S");
		compM = type.compare("M");

		//if its either l or s pass it to accessCache 
		if (compL == 0 || compS == 0)
		{
			accessCache(addr);
		}
		//if m its read and write
		if (compM == 0)
		{
			accessCache(addr);
			accessCache(addr);
		}
		
		
	} 



}

/* accessCache
 * Takes as input a 64 bit address.
 * Uses the address to access the cache pointed to by cacheP
 * and updates hits, misses, and evictions.
 */
void Simulate::accessCache(int64_t address)
{
   //TODO
   //cacheP contains a pointer to the cache object
   //Call the appropriate methods in the Cache class
   //to determine whether to increment hits, misses, and/or evictions
   //If verbose is true, output the verbose output (see assignment)
	
	//if it hits its a hit
	if (cacheP->isHit(address) == true)
	{
		hits = hits + 1;
		if (verbose == true)
		{
			std::cout << "Hit" << std::endl;
		}
	}
	//otherwise a miss
	else
	{
		misses = misses + 1;
		if (verbose == true)
		{
			std::cout << "Miss" << std::endl;
		}
		//possibly an evict
		if (cacheP->isEvict(address) == true)
		{
			evictions = evictions + 1;
			if (verbose == true)
			{
				std::cout << "Evict" << std::endl;
			}

		}

	}

		cacheP->update(address);


}

/*
 * printSummary
 * Print the number of hits, misses, and evictions at the end of
 * the simulation.
 */
void Simulate::printSummary()
{
   std::fstream fs;
   printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
   fs.open(".csim_results", std::fstream::out);
   assert(fs.is_open());
   fs << hits << " " << misses << " " << evictions <<"\n";;
   fs.close();
}

