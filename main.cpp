/*
Submission 2
NAME : MANAN MANAN
NETID : mxm163530
CLASS : CS1337.001
Professor : Jason Smith
*/

#include <iostream>
#include<sstream>
#include<string>
#include<fstream>

using namespace std;

/*
 The following definitions of faceValue and placeValue will be used in the program:
 faceValue : the digit itself. faceValue of '5' in 34562 is 5 itself.
 placeValue : the value of the place the digit is in. It is counted from the right. placeValue of '5' in 34562 is 3 i.e. it
 is in hundreds place.
 */

 string digit2letters(int faceValue, int placeValue);
 string arabic2roman (string number);

 int romanChar2number (char roman);
 int roman2arabic (string number);

int main()
{
    string rawValue; //this is the variable that will store the value that will be converted

    fstream file("numbers.txt", ios::in | ios::out);

if(file){//checking to see if the file is open

    //the for loop below
        for (int i=0; file>>rawValue; i++){ //file>>rawValue serves both as a condition and a command

            file.clear(); //in case the end of file bit is reached.
                    //This is only a problem if the last line contains a 4 digit arabic number.

                if (rawValue[0] > 58){ //no digit has the ASCII code greater than 58, but all letters do
                //if the above condition is true, then it is a letter. So, I have to convert from roman to arabic
                    file.seekp((22L*i) + 16);
                    //in the statement above, 22L*i is in long format. It will move the pointer to the beginning of the current line.
                    // so, 22*i + 16 will move the put pointer to the 17th byte of the current line, where the roman Arabic numerals start

                    file << roman2arabic(rawValue); //inputs the converted Arabic numeral to the position where put pointer is

                }
                else {
                    file.seekp(22L*i);
                    // seekp((22L*i), ios::beg) moves the put pointer to the beginning of the current line, because there are 20 characters
                    // per line and 2 characters for the next line.
                    file << arabic2roman(rawValue); //inputs the converted roman numeral to the position where put pointer is
                }

                file.seekg(22L*(i+1)-2); //this brings the get pointer to the end of the current line
        }

        file.close(); //closing the file
}

else cout<<"Error opening the file"; //show an error message if the file couldnt be opened

    return 0;
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
        for (int i = 0 ; i < number.length(); i++){
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
    for (int i=0; i < number.length(); i++){
        sum += romanChar2number(number[i]);
        // the function romanChar2number() is used here.
        //this is just mindless addition of converted roman characters. Sum might be incorrect at this point.
    }


    for (int i=0; i< number.length()-1; i++) { //
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

