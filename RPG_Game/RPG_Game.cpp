#include <iostream>
#include <memory>
#include <random> 
#include <string>
#include "Team.h"

using namespace std;

// 攻撃,防御の相性を判定する
void ResolveAttackVsDefend(Team& atkTeam, Character* atkChar, Team& defTeam, Character* defChar) {
    string aName = atkChar->GetName();
    string dName = defChar->GetName();

    if (aName == dName) {
        cout << "相殺された！ドロー（何も起こらない）\n";
    }
    // クリティカルになる組み合わせ（剣士>召喚士、魔法使い>剣士、召喚士>魔法使い）
    else if ((aName == "剣士" && dName == "召喚士") ||
        (aName == "魔法使い" && dName == "剣士") ||
        (aName == "召喚士" && dName == "魔法使い")) {
        int dmg = atkChar->GetAttackPower() * 2;
        cout << "クリティカル攻撃発生！ " << defTeam.GetName() << " に " << dmg << " のダメージ！\n";
        defTeam.TakeDamage(dmg);
    }
    // それ以外はカウンターになる
    else {
        int dmg = atkChar->GetAttackPower() * 2;
        cout << "カウンター発生！ " << atkTeam.GetName() << " に " << dmg << " のダメージ！\n";
        atkTeam.TakeDamage(dmg);
    }
}

int main() {
    // 乱数の準備
    random_device rd;
    mt19937 gen(rd());
    // 0〜2の乱数（キャラ選択用）
    uniform_int_distribution<> charDist(0, 2);
    // 0〜1の乱数（行動選択用）
    uniform_int_distribution<> actDist(0, 1);  

    Team ally("味方陣営");
    Team enemy("敵陣営");

    int turn = 1;
    cout << "=== バトル開始 ===\n";

    // どちらかのHPが0になるまでループを繰り返す
    while (ally.GetHp() > 0 && enemy.GetHp() > 0) {
        cout << "\n--- ターン " << turn << " ---\n";
        cout << "[戦力] " << ally.GetName() << ": " << ally.GetHp() << " | " << enemy.GetName() << ": " << enemy.GetHp() << "\n";

        // 1. 味方陣営の入力
        int allyCharIndex, allyActionIndex;
        cout << "キャラクターを選択 (1:剣士, 2:魔法使い, 3:召喚士): ";
        cin >> allyCharIndex;
        // 内部的には0,1,2で管理するため-1する
        allyCharIndex -= 1;

        cout << "行動を選択 (1:攻撃, 2:防御): ";
        cin >> allyActionIndex;

        // 2. 敵陣営のランダム決定
        int enemyCharIndex = charDist(gen);
        // 1か2にする
        int enemyActionIndex = actDist(gen) + 1; 

        Character* aChar = ally.GetCharacter(allyCharIndex);
        Character* eChar = enemy.GetCharacter(enemyCharIndex);

        if (aChar == nullptr || eChar == nullptr) {
            cout << "入力が不正です。ターンをやり直します。\n";
            continue;
        }

        // 行動宣言の表示
        bool allyIsAttack = (allyActionIndex == 1);
        bool enemyIsAttack = (enemyActionIndex == 1);

        cout << "\n【行動宣言】\n";
        cout << ally.GetName() << "の" << aChar->GetName() << " は " << (allyIsAttack ? "攻撃" : "防御") << " を選択！\n";
        cout << enemy.GetName() << "の" << eChar->GetName() << " は " << (enemyIsAttack ? "攻撃" : "防御") << " を選択！\n";
        cout << "\n【結果】\n";

        //行動の解決
        if (allyIsAttack && enemyIsAttack) {
            // お互い攻撃
            if (aChar->GetAttackPower() > eChar->GetAttackPower()) {
                cout << ally.GetName() << "の攻撃が上回った！ " << enemy.GetName() << " に " << aChar->GetAttackPower() << " のダメージ！\n";
                enemy.TakeDamage(aChar->GetAttackPower());
            }
            else if (aChar->GetAttackPower() < eChar->GetAttackPower()) {
                cout << enemy.GetName() << "の攻撃が上回った！ " << ally.GetName() << " に " << eChar->GetAttackPower() << " のダメージ！\n";
                ally.TakeDamage(eChar->GetAttackPower());
            }
            else {
                cout << "攻撃力が互角！ドロー（何も起こらない）\n";
            }
        }
        else if (!allyIsAttack && !enemyIsAttack) {
            // お互い防御
            cout << "お互いに様子を見ている。ドロー（何も起こらない）\n";
        }
        else {
            // 攻撃と防御が分かれた場合
            if (allyIsAttack) {
                ResolveAttackVsDefend(ally, aChar, enemy, eChar);
            }
            else {
                ResolveAttackVsDefend(enemy, eChar, ally, aChar);
            }
        }

        turn++;
    }

    // 決着
    cout << "\n=== 決着 ===\n";
    cout << "[最終戦力] " << ally.GetName() << ": " << ally.GetHp() << " | " << enemy.GetName() << ": " << enemy.GetHp() << "\n";

    if (ally.GetHp() == 0 && enemy.GetHp() == 0) {
        cout << "相打ち！引き分けです。\n";
    }
    else if (ally.GetHp() == 0) {
        cout << "敵陣営の勝利です...\n";
    }
    else {
        cout << "味方陣営の勝利です！\n";
    }

    return 0;
}