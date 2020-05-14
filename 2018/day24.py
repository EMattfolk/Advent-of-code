from time import process_time as clock
from copy import deepcopy as cp

class Army:
    def __init__ (self):
        self.units = 0
        self.hitpoints = 0
        self.immunities = set()
        self.weaknesses = set()
        self.attack = 0
        self.attack_type = ""
        self.initiative = 0

# Initialize the data
with open("24.txt") as f:
    immune = []
    infect = []
    for l in f:
        if l[:6] == "Immune":
            is_infection = False
            continue
        if l[:9] == "Infection":
            is_infection = True
            continue

        army = Army()
        
        if "(" not in l:
            l = [l[:l.index("points") + 6], "", l[l.index("points") + 6:]]
        else:
            l = l.split("(")
            l += l[1].split(")")
            del l[1]

        section = l[0].split()
        army.units = int(section[0])
        army.hitpoints = int(section[4])

        if l[1] != "":
            section = l[1].split("; ")
            for s in section:
                s = s.split()
                prop = set()
                for p in s[2:]:
                    if p[-1] == ',':
                        prop.add(p[:-1])
                    else:
                        prop.add(p)
                if s[0] == "weak":
                    army.weaknesses = prop
                else:
                    army.immunities = prop

        section = l[2].split()
        army.attack = int(section[5])
        army.attack_type = section[6]
        army.initiative = int(section[-1])

        if is_infection:
            infect.append(army)
        else:
            immune.append(army)
"""
print("immune")
for att, init, i in immune:
    print(att, init, i.units, i.hitpoints, i.immunities, i.weaknesses, i.attack, i.attack_type, i.initiative)
print("infection")
for att, init, i in infect:
    print(att, init, i.units, i.hitpoints, i.immunities, i.weaknesses, i.attack, i.attack_type, i.initiative)
"""

def solve (boost=0):
    global immune
    global infect
    im_backup = cp(immune)
    in_backup = cp(infect)
    for i in range(len(immune)):
        immune[i].attack += boost
        immune[i] = (immune[i].attack * immune[i].units, immune[i].initiative, immune[i])
    for i in range(len(infect)):
        infect[i] = (infect[i].attack * infect[i].units, infect[i].initiative, infect[i])

    killed = True
    while immune and infect and killed:
        killed = False
        immune, infect = sorted(immune, reverse=True), sorted(infect, reverse=True)

        # Targeting phase
        im_targets = [-1] * len(immune)
        if_targets = [-1] * len(infect)

        for j, im in enumerate(immune):
            target = -1
            damage = im[0]
            dmg_type = im[2].attack_type
            high = 0
            for i, t in enumerate(infect):

                if (dmg_type in t[2].immunities) or (i in im_targets):
                    continue

                if dmg_type in t[2].weaknesses:
                    mod = 2
                else:
                    mod = 1

                if damage * mod > high:
                    high = damage * mod
                    target = i
                elif damage * mod == high:
                    if infect[i][2].attack * infect[i][2].units > infect[target][2].attack * infect[target][2].units:
                        target = i
                    elif infect[i][2].attack * infect[i][2].units == infect[target][2].attack * infect[target][2].units:
                        if infect[i][2].initiative > infect[target][2].initiative:
                            target = i


            im_targets[j] = target


        for j, im in enumerate(infect):
            target = -1
            damage = im[0]
            dmg_type = im[2].attack_type
            high = 0
            for i, t in enumerate(immune):

                if (dmg_type in t[2].immunities) or (i in if_targets):
                    continue

                if dmg_type in t[2].weaknesses:
                    mod = 2
                else:
                    mod = 1

                if damage * mod > high:
                    high = damage * mod
                    target = i
                elif damage * mod == high:
                    if immune[i][2].attack * immune[i][2].units > immune[target][2].attack * immune[target][2].units:
                        target = i
                    elif immune[i][2].attack * immune[i][2].units == immune[target][2].attack * immune[target][2].units:
                        if immune[i][2].initiative > immune[target][2].initiative:
                            target = i

            if_targets[j] = target

        immune_priority = sorted([(immune[i][1], im_targets[i], i) for i in range(len(immune))])
        infect_priority = sorted([(infect[i][1], if_targets[i], i) for i in range(len(infect))])

        # Attacking phase
        while immune_priority or infect_priority:
            if len(immune_priority) == 0:
                protecting = True
                attacker = infect_priority.pop()
            elif len(infect_priority) == 0:
                protecting = False
                attacker = immune_priority.pop()
            elif immune_priority[-1][0] > infect_priority[-1][0]:
                protecting = False
                attacker = immune_priority.pop()
            else:
                protecting = True
                attacker = infect_priority.pop()

            if attacker[1] == -1: continue

            if protecting:
                protector = immune[attacker[1]][2]
                attacker_army = infect[attacker[2]][2]
            else:
                protector = infect[attacker[1]][2]
                attacker_army = immune[attacker[2]][2]

            if attacker_army.attack_type in protector.weaknesses:
                mod = 2
            else:
                mod = 1

            dead = (attacker_army.units * attacker_army.attack * mod) // protector.hitpoints

            if dead > 0:
                killed = True
                protector.units = max(0, protector.units - dead)

        # Update armies
        immune = [(army.units * army.attack, init, army) for att, init, army in immune if army.units > 0]
        infect = [(army.units * army.attack, init, army) for att, init, army in infect if army.units > 0]

    res = sum([army.units for att, init, army in immune + infect]), len(immune) > 0 and killed

    immune = im_backup
    infect = in_backup

    return res
# Function for solving the first problem
def first ():
    st = clock()
    res = solve()[0]
    print("First:", res, "Time:", clock() - st)

# Function for solving the second problem
def second ():
    st = clock()
    outcome = False
    boost = 0
    while not outcome:
        boost += 1
        res, outcome = solve(boost)
    print("Second:", res, "Time:", clock() - st)

# Solve the problems
if __name__ == "__main__":
    first()
    second()
