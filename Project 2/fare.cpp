//
//  main.cpp
//  fare
//
//  Created by Abhishek Naik on 10/13/17.
//  Copyright © 2017 AbhishekNaik. All rights reserved.
//

#include <iostream>
using namespace std;
#include <string>


int main()
{
    double fare = 1.35;     //declaration and initialization of variables
    double boundaryFare = 0.55;
    double totalFare = 0;
    int age = 0;
    string student;
    string destination;
    int numCrossed = 0;
    
    
    cout << "Age of rider?: ";  //This block asks for and reads in the age of the rider while checking for an invalid input
    cin >> age;
    cin.ignore(10000, '\n');//clears any left over spaces
    if(age < 0){
        cout << "---"<<endl;
        cout << "The age must not be negative" << endl; 
        return 1;
    }
    
    cout << "Student?: ";   //This block asks for and reads in the student status of the rider while checking for an invalid input
    getline(cin, student);
    if(student != "y" && student != "n"){
        cout << "---"<<endl;
        cout << "You must enter y or n" << endl;
        return 1;
    }
    
    cout << "Destination: ";//This block asks for and reads in the destination of the rider while checking for an invalid input
    getline(cin, destination);
    if(destination == ""){
        cout << "---"<<endl;
        cout << "You must enter a destination" << endl;
        return 1;
    }
    
    
    cout << "Number of boundaries crossed: ";   //This block asks for and reads in the number of boundaries the rider will cross while checking for an invalid input
    cin >> numCrossed;
    if(numCrossed < 0){
        cout << "---"<<endl;
        cout << "The number of zone boundaries crossed must not be negative" << endl;
        return 1;
    }
    
    cout.setf(ios::fixed); //sets all doubles values to contain two decimal places.
    cout.precision(2);
    
    if(numCrossed<2){   //checks if the number of boundaries crossed is less than two as the breaks apply to only short trips
        if(age<18){ //checks to see if the rider is younger than 18, which is one criterion for the break to apply
            totalFare = .65;
            cout << "---"<<endl;
            cout << "The fare to "<<destination<<" is $"<< totalFare<< endl;
            return 0;
        }
        if(student == "y"){ //checks for the other criterion if the age fails to be below 18
            if(numCrossed < 1){ //checks for seniors who may also be students
                if(age>65){
                    totalFare=.45;
                    cout << "---"<<endl;
                    cout << "The fare to "<<destination<<" is $"<< totalFare<< endl;
                    return 0;
                }
            }
            totalFare = .65; //sets the far to .65 for students making a short trip
            cout << "---"<<endl;
            cout << "The fare to "<<destination<<" is $"<< totalFare<< endl;
            return 0;
        }
        if(numCrossed < 1){ //checks for trips crossing no boundaries, which gives senior citizens a larger break
            if(age>65){
                totalFare=.45;
                cout << "---"<<endl;
                cout << "The fare to "<<destination<<" is $"<< totalFare<< endl;
                return 0;
            }
        }
    }
    
    if(age>65){ //sets the fare for the senior citizen who does not meet the criteria for any breaks
        fare = .55;
        boundaryFare = .25;
    }
    
    totalFare = fare + (numCrossed*boundaryFare);   //the default fare for the rider who does not meet any of the criteria for breaks
    
    cout << "---"<<endl;
    cout << "The fare to "<<destination<<" is $"<< totalFare<< endl;
    
    
    
    return 0;
}
