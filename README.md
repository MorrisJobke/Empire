Project Empire
==============

Dies ist das Git-Repository zum Softwareengineering-Praktikum.

Pflichtenheft
-------------

Erstellen:

	make pflichtenheft

Benötigte Pakete
----------------

Ubuntu:

    sudo apt-get install libluabind-dev cmake libboost-test-dev

ArchLinux:

    sudo pacman -S boost cmake doxygen graphviz lua pcre

Mac:

    brew install cmake boost lua doxygen

CMake
-----

	cd src/build/
	cmake ..
	make

Tests
-----

	cd src/build/bin
	./EmpireTest --log_level=test_suite

Testprotokolle
-------------

Erstellen:

	make testprotokolle

Doxygen
-------

	cd src/
	doxygen doxygen.config
