#include "deck.h"

template<typename T>
DLLnode<T>::DLLnode():next(nullptr),prev(nullptr),card(nullptr){}

template<typename T>
DLLnode<T>::DLLnode(T* card):next(nullptr), prev(nullptr), card(card){}

template<typename T>
DLLnode<T>::~DLLnode(){
    next = nullptr;
    prev = nullptr;
    delete card;
}

template<typename T>
DLLnode<T>* DLLnode<T>::getNext(){
    return next;
}

template<typename T>
DLLnode<T>* DLLnode<T>::getPrev(){
    return prev;
}

template<typename T>
void DLLnode<T>::setNext(DLLnode<T>* nextNode){
    next = nextNode;
}

template<typename T>
void DLLnode<T>::setPrev(DLLnode<T>* prevNode){
    prev = prevNode;
}

template<typename T>
T* DLLnode<T>::getCard(){
    return card;
}

template<typename T>
void DLLnode<T>::displayCard(){
    cout << *card;
}

template<typename T>
Deck<T>::Deck():head(nullptr), tail(nullptr), size(0){}

template<typename T>
Deck<T>::~Deck(){
    deleteDeck(head);
}


template<typename T>
Deck<T>::Deck(vector<T*> deck): head(nullptr), tail(nullptr){

    for(T* i : deck){
        addToTop(i);
    }

    head = shuffleList(head);
}



//delete the deck recursively
template<typename T>
void Deck<T>::deleteDeck(DLLnode<T>* head){
    if(!head){
        return;
    }

    deleteDeck(head->getNext()); 

    delete head;
}


template<typename T>
T* Deck<T>::takeCard() {
    if(!head) return nullptr;
    
    // Store the card to return
    T* drawnCard = head->getCard();
    cout << "\nCard Drawn:\n";
    cout << *drawnCard;
    
    // Remove the top node
    DLLnode<T>* oldHead = head;
    head = head->getNext();
    if(head) {
        head->setPrev(nullptr);
    } else {
        tail = nullptr;  // List is now empty
    }
    
    delete oldHead;
    
    // Add a copy of the card to bottom
    addToBottom(drawnCard);
    
    size--;
    return drawnCard;
}
//add card to top of the deck
//used when creating deck
template<typename T>
void Deck<T>::addToTop(T* card) {
    DLLnode<T>* node = new DLLnode<T>(card);
    
    if(!head) {
        // Empty deck
        head = tail = node;
    } else {
        // Non-empty deck
        node->setNext(head);
        head->setPrev(node);
        head = node;
    }
    size++;
}
//add to bottom of the deck
//when taking the top card, use this function to put it to the bottom
template<typename T>
void Deck<T>::addToBottom(T* card) {
    DLLnode<T>* node = new DLLnode<T>(card);

    if(!tail) {
        // Empty deck
        head = tail = node;
    } else {
        // Non-empty deck
        tail->setNext(node);
        node->setPrev(tail);
        tail = node;
    }
    size++;
}

template<typename T>
DLLnode<T>* Deck<T>::shuffleList(DLLnode<T>* head) {
    if (!head || !head->getNext()) {
        return head;  // Base case: if the list has 0 or 1 node, it's already shuffled
    }

    // Find the length of the list
    int length = 0;
    DLLnode<T>* temp = head;
    while (temp) {
        length++;
        temp = temp->getNext();
    }

    // Pick a random position in the list
    int randomPos = rand() % length;
    DLLnode<T>* randomNode = head;
    for (int i = 0; i < randomPos; i++) {
        randomNode = randomNode->getNext();
    }

    // Move the random node to the front
    if (randomNode != head) {
        // Disconnect randomNode from its current position
        if (randomNode->getPrev()) {
            randomNode->getPrev()->setNext(randomNode->getNext());
        }
        if (randomNode->getNext()) {
            randomNode->getNext()->setPrev(randomNode->getPrev());
        }

        // Move it to the head
        randomNode->setNext(head);
        head->setPrev(randomNode);
        randomNode->setPrev(nullptr);
        head = randomNode;
    }

    // Recursively shuffle the rest of the list (after the head)
    head->setNext(shuffleList(head->getNext()));

    return head;
}



