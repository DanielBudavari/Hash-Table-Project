// ASU CSE310 Assignment #5 Spring 2024
// Name of Author: Daniel Budavari
// ASU ID:1224612207
// Description: A simple linked list that implements a list of Car objects. A user can
//              perform searching, insertion or deletion on the linked list.
//              this performs the bulk of the work, along with key Hash.h uses many of these functions

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Car
{
    string model, make;
    int vin;
    double price;
    struct Car* next;
};

class LinkedList
{
private:
    struct Car* head;
    int size;      //a variable represents number of Cars inside the list
public:
    LinkedList();
    ~LinkedList();
    Car* getHead();
    int getSize();
    bool searchCar(int carVIN);
    bool insertCar(string model, string make, int vin, double price);
    bool deleteCar(int carVIN);
    void displayList();
};

//Constructor
LinkedList::LinkedList() {
    head = NULL;
    size = 0;
}

//Destructor
LinkedList::~LinkedList() {
    int carCount = 0;

    //starts from the head and traverses to the end deleting every element
    while (head != NULL) {
        struct Car* delList = head;
        head = head->next;
        delete delList;
        carCount++;
        size--;
    }
}

Car* LinkedList::getHead() {
    return head;
}

//Return number of Cars inside the Linked list
int LinkedList::getSize() {
    return size;
}

//This function searches the Car list with the given Car VIN
//it returns true if the corresponding Car is found, otherwise it returns false.
bool LinkedList::searchCar(int carVIN) {
    
    struct Car* carList = head;

    while (carList != NULL) {
        if (carVIN == carList->vin) {
            return true;
        }
        else {
            carList = carList->next;
        }
    }
    return false;
}

//Insert the parameter Car at the head of the linked list.
//returns true if it is inserted successfully and false otherwise
bool LinkedList::insertCar(string model, string make, int vin, double price) {
    //assign all the proper values
    Car* carAdded = new Car;
    carAdded->model = model;
    carAdded->make = make;
    carAdded->vin = vin;
    carAdded->price = price;
    carAdded->next = NULL;

    //when list is empty, add car
    if (head == NULL) {
        head = carAdded;
        size++;
        return true;
    }
    //else the list is not empty add the car where necessary
    carAdded->next = head;
    head = carAdded;
    size++;
    return true;
    
}

//Delete the Car with the given Car VIN from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteCar(int carVIN) {
    
    //car is not found, cant be deleted
    if (searchCar(carVIN) == false) {
        cout << "Car is not in the list, cannot be deleted" << endl;
        return false;
    }

    Car* curr = head;
    Car* prev = nullptr;

    // Traverse the list to find the car with the given VIN
    while (curr != nullptr) {
        
        if (curr->vin == carVIN) {
           
            if (prev == nullptr) {
                head = curr->next;
            }
            else {
                
                prev->next = curr->next;
            }
            delete curr; 
            size--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }

    return false;

}

//This function displays the content of the linked list.
void LinkedList::displayList() {
    struct Car* temp = head;
    if (head == NULL)
    {
        //empty linked list, print nothing here
        cout << "The linked list is empty." << endl;
    }
    else
    {
        while (temp != NULL)
        {
            cout << left << setw(18) << temp->model
                << left << setw(18) << temp->make
                << right << setw(8) << temp->vin
                << setw(10) << fixed << setprecision(2) << temp->price << "\n";
            temp = temp->next;
        }
    }
}