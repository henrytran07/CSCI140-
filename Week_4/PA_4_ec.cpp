
#include <iostream>
#include <vector>
using namespace std;

int main() {

   /* Type your code here. */
    int array_size; 
    cout << "Please enter the number of elements in the list: ";
    cin >> array_size; 
   
    vector<int> number(array_size); 
    int logical_size = 0, userInput; 
   
    while (logical_size < array_size) {
        cout << "Please enter a number: ";
        cin >> userInput; 
        number[logical_size++] = userInput; 
    }
   
    int lower_bound, upper_bound; 
    cout << "Please enter a lower bound and upper bound for the list: ";
    cin >> lower_bound >> upper_bound;

    size_t index = 0; 
    while (index < number.size()) {
        if (number[index] < lower_bound || number[index] > upper_bound) {
        number.erase(number.begin() + index); 
        } else index++; 
    }
   
    for (size_t index = 0; index < number.size(); index++) {
        if (index != number.size() - 1){
            cout << number[index] << ",";
        } else {
            cout << number[index] << endl;
        }
    }
   return 0;
}
