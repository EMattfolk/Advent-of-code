#include "stdio.h"
#include "string.h"
#include "utils.h"

char* solve_day_22(char* input) {

	typedef struct state {
		int hp;
		int mana;
		int spent_mana;
		int boss_hp;
		int turn;
		int shield;
		int poison;
		int recharge;
	} state;

	int boss_hp = atoi(strtok(input, "Hit Points: \n"));
	int boss_damage = atoi(strtok(NULL, "Damage: \n"));

	int least_spent_mana = 1 << 30;
	bool hard;

	void fight_boss(state s) {

		if (hard && s.turn % 2 == 0) {
			s.hp--;
			if (s.hp <= 0) {
				return;
			}
		}

		int actual_boss_damage;
		if (s.shield > 0) {
			s.shield--;
			actual_boss_damage = MAX(1, boss_damage - 7);
		} else {
			actual_boss_damage = boss_damage;
		}

		if (s.poison > 0) {
			s.poison--;
			s.boss_hp -= 3;
		}

		if (s.recharge > 0) {
			s.recharge--;
			s.mana += 101;
		}

		if (s.boss_hp <= 0) {
			least_spent_mana = MIN(s.spent_mana, least_spent_mana);
			return;
		}

		if (s.mana < 53) {
			return;
		}

		if (s.turn++ % 2 == 0) {

			s.mana -= 53;
			s.spent_mana += 53;
			s.boss_hp -= 4;
			fight_boss(s);
			s.mana += 53;
			s.spent_mana -= 53;
			s.boss_hp += 4;

			if (s.mana >= 73) {
				s.mana -= 73;
				s.spent_mana += 73;
				s.boss_hp -= 2;
				s.hp += 2;
				fight_boss(s);
				s.mana += 73;
				s.spent_mana -= 73;
				s.boss_hp += 2;
				s.hp -= 2;
			}

			if (s.mana >= 113 && s.shield == 0) {
				s.mana -= 113;
				s.spent_mana += 113;
				s.shield = 6;
				fight_boss(s);
				s.mana += 113;
				s.spent_mana -= 113;
				s.shield = 0;
			}

			if (s.mana >= 173 && s.poison == 0) {
				s.mana -= 173;
				s.spent_mana += 173;
				s.poison = 6;
				fight_boss(s);
				s.mana += 173;
				s.spent_mana -= 173;
				s.poison = 0;
			}

			if (s.mana >= 229 && s.recharge == 0) {
				s.mana -= 229;
				s.spent_mana += 229;
				s.recharge = 5;
				fight_boss(s);
				s.mana += 229;
				s.spent_mana -= 229;
				s.recharge = 0;
			}
		} else {
			s.hp -= actual_boss_damage;
			if (s.hp <= 0) {
				return;
			}

			fight_boss(s);
		}
	}

	state init_state = { 50, 500, 0, boss_hp, 0, 0, 0, 0 };

	hard = false;
	fight_boss(init_state);
	int ans1 = least_spent_mana;

	least_spent_mana = 1 << 30;
	hard = true;
	fight_boss(init_state);
	int ans2 = least_spent_mana;

	sprintf(input, "%d, %d", ans1, ans2);

    return input;
}
