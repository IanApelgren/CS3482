
#include "WordList.h"
#include "NgramList.h"
#include "NgramSTL.h"
#include <list>
#include <set>
#include <utility>
#include <map>
#include <tuple>
#include <unordered_map>
#include <array>
#include <iterator>
#include <string>

using namespace std;
vector<pair<string,int>> vect;
std::map<std::string,int> hashmap;
/* You may NOT include any additional header files or declare any global variables. */
/* You may add data members to the class by adding them to NgramSTL.h */
/* You may add more methods to the class. Add the prototype to NgramSTL.h */
/* You can also add functions (outside of any class) to this file, but only */
/* if you absolutely are required to by the STL. */

/*
 * Ngrams
 *
 * Takes as input the size of the ngrams to be built and the list  
 * of words to build the ngrams from and calls insertNgram to
 * insert the ngram into some collection object defined using a 
 * C++ template class. You get to choose the template class.
 * You'll need to add a declaration of the template class object
 * to NgramSTL.h.  You may need more than one.
 *
 * param: int ngramSz - size of the ngram
 * param: const WordList & wl - list of the words use
 */
Ngrams::Ngrams(int ngramSz, WordList & wl)
{
   //Add any code you need to initialize whatever structure
   //you use to hold your ngrams.
	//vector<pair<string,int>> vect;
	//std::map<std::string,int> hashmap;

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
 * If you didn't dynamically allocate any date then this 
 * method stays empty.
 */
Ngrams::~Ngrams()
{

}


/*
 * insertNgram
 *
 * Inserts the ngram into whatever collection object you choose to hold
 * your ngrams. If the ngram is already in the collection, it should
 * simply increment the count.
 *
 * param: std::string s - ngram to be inserted
 * return: none
 */
void Ngrams::insertNgram(std::string s)
{
	int count = 0;
	//for the first insert
	if(hashmap.count(s) == 0)
	{
		hashmap.emplace(pair<string,int>(s,1);
	}
	else
	{
		count = hashmap.at(s);
		count = count + 1;
		//replace entry with updated 1
		hashmap.erase(hashmap.find(s));
		hashmap.emplace(pair<string,int>(s,count));
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
	for (it = hashmap.begin(); it = hashmap.end(); it++)
	{
		vect.push_back(make_pair(it->first, it->second));
	}
	sort(vect.begin(), vect.end(), sortVals);
	for int i = 0; i < vect.length(); i++)
	{
      		incrLst->addToNgramList(vect[i].first, vect[i].second);
	}
      //You will probably have this call inside of a loop
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
	for (it = hashmap.begin(); it = hashmap.end(); it++)
	{
		vect.push_back(make_pair(it->first, it->second));
	}
	sort(vect.begin(), vect.end(), sortVals);

	for(int i = vect.length(); i != 0; i--)
	{
      		decrLst->addToNgramList(vect[i].first, vect[i].second);
	}
      //You will probably have this call inside of a loop
}









