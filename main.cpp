#include <iostream>
#include <vector>
using namespace std;

void print_numeral(vector<char> numeral){
    for(int i = 0; i < numeral.size(); i++){
        cout << numeral.at(i);
    }
}

void print_decimal(vector<int> decimal){
    for(int i = 0; i < decimal.size(); i++){
        cout << decimal.at(i) << " ";
    }
    cout << endl;
}

void create_decimal_vector(vector<char> numeral, vector<int>& decimal){
    for(int i = 0; i < numeral.size(); i++){
        if ('I' == numeral.at(i)){
            decimal.push_back(1);
        }else if ('V' == numeral.at(i)){
            decimal.push_back(5);
        }else if ('X' == numeral.at(i)){
            decimal.push_back(10);
        }else if ('L' == numeral.at(i)){
            decimal.push_back(50);
        }else if ('C' == numeral.at(i)){
            decimal.push_back(100);
        }else if ('D' == numeral.at(i)){
            decimal.push_back(500);
        }else if ('M' == numeral.at(i)){
            decimal.push_back(1000);
        }
    }
}

void check_subtraction(vector<int>& decimal){
    for(int i = 1; i < decimal.size(); i++){
        if (decimal.at(i) > decimal.at(i-1)){ //need to subtract
            decimal.at(i) = decimal.at(i) - decimal.at(i-1);
            decimal.at(i - 1) = 0;
            i++;
        }
    }
}

bool violate_fourth_rule(vector<int> &decimal){
    for(int i = 1; i < decimal.size(); i++){
        if ((decimal.at(i - 1) * 10 + 1) < decimal.at(i)){
            return true;
        }
    }
    return false;
}

int add(vector<int> & decimal){
    int finalDecimal = 0;
    for (int i = 0; i < decimal.size(); i++){
        finalDecimal = finalDecimal + decimal.at(i);
    }
    return finalDecimal;
}

void check_letter_half(int& finalDecimal, vector<char> &checkNumeral, char large, int largeValue, char small){
    while ((finalDecimal / largeValue) >= 1){
        checkNumeral.push_back(large);
        finalDecimal = finalDecimal - largeValue;
    }
    if (finalDecimal % largeValue >= (largeValue * .9)){
        checkNumeral.push_back(small);
        checkNumeral.push_back(large);
        finalDecimal = finalDecimal - (largeValue * .9);
    }
}

void check_letter_fifth(int& finalDecimal, vector<char> &checkNumeral, char large, int largeValue, char small){
    while ((finalDecimal / largeValue) >= 1){
        checkNumeral.push_back(large);
        finalDecimal = finalDecimal - largeValue;
    }
    if (finalDecimal % largeValue >= (largeValue * .8)){
        checkNumeral.push_back(small);
        checkNumeral.push_back(large);
        finalDecimal = finalDecimal - (largeValue * .8);
    }
}

void decimal_to_numeral(vector<char> & checkNumeral, int &finalDecimal) {
    check_letter_half(finalDecimal, checkNumeral, 'M', 1000, 'C');
    check_letter_fifth(finalDecimal, checkNumeral, 'D', 500, 'C');
    check_letter_half(finalDecimal, checkNumeral, 'C', 100, 'X');
    check_letter_fifth(finalDecimal, checkNumeral, 'L', 50, 'X');
    check_letter_half(finalDecimal, checkNumeral, 'X', 10, 'I');
    check_letter_fifth(finalDecimal, checkNumeral, 'V', 5, 'I');
    while (finalDecimal >= 1){
        checkNumeral.push_back('I');
        finalDecimal--;
    }
}

int main() {
    vector<char> numeral;
    vector<int> decimal;
    char nextNumeral;

    cout << "Hello! Please enter the roman numeral you would like to convert to a decimal." << endl;
    cout << "This will be done numeral by numeral, starting with the first numeral on the left." << endl;
    cout << "Once you are done, enter 0." << endl;
    cout << "Numeral must already be in upper case to function." << endl;
    cout << endl;
    cout << "Enter first numeral: ";
    cin >> nextNumeral;
    while (nextNumeral == 'I' || nextNumeral == 'V' || nextNumeral == 'X' || nextNumeral == 'L' || nextNumeral == 'C' || nextNumeral == 'D' || nextNumeral == 'M'){
        numeral.push_back(nextNumeral);
        cout << "Enter next numeral: ";
        cin >> nextNumeral;
    }
    print_numeral(numeral);
    cout << endl;

    create_decimal_vector(numeral, decimal); //converts numeral vector to decimal vector
    // print_decimal(decimal);
    if (violate_fourth_rule(decimal) == true){ //checks the fourth rule from the instructions sheet
        cout << "This numeral breaks the fourth rule meaning a symbol representing 10x may not precede any symbol larger than 10x+1. Please try again!" << endl;
        return 0;
    }
    check_subtraction(decimal);
    // print_decimal(decimal, decimalSize);

    cout << "The decimal value of "; //prints translation of numeral to decimal
    print_numeral(numeral);
    int finalDecimal = add(decimal);
    int decimalValue = finalDecimal;
    cout << " is "<< finalDecimal << "." << endl;

    vector<char> checkNumeral;//convert decimal to roman numerals
    decimal_to_numeral(checkNumeral, finalDecimal);
    cout << decimalValue << " converted back into numeral form is ";
    print_numeral(checkNumeral);
    cout << "." << endl;

    cout << "Task complete!" << endl;
    return 0;
}

// extra code I used in my logic before I cleaned it up
    /*while ((finalDecimal / 1000) >= 1){
        checkNumeral.push_back('M');
        finalDecimal = finalDecimal - 1000;
    }
    if (finalDecimal % 1000 >= 900){
        checkNumeral.push_back('C');
        checkNumeral.push_back('M');
        finalDecimal = finalDecimal - 900;
    }
    while (finalDecimal / 500 >= 1){
        checkNumeral.push_back('D');
        finalDecimal = finalDecimal - 500;
    }
    if (finalDecimal % 500 >= 400){
        checkNumeral.push_back('C');
        checkNumeral.push_back('D');
        finalDecimal = finalDecimal - 400;
    }
    while (finalDecimal / 100 >= 1){
        checkNumeral.push_back('C');
        finalDecimal = finalDecimal - 100;
    }
    if (finalDecimal % 100 >= 90){
        checkNumeral.push_back('X');
        checkNumeral.push_back('C');
        finalDecimal = finalDecimal - 90;
    }
    while (finalDecimal / 50 >= 1){
        checkNumeral.push_back('L');
        finalDecimal = finalDecimal - 50;
    }
    if (finalDecimal % 50 >= 40){
        checkNumeral.push_back('X');
        checkNumeral.push_back('L');
        finalDecimal = finalDecimal - 40;
    }
    while (finalDecimal / 10 >= 1){
        checkNumeral.push_back('X');
        finalDecimal = finalDecimal - 10;
    }
    if (finalDecimal % 10 >= 9){
        checkNumeral.push_back('I');
        checkNumeral.push_back('X');
        finalDecimal = finalDecimal - 9;
    }
    while (finalDecimal / 5 >= 1){
        checkNumeral.push_back('V');
        finalDecimal = finalDecimal - 5;
    }
    if (finalDecimal % 5 >= 4){
        checkNumeral.push_back('I');
        checkNumeral.push_back('V');
        finalDecimal = finalDecimal - 4;
    }
    while (finalDecimal >= 1){
        checkNumeral.push_back('I');
        finalDecimal = finalDecimal - 1;
    }
}
     void four_in_a_row(vector<char> &checkNumeral){
    for (int i = 1; i < checkNumeral.size() - 3; i++){
        if (checkNumeral.at(i) == checkNumeral.at(i+1) == checkNumeral.at(i+2) == checkNumeral.at(i+3)){
            // checkNumeral.erase(i, i+3);//delete the four values
            //insert the value i-1, i
        }
    }*/