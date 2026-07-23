#pragma once
#include <string>

class Character {
protected:
    // 派生クラス
    std::string name;
    int attackPower;

public:
    Character(std::string characterName, int power);
    // 継承を行う仮想デストラクタ
    virtual ~Character() = default; 

    std::string GetName() const;
    virtual int GetAttackPower() const; 
};
