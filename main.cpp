#include <iostream>
#include <string>

using namespace std;

int roman_to_arabic(char roman_letter){
    if (roman_letter == 'M')
        return 1000;
    else if(roman_letter == 'D')
        return 500;
    else if(roman_letter == 'C')
        return 100;
    else if(roman_letter == 'L')
        return 50;
    else if(roman_letter == 'X')
        return 10;
    else if(roman_letter == 'V')
        return 5;
    else if(roman_letter == 'I')
        return 1;
    return 0;
}

float get_decimal(string &roman, std::size_t decimal_start_pos){
    float decimal = 0;

    for (int i = decimal_start_pos; i < roman.length(); ++i) {
        if (roman[i] == 'S')
            decimal += 6;
        else if (roman[i] == '.')
            ++decimal;
    }

    //remove decimal part form roman number
    roman.erase(decimal_start_pos, roman.length() - decimal_start_pos);

    return decimal/12;
}

bool check_for_decimal(const string &roman, std::size_t &decimal_start_pos){
    //if it can't find "S" or "." in roman,
    //there are no decimals.
    decimal_start_pos = roman.find("S");
    if (decimal_start_pos == std::string::npos){
        decimal_start_pos = roman.find(".");

        if (decimal_start_pos == std::string::npos)
            return false;
    }
    return true;
}

void get_current_and_next_number(const string &roman, const int &i, const bool &was_made_of_2, int &current_number, int &next_number){
    if (i >= roman.length()){
        if (was_made_of_2) {
            current_number = 0;
            next_number = 0;
            return;
        }else {
            current_number = roman_to_arabic(roman[i]);
            next_number = 0;
        }
    } else {
        current_number = roman_to_arabic(roman[i]);
        next_number = roman_to_arabic(roman[i + 1]);
    }
}

int main() {
    string roman;
    cout << "Enter roman number to convert: ";
    cin >> roman;
    string roman_original = roman;

    float arabic = 0;
    int current_number;
    int next_number;
    bool was_made_of_2 = 0;
    std::size_t decimal_start_pos;
    bool has_decimals = check_for_decimal(roman,decimal_start_pos);
    float decimal = 0.0;


    if(has_decimals)
        decimal = get_decimal(roman,decimal_start_pos);

    for (int i = 0; i < roman.length(); ++i) {
        get_current_and_next_number(roman, i, was_made_of_2, current_number, next_number);

        //If roman[i] == 1000 OR roman[i] >= roman[i+i]
        //The next number is formed form only 1 letter
        //Else it is formed from 2 letters
        if (current_number == 1000 || current_number >= next_number){
            arabic += current_number;
        } else{
            arabic += (next_number - current_number);
            was_made_of_2 = true;
            ++i;
        }
    }

    //cout.precision(5);

    cout << roman_original<< " = " << arabic + decimal;

    return 0;
}
