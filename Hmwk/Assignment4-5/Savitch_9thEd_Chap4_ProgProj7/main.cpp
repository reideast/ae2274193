/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 25, 2015, 9:34 PM
    Purpose: Compute the different between a start time and a time up to 24 hours in the future
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes

//computeDifference: Calc how many minutes are between two times <24 hours
int computeDifference(int startHour, int startMin, bool startIsAM, int futureHour, int futureMin, bool futureIsAM);
//Preconditions:
//  hours must be between 1-12, minutes must be between 0 and 59
//  isAM variables are true if AM, false if PM
//Postconditions:
//  returns how many minutes are between the times

//absoluteTime: Given a time, compute how many minutes have passed since midnight of that day
int absoluteTime(int hour, int minute, bool isAM);
//Preconditions:
//  hours must be between 1-12, minutes must be between 0 and 59
//  isAM variable are true if AM, false if PM
//Postconditions:
//  returns how many minutes hour:minutes is since midnight

//getTime: inputs a time from <iostream>
void getTime(int& hour, int& minute, bool& isAM);
//Preconditions:
//  hour, minute, and isAM are initialized variables
//Postconditions:
//  hour, minute, and isAM are set to time inputted (isAM is true for AM, false for PM)


//GetInput: Get input from <iostream> between a minimum and maximum value
//  (From my Savitch_9thEd_Chap4_ProgProj1)
void getInput(string prompt, int& input, int min = 0, int max = ~(1 << (sizeof(int) * 8) - 1));
void getInput(string prompt, float& input, float min = 0, float max = 1.0e38f);
//Preconditions:
//  prompt contains something to display through cout.
//  input is an initialized variable.
//  min/max contains the range desired (inclusive)
//    if not included, min/max will be zero to the largest integer on this system (calculated a bit shift based on the number of bytes in an int, then inversion (only works on two's complement based systems!))
//    for a float, a hard-coded value of 1.0e38f is chosen (based on windows 7 x64 g++ machine)
//Postconditions:
//  input will contain a valid value within the range

//Execution Begins Here
int main(int argc, char** argv)
{
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  while (!isUserFinished)
  {
    int startHour = 0, startMin = 0, futureHour = 0, futureMin = 0, minInFuture = 0;
    bool startIsAM = false, futureIsAM = false;
    
    cout << "What is the start time?" << endl;
    getTime(startHour, startMin, startIsAM);
    cout << "The start time is " << startHour << ":" << startMin << " " << (startIsAM ? 'A' : 'P') << 'M' << '.' << endl;
    cout << endl;
    cout << "What is the future time?" << endl;
    getTime(futureHour, futureMin, futureIsAM);
    cout << "The future time is " << futureHour << ":" << futureMin << " " << (futureIsAM ? 'A' : 'P') << 'M' << '.' << endl;
    cout << endl;
    
    minInFuture = computeDifference(startHour, startMin, startIsAM, futureHour, futureMin, futureIsAM);
    cout << "The time machine must travel " << minInFuture << " minutes into the future." << endl;
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to do more calculations? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
    else
      cout << endl; //a blank line for readability
  }
  return 0;
}


int computeDifference(int startHour, int startMin, bool startIsAM, int futureHour, int futureMin, bool futureIsAM)
{
  //get minutes from midnight for each time
  int startTime = absoluteTime(startHour, startMin, startIsAM);
  int futureTime = absoluteTime(futureHour, futureMin, futureIsAM);
  
  //if the time in the future is earlier in the day than the time in the past,
  //  then adjust it to be in the future by adding 24-hours worth of minutes
  //Note: I judged that problem was ambiguous if "up to 24 hours" was inclusive of 24 hours,
  //  so I decided if the start time == future time, they did in fact deign to go a full 24 hours
  if (futureTime <= startTime)
    futureTime += 24 * 60; // += 24-hours
  
  //return the difference in the times, ie. how many minutes have passed
  return futureTime - startTime;
}

//absoluteTime: Given a time, compute how many minutes have passed since midnight of that day
int absoluteTime(int hour, int minute, bool isAM)
{
  //hour (12 => 0) * 60 minutes, plus minutes, add 12 hours worth of minutes if afternoon
  return ((hour % 12) * 60) + minute + (isAM ? 0 : (12 * 60));
}

//getTime: inputs a time from <iostream>
void getTime(int& hour, int& minute, bool& isAM)
{
  getInput("Hour? ", hour, 1, 12);
  getInput("Minute? ", minute, 0, 59);
  char a = 0, b = 0;
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << "AM or PM? ";
    cin >> a >> b;
    //do not test for M, doesn't change value
    if (a == 'A' || a == 'a')
    {
      isAM = true;
      isInputValid = true;
    }
    else if (a == 'P' || a == 'p')
    {
      isAM = false;
      isInputValid = true;
    }
    else
    {
      cout << "You must input \"AM\" or \"PM\"." << endl;
    }
  }
}

void getInput(string prompt, int& input, int min, int max)
{
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << prompt;
    cin >> input;
    if (input < min)
      cout << "The input cannot be less than " << min << ". Please input again." << endl;
    else if (input > max)
      cout << "The input cannot be greater than " << max << ". Please input again." << endl;
    else
      isInputValid = true;
  }
}

void getInput(string prompt, float& input, float min, float max)
{
  bool isInputValid = false; //controls input loop (ie, loop until input is right)
  while (!isInputValid)
  {
    cout << prompt;
    cin >> input;
    if (input < min)
      cout << "The input cannot be less than " << min << ". Please input again." << endl;
    else if (input > max)
      cout << "The input cannot be greater than " << max << ". Please input again." << endl;
    else
      isInputValid = true;
  }
}
