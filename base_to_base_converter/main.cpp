// EE 176 Exercise 0 by Thomas Anthony Ortiz
// the coder tried to incorporate conio.h to the system but it didn't work since student used  WSL
// ncurses.h was tried to call getch() but it didn't work

#include <iostream> // Used for user prompted i/o
#include <cmath> // Used specifically for the power exponent for converting the input into base-10
#include <string>

using namespace std;

// Function to check if an input value contains valid digits or is in the proper format for the given base
bool are_digits_valid(const string & value, int base) {
    for (char digit : value) {
        digit = toupper(digit);
        if (base <= 10) {
            if (!(digit >= '0' && digit < '0' + base)) {
                return false; 
            }
        } else {
            if (!((digit >= '0' && digit <= '9') || (digit >= 'A' && digit < 'A' + (base - 10)))) {
                return false; 
            }
        }
    }
    return true;
}

// Function to check if the characters in a string is all numeric
bool are_characters_numeric(const string & str) {
    for (char c : str) {
        if (!isdigit(c)) {
            return true;
        }
    }
    return false; 
}

// Function to convert a number in base 2 to 16 to decimal
int input_value_to_decimal(const string & number, int base) {
    int output_decimal = 0;
    int power = 0;
    
    for (int i = number.length() - 1; i >= 0; i--) {
        char digit = number[i];
        digit = toupper(digit);
        if (digit >= '0' && digit <= '9') {
            output_decimal += (digit - '0') * pow(base, power);
        } else if (digit >= 'A' && digit <= 'F') {
            output_decimal += (digit - 'A' + 10) * pow(base, power);
        }
        
        power++;
    }
    
    return output_decimal;
}

// Function to convert a number in decimal to any base
string decimal_to_base_x(int input_decimal, int base) {
    string output_base_x = "";
    while (input_decimal > 0) {
        int remainder = input_decimal % base;
        char digit = (remainder < 10) ? ('0' + remainder) : ('A' + remainder - 10);
        output_base_x = digit + output_base_x;
        input_decimal /= base;
    }
    return output_base_x;
}

int main() {
    while (true) {
        string input_value;
        int input_base;
        int output_base;
        string input_base_str;
        string output_base_str;

        cout << "\nEE 176\nExercise 0: Base to Base Converter\nby Thomas Anthony Ortiz\nEnter 'x' to exit.\n\n";

        // Input the input base with validation such that the input base should only be within integers 2 to 16 
        do {
            cout << "Enter the input base (2-16): ";
            cin >> input_base_str;
            
            if (input_base_str == "x" || input_base_str == "X") {
                cout << "Goodbye.\n" << endl;
                return 0;
            }

            try {
            
            input_base = stoi(input_base_str);
            
            if (are_characters_numeric(input_base_str) || input_base < 2 || input_base > 16) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\tError: Invalid input base value. Please enter a value between 2 and 16." << endl;
                continue;
            }

            break; // If the input is a valid integer, break out of the loop
            } catch (const invalid_argument& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\tError: Invalid input base value. Please enter a value between 2 and 16." << endl;
            }


        } while (true);

        // Input the input value with validation such that the value should follow the proper format of the chosen base, 
        // and that the input value should not exceed the input equivalnet 255 base 10
        do {
            cout << "Enter input value in base-" << input_base << ": ";
            cin >> input_value;

            if (input_value == "x" || input_value == "X") {
                cout << "Goodbye.\n" << endl;
                return 0;
            }

            if (!are_digits_valid(input_value, input_base)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\tError: Invalid input value for base-" << input_base << "." << endl;
                continue;
            }

            int input_in_decimal = input_value_to_decimal(input_value, input_base);

            if (input_in_decimal > 255) {
                cout << "\tError: The input value exceeds the maximum decimal input equivalent of 255." << endl;
                continue;
            }

            break;
        } while (true);

        // Input the output base with validation such that the output base should only be within integers 2 to 16
        do {
            cout << "Enter the output base (2-16): ";
            cin >> output_base_str;

            if (output_base_str == "x" || output_base_str == "X") {
                cout << "Goodbye.\n" << endl;
                return 0;
            }

            try {
                
            output_base = stoi(output_base_str);

            if (are_characters_numeric(input_base_str) || output_base < 2 || output_base > 16) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\tError: Invalid output base value. Please enter a value between 2 and 16." << endl;
                continue;
            }

            break; // If the input is a valid integer, break out of the loop
            } catch (const invalid_argument& e) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\tError: Invalid output base value. Please enter a value between 2 and 16." << endl;
            }

        } while (true);

        // Convert the number to decimal and binary using the input_value_to_decimal & decimal_to_binary functions
        int output_base_decimal = input_value_to_decimal(input_value, input_base);
        string output_base_binary = decimal_to_base_x(output_base_decimal, 2);


        // Convert the decimal result to the new base and display it only if the output base is not in base-2 or base-10
        // This is to reduce redundancy since it is a requirement that the binary and decimal equivalents are always posted
        if (!(output_base == 2 || output_base == 10)) {
        string output_base_result = decimal_to_base_x(output_base_decimal, output_base);
        cout << "\nBase-" << output_base << " equivalent: " << output_base_result << endl;
        }

        // Display decimal and binary equivalent
        cout << "\nDecimal equivalent: " << output_base_decimal << "\n";
        cout << "Binary equivalent: " << output_base_binary << "\n";


        // Once the operation is done, code will prompt the user if they want to convert anotehr value
        do {
            char choice;
            cout << "\nConvert another? (y/n): ";
            cin >> choice;
            string validChoices = "ynx";
            choice = tolower(choice);

            if (cin.peek() != '\n') {
                cerr << "\tError: Invalid choice." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else if (validChoices.find(choice) == string::npos) {
                cerr << "\tError: Invalid choice." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            } else if (choice == 'n' || choice == 'x') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Goodbye.\n" << endl;
                return 0; 
            } else if (choice == 'y') {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        } while (true); 
        

    }

    return 0;
    
}
