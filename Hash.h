// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Daniel Budavari
// ASU ID:1224612207
// Description: hash fucntions for inserting into proper loactions
// uses linkedList functions as well. These functions are mainly used by our table in the main

#include "LinkedList.h";

using namespace std;

class Hash
{
private:
    LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
    int m;                     //slots number of the hash table
    double numCars;
public:
    Hash(int size);
    ~Hash();
    bool hashSearch(string model, string make, int vin);
    bool hashInsert(string model, string make, int vin, double price);
    bool hashDelete(string model, string make, int vin);
    int hashLoadFactor();
    void hashDisplay();
    int hashFunction(string key);
    int getHashSize();
    double getNumCars();
};

//constructor
Hash::Hash(int size) {
    m = size;
    hashTable = new LinkedList[m];
    numCars = 0; //used for loadFactor calculations
}

//Destructor
Hash::~Hash() {
    delete[] hashTable;
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashSearch(string model, string make, int vin) {
  
    int key = hashFunction(model + make + to_string(vin)); //create key
    bool found = hashTable[key].searchCar(vin);     //call linked list search

    if (found == true) {
        cout << "\n" << left
            << setw(18) << model
            << setw(18) << make
            << setw(8) << vin
            << " is found inside the hash table." << endl;
        return found;
    }
    else {
        cout << "\n" << left
            << setw(18) << model
            << setw(18) << make
            << setw(8) << vin
            << " is NOT found inside the hash table." << endl;
        return found;
    }
}

//hashInsert inserts a Car with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string model, string make, int vin, double price) {
  
    int key = hashFunction(model + make + to_string(vin)); //create key
  
    bool result = hashTable[key].insertCar(model, make, vin, price); //call linked insert
    if (result == true) {
        numCars++;  //increment numCars, used for loadFactor calculations
    }

    return result;
}

//hashDelete deletes a Car with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of model, make and vin
bool Hash::hashDelete(string model, string make, int vin) {
    
    bool found = hashSearch(model, make, vin); //first search if it exists

    int key = hashFunction(model + make + to_string(vin)); 
    bool result = false;

    result = hashTable[key].deleteCar(vin); //call delete from linkedList

    if (result == true) {
        cout << "\n";
        cout << setw(18) << model
            << setw(18) << make
            << setw(8) << vin
            << " is deleted from hash table." << endl;
        return true;
    }
       //if the car cannot be deleted
    cout << "\n";
    cout << setw(18) << model
         << setw(18) << make
         << setw(8) << vin
         << " is NOT deleted from hash table." << endl;
    return false;
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor() {
  
    int longestList = 0;
    for (int i = 0; i < m; ++i) {
        int listSize = hashTable[i].getSize();
        
        if (listSize > longestList) { //find the longest list in the hash
            longestList = listSize;
        }
    }
    int realFac = longestList; //now we have our longest list for calculations
    return realFac;
}

int Hash::getHashSize() {
    return m;
}

double Hash::getNumCars() {
    return numCars;
}
//This function prints all elements from the hashTable.
void Hash::hashDisplay() {
   
    for (int i = 0; i < m; ++i) {
        
        int listSize = hashTable[i].getSize();
        cout << "\nHashTable[" << i << "], size = " << listSize << endl;

        if (listSize == 0) {
            cout << "empty" << endl;
        }
        else {
            struct Car* temp = hashTable[i].getHead();
           
            while (temp != NULL) {
                cout << left;
                cout << setw(12) << temp->model 
                    << setw(12) << temp->make
                    << setw(8) << temp->vin
                    << setw(8) << fixed << setprecision(2) 
                    << temp->price << endl;
                temp = temp->next;
            }
        }
    }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we will hash the key to
int Hash::hashFunction(string key) {
    
    int k = 0;
    int hashSlot = 0;

    for (char ascii : key) { //find the ascii value of the entire key
        k += ascii;
    }

    return hashSlot = k % m; //use modolus using the size of the hash
   
}