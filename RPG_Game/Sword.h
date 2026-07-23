#pragma once
#include "Character.h"

class Sword: public Character {
public:
    Sword();
    int GetAttackPower() const override; 
};