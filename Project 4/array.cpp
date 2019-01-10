//
//  main.cpp
//  array
//
//  Created by Abhishek Naik on 11/4/17.
//  Copyright © 2017 AbhishekNaik. All rights reserved.
//

#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
#include <array>

using namespace std;


int appendToAll (string [], int, string);
int lookup (const string [], int, string);
int positionOfMax (const string [], int);
int rotateLeft (string [], int, int);
int countRuns (const string [], int);
int flip (string [], int);
int differ (const string [], int, const string [], int);
int subsequence (const string [], int, const string [], int);
int lookupAny (const string [], int, const string [], int);
int split (string [], int, string);
//bool hasSubsequence (const string [],const string [], int, int);



int main()
{
    string h[7] = { "selina", "reed", "diana", "tony", "", "logan", "peter" };
    assert(lookup(h, 7, "logan") == 5);
    assert(lookup(h, 7, "diana") == 2);
    assert(lookup(h, 2, "diana") == -1);
    string g[4] = { "selina", "reed", "peter", "sue" };
    assert(positionOfMax(g, 2) == 0);
    assert(positionOfMax(h, 1) == 0);
    assert(positionOfMax(g, 3) == 0);
    assert(positionOfMax(h, 4) == 3);
    assert(positionOfMax(g, 4) == 3);
    assert(positionOfMax(g, 0) == -1);
    assert(positionOfMax(h, 0) == -1);
    
    //string g[4] = { "selina", "reed", "peter", "sue" };
    assert(differ(h, 4, g, 4) == 2);
    assert(appendToAll(g, 4, "?") == 4 && g[0] == "selina?" && g[3] == "sue?");
    assert(rotateLeft(g, 4, 1) == 1 && g[1] == "peter?" && g[3] == "reed?");
    
    string e[4] = { "diana", "tony", "", "logan" };
    assert(subsequence(h, 7, e, 4) == 2);
    
    string d[5] = { "reed", "reed", "reed", "tony", "tony" };
    assert(countRuns(d, 2) == 0);
    
    string f[3] = { "peter", "diana", "steve" };
    assert(lookupAny(h, 7, f, 3) == 2);
    assert(flip(f, 3) == 3 && f[0] == "steve" && f[2] == "peter");
    
    assert(split(h, 7, "peter") == 3);
    
    
    cout << "All tests succeeded" << endl;
    
    return 0;
}

int appendToAll (string a[], int n, string value){
    if(n<0)
        return -1;
    else
        for(int i = 0; i < n; i++){
            a[i]+= value;
        }
    return n;
}

int lookup (const string a[], int n, string target){
    if(n<0)
        return -1;
    for(int i = 0; i < n; i++){
        if(a[i] == target)
            return i;
    }
    return -1;
}

int rotateLeft (string a[], int n, int pos){
    if(n<0)
        return -1;
    string temp = a[pos];
    int i = pos;
    while(i < n-1){
        a[i] = a[i+1];
        i++;
    }
    a[n-1] = temp; //moves value to the last index in scope
    return pos;
}

int countRuns (const string a[], int n){
    int counter = 0;
    if (n<0)
        return -1;
    for(int i = 0; i < n-1; i++){
        if(a[i] != a[i+1])
            counter++;
    }
    if(counter>0)
        return counter +1; //adds one to the number of changes to achieve number of unique elements if the number of changes is greater than 0
    else
        return counter;
}

int flip (string a[], int n){
    if(n<0)
        return -1;
    string temp = "";
    for(int i = 0; i < n/2; i++){
        temp = a[i]; //temporarily saves a[i]
        a[i] = a[n-1-i]; //swaps the values
        a[n-1-i] = temp;
    }
    return n;
}

int differ (const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2< 0)
        return -1;
    if(n1<n2){ //finds limiting n value
        for(int i=0; i<n1; i++){
            if(a1[i]!=a2[i])
                return i; // returns differing value
        }
        return n1;
    }
    else{
        for(int i=0; i<n2; i++){
            if(a1[i] != a2[i])
                return i;
        }
        return n2;
    }
}

int lookupAny (const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2< 0)
        return -1;
    for(int i = 0; i < n1; i++){
        for(int j = 0; j < n2; j++){
            if(a1[i] == a2[j])
                return i;
        }
    }
    return -1;
}

int subsequence (const string a1[], int n1, const string a2[], int n2){
    if(n1<0 || n2< 0)
        return -1;
    if(n2 == 0)
        return 0;
    int temp;
    for(int i = 0; i < n1; i++){
        for(int k = 0; k < n2; k++){
            if(a1[i] == a2[k]){ //finds values that are the same in both arrays
                temp = i; //saves position of first of potential subsequence
                for(int j = 0; j < n2; j++){
                    if((i+j)<n1 && (k+j) <n2){ //compares the values by checking the next n2 values and sees if they are equal
                        if(a1[i+j] == a2 [k+j])
                            return temp; //returns the first position
                    }
                }
            }
        }
    }
    
    return -1;
}

int positionOfMax (const string a[], int n){
    if(n<0 || n==0)
        return -1;
    string maximum = "";
    int max=0;
    int i = 0;
    //sets max value to string maximum
    while (i<n){
        if(a[i]>maximum)
            maximum = a[i];
    i++;
    }
    //finds the first value with maximum value, breaks and then returns that value
    for(int j = 0; j< n; j++){
        if(a[j] == maximum){
            max = j;
            break;
        }
    }
    return max;
}

int split (string a[], int n, string splitter){
    
    //finds any splitters in the array, moves them to the end of the array
    int num = 0;
    for(int i = 0; i < n; i++){
        if(a[i] == splitter){
            rotateLeft(a, n, i);
            i--;
            num++;
        if(i>=(n-num))
            break;
        }
    }
    //goes through array again and moves any values greater than splitter to the end and moves a counter closer toward center of array every time
    int div = n;
    for(int i = 0; i<n; i++){
        if(a[i]>splitter){
            rotateLeft(a, n, i);
            i--;    //to avoid skipping values in the array due to reorganizations
            div--;
        }
        //if the loop gets passed the divide between values less than or greater than splitter, it breaks from loop
        if(i>=div)
            break;
    }
    return div;
    
}







