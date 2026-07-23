#pragma once
#include "Character.h"

class Summoner : public Character {
public:
    Summoner();
    int GetAttackPower() const override;
};