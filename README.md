### About the components

The main program reads the properties of monsters (name, health, damage, etc.) from .json files given as commandline arguments, and plays the battle between them until one of them loses its health points.

The various .json files are the parseable monster unit files which can be loaded into **Unit** objects.

The **attack_test.sh** script is used for the testing of application outputs, the **units** folder contains some monster units used for testing. The desired output which the script compares to can be found in **attack_test_target.txt**.

Documentation: https://teaching-projects.github.io/SZE-MOSZE-2020-Random/
