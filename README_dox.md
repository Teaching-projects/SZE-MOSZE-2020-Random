### About the project

This project is a game that can be played via user input from a console environment. The output from the app is also shown via the console.

#### Operating the game:

The user starts the game from the command line interface, giving an input parameter. This input parameter is a **JSON** file. I will refer to this file as ***game configuration file***.

The file is formatted as follows:

    {
      "map"  : "../maps/map1",
      "hero" : "Dark_Wanderer.json",
      "monster-1" : "Fallen.json",
      "monster-2" : "Zombie.json",
      "monster-3" : "Blood_Raven.json"
    }

Here the *\"map\"* value represents the ***map*** file, which is formatted like this:

    ##############
    # H #  ####  #
    #1####  ##  #
    #121#  ##  #
    ###1# ##  #
    #  2133  #
    #########

On the ***map***, the ***hero*** is shown by the *H* character, and similarly the *1, 2, 3...* numbers give the position of different types of ***monsters***. These ***monsters*** can be seen in the ***game configuration file*** described as *\"monster-x\"* where the x can be any simple character.

In the ***game configuration file*** after the *\"hero\"* and *\"monster\"* tags, there is a specific **JSON** file, which contains the parameters of ***heroes*** and ***monsters***.

Their format of the ***hero***'s file is the following:

    {
        "name" : "Prince Aidan of Khanduras",
        "base_health_points" : 30,
        "base_damage" : 3,
        "base_magical_damage" : 1,
        "base_attack_cooldown" : 1.1,
        "experience_per_level" : 20,
        "health_point_bonus_per_level" : 5,
        "damage_bonus_per_level" : 1,
        "magical_damage_bonus_per_level" : 1,
        "cooldown_multiplier_per_level": 0.9,
        "base_defense" : 1,
        "defense_bonus_per_level" : 1,
        "base_light_radius" : 1
    }

In this file, the:
* *\"name\"* tag shows the name of the hero,
* *\"base_health_points\"* tag shows the basic starting health of the hero,
* *\"base_damage\"* and
* *\"base_magic_damage\"* tags show the basic starting damage types of the hero,
* *\"base_attack_cooldown\"* tag shows the time it takes for the hero to reload its attack,
* *\"experience_per_level\"* tag shows the amount of experience the hero gets on each levelup,
* *\"defense\"* tag shows the amount of physical damage the hero can nullify and the
* *\"base_light_radius\"* tag shows the initial distance the hero can see the map while in game.

I didn't specify some of the tags, however these tags mainly have a `per_level` in their name showing that they increase or multiply a given value of the hero when leveling up.

The *.json* files for the ***monsters*** are very similar to the ***heroes***, some of the tags are the same without the `base_` prefix, and some are not specified in them. This is mainly because the ***monsters*** are unable to level up, and the player mostly controls ***heroes***.
