//BINARY SEARCH LINES 625 - 755, CALL LINE 154
//INPUT VALIDATION

/*Note: For binary search, the function is binarySearch() and is called as "binarySearch(head, input)"
  Please find it if for whatever reason the line numbers get messed up in different editors*/

/*
Project 3 Draft 1
NAME : MANAN MANAN
NETID : mxm163530
CLASS : CS1337.001
Professor : Jason Smith
*/

#include <iostream>
#include<sstream>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;

//the main structure
 struct Node{

    int arabic;
    string roman;

    Node* next;

};

 //function to "clear" screen
 void ClearScreen();

//convert string to integer
 int string2int(string);

//for validation
 void isValidFileInput(string&);
 bool isValidArabic (string);
 bool isValidRoman (string);

//functions for conversion
 string digit2letters(int faceValue, int placeValue);
 string arabic2roman (string number);
 int romanChar2number (char roman);
 int roman2arabic (string number);

//functions for sorting
void swapNodes(Node*&, Node*&, Node*&);
void selectionSort (Node*&, string);

//functions for searching
string binarySearch(Node*, string);

//for deleting a linked list
void deleteList (Node*&);


/*
 The following definitions of faceValue and placeValue will be used in the program:
 faceValue : the digit itself. faceValue of '5' in 34562 is 5 itself.
 placeValue : the value of the place the digit is in. It is counted from the right. placeValue of '5' in 34562 is 3 i.e. it
 is in hundreds place.
 */

int main()
{

    string input;
    Node *head = nullptr;
    Node *nodePtr = nullptr; //this will be used a lot to point to/navigate through the list
    ifstream fileIn("numbers.txt");

    //----
    //Getting the linked list
    //----


    while (getline(fileIn, input)){//while loop until the file can be read

            isValidFileInput(input); //this function changes things by reference. It checks if there are 2 elements in the line.

            Node *newNode = new Node; //creating a new dynamic node

            if (isValidArabic(input)){ //if the input is arabic
                    newNode->arabic = string2int(input);
                    newNode->roman = arabic2roman(input);
                }


            else if (isValidRoman(input)){//if the input is roman
                newNode->roman = input;
                newNode->arabic = roman2arabic(input);
            }

            else {
                delete newNode; //if input is not arabic or roman, then delete the node
                continue;
            }

            newNode->next = nullptr; //prepare the node to me added to the end of the linked list

            if(!head) {// if head is nullptr, then the list is empty. newNode will be the first node
                head = newNode;
                nodePtr = head; //assign the location of head to nodePtr. nodePtr IS NOW POINTING TO THE LAST ELEMENT OF THE LIST
            }
            else{// if head != nullptr, adds the newNode to the end of the list
               while(nodePtr->next){
//Stops the loop when nodePtr->next == nullptr i.e. nodePtr points to the last Node of the list
                    nodePtr = nodePtr->next; //moves to the next node
               }
                nodePtr->next = newNode; //connecting the last node to newNode
            }
        }

    fileIn.close(); //closing the file
    input.clear(); //clearing the input variable

    //----
    //----

    //the User Interface is below

    while (true){//this is the loop for the UI

       ClearScreen();
        cout<<endl<<"************************************"<<endl;
        cout<<endl<<"Enter '1', '2', or '3'."<<endl;
        cout<<endl<<" 1. Search"<<endl;
        cout<<" 2. Sort"<<endl;
        cout<<" 3. Exit & Write to file"<<endl<<endl;
        cout<<" Choose an option : ";
        getline(cin,input);

        while (!(input == "1" || input == "2" || input == "3")){ //this loop is for input validation
            cout<<" Invalid input. Enter only 1', '2', or '3' :";
            getline(cin,input);
        }

        if (input == "1"){

            cout<<endl<<"   |\n   Enter the number you want to search : ";

            getline(cin, input);

            while(!(isValidArabic(input) || isValidRoman(input))){
            //this loop will go on if ALL the two conditions isValidArabic(input) AND isValidRoman(input) are false
                cout<<"   Invalid input. Enter the number you want to search again : ";
                getline(cin, input);
            }

/*BINARY-SEARCH CALL */cout<<endl<<"******\nSEARCH RESULT : "<<input<<" is "<<binarySearch(head, input)<<"\n*****"<<endl; //BINARY SEARCH USED HERE
            cout<<endl<<"Press enter to go back to main menu....";
            getline(cin, input);
        }

        else if (input == "2"){

            cout<<endl<<"   |\n   Sort menu: Please only enter '1' or '2'"<<endl; //formatted this way to make is aesthetically pleasing
            cout<<"     1. Sort by Roman numeral"<<endl;
            cout<<"     2. Sort by Arabic numeral"<<endl;

            cout<<"     Choose an option : ";
            getline(cin, input);

            while (!(input == "1" || input == "2" )){

                cout<<"     Invalid input. Choose either '1' or '2' : ";
                getline(cin, input);
            }

            selectionSort(head, input); //selection sort used here. MAKES PERMANENT CHANGES TO THE ORIGINAL LIST

            if (input == "1"){

                cout<<endl<<"   Here are the Roman numerals in alphabetical order :"<< endl;
                for (nodePtr = head; nodePtr; nodePtr = nodePtr->next){
                        cout<<"   "<<nodePtr->roman<<endl;
                }
            }
            else if (input == "2"){

                cout<<endl<<"   Here are the Arabic numerals in ascending order :"<< endl;
                for (nodePtr = head; nodePtr; nodePtr = nodePtr->next){
                        cout<<"   "<<nodePtr->arabic<<endl;
                }

            }

            cout<<endl<<"Press enter to go back to main menu.... ";
            getline(cin, input);
        }

        else if (input == "3"){
            cout<<endl<<"Exiting & Writing...";
            break;
        }

        else {

            return -1;

        }

    }

    //the menu has ended, so write to the file

    ofstream fileOut("numbers.txt");

    for (nodePtr = head; nodePtr; nodePtr = nodePtr->next){//the for loop stops when nodePtr
        //writ the linked list to the file in the same format
        fileOut<< setw(16) << left << nodePtr->roman;
        fileOut<<' ';
        fileOut<< setw(4) << left << nodePtr->arabic <<endl;

    }

    fileOut.close();

    //----
    return 0;
}

void ClearScreen(){
    //this function "clears" screen by printing 15 newlines (length of the main menu)
    cout << string(15, '\n' );
    }

int string2int(string theString){
    //using string streams, converts string to integer
    int returnValue;
    stringstream sso("");
    sso << theString;
    sso >> returnValue;

    return returnValue;
}

void isValidFileInput(string& input){//input is pass by reference

    //this function checks if a line of the string (form inputFile) is *continuous*

    //the input is expected to to be a line from the file
    //The line should have only one thing that is not separated by spaces

    /*assume that the input is inputA and inputB.
      inputA = "CXXCSFG              ". inputB = "   MMX    XII   12345".
      inputA is "correct" as it is in correct file format. inputB is wrong.
      IT DOES NOT CHECK WHETHER THE INPUT ITSELF IS CORRECT. There are other functions for that.
      */

    stringstream sso;

    sso << input; //puts the input in string stream
    input.clear(); //clears the input
    sso >> input; //extracts from the sso

    if (sso >> input){//if the operation is successful once again
//if the input was continuous, then this operation would fail as there would be nothing in sso to extract (>> operator does not read whitespace)

        input = "NOT VALID"; //input is set to "NOT VALID" which would result in isValidArabic(input) and isValidRoman(input) being false
    }
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

    if ((string2int(input) <= 0) || (4999 < string2int(input))){ //CHECK 2: if the number is outside the 1-4999 range, return false
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

void swapNodes(Node*& first, Node*& second, Node*& head){
    //swaps nodes "first" and "second". first, second, and head are all passed by reference.
    //first will always be behind second

    //NOTE : The "first" pointer is pointing to secondN and second pointer to secondN. This is dealt with latter in the function.

    Node *temp, *previous1, *previous2;

    /* Cases for swapping node:
        a. if first == second
        b. If first == head (or not)
        c. If if first->next == second (or not)
    So we essentially have 5 cases: */

    if (first == second){//If both the Nodes are infact the same node
    //do nothing
    }

    else if (first == head){ //these MOVE THE HEAD PERMANENTLY
        //---When the first element is the head, then (previous1->next) is simply head = *something*!---

        if (first->next != second){

            // *head*---->(firstN)---->(nextFirstN)---->....(previous2)---->(secondN)---->(nextSecondN)---->....

            for (previous2 = head; previous2->next != second; previous2 = previous2->next);

            temp = second->next;
            second->next = first->next; // (secondN)---->(nextFirstN)
            first->next = temp; // (firstN)---->(nextSecondN)

            previous2->next = first;// (previous2)---->(first)
            head = second;// *head*---->(secondN)

        }

        else if (first->next == second){//first and second are consecutive


            /*When the elements are consecutive, then
                a. (first->next) is simply second
                b. The above implies that previous2 is first
                */

            //In this case, previous1->next = head, previous2->next = second, first->next = second
            // *head*---->(firstN)---->(secondN)---->(nextSecondN)

            head = second; //*head*---->(secondN). THIS MOVES THE HEAD OF THE ORIGINAL LINKED LIST
            first->next = second->next; // (firstN) ----> (nextSecondN)
            second->next = first; //(secondN)----> (first)

            //So *head*---->(secondN)---->(firstN)---->(nextSecondN)

        }


    }

    else if (first != head){

        if (first->next != second){
            //if the first and second nodes are not consecutive and first node != head

            /* *head*---->....(previous1)---->(firstN)---->(nextFirstN)---->....(previous2)---->(secondN)---->(nextSecondN)---->.... */

            //assign the locations of the previous nodes of first and second to previous1 and previous2 respectively
            for (previous1 = head; previous1->next != first; previous1 = previous1->next);
            for (previous2 = head; previous2->next != second; previous2 = previous2->next); //for loop STOPS when previous2->next == first

            //swapping the next values in the current nodes
            temp = first->next;
            first->next = second->next; //(firstN)---->(nextSecondN)
            second->next = temp;// (secondN)---->(nextFirstN)

            //swapping the *current* node i.e. swapping the next values in the previous nodes
            previous1->next = second; // (previous1)---->(secondN)
            previous2->next = first; // (previous2)---->(firstN)

            // *head*---->....(previous1)---->(secondN)---->(nextFirstN)---->....(previous2)---->(firstN)---->(nextSecondN)---->....

        }

        else if (first->next == second){

        //if nodes are consecutive (and first != head) ....(previous1)---->(firstN)---->(secondN)---->(thirdN)---->....

        for (previous1 = head; previous1->next != first; previous1 = previous1->next); //when previous1->next = first, stops the for loop

        previous1->next = second; // (previous1)---->(secondN)
        first->next = second->next; // (firstN)----> (thirdN)
        second->next = first; //(secondN)----> (firstN)

        //So ....(previous1)---->(secondN)---->(firstN)---->(thirdN)---->....
    }



    }


    //swapping the first and second *pointers*
    temp = first;
    first = second;
    second = first;

}

void selectionSort (Node*& head, string typeOfSort){

    if (!head) return; //if the list is empty, there is no need for sorting it

    Node *minValue; //this is the pointer to the node which holds the minimum value

    //the algorithm for selection sort in arrays and the one modified here to be used with linked list is basically the same

    if (typeOfSort == "1"){//if the sort is alphabetical

        for (Node *nodePtr1 = head; nodePtr1->next; nodePtr1 = nodePtr1->next){//for loops goes own until the last node

            minValue = nodePtr1;

            for (Node *nodePtr2 = nodePtr1->next; nodePtr2; nodePtr2 = nodePtr2->next){//for loop goes on until nodePtr2 is null

                if(nodePtr2->roman < minValue->roman){

                    minValue = nodePtr2;
                        }

            }

            swapNodes(nodePtr1, minValue, head); //swap nodes

        }
    }

    else if (typeOfSort == "2"){//the code is same as for option "a". "roman" is replaced with "arabic

        for (Node *nodePtr1 = head; nodePtr1->next; nodePtr1 = nodePtr1->next){

            minValue = nodePtr1;

            for (Node *nodePtr2 = nodePtr1->next; nodePtr2; nodePtr2 = nodePtr2->next){

                if(nodePtr2->arabic < minValue->arabic){

                    minValue = nodePtr2;
                        }

            }

            swapNodes(nodePtr1, minValue, head); //swap the nodes

        }
    }


}

string binarySearch(Node* nodePtr1, string input){

    //nodePtr1 is used as the pointer the the first element from where you want the search to start
    //for this program, assume that nodePtr1 is the head

    if (!nodePtr1) return "not found. The list is empty!"; // if nodePtr1 is null, there are no nodes after it and hence "not found"

    //making a copy of the Linked List

    Node *head2 = new Node; //creating a new head

    *head2 = *nodePtr1; //copying the value of nodePtr1 to head2

    nodePtr1 = nodePtr1->next;

    for (Node *nodePtr2 = head2; nodePtr1; nodePtr2 = nodePtr2->next, nodePtr1 = nodePtr1->next){

/*  nodePtr1 starts on the SECOND node of the first list
    nodePtr2 starts from the FIRST node of the second list
    this loop goes on until nodePtr1 is null.
    both nodePtr1 and nodePtr2 move one node ahead after each iteration
    */

    //similar process that was used to create the first linked list
        Node *newNode = new Node;
        *newNode = *nodePtr1;
        newNode->next = nullptr;
        nodePtr2->next = newNode;

    }

//a Linked List has now been created that is exact copy of our original Linked List. This has a head "head2".

    //the binary search will start now

    int indexL,indexM, indexR;
    //3 "indexes" that will simulate the indexes of the array
    //Every time I move the left, right, or middle pointers, I will move indexL, indexM, or indexR to reflect it.
    //This makes the code below as virtually same for arrays.

    Node *left = nullptr, *middle = nullptr, *right = nullptr;


    if(isValidArabic(input)){
        int arabicInput = string2int(input); //converting arabic input in string to arabic input in int

        selectionSort(head2, "2"); //sorting linked list 2

        //moving left to the leftmost element
        left = head2;
        indexL = 0; //Changing the index to the leftmost element

        if (arabicInput < left->arabic){ //imp: if the value to be found is less than the first element, then obviously the element is not there
            return "not found";
        }

        for(indexR = 0,right = head2    ;    right->next    ;   right = right->next, indexR++); //moving right and indexR to rightmost element.

        while(indexL <= indexR){
            for(indexM = 0, middle = head2      ;        indexM != (indexL + indexR)/2      ;        middle = middle->next, indexM++);

            if (middle->arabic == arabicInput){

                deleteList(head2);

                if (input[0] == '0'){ //if input starts with 0
                    cout<<"Well...."<<input<<" is same as "<<string2int(input)<<", so...";
                }

                return "found";
            }

            else if (middle->arabic < arabicInput){

                while (middle->next != left){ //moving left to middle+1
                    left = left->next;
                    indexL++;
                }
            }

            else if (arabicInput < middle->arabic){
                for (indexR = 0, right = head2   ;    right->next != middle   ;     right=right->next,indexR++); //moving right to middle-1
            }
        }
    }

    else if(isValidRoman(input)){ //the process for the roman numeral is the same except ->arabic is replaced with ->roman

        selectionSort(head2, "1");

        left = head2;

        if (input < left->roman){
            return "not found";
        }

        indexL = 0;
        for(indexR = 0,right = head2    ;    right->next    ;   right = right->next, indexR++);

        while(indexL <= indexR){
            for(indexM = 0, middle = head2      ;        indexM != (indexL + indexR)/2      ;        middle = middle->next, indexM++);

            if (middle->roman == input){

                deleteList(head2);
                return "found";
            }

            else if (middle->roman < input){

                while (middle->next != left){
                    left = left->next;
                    indexL++;
                }
            }

            else if (input < middle->roman){
                for (indexR = 0, right = head2   ;    right->next != middle   ;     right=right->next,indexR++);
            }
        }
    }

    deleteList(head2);

    if (input[0] == '0'){ //an additional check
        cout<<"Well...."<<input<<" is same as "<<string2int(input)<<", so...";
    }

    return "not found";
}


void deleteList (Node*& head){
    //takes the head of a list by reference and deletes the whole list

    Node* nodePtr;

    while (head){ //Loop stops when head is pointing to null
        nodePtr = head; //move nodePtr to head
        head = head->next; //move head to next node
        delete nodePtr; //delete the dynamic data that nodePtr is pointing to
    }

}
