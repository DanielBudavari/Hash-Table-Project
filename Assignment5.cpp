// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Daniel Budavari
// ASU ID:1224612207
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.


/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Car
//   object's hash value.

I get the has value by adding the ascii values of the string created from model
    make, price, and vin.
My hash function is the hashvalue % m where m is size of hash table

//(2)
Test Case 1#:
    Performance Ratio: 1.88
    Longest List: 6

Test Case 2#:
    Performance Ratio: 1.66
    Longest List: 9

Test Case 3#:
    Performance Ratio: 1.69
    Longest List: 8

Test Case 4#:
    Performance Ratio: 1.44
    Longest List: 25

//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
I would implement a hash function more similar to multiplicative hashing, 
taking m* key * mod 1 and taking the floor of the result
********************************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include "Hash.h"
#include <sstream>

using namespace std;
double price;

int main()
{
    int size = 0;
    int numOfCommand = 0;
    string model, make;
    int vin;
    
    string firstToken, command = "";

    cout << "Enter the size of the hash table: ";
    cin >> size;
    cin.ignore(20, '\n');
    Hash newHash(size);
    
    do {
        string oneLine;
        bool result;
        
        cout << "Enter model, make, vin, price. Type 'InsertionEnd' to terminate"  << endl;
        getline(cin, oneLine);

        if (oneLine == "InsertionEnd") {
            break; // Exit the loop if "InsertionEnd" is entered
        }
        else { //get car info using the comma as the delimiter
            string delimiter = ",";
            int pos = oneLine.find(delimiter);
            string token = oneLine.substr(0, pos);
            model = token;
            oneLine.erase(0, pos + delimiter.length());

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            make = token;
            oneLine.erase(0, pos + delimiter.length());

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            vin = stoi(token);
            oneLine.erase(0, pos + delimiter.length());

            pos = oneLine.find(delimiter);
            token = oneLine.substr(0, pos);
            price = stoi(token);
            oneLine.erase(0, pos + delimiter.length());
        }
        result = newHash.hashInsert(model, make, vin, price); //insert car using our info from the tokens

        if (result == true) {
            cout << "Car Inserted" << endl;
        } 
        else {
            cout << "Car NOT Inserted" << endl;
        }
    } while (true);

   
   // cout << "\nEnter number of commands: ";   //***need to comment out in submitting 
    cin >> numOfCommand;
    cin.ignore(20, '\n');
    for (int i = 0; i < numOfCommand; i++) {

        cout << "Enter command " << i + 1 << ": "; //plus one since i starts at 0
        string commandInpt;
        getline(cin, commandInpt);
        
        string delimiter = ","; //reuse comma delim.
        int pos = commandInpt.find(delimiter);
        string token = commandInpt.substr(0, pos);
        string firstToken = token;
        commandInpt.erase(0, pos + delimiter.length()); //take our token
        
        if (firstToken.compare("hashDisplay") == 0)  {
            
            newHash.hashDisplay();
        }
        else { 
            
            command = firstToken;
            
            if (command.compare("hashSearch") == 0) {
                //get the model make vin
                pos = commandInpt.find(delimiter);
                token = commandInpt.substr(0, pos);
                model = token;
                commandInpt.erase(0, pos + delimiter.length());

                pos = commandInpt.find(delimiter);
                token = commandInpt.substr(0, pos);
                make = token;
                commandInpt.erase(0, pos + delimiter.length());

                pos = commandInpt.find(delimiter);
                token = commandInpt.substr(0, pos);
                vin = stoi(token);
                commandInpt.erase(0, pos + delimiter.length());

                newHash.hashSearch(model, make, vin);
              
            }
            else if (command.compare("hashDelete") == 0) {
                //get the model make vin
                pos = commandInpt.find(delimiter);
                token = commandInpt.substr(0, pos);
                model = token;
                commandInpt.erase(0, pos + delimiter.length());

                pos = commandInpt.find(delimiter);
                token = commandInpt.substr(0, pos);
                make = token;
                commandInpt.erase(0, pos + delimiter.length());

                pos = commandInpt.find(delimiter);
                token = commandInpt.substr(0, pos);
                vin = stoi(token);
                commandInpt.erase(0, pos + delimiter.length());

                newHash.hashDelete(model, make, vin);

            }
            else if (command.compare("hashLoadFactor") == 0) {
                //calculate our ratios for load factor
                double idealLoadFactor = (newHash.getNumCars()) / (newHash.getHashSize()); //ideal calculations using numCars / the hash size
                double realFac = newHash.hashLoadFactor(); //calls the calculation in Hash.h
                double ratio =  realFac / idealLoadFactor; //final ratio calculation

                    cout << fixed << setprecision(2);
                cout << "The ideal load factor is: " << idealLoadFactor << endl;
                cout << "My hash table real load factor is: " << realFac << endl;
                cout << "My hash table performance ratio is: " << ratio << endl;

            }
            else {
                cout << "Invalid command" << endl;
            }
        }
    } //end for loop
    return 0;
}