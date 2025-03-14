# Samurai vs Zombies Data Parser
This small library for **C++17** and up parses the TXT data files found in ***Samurai vs Zombies Defense*** by Glu Mobile.

I don't know if this format is used in other games, or if the programmers designed their own system just for this game (it's not used in the sequel), but regardless, this should prove useful for anyone looking to easily read data from those files.

At least for now, this tool can only **read** and not write.

## Example
File:
```txt
/--------------------------------------------------
/ General
/--------------------------------------------------

displayName = @helper_farmer_name
desc = @helper_farmer_desc
prefab = Characters/PFFarmer
HUDIcon = Sprites/Icons/ally_farmer
weaponMeleePrefab = Props/PFFarmerssword
waveToUnlock = 2
resourcesCost = 5.0
cooldownTimer = 1.0
attackFrequency = 1.0
usesBladeWeapon = true

achievementGC = SAMUZOMBIE_ACHIEVE_FROM_THE_FIELDS


/--------------------------------------------------
/ Levels
/--------------------------------------------------

[001]
	cost = 50,0
	health = 37
	speedMin = 100
	speedMax = 100
	meleeRange = 100
	meleeDamage = 11
	knockbackPower = 5
	knockbackResistance = 10

[002]
	cost = 275,0
	health = 50
	speedMin = 100
	speedMax = 100
	meleeRange = 100
	meleeDamage = 15
	knockbackPower = 5
	knockbackResistance = 10
(...)
```
Code:
```cpp
#include <iostream>
#include "include/svz_data.hpp"

int main() {
    SvZ_Data farmer_data{"./helpers/Farmer.txt"};

    std::cout << farmer_data.fetch("weaponMeleePrefab") << '\n';
    std::cout << farmer_data.fetch("002", "meleeDamage");
}
```
Output:
```
Props/PFFarmerssword
15
```