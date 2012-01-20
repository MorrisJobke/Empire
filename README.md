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

    sudo apt-get install cmake libboost-test-dev libluabind-dev libpcre3-dev

ArchLinux:

    sudo pacman -S boost cmake doxygen graphviz lua pcre

Mac:

    brew install boost cmake doxygen lua

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
