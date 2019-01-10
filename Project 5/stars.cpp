//
//  main.cpp
//  stars
//
//  Created by Abhishek Naik on 11/13/17.
//  Copyright © 2017 AbhishekNaik. All rights reserved.
//


#include "utilities.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <random>
#include <string>


using namespace std;

//sets the word list to document
const char WORDFILENAME[] = "/Users/abhisheknaik/Desktop/teststars.txt";

//declaration of functions
int runOneRound(const char words[][7], int nWords, int wordnum);
bool hasWord(const char words[][7], const char probeWord[7], int numWords);
bool isValidWord(const char probeWord[7]);
void countStarsPlanets(const char words[][7], const char probeWord[7], int);


int main()
{
    //declaration of variables and arrays
    const int MAXWORDS = 9000;
    const int MAXWORDLEN = 6;
    int roundScore = 0;
    int arraySize = 7265;
    int maxScore = 0;
    int minScore = 1000000;
    double avgScore = 0;
    int totalScore = 0;
    int numRounds = 0;
    char w[MAXWORDS][MAXWORDLEN + 1];
    int n = getWords(w, arraySize, WORDFILENAME);
    if(n < 1){//checks that getWords was implemented properly
        cout<<"No words were loaded, so I can't play the game.";
        return -1;
    }
    if(n > MAXWORDS)
        return -1;
    
    cout<<"How many rounds do you want to play? ";
    cin>>numRounds;
    cin.ignore(10000, '\n');
    if(numRounds<0){
        cerr<<"The number of rounds must be positive."<<endl;//terminates program if number of words is negative
        return -1;
    }
    cout<<endl;
    
    //forces doubles to contain two decimal places
    cout.setf(ios::fixed);
    cout.precision(2);
        
    
    //runs the number of tries that the user inputs
    for(int i = 0; i < numRounds; i++){
        int r = randInt(1, n-1);//randomly generates index of secret word between 1 and one less than the number of words in the array
        cout<< "Round "<<i+1<<endl;
        cout<<"The secret word is "<<strlen(w[r])<<" letters long"<<endl;
        roundScore = runOneRound(w, n, r);//calls runOneRound and sets score to roundScore
        if(roundScore == -1){//terminates program if runOneRoun encountered an error
            cerr<<"There was an error, try again."<<endl;
            return -1;
        }
        totalScore += roundScore;//keeps a running total of score to calculate the average score
        if(roundScore > maxScore)
            maxScore = roundScore;//sets max score if roundScore is greater than maxScore
        if(roundScore < minScore)
            minScore = roundScore;//sets min score if roundScore is greater than minScore
        avgScore = (double)totalScore/(i+1);//calculates average score
        if(roundScore == 1)//writes out the score
            cout<<"You got it in 1 try."<<endl;
        else
            cout<<"You got it in "<<roundScore<<" tries."<<endl;
        cout<<"Average: "<<avgScore<<", minimum: "<<minScore<<", maximum: "<<maxScore<<endl; //prints stats for that round
        cout<<endl;
    }
}

//runs one round of the game with the array of words, the number of words, and the number of the secret word
int runOneRound(const char words[][7], int nWords, int wordnum){
     
    int scoreCounter = 1;
    char probeWord[MAXWORDLEN+1];
    if(nWords < 0 || wordnum < 0 || wordnum >= nWords)//returns -1 if arguments are incorrect
        return -1;
    for(;;){
        cout<<"Probe word: ";
        cin.getline(probeWord, MAXWORDLEN+1);
        if(!isValidWord(probeWord)){//checks to make sure that the probe word is between 4 and 6 characters and is lowercase
            cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
            continue;
        }
        if(!hasWord(words, probeWord, nWords)){//checks to make sure that the probe word is a valid word in the word list
            cout<<"I don't know that word."<<endl;
            continue;
        }
        if(strcmp(probeWord, words[wordnum]) == 0){//checks to see if the probe word is the secret word
            //scoreCounter++;
            return scoreCounter;
        }
        countStarsPlanets(words, probeWord, wordnum);//calculates and prints the planets and stars in the probe word
        scoreCounter++;//increments score counter
    }
    
}

//checks that the probe word is in the list
bool hasWord(const char words[][7], const char probeWord[7], int numWords){
    for(int j = 0; j< numWords; j++){
        if(strcmp(probeWord, words[j]) == 0)
            return true;
    }
    return false;
}

//checks that the probe word is valid by checking its size is valid and that it consists of lower case letters
bool isValidWord(const char probeWord[7]){
    if(strlen(probeWord) > 6 || strlen(probeWord) < 4)
       return false;
    for(int i = 0; i < strlen(probeWord); i++){
        if(!isalpha(probeWord[i]) && !islower(probeWord[i]))
            return false;
    }
    return true;
}

//calculates and prints the planets and stars in the porbe word
void countStarsPlanets(const char words[][7], const char probeWord[7], int wordnum){
    char copySecret[MAXWORDLEN+1];
    char copyProbe[MAXWORDLEN+1];
    
    int stars = 0;
    int planets = 0;
    
    //copies the probe word and the secret word into copy ctrings that can be maipulated
    strcpy(copySecret, words[wordnum]);
    strcpy(copyProbe, probeWord);
    
    for(int i = 0; i < strlen(copyProbe); i++){//finds stars and replaces those letters with spaces
        if(copyProbe[i] == copySecret[i]){
            copyProbe[i] = ' ';
            copySecret[i] = ' ';
            stars++;
        }
    }
    for(int i = 0; i < strlen(copyProbe); i++){
        for(int j = 0; j < strlen(copySecret); j++){
            if((copyProbe[i] == copySecret[j]) && copyProbe[i]!=' '){//finds planets by finding pairs that are not spaces
                planets++;
                break;//avoids double counting
            }
        }
    }
    cout<<"Stars: "<<stars<<", Planets: "<<planets<<endl;//prints the planets and stars
}






