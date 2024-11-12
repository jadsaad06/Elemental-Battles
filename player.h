#pragma once
#include "myutil.h"
#include "card.h"
#include "health.h"

class Player{
    private:
    Health stats;
    string name;
    Type type;
    
    bool isWeakAgainst(const Card&) const;
    bool isStrongAgainst(const Card&) const;

    public:
    Player();
    Player(string name, Type type);
    
    friend ostream& operator<<(ostream& out, const Player&);
    bool operator<(const Player&);
    bool operator>(const Player&); //cmp health
    Player operator+(const Offense&); //apply dmg
    Player operator+(const Defense&);
    Player operator+(const Support&);
    Player& operator+=(const Offense&); 
    Player& operator+=(const Defense&);
    Player& operator+=(const Support&);
    operator bool() const; //check health

    void takeTurn();
    void displayName();
    bool isStunned();
    void applyStun();
};   

