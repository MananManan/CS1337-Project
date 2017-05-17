#include "LinkedList.h"

LinkedList::LinkedList(){ //constructor sets the head and tail ptr to null
    head = tail = nullptr;
}

LinkedList::LinkedList(DoubleLinkNode* h){ //constructor sets head and tail pointer to the h
    head = tail = h;
    //also sets next and previous ptr to null
    head->setNext(nullptr);
    tail->setPrevious(nullptr);
}

void LinkedList::deleteList(){

    if (!head) { tail = head; return;} //base case, until head is not null
    static DoubleLinkNode* nodeptr; //creating a static nodeptr to delete recursively
    nodeptr = head; //move nodeptr to head
    head = head->getNext(); //move head to the next
    delete nodeptr; //delete nodeptr
    deleteList(); //recursive call

}

int LinkedList::getCount(){ //this function gets the number of elements in the Linked List
        int i = 0;
        DoubleLinkNode* nodeptr;
        for (nodeptr = head, i = 0 ; nodeptr; nodeptr = nodeptr->getNext(), i++);
        return i;
    }


void LinkedList::printList2Console(){
    //this function prints the linked list to console
    static DoubleLinkNode* nodeptr = head;
    static bool over = false;

    if (over){
        nodeptr = head;
        over = false;
    }

    if (!nodeptr){ //base case
        over = true;
        return;
    }
    cout<<*nodeptr<<endl;
    nodeptr = nodeptr->getNext();
    printList2Console();

}


void LinkedList::printList2File(ostream& out){
//
    static DoubleLinkNode* nodeptr = head;
    static bool over = false; //over means that the function has written everything to file

    if (over){ //if over is true, move the nodeptr back to head and set over = false for the next function
        nodeptr = head;
        over = false;
    }

    if (!nodeptr){ //base case
        //if nodeptr has reached the end, set over = true for the next function
        over = true;
        return;
    }
    out<< *nodeptr <<endl;
    nodeptr = nodeptr->getNext();
    printList2File(out); //recursive call

}

void LinkedList::swapConsec(DoubleLinkNode* &nodeptr){

    if (!nodeptr || getCount() == 1) return; //if list has less than 2 elements, than do nothing

    else if (nodeptr == head){
        //putting all the next pointers in right position
        head = head->getNext(); //moving head one forward
        nodeptr->setNext(head->getNext());
        head->setNext (nodeptr);
        nodeptr = head;
        // at this point, all the next positions are ok. Now setting the previous positions
        head->setPrevious(nullptr);
        head->getNext()->setPrevious(head);
        if (getCount() > 2) head->getNext()->getNext()->setPrevious(head->getNext());

    }

    else if (nodeptr->getNext() == tail){ //using a similar process as above

        //this time changing all the previous first
        nodeptr = nodeptr->getNext();
        tail = tail->getPrevious();
        nodeptr->setPrevious(tail->getPrevious());
        tail->setPrevious(nodeptr);

        //now changing the next
        tail->setNext(nullptr);
        tail->getPrevious()->setNext(tail);
        tail->getPrevious()->getPrevious()->setNext(tail->getPrevious());

    }

    else{
        DoubleLinkNode* holder = nodeptr;
        nodeptr = nodeptr->getNext();

        holder->setNext(nodeptr->getNext());
        nodeptr->setNext(holder);
        holder->getPrevious()->setNext(nodeptr);

        //setting the previous now
        nodeptr->setPrevious(holder->getPrevious());
        holder->setPrevious(nodeptr);
        holder->getNext()->setPrevious(holder);
    }

}

void LinkedList::sortList(int value){

    bool flag;

    if (getCount() < 2) return;

    if (value == 1){
        do{
            flag = false;
            for (DoubleLinkNode* nodeptr = head; nodeptr->getNext(); nodeptr = nodeptr->getNext()){
                if (nodeptr->getRoman() > nodeptr->getNext()->getRoman()){
                    swapConsec(nodeptr);
                    flag = true;
                }
            }
        }while (flag);
    }

    else if (value == 2){
        do{
            flag = false;
            for (DoubleLinkNode* nodeptr = head; nodeptr->getNext(); nodeptr = nodeptr->getNext()){
                if (nodeptr->getArabic() > nodeptr->getNext()->getArabic()){
                    swapConsec(nodeptr);
                    flag = true;
                }
            }
        }while (flag);
    }
}

DoubleLinkNode* LinkedList::binarySearch(string input){

    if (isValidRoman(input)){ //if the number is roman number

        sortList(1); //sorting the list according to roman
        int indexL = 0, indexM, indexR = getCount()-1; //setting the indexes
        DoubleLinkNode *ptrL = head, *ptrM, *ptrR = tail; //initializing pointers

        while (indexL <= indexR){ //using the algorithm for binary search, i.e. repeat until indexL < indexR

            indexM = (indexL + indexR)/2;
            ptrM = head;
            for (int i = 0; i != indexM; i++, ptrM = ptrM->getNext()); //move ptrM to where indexM is pointing

            if (input == ptrM->getRoman()){
                return ptrM;
            }

            else if (indexL == indexR){
                    break;
            }

            else if (input < ptrM->getRoman()){//if the input is less than the value inside the node ptrM is pointing to
                while (ptrR->getNext() != ptrM){ //move the ptrL to the right of ptrM and increment indexL
                    ptrR = ptrR->getPrevious();
                    indexR--;
                }
            }

            else if (ptrM->getRoman() < input){ //use a similar approach here
                while (ptrL->getPrevious() != ptrM){
                    ptrL = ptrL->getNext();
                    indexL++;
                }
            }

            else {
                return ptrM;
            }
        }
        sortList(2);
    }

    else if (isValidArabic(input)){ //if the number is arabic number
        //the process is almost the same as the previous one
        int indexL = 0, indexM, indexR = getCount()-1;
        DoubleLinkNode *ptrL = head, *ptrM, *ptrR = tail;

        while (indexL <= indexR){

            indexM = (indexL + indexR)/2;
            ptrM = head;
            for (int i =0; i <indexM; i++, ptrM = ptrM->getNext());

            if (atoi(input.c_str()) == ptrM->getArabic()){
                return ptrM;
            }

            else if (indexL == indexR){
                    break;
                }

            else if (atoi(input.c_str()) < ptrM->getArabic()){
                while (ptrR->getNext() != ptrM){
                    ptrR = ptrR->getPrevious();
                    indexR--;
                }
            }

            else if (ptrM->getArabic() < atoi(input.c_str())){
                while (ptrL->getPrevious() != ptrM){
                    ptrL = ptrL->getNext();
                    indexL++;
                }
            }
        }
    }
    //if the function makes it this far
    return nullptr;

}

void LinkedList::deleteNode(DoubleLinkNode* node){

   if (node == head) --(*this); //use the prefix operator to delete the first node
   else if (node == tail) (*this)--; //use the postfix operator to delete the last node
   else{ //if node, then delete the node normally
   node->getPrevious()->setNext(node->getNext());
   node->getNext()->setPrevious(node->getPrevious());
   delete node;
   }

}

bool LinkedList::operator +=(DoubleLinkNode &dln){ //dln is double link node

    if(dln.getArabic() == 0 && dln.getRoman() == ""){ // if the node is empty
        return false;
    }

    if(!head) {//if the list is empty
        head = tail = &dln; //set the head and tail to dln
        dln.setPrevious(nullptr);
    }

    else{ //if the list is not empty
        dln.setPrevious(tail); //set previous to current tail
        tail->setNext(&dln); //set tail's next to dln
        tail = &dln; //set tail to dln
    }

    dln.setNext(nullptr); //next is always set to null

    return true;
}

bool LinkedList::operator--(){
//this is the prefix operator
    if(!head) return false;
    else if (head == tail) tail = nullptr;
    DoubleLinkNode* nodeptr = head;
    head = head->getNext();
    delete nodeptr;
    if(head) head->setPrevious(nullptr);
    return true;
}

bool LinkedList::operator--(int){
    // the postfix operator

    if(!tail) return false;
    else if (tail == head) head = nullptr;
    DoubleLinkNode* nodeptr = tail;
    tail = tail->getPrevious();
    delete nodeptr;
    if (tail) tail->setNext(nullptr);
    return true;
}

