#pragma once
#include "card.h"

template<typename T>
class DLLnode{
    private:
    DLLnode<T>* next;
    DLLnode<T>* prev;
    T* card;

    public:
    DLLnode();
    ~DLLnode();
    DLLnode(T* card);
    
    DLLnode<T>* getNext();
    DLLnode<T>* getPrev();
    T* getCard();
    void setNext(DLLnode<T>*);
    void setPrev(DLLnode<T>*);

    void displayCard();
};


template<typename T>
class Deck{
    private:
    DLLnode<T>* head;
    DLLnode<T>* tail;
    int size;

    DLLnode<T>* shuffleList(DLLnode<T>* curr);
    void addToBottom(T* card);
    void addToTop(T* card);
    void deleteDeck(DLLnode<T>* head);


    public:
    Deck();
    ~Deck();
    Deck(vector<T*> deck);

    T* takeCard();
}; 


