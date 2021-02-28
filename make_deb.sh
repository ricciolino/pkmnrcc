#!/bin/bash
cd pkmnrcc-1.0
make backup
echo "Created backup inside $HOME/Backups/pkmnrcc"
sleep 3
cd ..
sed "s/DEPS := -MMD/DEPS :=#-MMD/" -i pkmnrcc-1.0/Makefile
sed "s/\/\/    char\* home = getenv/    char\* home = getenv/" -i pkmnrcc-1.0/src/Game.cpp
sed "s/\/\/    fs::path pkmn_dir = std/    fs::path pkmn_dir = std/" -i pkmnrcc-1.0/src/Game.cpp
sed "s/    fs::path pkmn_dir = \"/\/\/    fs::path pkmn_dir = \"/" -i pkmnrcc-1.0/src/Game.cpp
sed "s/home = \"\.\.\/HOME\"/home = os\.getenv(\"HOME\")/" -i pkmnrcc-1.0/assets/scripts/*
tar -czf pkmnrcc_1.0.orig.tar.gz pkmnrcc-1.0/
cd pkmnrcc-1.0/
debuild -us -uc
make clean
cd ..
rm pkmnrcc_1.0.* pkmnrcc_1.0_amd64.[!d]* pkmnrcc-d*
rm -r pkmnrcc-1.0/debian/pkmnrcc
rm -r pkmnrcc-1.0/debian/.debhelper
rm pkmnrcc-1.0/debian/debhelper*
rm pkmnrcc-1.0/debian/files
rm pkmnrcc-1.0/debian/pkmnrcc.substvars
sed "s/DEPS :=#-MMD/DEPS := -MMD/" -i pkmnrcc-1.0/Makefile
sed "s/    char\* home = getenv/\/\/    char\* home = getenv/" -i pkmnrcc-1.0/src/Game.cpp
sed "s/    fs::path pkmn_dir = std/\/\/    fs::path pkmn_dir = std/" -i pkmnrcc-1.0/src/Game.cpp
sed "s/\/\/    fs::path pkmn_dir = \"/    fs::path pkmn_dir = \"/" -i pkmnrcc-1.0/src/Game.cpp
sed "s/home = os\.getenv(\"HOME\")/home = \"\.\.\/HOME\"/" -i pkmnrcc-1.0/assets/scripts/*
#sudo dpkg -i pkmnrcc_1.0_amd64.deb
#rm pkmnrcc_1.0_amd64.deb
