#ifndef DOUBLELINKNODE_H
#define DOUBLELINKNODE_H

#include "BaseNode.h"

class DoubleLinkNode : public BaseNode{
private:
    void dummy(){}
    DoubleLinkNode* next;
    DoubleLinkNode* previous;

public:
    //constructors
    DoubleLinkNode() : BaseNode() { next = previous = nullptr; } //default
    DoubleLinkNode(string input) : BaseNode(input) { next = previous = nullptr; } //overloaded
    DoubleLinkNode(DoubleLinkNode& abc) : BaseNode(abc) {next = nullptr; previous = nullptr;}; //copy
    //in the above statement, BaseNode(abc) works because of polymorphism

    //accessors
    DoubleLinkNode* getNext() { return next;}
    DoubleLinkNode* getPrevious() {return previous;}

    //mutators
    void setNext(DoubleLinkNode* x) { next = x;}
    void setPrevious (DoubleLinkNode* x) { previous = x;}

};

#endif // DOUBLELINKNODE_H
