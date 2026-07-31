#include "Character.h"

// コンストラクタでセットする
Character::Character(std::string characterName, int power)
    : name(characterName), attackPower(power) {
}

std::string Character::GetName() const {
    return name;
}

int Character::GetAttackPower() const {
    return attackPower;
}