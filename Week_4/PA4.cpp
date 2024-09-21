
#include <iostream> 

using namespace std; 

const int MAXIMUM_NUMBER_SIZE = 25; 

bool userInputValidation(const string& userInput);

int main()
{
    string number[MAXIMUM_NUMBER_SIZE];
    string user_input; 

    for (int index = 0; index < MAXIMUM_NUMBER_SIZE; index++){
        number[index] = "0"; 
    }

    do {
        cout << "Enter a large integer up to 25 digits: ";
        cin >> user_input; 
    } while (!userInputValidation(user_input));

    int user_input_size = user_input.size();

    int count = 1; 
    for (int user_index = user_input_size - 1; user_index >= 0; user_index--){
        number[MAXIMUM_NUMBER_SIZE - count] = user_input[user_index];
        count++; 
    }

    cout << "Digits: ";
    for (int index = 0; index < MAXIMUM_NUMBER_SIZE; index++){
        cout << number[index] << " ";
    }
    cout << endl; 

    cout << "Number of digits: " << user_input_size << endl; 
}

bool userInputValidation(const string& userInput) {
    for (char c: userInput){
        if (!isdigit(c)){
            cout << "Invalid input. Please retry it again with numeric input" << endl; 
            return false; 
        }
    }

    if (userInput.size() > MAXIMUM_NUMBER_SIZE) {
        cout << "Invalid input. Please retry it by entering a number less than 25 digits." << endl; 
        return false; 
    }
    return true; 
}
