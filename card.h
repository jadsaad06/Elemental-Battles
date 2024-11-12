#pragma once
#include "myutil.h"

class Card{
    protected:
    char* name;
    Type type;
    int energyUsed;
    Effect eff;
        
    public:
    Card();
    ~Card();
    Card(const string& strName, Type type, int energyUsed, Effect eff);
    Card(const Card&);
    Card operator=(const Card&);
    friend ostream& operator<<(ostream& out, const Card&);

    Effect getEffect() const;
    bool isStrongAgainst(Type defender) const;
    bool isWeakAgainst(Type defender) const;
};

class Offense: public Card{
    private:
    char* mvPrompt;
    int dmgApplied;


    public:
    Offense();
    ~Offense();
    Offense(const string& strName, Type type, int energyUsed,
    Effect eff, const string& strPrompt, int defGained);
    Offense(const Offense&);
    Offense operator=(const Offense&);

    friend ostream& operator<<(ostream& out, const Offense&);
    
    int getDamage() const;
};

class Defense: public Card{
    private:
    string mvPrompt;
    int defGained;

    public:
    Defense();
    Defense(const string& strName, Type type, int energyUsed,
    Effect eff, const string& mvPrompt, int defGained);

    friend ostream& operator<<(ostream& out, const Defense&);

    int getDefense() const;
};

class Support: public Card{
    private:
    string mvPrompt;
    int supGained;

    public:
    Support();
    Support(const string& strName, Type type, int energyUsed,
    Effect eff, const string& mvPrompt, int supGained);

    friend ostream& operator<<(ostream& out, const Support&);

    int getSupport() const;
};
