//DELETE ANY NODE

//Manan Manan mxm163530
//Binary Search is called in line 58
#include <iostream>
#include <iomanip>
#include <fstream>

#include "DoubleLinkNode.h"
#include "LinkedList.h"

using namespace std;

int main()
{
    //*********initializing the variables***********
    ifstream inFile ("numbers.txt");
    string input;
    DoubleLinkNode *newNode = nullptr, *nodeptr = nullptr;
    stringstream sso("");

    LinkedList theList;

    while (getline(inFile, input)){//while can read new line

        if(isValidFileInput(input)){//this function sets input to just input if it is valid

            newNode = new DoubleLinkNode(input); //creating a dynamic node
            theList += *newNode; //using the += overloaded operator to add node
        }

    }

    inFile.close(); //closing the file!

    theList.sortList(2); //sort the list using arabic

    while (true){//this is the loop for the UI, which is self-explanatory
        cout << string(15, '\n' );
        cout<<endl<<"************************************"<<endl
            <<" 1. Search"<<endl
            <<" 2. Add"<<endl
            <<" 3. Delete First"<<endl
            <<" 4. Delete Last"<<endl
            <<" 5. Delete Specific"<<endl
            <<" 6. Exit"<<endl<<endl
            <<" Number of nodes : "<<theList.getCount()<<endl<<endl
            <<" Choose an option : ";
        getline(cin,input);

        if (input == "1"){

            cout<<"Enter the number you want to search :"<<endl;
            getline(cin,input);


            cout<<input<<" is ";
            if(theList.binarySearch(input)) cout <<"found!"<<endl;
            //binary search returns the pointer to the node
            else if (!theList.binarySearch(input)) cout <<"not found!"<<endl;

            cout<<"Press enter to continue";
            getline(cin,input);

        }

        else if (input == "2"){
            cout<<"Enter the number you want to add :"<<endl;
            getline(cin,input);

            newNode = new DoubleLinkNode(input);//create a new node and use the overloaded constructor
            theList += *newNode; //use the overloaded operator
            theList.sortList(2); //sort list using arabic
            cout<<"The node has been added!"<<endl;

            cout<<"Press enter to continue";
            getline(cin,input);


        }
        else if (input == "3"){
            --theList; //using the overloaded operator to delete node
            if (theList.getHead() != nullptr) cout<<"First node has been deleted!"<<endl;
            else cout<<"The list is now empty"<<endl;

            cout<<"Press enter to continue";
            getline(cin,input);

        }
        else if (input == "4"){
            theList--;//using the overloaded operator to delete node
            if (theList.getTail() != nullptr) cout<<"Last node has been deleted!"<<endl;
            else cout<<"The list is now empty"<<endl;

            cout<<"Press enter to continue";
            getline(cin,input);

        }
        else if (input == "5"){

            cout<<"Enter the number you want to delete :"<<endl;
            getline(cin,input);

            newNode = theList.binarySearch(input);
            //the binarySearch returns the pointer to the node when it is found

            if(newNode){

                theList.deleteNode(newNode);
                //the delete node takes a node pointer and delete that node
                cout <<"Node with number "<<input<<" has been deleted"<<endl;
            }

            else if (!newNode) cout <<"Node with number "<<input<<" not found"<<endl;

            cout<<"Press enter to continue";
            getline(cin,input);

        }
        else if (input == "6"){

            ofstream outFile ("answers.txt");

            theList.printList2File(outFile); //print list to the file using the member function

            outFile.close(); //closing the output file

            break;

        }
    }
}
