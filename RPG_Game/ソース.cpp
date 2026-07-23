#include "Team.h"
#include "Sword.h"
#include "Wizard.h"
#include "Summoner.h"

Team::Team(std::string teamName) : name(teamName), hp(300) {
    // 陣営が生成された時にスマートポインタで追加する
    AddCharacter(std::unique_ptr<Character>(new Sword()));
    AddCharacter(std::unique_ptr<Character>(new Wizard()));
    AddCharacter(std::unique_ptr<Character>(new Summoner()));
}

void Team::AddCharacter(std::unique_ptr<Character> newCharacter) {
    members.push_back(std::move(newCharacter));
}

std::string Team::GetName() const {
    return name;
}

int Team::GetHp() const {
    return hp;
}

void Team::TakeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

Character* Team::GetCharacter(int index) const {
    if (index >= 0 && index < members.size()) {
        return members[index].get();
    }
    return nullptr;
}