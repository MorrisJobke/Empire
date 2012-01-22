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

	cd build/
	cmake ../src
	make

Tests
-----

	cd bin/
	./EmpireTest --log_level=test_suite

Handbuch
-------------

Erstellen:

	make handbuch

Testprotokolle
-------------

Erstellen:

	make testprotokolle

Doxygen
-------

	cd src/
	doxygen doxygen.config
