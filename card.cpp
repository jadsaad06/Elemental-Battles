//Name: Jad Saad
//Class: CS302
//This file holds all the code for my card classes
//It controls every version of card and how it can interact with the user

#include "card.h"

//Card Functions

//Constructor
Card::Card() : name(nullptr), type(fire), energyUsed(0), eff(none) {}

Card::Card(const string& strName, Type type, int energyUsed, Effect eff) :
    type(type), energyUsed(energyUsed), eff(eff) {
    name = new char[strName.size() + 1];  // +1 for null terminator
    
    for(size_t i = 0; i < strName.size(); i++) {
        name[i] = strName[i];
    }
    name[strName.size()] = '\0';  // Add null terminator
}

// Copy constructor - now copies all members
Card::Card(const Card& toCopy) {
    name = new char[strlen(toCopy.name) + 1];
    strcpy(name, toCopy.name);
    
    type = toCopy.type;
    energyUsed = toCopy.energyUsed;
    eff = toCopy.eff;  // Added missing member
}

Card::~Card(){
    if(name){
        delete[] name;
        name = nullptr;
    }
}

// Assignment operator - now copies all members
Card Card::operator=(const Card& toCopy) {
    if(this == &toCopy) {
        return *this;
    }
    
    if(this->name) {
        delete[] this->name;
    }
    
    this->name = new char[strlen(toCopy.name) + 1];
    strcpy(this->name, toCopy.name);
    
    this->type = toCopy.type;
    this->energyUsed = toCopy.energyUsed;
    this->eff = toCopy.eff;  // Added missing member
    
    return *this;
}

//Dispaly Card Details
ostream& operator<<(ostream& out, const Card& card){
    out << "\nCard Name; " << card.name
        << "\nType: " << card.type;

        return out;
}


Effect Card::getEffect() const{
    return eff;
}

//compares types, check if strong against player type
bool Card::isStrongAgainst(Type defender) const{
    return (type == fire && defender == plant) ||
           (type == plant && defender == water) ||
           (type == water && defender == fire);
}

//compares types, checks if weak against player type
bool Card::isWeakAgainst(Type defender) const {
    return (type == plant && defender == fire) ||
           (type == water && defender == plant) ||
           (type == fire && defender == water);
}



//Offense Functions
Offense::Offense() : Card(), mvPrompt(nullptr), dmgApplied(0) {}

Offense::Offense(const string& strName, Type type, int energyUsed,
                Effect eff, const string& strPrompt, int dmgApplied) 
    : Card(strName, type, energyUsed, eff), dmgApplied(dmgApplied) {
    mvPrompt = new char[strPrompt.size() + 1];  // Fixed: using mvPrompt instead of name
    
    for(size_t i = 0; i < strPrompt.size(); i++) {
        mvPrompt[i] = strPrompt[i];
    }
    mvPrompt[strPrompt.size()] = '\0';  // Add null terminator
}

Offense::Offense(const Offense& toCopy) : Card(toCopy), dmgApplied(toCopy.dmgApplied) {
    mvPrompt = new char[strlen(toCopy.mvPrompt) + 1];
    strcpy(mvPrompt, toCopy.mvPrompt);
}

Offense::~Offense(){
    if(mvPrompt)
    {
        delete[] mvPrompt;
        mvPrompt = nullptr;
    }
}
Offense Offense::operator=(const Offense& toCopy) {
    if(this == &toCopy) {
        return *this;
    }
    
    // Call base class assignment operator
    Card::operator=(toCopy);
    
    if(this->mvPrompt) {
        delete[] mvPrompt;
    }
    
    this->mvPrompt = new char[strlen(toCopy.mvPrompt) + 1];
    strcpy(this->mvPrompt, toCopy.mvPrompt);
    
    this->dmgApplied = toCopy.dmgApplied;
    
    return *this;
}

ostream& operator<<(ostream& out, const Offense& card){
    out << "\nDamage: " << card.dmgApplied
        << "\nEnergy: " << card.energyUsed;

        return out;
}

int Offense::getDamage() const{
    return dmgApplied;
}

//Defense functions
Defense::Defense(): Card(), mvPrompt("none"){}


Defense::Defense(const string& strName, Type type, int energyUsed,
Effect eff, const string& mvPrompt, int defGained):Card(strName, type, energyUsed, eff), mvPrompt(mvPrompt), defGained(defGained){}

ostream& operator<<(ostream& out, const Defense& card){
    out << "\nEffect: " << card.eff
        << "\nEffect Gained: " 
        << card.defGained;

        return out;
}

int Defense::getDefense() const{
    return defGained;
}


//Supoort Functions
Support::Support(): Card(),mvPrompt("none"){}
Support::Support(const string& strName, Type type, int energyUsed,
Effect eff, const string& mvPrompt, int supGained):Card(strName, type, energyUsed, eff), mvPrompt(mvPrompt), supGained(supGained){}

ostream& operator<<(ostream& out, const Support& card){
    out << "Effect: " << card.eff
        << "Effect Gained: " << card.supGained;

        return out;
}

int Support::getSupport() const{
    return supGained;
}





