#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "DoubleLinkNode.h"


class LinkedList {

private:
    DoubleLinkNode* head;
    DoubleLinkNode* tail;
    void swapConsec(DoubleLinkNode*&);
public:

    LinkedList(); //default constructor

    LinkedList (DoubleLinkNode* h);

    void deleteList();

    ~LinkedList() { deleteList(); } //destructor

    //Mutators
    void setHead (DoubleLinkNode* h) { head = h;}
    void setTail (DoubleLinkNode* t) { tail = t;}

    //Accessors
    DoubleLinkNode* getHead () { return head;}
    DoubleLinkNode* getTail () { return tail;}
    int getCount(); //get the number of elements in the Linked List

    //Functions
    void printList2Console (); //to print the list recursively

    void printList2File(ostream&);

    void sortList (int); //this function sorts the nodes according to bubble sort

    DoubleLinkNode* binarySearch(string); //this function uses binary search

    void deleteNode(DoubleLinkNode* node); //delete a node whose node pointer is given

    bool operator+=(DoubleLinkNode&); //adds a node to the end of the linked list

    bool operator--(); //delete the last node and moves the tail ptr

    bool operator--(int); //deletes the first node and moves the head ptr


};



#endif // LINKEDLIST_H
