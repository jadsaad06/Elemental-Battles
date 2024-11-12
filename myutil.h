#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;

enum Type{
    fire,
    water,
    plant,
};

istream& operator>>(istream& input, Type& type);

enum Effect{
    stun,
    damage,
    shieldGain,
    dmgNegation,
    healthGain,
    energyGain,
    none
};
