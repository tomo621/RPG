#pragma once
#include "Character.h"

class Wizard : public Character {
public:
    Wizard();
    int GetAttackPower() const override;
};