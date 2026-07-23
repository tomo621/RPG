#include "Sword.h"


Sword::Sword() : Character("Œ•Žm", 40) {
}

int Sword::GetAttackPower() const {
    return attackPower;
}