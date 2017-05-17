#include "BaseNode.h"

BaseNode::BaseNode(string input){ //overloaded

    if (input[0] >= '0' && input[0] <= '9'){ //if the input is a number (assuming input is valid
        arabic = atoi(input.c_str());
        roman = arabic2roman(input);

    }
    else if (input[0] >= 'A' && input[0] <= 'Z'){ //if the input is a roman number (assuming input is valid
        roman = input;
        arabic = roman2arabic(input);
    }

    else{
        roman = "";
        arabic = 0;
    }
}

//mutators
void BaseNode::setArabic (int x){

    string str;
    stringstream sso("");
    sso<<x;
    sso>>str;

    if(!(x <= 5000 && x >= 1)) return;

    arabic = x;
    roman = arabic2roman(str); //changing roman so that it does not go stale

}
void BaseNode::setRoman (string x){

    if (!isValidRoman(x)) return;
    roman = x;
    arabic = roman2arabic(x); //changing arabic so that it does not go stale

}


//overloaded <<
ostream& operator<<(ostream& out, BaseNode& node){

   return out<<setw(16)<<left<<node.roman<<setw(4)<<node.arabic;

}

//overloaded >>
istream& operator>>(istream& in, BaseNode& node){
    string input;

    in>>input;

    if (input[0] >= '0' && input[0] <= '9'){
        node.arabic = atoi(input.c_str());
        node.roman = arabic2roman(input);

    }
    else if (input[0] >= 'A' && input[0] <= 'Z'){
        node.roman = input;
        node.arabic = roman2arabic(input);
    }

    return in;
}

bool isValidArabic (string input){
//checks if the given string is valid arabic number or not

    if (input == ""){ //CHECK 0: Empty String
        return false;
    }

    for (unsigned int i =0; i < input.length(); i++){ //CHECK 1: checking if everything is a digit
        if (!(input[i] >= '0' && input[i] <= '9')){
            return false; //continue i.e. skip the next (return false) statement if it is a digit
        }
    }

    if ((atoi(input.c_str()) <= 0) || (4999 < atoi(input.c_str()))){ //CHECK 2: if the number is outside the 1-4999 range, return false
        return false;
    }
    return true; //if the program made it this far (passed the 2 checks), return true
}

bool isValidRoman (string input){

//Checks if the input is valid roman

    if (input == ""){ //CHECK 0: Empty String
        return false;
    }

    for (unsigned int i =0; i < input.length(); i++){ //CHECK1 : Checking if everything is a valid roman digit
        switch (input[i]){
        case 'I' : case 'X' : case 'C': case 'M': case 'V': case 'L': case 'D': break;
        default : return false;
        }
    }
/*For checking the order:
    1. Convert the input to arabic number in string format.
    2. Convert the arabic to roman again using the converter in this program. Let's say it's roman_correct
    3. Because for any given number, only one counterpart exists, if roman_correct == roman, then the order is correct.
    4. For example, XCC will give 200(X + C + C = 10 + 100 + 100) as output. Converted 200 will give CC.
       Since XCC is not equal to CC(which is correct), it is not valid.
*/

    string arabicInputString;
    stringstream sso;
    sso.clear();
    sso << roman2arabic(input);
    sso >> arabicInputString;

    if (input != arabic2roman(arabicInputString)){//CHECK 2 : If the arabicInputString is not equal to the original input
        return false;
        }
    return true;
}

bool isValidFileInput(string& input){//input is pass by reference

    //this function checks if a line of the string (form inputFile) is *continuous*

    //the input is expected to to be a line from the file
    //The line should have only one thing that is not separated by spaces

    if(input == "" || (!isalpha(input[0]) && !isdigit(input[16])) || isdigit(input[15])){ //some checks
        return false;
    }

    stringstream sso;

    sso << input; //puts the input in string stream
    input.clear(); //clears the input
    sso >> input; //extracts from the sso

    if (sso >> input){//if the operation is successful once again
//if the input was continuous, then this operation would fail as there would be nothing in sso to extract (>> operator does not read whitespace)
        return false;
    }

    if (isValidArabic(input) || isValidRoman(input)){
        return true;
    }

    else {
        return false;
    }

}

string digit2letters(int faceValue, int placeValue){
    /*This function converts a single digit with its faceValue and placeValue known to the corresponding roman numeral.
  For example, '1' in 100 will be represented as : digit2Letters(1,3) = C  or 100. '9' in 9 as digit2Letters(9,1) = IX etc. */

    string theRoman; //this will be the returned value.

    if (faceValue == 0){
        theRoman.assign(""); // 0 has no roman equivalent. 101 is C (for 100) and I (for 1). 0 plays no role.
    }

    else if (placeValue == 1){ //if place value is 1, then it is a unit's digit.

            switch (faceValue){

                case 1 : // these statements are blank as the third case will apply to
                case 2 : //  case 1 and case 2 also. No point in repeating.
                case 3 : theRoman.assign(faceValue, 'I'); break; // if faceValue is 1, then I. If 2 then II. If 3 then III.
                case 4 : theRoman.assign("IV"); break;
                case 5 :
                case 6 :
                case 7 :
                case 8 : (theRoman.assign("V")).append(faceValue - 5, 'I');
                            break; // Add V + (facevalue -5) number of 'I'. So for 6, V + I. For 7, V + II.. and so on.
                case 9 : theRoman.assign("IX"); break;
                }
    }
// the statements below follow a similar logic to the last set of statements.
    else if (placeValue == 2){ // if place value is 2, then it's a 10s digit, and requires a different set of characters.
                switch (faceValue){

                case 1 :
                case 2 :
                case 3 : theRoman.assign(faceValue, 'X'); break;
                case 4 : theRoman.assign("XL"); break;
                case 5 :
                case 6 :
                case 7 :
                case 8 : (theRoman.assign("L")).append(faceValue - 5, 'X');
                            break;
                case 9 : theRoman.assign("XC"); break;
                }
    }
    else if (placeValue == 3){
                switch (faceValue){ // if place value is 3, then it's a 100s digit, and requires a different set of characters.

                case 1 :
                case 2 :
                case 3 : theRoman.assign(faceValue, 'C'); break;
                case 4 : theRoman.assign("CD"); break;
                case 5 :
                case 6 :
                case 7 :
                case 8 : (theRoman.assign("D")).append(faceValue - 5, 'C');
                            break;
                case 9 : theRoman.assign("CM"); break;
                }
    }
    else if (placeValue == 4){
                switch (faceValue){ // if place value is 4, then it's a 1000s digit, and requires a different set of characters.

                case 1 :
                case 2 :
                case 3 :
                case 4 : theRoman.assign(faceValue, 'M'); break;
                }
    }


    return theRoman;

}

string arabic2roman (string number){
//this function converts Arabic numbers in string format to roman numbers using the function digit2letters().

    string theRomanNumber = ""; // this will be the returning value.

    //using loop to tackle each digit one by one.
        for (unsigned int i = 0 ; i < number.length(); i++){
                //this loop will repeat as many times as there are digits in the number.

            theRomanNumber += digit2letters((number[i]-48), (number.length()-i));

            /* in the statement above:
            1. the function digit2letters() is being used here.
            2. number[i] represents the ASCII value digit in the string at the i th position
            3. (number[i]-48) gives us the face value of digit as ASCII value are 48 ahead of the face values.
            4. (number.length() -i) indirectly gives us the "place value" of the digit (see the definitions above)
            5. after a digit is converted, it is added to theRomanNumber and
               the loop moves to the next digit until the whole digit is converted to roman numerals.
            */
        }

    return theRomanNumber;

}

int romanChar2number (char roman){
// this function converts a roman character to the corresponding number;

    int converted; //this will be the return value
    switch (roman){ //this is pretty self explanatory. Values are assigned to "converted" depending on "roman"
        case 'I' : converted = 1; break;
        case 'V' : converted = 5; break;
        case 'X' : converted = 10; break;
        case 'L' : converted = 50; break;
        case 'C': converted = 100; break;
        case 'D' : converted = 500; break;
        case 'M' : converted = 1000; break;
        case 'v' : converted = 5000; break;

    }
return converted;
}

int roman2arabic (string number){
    /* This function:
        1. Adds the value of each roman character (based on the function above).
        2. Check if "special" characters i.e. characters which require subtraction are present and fix the answer accordingly.
        3. Converts the final integer to string and returns.
    */


    int sum = 0; //this is going to be our return value a.k.a converted Arabic number.
    for (unsigned int i=0; i < number.length(); i++){
        sum += romanChar2number(number[i]);
        // the function romanChar2number() is used here.
        //this is just mindless addition of converted roman characters. Sum might be incorrect at this point.
    }


    for (unsigned int i=0; i< number.length()-1; i++) { //
            static string temp; //a temp variable.
            temp = number.substr(i,2); // this creates a substring of 2 characters (starting from the beginning) and assigns it to temp

            // the statements below check if the characters in substring are equal to the special characters or not.
            // if condition is satisfied, they subtract values from the sum to make it correct.
            if (temp == "IV" || temp == "IX") {sum -= 2;}
            else if (temp == "XL" || temp == "XC") {sum -= 20;}
            else if (temp == "CD" || temp == "CM") {sum -= 200;}
    }

    return sum;

}


