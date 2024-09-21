
/*I, Henry Tran, verify that the code below is mine. */
#include <iostream> 
#include <cmath> 
using namespace std; 

char letterGrade(int userInput);

int main(){
    int userInput; 
    
    cout << "Please enter your grade in between 70 and 99: ";
    cin >> userInput; 
    
    char grade = LetterGrade(userInput);
    
    cout << "You got " << (grade == 'A' ? "an " : "a ") << grade << endl; 
}

char letterGrade(int userInput){
    char standardLetterGrade[] = {'A', 'B', 'C'};
    int index = abs(floor(userInput / 10) - 9);
    
    return standardLetterGrade[index];
}