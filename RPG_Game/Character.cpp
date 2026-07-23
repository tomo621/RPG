#include "Character.h"

// コンストラクタで初期値をセットする
Character::Character(std::string characterName, int power)
    : name(characterName), attackPower(power) {
}

std::string Character::GetName() const {
    return name;
}

int Character::GetAttackPower() const {
    return attackPower;
}