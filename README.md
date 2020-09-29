### About the components

* **Unit** - this class contains the properties of monsters, and also has an overload of the operator "<<" for easier display
* **Unit::attack** - this function is used to execute an attack between the monsters, with the help of **Unit::suffer_damage**
* **Unit::parse_unit** - reads the parameters of monster units into the object for use
* getters are used for read only operations

The main program reads the properties of monsters (name, health, damage) from .json files given as commandline arguments, and plays the battle between them until one of them loses its health points.

The various .json files are the parseable monster unit files which can be loaded into **Unit** objects.

The **attack_test.sh** script is used for the testing of application outputs, the **units** folder contains some monster units used for testing. The desired output which the script compares to can be found in **attack_test_target.txt**.
