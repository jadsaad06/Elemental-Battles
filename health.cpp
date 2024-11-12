//Name: Jad Saad
//Class: CS302
//The health.cpp file holds all the code for the players attack stats
//and the players health. This is the main way of tracking the card
//effects and the win condition

#include "health.h"

//Attack Stat Functions

//initialize attack stats
attStats::attStats(): dmgNegation(false), shield(0), stun(false){}

//reduces damage by amt shield available
int attStats::applyShield(int damage){
    if(shield > damage){
        shield -= damage;
        cout << "\nShield took " << damage << "damage!\n";
        damage = 0;
    }else if(shield <= damage && shield > 0){
        cout << "\nShield broke\n";
        damage -= shield;
        shield = 0;
    }

    return damage;
}

//reduce damage by 50% if you have damage negation
int attStats::applyNegation(int damage){
    if(dmgNegation){
        damage = static_cast<double>(damage) * 0.5;
        dmgNegation = false;
    }

    return damage;
}

//if stunned skip turn
bool attStats::applyStun(){
   if(stun){
       stun = false;
       return true;
    }

    return false;
}

bool attStats::getStun(){
    return stun;
}

//apply shield gain
int attStats::gainShield(int effect){
    shield += effect;

    if(shield > 100){
        shield = 100;
    }

    return shield;
}

//apply negation; if already applied, don't allow use of card
bool attStats::gainNegation(){
    if(dmgNegation){
        return false;
    }

    dmgNegation = true;
    return true;
}

//apply stun; if already applied, don't allow use of card
bool attStats::gainStun(){
    if(stun){
        return false;
    }

    stun = true;
    return true;
}

//Health and Energy Functions

//initialize health and energy
Health::Health():health(100), energy(100){}

//apply effects to damage, then apply damage to health
int Health::getHit(int dmg, float multiple){
    dmg *= multiple;
    dmg = applyNegation(dmg);
    dmg = applyShield(dmg);

    health -= dmg;

    return health;
}

//reduce energy by amount card inheritately takes
int Health::useEnergy(int consumption){
    energy -= consumption;

    if(energy < 0){
        energy = 0;
    }

    return energy;
}

int Health::gainHealth(int gain){
    health += gain;

    if(health > 100){
        health = 100;
    }

    return health;
}


int Health::gainEnergy(int gain){
    energy += gain;

    if(energy > 100){
        energy = 100;
    }

    return energy;
}

bool Health::cmpHealth(const Health playerHealth) const{
    return health > playerHealth.health;
}

bool Health::cmpHealth(const int cmp) const{
    return health > cmp + 1;
}

//Display stats
ostream& operator<<(ostream& out, const attStats& stats){
    out << "\nShield: " << stats.shield;
    out << "\tNegation: ";
    (stats.dmgNegation) ? out << "Ready" : out << "None";
    out << "\tStun Status: ";
    (stats.stun) ? out << "Stunned" : out << "None";

    return out;
}


ostream& operator<<(ostream& out, const Health& health){
    out << "\nHealth: " << health.health;
    out << "\tEnergy: " << health.energy;

    out << static_cast<attStats>(health);

    return out;
}
