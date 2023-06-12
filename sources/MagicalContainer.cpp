#include <iostream>
#include <algorithm>
#include "MagicalContainer.hpp"

using namespace ariel;

void MagicalContainer::addElement(int newElement)
{
	auto pointerToElement = find(mysticalElements.begin(), mysticalElements.end(), newElement); //searches for the newElement in the mysticalElements vector using the std::find algorithm. It returns an iterator pointing to the element if found or mysticalElements.end() if not found.

	if (pointerToElement != mysticalElements.end()) //checks if the element already exists in the mysticalElements vector. If it does, the function returns without performing any further operations.
	{	
		return; //if element already exist return
	}

	auto toInstert = upper_bound(mysticalElements.begin(), mysticalElements.end(), newElement, [](int a, int b){ return a < b; }); //find the position where the newElement should be inserted while maintaining the sorted order. 
	mysticalElements.insert(toInstert, newElement); // inserts the newElement at the position determined by to_insert into the mysticalElements vector.

	primeElements.clear();
	primeElements.reserve(mysticalElements.size()); //reserves memory in the primeElements vector to optimize the storage capacity based on the size of the mysticalElements vector.

	for (int& element : mysticalElements)
	{
		if (isPrime(element))  //checks if the element elem is prime
		{ 
			primeElements.push_back(&element);
		}
	}

}

void MagicalContainer::removeElement(int newElement)
{
	auto pointerToElement = find(mysticalElements.begin(), mysticalElements.end(), newElement);

	if (pointerToElement == mysticalElements.end())
	{
		throw runtime_error("Element not found");
	}

	int* ptr = &(*pointerToElement);

	mysticalElements.erase(pointerToElement);

	if (isPrime(newElement))
	{
		auto pointerToElement2 = find(primeElements.begin(), primeElements.end(), ptr);
		primeElements.erase(pointerToElement2);
	}

	if (size() == 0)
	{
		return;
	}

	
}

int MagicalContainer :: size()const{ //return size of container
    return this -> mysticalElements.size();
}

std::vector<int>  MagicalContainer :: getElements()const{ //get Elements of container
    return this ->mysticalElements;
}

bool MagicalContainer :: isPrime(int number){ //help function check if number is prime

    if (number <2){
        return false;
    }
    if (number == 2){
        return true;
    }
    for (int i = 2; i < number ; i++){
        if (number%i == 0){
            return false;
        }
    }
    return true;
}