### About the components

* **Unit** - this structure contains the properties of monsters, and also has an overload of the operator "<<" for easier display
* **Unit::attack** - this function is used to execute an attack between the monsters, with the help of **Unit::suffer_damage**
* getters are used for read only operations

The main program reads the properties of monsters (name, health, damage) from command line arguments, and plays the battle between them until one of them loses its health points.
