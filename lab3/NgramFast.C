#include <iostream>
#include <string>
#include "WordList.h"
#include "NgramList.h"
#include "NgramFast.h"

/* You may NOT declare any global variables. */

/* You may add data members to the NgramFast class by adding them to NgramFast.h */
/* You may add more methods to the NgramFast class.  Put prototypes in NgramFast.h */
/* You may add more classes.  If you do, they need to be cleanly
 * separated into a .h and a .C files. You would add an include
 * for the .h at the top.  You would need to change the makefile
 * so that your new classes are compiled and linked with the
 * executable. */

unsigned long hashFunction(char* str)
{
   unsigned long i = 0;
   for (int j=0; str[j]; j++)
   {
      i += str[j] * pow(53,j);
   }
   return i % 500000;
}

typedef struct htItem htItem;

//define hash table item
struct htItem
{
   std::string key;
   int value;
	int count;
	htItem * next;
};

typedef struct HashTable HashTable;

struct HashTable 
{
   //arrray of pointers to items
   htItem** items;
   int size;

};







/*
 * Ngrams
 *
 * Takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and builds a collection
 * of ngrams. You may not use the C++ STL to define a collection object.
 * You need to implement your own. 
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, WordList & wl)
{
   //Add any code you need to initialize whatever structure
   //you use to hold your ngrams.
   HashTable* table (HashTable*) malloc (sizeof(HashTable));
   //This code doesn't change
   this->ngramSz = ngramSz;
   wl.beginIter();
   while (!wl.endIter())
   {
      std::string ngram = wl.getNextNgram(ngramSz);
      wl.incrementIter();
      //Insert the ngram in the collection object
      if (!ngram.empty()) insertNgram(ngram);
   }

   //You can make additional calls here if you need to.

}


/*
 * Ngrams destructor
 *
 * Automatically called when Ngrams object goes out of scope.
 * Delete any space dynamically allocated to hold the ngrams.
 */
Ngrams::~Ngrams()
{
	Ngram * temp;
	Ngram * tempsuc;
	for(int i = 0; i < HashTable.length(); i++)
	{
		temp = HashTable[i];
		while(temp != NULL)
		{
			tempsuc = temp->next;
			delete(temp);
			temp = tempsuc;
		}
	}
}


/*
 * insertNgram
 *
 * Inserts ngram into whatever structure you choose to hold
 * your ngrams. If the ngram is already in the collection, the
 * insert simply increments the count.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(std::string s)
{
	int hash = hashFunction(s);
	htItem * item = new htItem();
	htItem * newItem = new htItem();
	newItem->key = s;
	newItem->count = 1;
	newItem->next = NULL;
	
	//if the table there is empty
	if(hashTable[hash] == NULL) 
	{
		HashTable[hash] = newItem;
	}
	else
	{
		htItem = HashTable[index];
		while (item != NULL)
		{
			if(item->htItem == s)
			{
				item->count = htItem->count + 1;
				delete(item);
				break;
			}
			item= htItem->next;
		}
		newNode->next = HashTable[hash];
		HashTable[hash] = newNode;
	}
	
}

bool sortVals(const pair<string,int> &x, const pair<string,int> &y)
{
	return (x.second < y.second);
}


/*
 * addIncreasing
 * 
 * Adds the ngrams to the ngram list in increasing order of ngram count.
 *
 */
void Ngrams::addIncreasing(NgramList * incrLst)
{
	
    map<string,int> :: iterator it;
	for (it = HashTable.begin(); it = HashTable.end(); it++)
	{
		vect.push_back(make_pair(it->first, it->second));
	}
	sort(vect.begin(), vect.end(), sortVals);
	for int i = 0; i < vect.length(); i++)
	{
      		incrLst->addToNgramList(vect[i].first, vect[i].second);
	}

       //The call to add it to the list looks something like this:
              //You will probably have this call inside of a loop (or two)
}

/*
 * addDecreasing
 *
 * Adds the ngrams to the ngram list in decreasing order of ngram count.
 *
 */
void Ngrams::addDecreasing(NgramList * decrLst)
{
	 map<string,int> :: iterator it;
	for (it = HashTable.begin(); it = HashTable.end(); it++)
	{
		vect.push_back(make_pair(it->first, it->second));
	}
	sort(vect.begin(), vect.end(), sortVals);

	for(int i = vect.length(); i != 0; i--)
	{
      		decrLst->addToNgramList(vect[i].first, vect[i].second);
	}

      //The call to add it to the list looks something like this:
      decrLst->addToNgramList(ngramStr, ngramCnt);
      //You will probably have this call inside of a loop (or two)
}







