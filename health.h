#pragma once
#include "myutil.h"

class attStats{
    protected:
    bool dmgNegation;
    int shield;
    bool stun;
    

    public:
    attStats();
    
    //apply effect and return new quantity
    int applyShield(int damage);
    int applyNegation(int damage);
    bool applyStun();

    int gainShield(int effect);
    bool gainNegation();
    bool gainStun();

    bool getStun();

    friend ostream& operator<<(ostream& out, const attStats&);
};

class Health: public attStats{
    private:
    int health;
    int energy;

    public:
    Health();

    int getHit(int dmg, float multiple);
    int useEnergy(int consumption);

    int gainHealth(int gain);
    int gainEnergy(int gain);
    bool cmpHealth(const Health playerHealth) const;
    bool cmpHealth(const int cmp) const;

    friend ostream& operator<<(ostream& out, const Health&);
};
