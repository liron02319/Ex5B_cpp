#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <algorithm>
#include <vector>
using namespace std;


namespace ariel{

class MagicalContainer {

private:
    std::vector<int> mysticalElements; 
    std::vector<int*> primeElements; //for primeElements

public:

    // distructor,default and copy constructors and Assignment operator(tidy ask for more)
    MagicalContainer() = default; 
    ~MagicalContainer() = default; //distructor
    MagicalContainer(const MagicalContainer& other) = default; //tidy
    MagicalContainer(MagicalContainer&& other) = default;//tidy
    MagicalContainer& operator=(const MagicalContainer& other) = default;//tidy
    MagicalContainer& operator=(MagicalContainer&& other) = default;//tidy
   


    std::vector<int> getElements() const; //help functions
    bool isPrime(int number);

    // container functions
    void addElement(int element);
    void removeElement(int element);
    int size() const;






    /*
    //class AscendingIterator 
    //example 6,5,4,3 -> 3,4,5,6
    */

    class AscendingIterator {

    public:

        MagicalContainer& container;
        std::vector<int>::size_type index;  //position

        // distructor,default and copy constructors and Assignment operator(tidy ask for more)
        AscendingIterator(MagicalContainer& container): container(container), index(0){}   //default
        AscendingIterator(const AscendingIterator& other): container(other.container), index(other.index){} //copy constructor
        AscendingIterator(AscendingIterator&& other) = default; //tidy
        ~AscendingIterator() = default; //distuctor
        AscendingIterator& operator=(AscendingIterator&& other) = delete; //tidy

        // constructor
        AscendingIterator(MagicalContainer& container, size_t index) : container(container), index(index) {
            if (index > container.mysticalElements.size()) {
                throw invalid_argument("Index out of bounds");
            }
        }


        // assigns the iterator to another iterator
        AscendingIterator& operator=(const AscendingIterator& other)
        {
            // check if it is the same type
            if(&this->container != &other.container){
                throw std :: runtime_error("containers are not the same type");
            }
            // if not the same one
            if(this != &other) {
                this->index = other.index;
            }

            return *this;
        }

        // operators:  == , != , > , < , * , ++ 
        bool operator==(const AscendingIterator& other) const{ //// compares 2 iterators
            return this->index == other.index;
        }
        bool operator!=(const AscendingIterator& other) const{
             return !(*this == other);
        }
        bool operator>(const AscendingIterator& other) const{
            return this ->index > other.index;
        }
        bool operator<(const AscendingIterator& other) const{
            return this ->index < other.index;
        }

         // (*) - returns the value of the element we are at
        int operator*() const{ 
            return container.mysticalElements[(index)];
        }

        AscendingIterator& operator++(){
             if (this ->index >= this->container.size()){
                throw std :: runtime_error("you are reached to end of container.");
            }

            index++;
            return *this;
        }

        /*
        • begin(type): Returns the appropriate iterator (ascending, cross, or prime)
         pointing to the first element of the container based on the specified type.
        */
         AscendingIterator begin() const{
            return AscendingIterator(container);
        }

        /*
        • end(type): Returns the appropriate iterator (ascending, cross, or prime)
         pointing one position past the last element of the container based on the specified type.
        */
        AscendingIterator end() const{
            return AscendingIterator (container, container.mysticalElements.size());
        }

    };






    /*
    //class SideCrossIterator
    //example 1,2,4,5,14 -> 1,14,2,5,4
    */


    class SideCrossIterator {
        
    private:
        MagicalContainer& container;

        std::vector<int>::size_type index; //count the steps (position)
        std::vector<int>::size_type currentLocationIndex; //current location

    public:

         // distructor,default and copy constructors and Assignment operator(tidy ask for more)
        SideCrossIterator(MagicalContainer& container) : container(container), index(0), currentLocationIndex(0){}
        SideCrossIterator(const SideCrossIterator& other) : container(other.container), index(other.index), currentLocationIndex(other.currentLocationIndex){}
        ~SideCrossIterator() = default;
        SideCrossIterator(SideCrossIterator&& other) = default; //tidy
        SideCrossIterator& operator=(SideCrossIterator&& other) = delete; //tidy
     
        //constructor
        SideCrossIterator(MagicalContainer& container,size_t index) : container(container), index(index), currentLocationIndex(0) {
            if (index > container.mysticalElements.size()) {
                throw invalid_argument("Index out of bounds");
            }
        }

        SideCrossIterator& operator=(const SideCrossIterator& other){
            if(&this->container != &other.container){
                throw std :: runtime_error("containers are not the same type");
            }
            if(this != &other) {
                this->index = other.index;
            }

            return *this;
        }

        // operators:  == , != , > , < , * , ++ 
        bool operator==(const SideCrossIterator& other) const{
            return this->index == other.index;
        }
        bool operator!=(const SideCrossIterator& other) const{
            return !(*this == other);     
        }
        bool operator>(const SideCrossIterator& other) const{
            return this ->index > other.index;
        }
        bool operator<(const SideCrossIterator& other) const{
            return this ->index < other.index;
        }

        // we are  returning the specialIndex used
        int operator*() const{
            return container.mysticalElements[(currentLocationIndex)];
        }

        SideCrossIterator& operator++(){
              if(index >= (container).mysticalElements.size()){
                throw std::runtime_error("you are at end of container");
            }

            ++index;
           
            if (index%2 == 0){  // index/2 from left side
                currentLocationIndex = index/2;
            }
            else{
                //calculate location
                currentLocationIndex = (container).mysticalElements.size()-1-(index/2) ; // index/2 from the end of the container 
            }
            return *this;
        }


        /*
        • begin(type): Returns the appropriate iterator (ascending, cross, or prime)
         pointing to the first element of the container based on the specified type.
        */
        SideCrossIterator begin() const{
            return SideCrossIterator(container);
        }


        /*
        • end(type): Returns the appropriate iterator (ascending, cross, or prime)
         pointing one position past the last element of the container based on the specified type.
        */
        SideCrossIterator end() const{
            return SideCrossIterator(container, container.mysticalElements.size());
        }


     
    };



    /*
    //class PrimeIterator
    //example 1,2,4,5,14 -> 2,5
    */

    class PrimeIterator {

    private:
        MagicalContainer& container;
        std::vector<int>::size_type index; //position

    public:

         // distructor,default and copy constructors and Assignment operator(tidy ask for more)
        PrimeIterator(MagicalContainer& container): container(container), index(0){}
        PrimeIterator(const PrimeIterator& other) : container(other.container), index(other.index){}
        ~PrimeIterator() = default; // destructor

        PrimeIterator(PrimeIterator&& other) = default; //tidy
        PrimeIterator& operator=(PrimeIterator&& other) = delete; //tidy
        
        // Constructor
        PrimeIterator(MagicalContainer& container, size_t index) : container(container), index(index) {
            if (index > container.mysticalElements.size()) {
                throw invalid_argument("index out of bound");
            }
        }


        // Assigns the iterator to another one
        PrimeIterator& operator=(const PrimeIterator& other){
            if(&container != &other.container){
                throw std :: runtime_error("containers are not the same type");
            }
            if(this != &other) {
                this->index = other.index;
            }
            return *this;
        }

        // operators:  == , != , > , < , * , ++ 
        bool operator==(const PrimeIterator& other) const{
            return this->index == other.index;
        }
        bool operator!=(const PrimeIterator& other) const{
            return !(*this == other);
        }
        bool operator>(const PrimeIterator& other) const{
            return this ->index > other.index;
        }
        bool operator<(const PrimeIterator& other) const{
            return this ->index < other.index;
        }

        // returns the value of number in that index
        int operator*() const{
            return *container.primeElements[(index)];
        }


        PrimeIterator& operator++(){

             // checks if not empty first
            if(this->container.primeElements.empty()){
                throw std::runtime_error("their is no number primes found");
            }
            // checks if it reached to the end
            if (this ->index >= this->container.primeElements.size()){
                throw std :: runtime_error("reached to the end of container");
            }
            index++;
            return *this;
        }


        // Uses default constructor ,now index = 0
         /*
        • begin(type): Returns the appropriate iterator (ascending, cross, or prime)
         pointing to the first element of the container based on the specified type.
        */
        PrimeIterator begin() const{
            return PrimeIterator(container);
        }




        /*
        • end(type): Returns the appropriate iterator (ascending, cross, or prime)
         pointing one position past the last element of the container based on the specified type.
        */
        PrimeIterator end() const{
            return PrimeIterator((this->container), (container).primeElements.size());
        }


    };




};
}

#endif