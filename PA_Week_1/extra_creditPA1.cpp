/*
    The program is to develope an algorithm and a program that will read in a positive integer
        that represents a potential power of 2 pluses 1 

    Programmer: Henry Tran
    
    I verify the code below is my work   
*/

#include <iostream> 
#include <stdexcept>
using namespace std; 

bool userInputVerification(const string userInput, int& number);
bool checkInteger(const int number);

int main(){
    string userInput; 
    int positive_number; 
    cout << "\nWelcome to our program that reads a positive integer "
        << "representing a potential power of 2 pluses 1." << endl; 

    do {
        cout << "\nPlease enter a positive integer: ";
        getline(cin, userInput);
    } while((!userInputVerification(userInput, positive_number)));
    
    cout << positive_number << ": positive_number" << endl; 

    if ((checkInteger(positive_number))){
        cout << "\nYes. Your input represents a number of the form 2^n + 1." << endl;
    } else {
        cout << "\nNo. Your input does not represent a number of the form 2^n + 1. " << endl; 
    }
}

bool userInputVerification(const string userInput, int& number){
    try {   
        number = stoi(userInput);
        if (number > 0){
            cout << "Valid input" << endl; 
            return true; 
        } else {
            throw invalid_argument("Invalid input: The number is a negative number.");
        } 
    } catch(const invalid_argument& e){
        cout << e.what() << ". Please enter a positive integer. " 
             << "Please retry entering the number. " << endl; 
        return false; 
    }
}

bool checkInteger(const int number){
    int even_number = number - 1; 
    
    if (even_number <= 0){
        return false; 
    }

    while (even_number % 2 == 0){
        even_number = even_number / 2; 
    }

    return (even_number == 1);
    
}