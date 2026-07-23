#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Character.h"

class Team {
private:
    std::string name;
    int hp;
    std::vector<std::unique_ptr<Character>> members;

public:
    Team(std::string teamName);

    void AddCharacter(std::unique_ptr<Character> newCharacter);

    std::string GetName() const;
    int GetHp() const;
    void TakeDamage(int damage);

    Character* GetCharacter(int index) const;
};