# ZorkHomage_DavidSierra

This game is a small homage to the original Zork game

It places the player in the surrounding area of a farm where something terrible's happened, a goblin attack resulting in the death of the farmer and dissappearance of the livestock.
The player incarnates an adventurer that has come in response to an official petition for help in the adventurers guild.
The player's quest is to find the goblin's hideout and kill it. In order to do so, he'll have to investigate the surrounding area in search of the goblin's hideout.

This homage has been developed by David Sierra, a graduate in Interactive Applications Development in the University of Barcelona.

The game works similarly to the original Zork, there are commands that can be understood by the program and will result in "actions in the world"

Available actions include:

- look/l ->If typed alone, relevant imformation of the room will be displayed. typing look followed by the name of an element in the current room will print specific information on that element. You can also look at yourself by typing: look self/me.

- go/walk/move ->Player moves towards a direction, changing where he's at -> Commands accepted are Go + "Direction" Directions accepted are north, south, east, west, up and down.

- clear/wipe/cls/clr -> Console is cleared.

- pick/grab/take/get -> if followed by the name of an element in the room, it adds it to player's inventory, if followed by "from" + the name of some element in the room, said item will be placed in the player's inventory.

- ivnentory/inv -> displays names of all elements in the player's inventory on the console.

- unlock/open -> Allows player to open closed containers/doors. Example: Open/Unlock door with key.

- equip/eq -> if followed by the name of an Equipable item in the players inventory, said item is equipped as weapon/armour and its stats are added to the bonus stats of the player.

- unequip/uneq -> if followed by the name of an equipped item, said item is unequipped and its stats are removed from the bonus stats of the player.

- examine/ex/inspect/ins -> if followed by the name of any Creature or equipment in the scene, it displays its properties (health, attack, defense) on the console. 

- drop/place -> if followed by the name of any element inside the player's inventory, said element is "placed" on the room the player's at, it can also be used to place items inside containers. Example: place note inside mailbox.

- strike/attack/kill -> if followed by the name of any creature in the player's room, it attacks said creature and deals damage to it.

- use/consume/drink -> if followed by the name of a consumable in the player's inventory, said consumable will use its effect on the player. Example: Drink potion -> This will result in player being healed.

- Game can be closed by typing in exit/close/quit

Killed creatures drop their entire inventory.
There's chances of missing attacks as well as dealing critical hits, critical hits stun creatures.
A creature that's been attacked will chase the player and attack him, if the player leaves a creature stunned in a room and gets two rooms away, said entity willl not chase him anymore.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//SPOILERS

The main path requires the player to:

Go to the woodsman cabin and retreive the key from the chest.
Go to the stables and retreive the doll
Unlock the farm's trapdoor
Go up the trapdoor and drop the doll there
Take the chisel the child leaves behind
Go to the goblin's cave entrance and unlock it with the chisel
Kill the goblin
Retreive the armour 
Place the armour inside the cart back in the farm outside

Notes: 
- Killing the goblin without a weapon, while posible, is unlikely. 
- A potion and an axe can be found at the Lake by killing the slime that is there.
- The dagger begins in the player's inventory, but is unequipped, player must equip it for an easier experience against the goblin.

The main path to finish the game is to use the following commands:

- Equip dagger
- Go south (x2)
- Go east
- Go south 
- Get key from chest
- Go north (x3)
- Go east (x2)
- Get doll
- Go west
- Go north
- Open trapdoor with key
- Go up
- Drop doll
- Get chisel
- Go down
- Go south
- Go west
- Go south
- Go west
- Open hole with chisel
- Go down
- Kill goblin (2 - 7 times)
- Pick armour
- Go up
- Go north
- Drop Armour inside cart

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Github repositroy link: https://github.com/devildrake/ZorkHomage_DavidSierra

The game has been developed using a GNU GENERAL PUBLIC LICENSE v3.0 which lets people do almost anything they want with your project, except distributing closed source versions.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Development notes

It had been about a year and a half since I last programmed anything using C++ so the code is probably not as optimal as I'd like it to be, I had issues with memory errors 
(trying to call delete on pointers that had already been deleted) as well as methods with the same name implemented in different classes that resulted in errors.

Polymorphism works similarly in C# so that wasn't a big problem.

My personal take on the game, besides the small story that takes place, is the implementation of RPG stats (Attack,Defense,Health), enemies that chase and attack you once they've been attacked, 
enemies that can be stunned by critical hits (random chances), attacks that can be missed (random chances). As well as consumable potions and specific events that some entities trigger once a 
specific item is placed in a specific place.