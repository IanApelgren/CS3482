#include <iostream>
#include <string>
#include <assert.h>
#include "Line.h"
#include "Set.h"

//TO DO: lots of work to do in this file. 
//       Look for TODO throughout the file

/*
 * initialize
 * Initialize the Set object.  
 * A Set is a linked list of Line objects.  Up to associativity Line objects can
 * be in the linked list.
 */
void Set::initialize(int32_t index, int32_t associativity, bool verbose)
{
   this->index = index;                   //index of this set
   this->associativity = associativity;   //way
   this->verbose = verbose;               //can be used to turn debugging prints on or off
   this->firstLine = NULL;                //pointer to the first Line object in the Set
}

/*
 * isHit
 * Looks in the Set for the tag. Returns true if found and false otherwise.
 */
bool Set::isHit(int64_t tag)
{
   //TODO
	
	Line *index = firstLine;
	
	while(index != NULL)
	{
		if(index->tag == tag)
		{
			return true;
		}
		index = index->next;
		
	}
	return false;
	
}

/*
 * isFull
 * Returns true if the Set is full. The Set is full if the linked listed contains
 * associativity (way) Line objects. This is used to determine whether an eviction 
 * is necessary.
 */
bool Set::isFull()
{
   
   //TODO 
   //Hint: Loop through the linked list, counting the number of objects 

	Line *index = firstLine;
	int counter = 0;
	
	//loop to see how many elements are in the set
	while(index != NULL)
	{
		counter = counter + 1;
		index = index->next;
	}
	//if its equal or more than assoc then its full
	if(counter >= associativity)
	{
		delete index;
		return true;
	}
	//less its fine
	else
	{
		delete index;
		return false;
	}
}

/*
 * updateSet
 * Updates the Set with the provided tag.
 * The Line objects in the linked list encapsulated by the Set object need to be kept in
 * in the Set in LRU order so that the MRU Line object is in the front
 * of the linked list.
 * 
 * Suppose tag is T and associativity is 4.
 * If the tags of the nodes in the linked list are: A B C D
 * then after the update, the tags are: T A B C
 * Notice that D (the LRU) got evicted.
 *
 * If the tags of the nodes in the linked list are: A B T D
 * then after the update, the tags are: T A B D
 * Notice that T was moved from where it was to the front of the linked list.
 *
 * If the tags of the nodes in the linked list are: A B 
 * (only two nodes)
 * then after the update, the tags are: T A B
 * Notice nothing was evicted because the Set isn't full.
 * 
 */
void Set::updateSet(int64_t tag)
{
   //TODO
   //Note: this work is completed by calling other methods in this 
   //      class.
   //
   //If the tag is already in the set then remove the Line containing
   //the tag.
   //
   //Or, if the set is full then remove the LRU Line.
   //
   //After that, insert a new Line with this tag in the front of the
   //linked list.

	bool full = isFull();
	bool hit = isHit(tag);
	//if its full and tag isnt there remove one
	if(full == true && hit == false)
	{
		removeLine(getLRUTag());
	}
	//if its full and tag is there move it
	if(full == true && hit == true)
	{
		removeLine(tag);
	}
	//always put tag at front
	insertInFront(tag);
}

/*
 * insertInFront
 * Create a new Line object and insert it in the front of the linked list.
 * This method is called by updateSet.
 */
void Set::insertInFront(int64_t tag)
{
   //TODO
	//make new front make it point to old front and update current
	
	Line *front = new Line(tag);
	front->next = firstLine;
	firstLine = front;
		
	
}

/*
 * removeLine
 * Remove the Line object from the linked list with the specified tag.
 * This will update firstLine if the Line object is the first one in the
 * linked list; otherwise, it updates the next field of the previous
 * Line in the linked list.
 * This method is called by updateSet.
 */
void Set::removeLine(int64_t tag)
{
   //TODO
	Line *index = NULL;
	Line *prev = NULL;

	//if tag is first move first up and remove old first
	if (firstLine->tag == tag)
	{
		index = firstLine;
		firstLine = firstLine->next;
		index->next = NULL;
		delete index;
		return;
	}

	//isnt the first one so index is second and prev is first and we march through
	index = firstLine->next;
	prev = firstLine;
	while(index != NULL)
	{
		if(index->tag == tag)
		{
			prev->next = index->next;
			index->next = NULL;
			delete index;
			return;
			
		}
		index = index->next;
		prev = prev->next;
		

	}	
}

/*
 * getLRUTag
 * Returns the tag of the LRU Line in the set. This is the tag of the
 * last Line object in the linked list.
 * This method is called by updateSet.
 */
int64_t Set::getLRUTag()
{
   //TOD	
	
	Line *index = firstLine;
	if(index == NULL)
	{
		return -1;
	}
	//loop through if the next is null than weve reached the end
	while (index != NULL)
	{
		if(index->next == NULL)
		{
			return index->tag;
			break;
		}
		index = index->next;
	}
		
}

/*
 * Destructor for the dynamically allocated data.
 */
Set::~Set()
{ 
  delete firstLine;
}


/*
 * print
 * Prints the tags in the Set if the set is non-empty. If the Set is empty
 * nothing is printed. This can be used for debugging.
 */
void Set::print()
{
   
   if (firstLine)
   {
      std::cout << "Set: " << index << " Tags: ";
      Line * ptr = firstLine;   //initialize to point to first node in the linked list
      while (ptr != NULL)
      {
         std::cout << std::hex << ptr->tag << " ";
         ptr = ptr->next;
      }
      std::cout <<"\n";
   }
}

