//
//  main.cpp
//  keyboard2
//
//  Created by Abhishek Naik on 10/28/17.
//  Copyright © 2017 AbhishekNaik. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

//initializing all my functions

bool hasCorrectSyntax(string);
bool isValidLetter(char);
bool isValidAccidental(string, int);
bool isValidNum(string, int);
bool isValidBeat(string);
int encodeSong(string, string&, int&);
char encodeNote(int, char, char);
int isPlayable(string);

int main(){
    string t, instructions = "";
    int badBeat;
    for (;;)
    {
        cout << "Enter song: ";
        getline(cin, t);
        if (t == "quit")
            break;
        cout << encodeSong(t, instructions, badBeat)<< endl;
        cout << instructions <<endl;
        
    }
}

//checks if the string input is syntyactically correct by checking every beat

bool hasCorrectSyntax(string song){
    int i =0;
    string beat="";
    while(i<song.size()){
        if(song[i] != '/')
            beat+= song[i];
        else
            if(!isValidBeat(beat))
                return false;
            else{
                beat = "";
                
            }
        i++;
    }
    if(song[song.size()-1] == '/')
        return true;
    else
        return false;
}

//checks if every beat is valid (syntactically) by checking if every letter, number, accidental are valid and in correct order
bool isValidBeat(string beat){
    int j =0;
    
    while(j<beat.size()){
        if(isalpha(beat[j]))
            if(!isValidLetter(beat[j]))
                return false;
        if(beat[j] == '#' || beat[j] == 'b')
            if(!isValidAccidental(beat, j))
                return false;
        if(isdigit(beat[j]))
            if(!isValidNum(beat, j))
                return false;
        j++;
    }
    return true;
}

//checks for a valid note letter
bool isValidLetter(char letter){
    if(letter == 'A' || letter == 'B' || letter == 'C' || letter == 'D'|| letter == 'E' || letter == 'F' || letter == 'G' || letter == 'b')
        return true;
    else
        return false;
}

//checks if the accidental character and order is valid
bool isValidAccidental(string beat, int num){
    if(!isValidLetter(beat[num-1]))
        return false;
    else
        return true;
}

//checks that the octave number is valid
bool isValidNum(string beat, int num2){
    if(isalpha(beat[num2-1]))
        if(!isValidLetter(beat[num2-1]))
            return false;
    if(beat[num2-1] == '#' || beat[num2-1] == 'b' )
        if(!isValidAccidental(beat, num2-1))
            return false;
    return true;
    
}

//*************************************
//  encodeNote
//*************************************

// Given an octave number, a note letter, and an accidental sign, return
// the character that the indicated note is encoded as if it is playable.
// Return a space character if it is not playable.
//
// First parameter:   the octave number (the integer 4 is the number of the
//                    octave that starts with middle C, for example).
// Second parameter:  an upper case note letter, 'A' through 'G'
// Third parameter:   '#', 'b', or ' ' (meaning no accidental sign)
//
// Examples:  encodeNote(4, 'A', ' ') returns 'Q'
//            encodeNote(4, 'A', '#') returns '%'
//            encodeNote(4, 'H', ' ') returns ' '

char encodeNote(int octave, char noteLetter, char accidentalSign)
{
    // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** encodeNote was called with first argument = "
        << octave << endl;
    }
    
    // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
    //      to -1, 0,   1,   2,   3, ...,  11, 12
    
    int note;
    switch (noteLetter)
    {
        case 'C':  note =  0; break;
        case 'D':  note =  2; break;
        case 'E':  note =  4; break;
        case 'F':  note =  5; break;
        case 'G':  note =  7; break;
        case 'A':  note =  9; break;
        case 'B':  note = 11; break;
        default:   return ' ';
    }
    switch (accidentalSign)
    {
        case '#':  note++; break;
        case 'b':  note--; break;
        case ' ':  break;
        default:   return ' ';
    }
    
    // Convert ..., A#1, B1, C2, C#2, D2, ... to
    //         ..., -2,  -1, 0,   1,  2, ...
    
    int sequenceNumber = 12 * (octave - 2) + note;
    
    string keymap = "Z1X2CV3B4N5M,6.7/A8S9D0FG!H@JK#L$Q%WE^R&TY*U(I)OP";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
    
//encodes a song from each beat
}int encodeSong(string song, string& instructions, int& badBeat){
    int tempbadBeat=0;
    string copy = "";
    int n=0;
    string note = "";
    int notecounter = 0;
    copy = "";
    if (!hasCorrectSyntax(song))
        return 1;
    tempbadBeat = isPlayable(song);
        if (tempbadBeat == 0){
        while(n<song.size()){
            if(n == 0 && song[n] == '/' && song[n+1] == '/')
                copy += "  ";
            else if((n != 0 && n != song.size()-1) && song[n] == '/' && song[n-1] == '/')
                copy += " ";
            if(isalpha(song[n]) && song[n] != 'b'){
                //checks for note by itself
                if(!isdigit(song[n+1]) && song[n+1] != 'b' && song[n+1] != '#'){
                    note += encodeNote(4, song[n], ' ');
                    notecounter++;
                }
                //checks for note and accidendtal, no octave number
                if((song[n+1] == 'b' || song[n+1] == '#') && !isdigit(song[n+2])){
                    note += encodeNote(4, song[n], song[n+1]);
                    notecounter++;
                }
                //checks for note and octave number, no accidental
                if(isdigit(song[n+1])) {//&& (song[n+2] != 'b' || song[n+2] != '#')){
                    note += encodeNote((song[n+1]-'0'), song[n], ' ');
                    notecounter++;
                }
                //checks for all three, note, oct, and accidental
                if((song[n+1] == 'b' || song[n+1] == '#') && isdigit(song[n+2])){
                    note += encodeNote(song[n+2]-'0', song[n], song[n+1]);
                    notecounter++;
                }
                
            }
            //prints brackets around chords
            if(song[n] == '/'){
                if(notecounter > 1){
                    copy += "[";
                    copy += note;
                    copy += "]";
                }
                else{ //prints without brackets if there is one note per beat
                    copy += note;
                }
                note = "";//resets for next beat
                notecounter = 0;
            }
            n++;
        }
        //sets instructions to copy if copy was encoded into song, leaves instructions unchanged if copy is empty
        if(copy != "")
            instructions = copy;
        return 0;
    }
    else{
        badBeat = tempbadBeat; //sets badBeat to the value returned by isPlayable
        return 2;
    }
}

//checks if song is playable beat by beat and returns which beat is not playable, 0 if perfect
int isPlayable (string song){
    int k = 0;
    
    int beatcounter = 1;//keeps track of which beat is being evaluated
    while(k < song.size()){
        if(song[k] == 'C' && song[k+1] == 'b' && song[k+2] == '2')
            return beatcounter;
        if(isdigit(song[k]))//evaluates string for playability
            if(song[k] == '1' || song[k] == '2' || song[k] == '6' || song[k] == '7' || song[k] == '8' || song[k] == '9'){
                if(song[k] == '1' && song[k-1] == '#' && song[k-2] == 'B')
                    continue;
                else if(song[k] == '6' && song[k-1] == 'b' && song[k-2] == 'C')
                    continue;
                else if(song[k] == '6' && song[k-1] == 'C')
                    continue;
                else
                    return beatcounter; //returns which beat was not plahyable
            }
        if(song[k] == '/' && k != song.size()-1) //
            beatcounter++; //increments beatcounter when it meets a "/"
        k++;
    }
    return 0;
}
