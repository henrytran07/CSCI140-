
/*  The program is to develope an algorithm to convert from total seconds 
to the equivalent nunber of hours, number of minutes, and leftover seconds.    
    Programmer: Henry Tran
    I verify the code below is my work   
*/

#include <iostream> 
#include <string> 

using namespace std; 

bool userInputVerification(string& userInput, int&);
void timeConversion(int& hours, int& minutes, int& seconds, int total_seconds);

int main(){
    string userInput; 
    int total_seconds; 

    cout << "\n Welcome to time conversion program. This program is to help you"
        << " convert from total seconds (from your input) to the equivalent number "
        << "of hours, number of minutes, and leftover seconds. " << endl; 
    cout << endl; 

    do {
        cout << "Please enter the total seconds you want to convert: ";
        getline(cin, userInput);
    } while ((!userInputVerification(userInput, total_seconds)));
    
    cout << total_seconds << ": total_seconds" << endl; 

    int hours, minutes, leftover_seconds; 

    timeConversion(hours, minutes, leftover_seconds, total_seconds);

    cout << "The conversion of time is "
        << hours << (hours <= 1 ? " hour" : " hours")
        << ", " << minutes << (minutes <= 1 ? " minute" : " minutes")
        << ", " << leftover_seconds << (leftover_seconds <= 1 ? " second" : " seconds") << endl;
    return 0; 
}

bool userInputVerification(string& userInput, int& total_seconds){
    try {
        total_seconds = stoi(userInput);
        return true; 
    } catch(const invalid_argument& e){
        cout << "Invalid input: You should enter an integer for the conversion." << endl; 
        return false; 
    }  
}

void timeConversion(int& hours, int& minutes, int& seconds, int total_seconds){
    int conversion_time = total_seconds; 

    hours = conversion_time / 3600; 
    conversion_time -= hours * 3600; 

    minutes = conversion_time / 60; 
    conversion_time -= minutes * 60; 

    seconds = conversion_time; 
    conversion_time -= seconds;

    // Handling unexpected cases for debugging 
    // If seconds are greater than 60, it means the program operates wrongly. 
    if (seconds >= 60) {
        cout << "Debug Info - Hours: " << hours << ", Minutes: " << minutes << ", Seconds: " << seconds << endl;
        exit(1);  
    }
}