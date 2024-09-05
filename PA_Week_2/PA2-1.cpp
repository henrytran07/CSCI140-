#include <iostream> 
#include <stdexcept>

using namespace std; 

bool userHandleException(string& userInput, int &number);
string coinSort(int amount_of_change);

int main(){
    string userInput; 
    int purchase_amount; 
    
    do {
        cout << "Enter a purchase amount [0-100]: ";
        getline(cin, userInput);
    } while(!userHandleException(userInput, purchase_amount));

    cout << "You entered a purchase amount of " << purchase_amount << endl; 

    int amount_of_change = 100 - purchase_amount; 
    int test_amount1 = amount_of_change; 
    int test_amount2 = amount_of_change; 
    
    if (amount_of_change % 5 != 0){
        cout << "Your change of " << amount_of_change << " cents is rounded to ";

        while(test_amount1 % 5 != 0){
            test_amount1++; 
        }

        while(test_amount2 % 5 != 0){
            test_amount2 --; 
        }

        if (test_amount1 - amount_of_change > test_amount2 - amount_of_change){
            amount_of_change = test_amount2; 
        } else {
            amount_of_change = test_amount1; 
        }
        
        cout << amount_of_change << " cents" << endl; 
    }

    string response = coinSort(amount_of_change);
    cout << response << endl; 
    return 0; 
}

bool userHandleException(string& userInput, int &number){
    try {
        number = stoi(userInput);
        if (number >= 0 && number <= 100){ 
            cout << "Valid Input!" << endl; 
            return true; 
        } else {
            throw invalid_argument("Invalid input");
        }
    } catch (const invalid_argument& e){
        cout << "\n" << e.what() << ": You should enter an integer from 1 to 100." << endl; 
    }
    return false; 
}

string coinSort(int amount_of_change){
    int initial_quarters = 2, initial_dimes = 2, initial_nickels = 2;
    int quarters = 25, dimes = 10, nickels = 5; 
    int quarters_for_change = 0, dimes_for_change = 0, nickels_for_change = 0; 

    int total_change = initial_quarters * quarters + initial_dimes * dimes + initial_nickels * nickels; 

    if (amount_of_change > total_change){
        return "Insufficient coins. Your change of " +  to_string(amount_of_change) + " cannot be proccessed.";
    }

    if (amount_of_change >= quarters){
        quarters_for_change = amount_of_change / quarters; 
        amount_of_change -= quarters_for_change * quarters; 
    } 

    if (amount_of_change >= dimes){
        dimes_for_change = amount_of_change / dimes; 
        amount_of_change -= dimes_for_change * dimes; 
    }

    if (amount_of_change >= nickels){
        nickels_for_change = amount_of_change / nickels; 
        amount_of_change -= nickels_for_change * nickels; 
    }

    string response = "Your change of 65 cents is given as: \n"
                  "quarter(s): " + to_string(quarters_for_change) + "\n" +
                  "dime(s): " + to_string(dimes_for_change) + "\n" +
                  "nickel(s): " + to_string(nickels_for_change);

    return response; 
}