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
struct CoinSolverFlags {
    bool already_solved = false; 
    bool already_solved_1 = false;  
    bool already_solved_2 = false; 
    bool inside_quarters = false; 
    bool inside_dimes = false; 
    bool inside_nickels = false; 
};

bool userHandleException(string& userInput, int &number);
void roundupAmountOfChange(int& amount_of_change);
string summaryResponse(int valid_transaction, int balance, int number_of_quarters, int number_of_dimes, int number_of_nickels);
void optimalExtractingCoins(int& valid_transaction, int& amount_of_change, int& number_of_quarters, int& number_of_dimes, int& number_of_nickels, bool &valid, CoinSolverFlags csf);

int main(){
    string userInput; 
    int purchase_amount, balance, number_of_quarters, number_of_dimes, number_of_nickels; 
    int original_quarters, original_dimes, original_nickels;
    int valid_transaction = 0; 
    string response; 
    cout << "Vending Machine Version 2 EC by Henry Tran\n";
    
    cout << "\nEnter number of quarters, dimes, and nickels: ";
    cin >> number_of_quarters >> number_of_dimes >> number_of_nickels; 

    original_quarters = number_of_quarters; 
    original_dimes = number_of_dimes; 
    original_nickels = number_of_nickels; 
    balance = QUARTERS * number_of_quarters + DIMES * number_of_dimes + NICKELS * number_of_nickels; 
    response = summaryResponse(valid_transaction, balance, number_of_quarters, number_of_dimes, number_of_nickels);

    cout << response << endl; 
    cout << "\nOnly one-dollar bill will be accepted.\n" 
        << "Only amount between 0 and 100 is accepted.\n"
        << "Enter 0 to stop the program. " << endl;
    
    cin.ignore(); 
    bool valid = false; 
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
        int copy_change = amount_of_change; 
        CoinSolverFlags csf;
        optimalExtractingCoins(valid_transaction, amount_of_change, number_of_quarters, number_of_dimes, number_of_nickels, valid, csf);
        if (valid){
            balance -= copy_change; 
            cout << copy_change << " cents is given: "
                << "\nNumber of quarters: " << original_quarters - number_of_quarters
                << "\nNumber of dimes: " << original_dimes - number_of_dimes 
                << "\nNumber of nickels: " << original_nickels - number_of_nickels << endl; 

            original_quarters -= number_of_quarters; 
            original_dimes -= number_of_dimes; 
            original_nickels -= number_of_nickels; 
            valid = false; 
        } else {
            balance -= DOLLARS; 
            cout << "Your 1 DOLLAR is out now" << endl; 
        }

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

void optimalExtractingCoins(int& valid_transaction, int& amount_of_change, int& number_of_quarters, int& number_of_dimes, int& number_of_nickels, bool &valid, CoinSolverFlags csf){
    int balance = number_of_quarters * QUARTERS + number_of_dimes * DIMES + number_of_nickels * NICKELS; 

    if (number_of_quarters < 0 || number_of_dimes < 0 || number_of_nickels < 0){
        cout << "Negative coins. Check the program..." << endl;
        exit(1);
        return;  
    }

    if (amount_of_change == 0){
        csf.already_solved = false; 
        csf.already_solved_1 = false;  
        csf.already_solved_2 = false; 
        csf.inside_quarters = false; 
        csf.inside_dimes = false; 
        csf.inside_nickels = false; 

        valid = true; 
        valid_transaction++; 
        return; 
    }

    if (amount_of_change < 0){
        cout << amount_of_change << ": amount of change inside the amount_of_change < 0" << endl; 
        cout << "over changed" << endl; 
        exit(1);
        return; 
    }

    if ((number_of_quarters == 0 && number_of_dimes == 0 && number_of_nickels == 0)){
        cout << "Not enough coins to process " << endl; 
        return; 
    }

    if (balance < amount_of_change){
        cout << "Not enough change to process the payment" << endl; 
        return; 
    }
   
    // cout << amount_of_change << ": amount_of_change " << endl; google c
    // cout << number_of_quarters << ": number of quarters (I)" << endl; 
    // cout << number_of_dimes << ": number of dimes(I)" << endl; 
    // cout << number_of_nickels << ": number of nickels (i)" << endl; 
    if ((amount_of_change != 0) && (!csf.already_solved) || (!csf.inside_quarters)){
        if (number_of_quarters == 0){
            amount_of_change += QUARTERS; 
            number_of_quarters++; 
            csf.already_solved = true; 
        } else if (amount_of_change >= QUARTERS){
            csf.inside_quarters = true; 
            amount_of_change -= QUARTERS; 
            number_of_quarters --; 
            optimalExtractingCoins(valid_transaction, amount_of_change, number_of_quarters, number_of_dimes, number_of_nickels, valid, csf);
        }    
    }


    if ((amount_of_change != 0) && (!csf.already_solved_1) || (!csf.inside_dimes)){
        // cout << "Inside" << endl; 
        if (number_of_dimes == 0){
            amount_of_change += DIMES; 
            number_of_dimes++; 
            csf.already_solved_1 = true; 
        } else if (amount_of_change >= DIMES) {
            csf.inside_dimes = true; 
            amount_of_change -= DIMES; 
            number_of_dimes --; 
            optimalExtractingCoins(valid_transaction, amount_of_change, number_of_quarters, number_of_dimes, number_of_nickels, valid, csf);
        }    
    }
    
    if (amount_of_change != 0 && !csf.already_solved_2 ||  (!csf.inside_nickels)){
        if (number_of_nickels == 0){
            amount_of_change += NICKELS; 
            number_of_nickels++; 
            csf.already_solved_2 = true; 
        }
        else if (amount_of_change >= NICKELS){
            // cout << "Inside Nickels" << endl; 
            amount_of_change -= NICKELS; 
            number_of_nickels --; 
            optimalExtractingCoins(valid_transaction, amount_of_change, number_of_quarters, number_of_dimes, number_of_nickels, valid, csf);
        }    
    }

    // cout << amount_of_change << ": amount_of_change (II) " << endl; 
    // cout << number_of_dimes << ": amount_of_dimes (II)" << endl; 
    // cout << number_of_quarters << ": number of quarters (II)" << endl;
    // cout << number_of_nickels << ": amount of nickels (II)" << endl; 
}