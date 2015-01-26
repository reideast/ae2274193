/* 
    File:   main.cpp
    Author: Andrew Reid East
    Class: CSC-5 40718
    Created on January 25, 2015, 7:39 PM
    Purpose: simulate putting money in a vending machine
 */

//System Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
//buyAnItem: Let a user insert coins into a machine until they have spent enough to buy it
bool buyAnItem(float itemPrice, float& change);
//Preconditions:
//  itemPrice is the item's cost in dollars (must be in multiples of 5 cents, since this machine doesn't take pennies)
//  change is an initialized variable
//Postconditions:
//  returns true if the item was successfully bought
//  returns false if the user canceled the transaction
//  change will contain any money due back to the customer in dollars

//insertACoin: Asks the user to insert one valid coin or cancel the transaction
float insertACoin();
//Preconditions:
//  getInput function is available
//Postconditions:
//  returns the value of the coin inserted in dollars
//  returns a negative number if the user canceled the whole transaction

//itemPriceReached: Determines if enough money has been inserted to purchase an item
bool itemPriceReached(float price, float moneyIn, float& change);
//Preconditions:
//  price is the cost of the item in dollars
//  moneyIn is the total money in dollars
//  change is an initialized variable
//Postconditions:
//  returns true if moneyIn is enough to purchase the item at price dollars
//    and change will be set to any dollars over the purchase price
//  returns false if more money is needed
//    and change will not be modified


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
  cout << fixed << setprecision(2); //set up cout for $$
  
  //main program, loops until user asks to quit (copied from my Savitch_9thEd_Chap3_ProgProj1)
  bool isUserFinished = false; //controls main loop
  char quit = 0;
  while (!isUserFinished)
  {
    float change = 0.0f;
    
    //buy an item worth $3.50
    cout << "You are buying a deep fried twinkie!" << endl;
    if (buyAnItem(3.50f, change))
      cout << "Enjoy your item!";
    else
      cout << "Transaction canceled.";
    if (change > 0)
      cout << " Your change is $" << change;
    cout << endl;
    
    
    //determine if the user would like to repeat the calculation (copied from my Savitch_9thEd_Chap3_ProgProj1)
    cout << endl;
    cout << "Would you like to buy another item? (N to quit) ";
    cin >> quit;
    if (quit == 'N' || quit == 'n')
      isUserFinished = true;
    else
      cout << endl; //a blank line for readability
  }
  return 0;
}

bool buyAnItem(float itemPrice, float& change)
{
  float totalMoney = 0.0f;
  float currentCoin = 0.0f;
  while (!itemPriceReached(itemPrice, totalMoney, change)) //while the user has NOT inputted enough money to buy it
  {
    currentCoin = insertACoin();
    if (currentCoin < 0)
    {
      change = totalMoney; //return any money already inserted
      return false; //transaction canceled
    }
    else
    {
      cout << "You have inserted $" << currentCoin << ". ";
      totalMoney += currentCoin;
      cout << "The total money inserted is " << totalMoney << ". " << endl;
    }
  }
  //according to the function definition, itemPriceReached will set change = overflow money
  return true; //transaction successful because user inserted enough money without canceling
}

float insertACoin()
{
  return 1;
}

bool itemPriceReached(float price, float moneyIn, float& change)
{
  if (moneyIn >= price)
  {
    change = moneyIn - price;
    return true;
  }
  else
  {
    return false;
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
