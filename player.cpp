//Name: Jad Saad
//Class: CS302
//This file holds all the code to the player. It controls how the 
//player interacts with the cards and most of all how the user interacts
//with all the data in the program. 

#include "player.h"

Player::Player():name("none"){}

Player::Player(string name, Type type): name(name), type(type){}

Player::operator bool() const{
    return stats.cmpHealth(0);
}

bool Player::operator>(const Player& player2){
    return stats.cmpHealth(player2.stats);
}
bool Player::operator<(const Player& player2){
    return !stats.cmpHealth(player2.stats);
}

//Apply Damage or Stun
Player Player::operator+(const Offense& toApply){
    Player temp;

    temp.name = this->name;
    temp.type = this->type;
    temp.stats = this->stats;
    
    if(toApply.getEffect() == stun){
        if(!temp.stats.gainStun()){
            cout << "\nPlayer already stunned!\n";
        }else{
            cout << "\nStun Applied!\n";
        }
    }else{
        bool isWeak = isWeakAgainst(toApply);
        bool isStrong = isStrongAgainst(toApply);
        float multiple = 1;

        if(isStrong) multiple = 0.5;
        if(isWeak) multiple = 2;

        int damage = temp.stats.getHit(toApply.getDamage(), multiple);
        cout << endl << damage << " damage done!\n";
    }

    return temp;
}

//Apply Defense or Damage Negation
Player Player::operator+(const Defense& toApply){
    Player temp;

    temp.name = this->name;
    temp.type = this->type;
    temp.stats = this->stats;

    if(toApply.getEffect() == dmgNegation){
        if(!temp.stats.gainNegation()){
            cout << "\nYou already have damgage negation!\n";
        }else{
            cout << "\nDamage Negation Gained!\n";
        }
    }
    else{
        int shield = temp.stats.gainShield(toApply.getDefense());
        cout << "\nUpdated Shield: " << shield << endl;
    }

    return temp;
}

//Apply Health or Energy Gain
Player Player::operator+(const Support& toApply){
    Player temp;

    temp.name = this->name;
    temp.type = this->type;
    temp.stats = this->stats;

    if(toApply.getEffect() == healthGain){
        int gained = temp.stats.gainHealth(toApply.getSupport());
        cout << "\nUpdated Health: " << gained;
    }else{
        int gained = temp.stats.gainEnergy(toApply.getSupport());
        cout << "\nUpdated Energy: " << gained;

    }


    return temp;
}

//Apply Damage or Stun
Player& Player::operator+=(const Offense& toApply){
    if(toApply.getEffect() == stun){
        if(!this->stats.gainStun()){
            cout << "\nPlayer already stunned!\n";
        }else{
            cout << "\nStun Applied!\n";
        }
    }else{
        bool isWeak = isWeakAgainst(toApply);
        bool isStrong = isStrongAgainst(toApply);
        float multiple = 1;

        if(isStrong) multiple = 0.5;
        else if(isWeak) multiple = 2;

        int damage = this->stats.getHit(toApply.getDamage(), multiple);
        cout << endl << damage << " damage done!\n";
    }

    return *this;
}

//Apply Defense or Damage Negation
Player& Player::operator+=(const Defense& toApply){
    if(toApply.getEffect() == dmgNegation){
        if(!this->stats.gainNegation()){
            cout << "\nYou already have damgage negation!\n";
        }else{
            cout << "\nDamage Negation Gained!\n";
        }
    }
    else{
        int shield = this->stats.gainShield(toApply.getDefense());
        cout << "\nUpdated Shield: " << shield << endl;
    }

    return *this;
}

//Apply Health or Energy Gain
Player& Player::operator+=(const Support& toApply){

    if(toApply.getEffect() == healthGain){
        int gained = this->stats.gainHealth(toApply.getSupport());
        cout << "\nUpdated Health: " << gained;
    }else{
        int gained = this->stats.gainEnergy(toApply.getSupport());
        cout << "\nUpdated Energy: " << gained;
    }


    return *this;
}

//Output Player Stats
ostream& operator<<(ostream& out, const Player& player){
    out << "\nName: " << player.name
        << "\nType: ";

    switch(player.type){
        case 0:
            out << "Fire";
            break;
        case 1:
            out << "Water";
            break;
        case 2:
            out << "Plant";
            break;
    }

    out << player.stats;

    return out;
}

bool Player::isStunned(){
    return stats.getStun();
}


void Player::displayName(){
    cout << name;
}

void Player::applyStun(){
    stats.applyStun();
}


//check if weak
bool Player::isWeakAgainst(const Card& oppCard) const{
    bool isWeak = oppCard.isStrongAgainst(type);

    if(isWeak){
        cout << "\nType Disadvantage! Damage 1.5x!" << endl;
    }

    return isWeak;
}

//check if strong
bool Player::isStrongAgainst(const Card& oppCard) const{
    bool isStrong = oppCard.isWeakAgainst(type);

    if(isStrong){
        cout << "\nType Advantage! Damage is Halved!" << endl;
    }

    return isStrong;
}
