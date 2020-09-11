### About the components of main.cpp

* **Mob** - this structure contains the properties of monsters, and also has an overload of the operator "<<" for easier display
* **random** - this function uses rand() to create a random number for a given interval
* **attack** - this function is used to execute an attack between the monsters

The main program generates two monsters with slightly randomized health and attack points, and plays the battle between them until one of them loses its health points.
