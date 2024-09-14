/*
    This program is to read an integer from 0 to 100, representing the purchase amount. 
    It will calculate the amount of change and maximize the coins by using the highest value first. 

    I, Henry Tran, verify that the code below is mine. 
*/
#include <iostream> 
#include <stdexcept>
#include <cmath> 
#include <iomanip> 
#include <sstream> 

using namespace std; 
const int DOLLARS = 100; 
const int QUARTERS = 25; 
const int DIMES = 10; 
const int NICKELS = 5; 

bool userHandleException(string& userInput, int &number);
void roundupAmountOfChange(int& amount_of_change);
string coinSort(int &amount_of_change, int &balance, int &number_of_quarters, int &number_of_dimes, int &number_of_nickels, int& valid_transaction);
string summaryResponse(int valid_transaction, int balance, int number_of_quarters, int number_of_dimes, int number_of_nickels);

int main(){
    string userInput; 
    int purchase_amount, balance, number_of_quarters, number_of_dimes, number_of_nickels; 
    int valid_transaction = 0; 
    string response; 
    cout << "Vending Machine Version 2 by Henry Tran\n";
    
    cout << "\nEnter number of quarters, dimes, and nickels: ";
    cin >> number_of_quarters >> number_of_dimes >> number_of_nickels; 

    balance = QUARTERS * number_of_quarters + DIMES * number_of_dimes + NICKELS * number_of_nickels; 
    response = summaryResponse(valid_transaction, balance, number_of_quarters, number_of_dimes, number_of_nickels);

    cout << response << endl; 
    cout << "\nOnly one-dollar bill will be accepted.\n" 
        << "Only amount between 0 and 100 is accepted.\n"
        << "Enter 0 to stop the program. " << endl;
    
    cin.ignore(); 
    do {
        do {
            cout << "\nEnter a purchase amount [0-100]: ";
            getline(cin, userInput);
        } while ((!userHandleException(userInput, purchase_amount)));
      
        if (purchase_amount == 0){
            response = summaryResponse(valid_transaction, balance, number_of_quarters, number_of_dimes, number_of_nickels); 
            cout << response << endl; 
            exit(0);
        }

        cout << "You entered a purchase amount of " << purchase_amount << endl; 
        cout << "Inserting one-dollar bill" << endl;  
        cout << "Processing your purchase..." << endl; 
        balance += DOLLARS;

        int amount_of_change = 100 - purchase_amount; 
        roundupAmountOfChange(amount_of_change);
        response = coinSort(amount_of_change, balance, number_of_quarters, number_of_dimes, number_of_nickels, valid_transaction);
        cout << response << endl; 
    } while(true);
    return 0; 
}

void roundupAmountOfChange(int& amount_of_change){
    int test_amount1 = amount_of_change; 
    int test_amount2 = amount_of_change; 

    if (amount_of_change % 5 != 0){
        while(test_amount1 % 5 != 0) test_amount1++;
        while(test_amount2 % 5 != 0) test_amount2--;

        amount_of_change = (abs(test_amount1 - amount_of_change) > abs(test_amount2 - amount_of_change)) ? test_amount2 : test_amount1;
    }
}

string summaryResponse(int valid_transaction, int balance, int number_of_quarters, int number_of_dimes, int number_of_nickels){
    stringstream stream; 
    stream << fixed << setprecision(2) << (balance / 100.0);
    string response = "Valid transaction: " + to_string(valid_transaction) + "\nNumber of quarters: " 
                    + to_string(number_of_quarters) + "\nNumber of dimes: " + to_string(number_of_dimes)
                    + "\nNumber of nickels: " + to_string(number_of_nickels)
                    + "\nMachine balance: $" + stream.str();
    return response;
}

bool userHandleException(string& userInput, int &number){
    try {
        number = stoi(userInput);
        if (number >= 0 && number <= 100){ 
            if (number == 0) {
                cout << "Ending program..." << endl;
            } else {
                cout << "Valid Input!" << endl; 
            }
            return true; 
        } else {
            throw invalid_argument("Invalid input");
        }
    } catch (const invalid_argument& e){
        cout << "\n" << e.what() << ": Please enter an integer from 1 to 100." << endl; 
    }
    return false; 
}

string coinSort(int &amount_of_change, int&balance, int &number_of_quarters, int &number_of_dimes, int &number_of_nickels, int& valid_transaction){
    string change = to_string(amount_of_change);
    int quarters_for_change = 0, dimes_for_change = 0, nickels_for_change = 0;
    int total_change = number_of_quarters * QUARTERS + number_of_dimes * DIMES + number_of_nickels * NICKELS; 
    string response; 
    if (amount_of_change > total_change){
        balance -= DOLLARS; 
        string response = "Insufficient changes.\nYour transactions cannot be processed.\nPlease take back your one dollar bill.\n";    
        return response; 
    }

    balance -= amount_of_change; 
    // Calculate quarters for change
    if (amount_of_change >= QUARTERS){
        quarters_for_change = amount_of_change / QUARTERS; 
        quarters_for_change = min(quarters_for_change, number_of_quarters);
        number_of_quarters -= quarters_for_change; 
        amount_of_change -= quarters_for_change * QUARTERS; 
    } 

    // Calculate dimes for change
    if (amount_of_change >= DIMES){
        dimes_for_change = amount_of_change / DIMES; 
        dimes_for_change = min(dimes_for_change, number_of_dimes);
        number_of_dimes -= dimes_for_change;
        amount_of_change -= dimes_for_change * DIMES; 
    }

    // Calculate nickels for change
    if (amount_of_change >= NICKELS){
        nickels_for_change = amount_of_change / NICKELS; 
        nickels_for_change = min(nickels_for_change, number_of_nickels);
        number_of_nickels -= nickels_for_change; 
        amount_of_change -= nickels_for_change * NICKELS; 
    }

    valid_transaction++; 
    return "\nYour change of " + change + " cents is given as: \n"
                  "quarter(s): " + to_string(quarters_for_change) + "\n" +
                  "dime(s): " + to_string(dimes_for_change) + "\n" +
                  "nickel(s): " + to_string(nickels_for_change);
}
