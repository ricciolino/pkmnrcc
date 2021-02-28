#!/bin/bash

cd tools/

FILE_1=""
while ! [ -f ../assets/tilemaps/$FILE_1.png ]; do
    printf "\nSelect a map from the following list:\n"
    ls -l ../assets/tilemaps/*.png | cut -f4 -d/ | cut -f1 -d'.'   
    echo ""
    read FILE_1
    if ! [ -f ../assets/tilemaps/$FILE_1.png ]; then
        printf "map $FILE_1 doesn't exists\n"
    fi
done

FILE_2=""
while ! [ -f ../assets/tilemaps/$FILE_2.png ] || [ "$FILE_2" = "$FILE_1" ]; do
    printf "\nSelect the map to append to \"$FILE_1\" map from the following list:\n"
    for i in $(ls -l ../assets/tilemaps/*.png | cut -f4 -d/ | cut -f1 -d'.'); do if [ "$i" != "$FILE_1" ]; then echo $i; fi; done
    echo ""
    read FILE_2
    if ! [ -f ../assets/tilemaps/$FILE_2.png ]; then
        printf "map $FILE_2 doesn't exists\n"
    fi
done

WHERE_TO_APPEND=""
if [[ "$WHERE_TO_APPEND" = "D" ]]; then
    printf "\nActually WHERE_TO_APPEND is: \n"
fi
while ! [[ "$WHERE_TO_APPEND" = "D" || "$WHERE_TO_APPEND" = "R" ]]; do
    printf "\nSpecify the position (\"R\" or \"D\") to where append \"$FILE_2\" map to \"$FILE_1\" map:\n"
    read WHERE_TO_APPEND
    if ! [[ "$WHERE_TO_APPEND" = "D" || "$WHERE_TO_APPEND" = "R" ]]; then
        printf "\nplease, enter either \"R\" or \"D\""
    fi
done

echo "Insert the name of the new map:"
read NEW_MAP
./appendMap ../assets/tilemaps/$FILE_1.map ../assets/tilemaps/$FILE_2.map $WHERE_TO_APPEND > /dev/null 2>&1
if [ "$?" -eq "1" ]; then
    echo "Exited 1 from appenMap: maps must be of the same dimension"
    exit 0
fi
mv outAppendMap.txt ../assets/tilemaps/$NEW_MAP.map
python appendPNG.py ../assets/tilemaps/$FILE_1.png ../assets/tilemaps/$FILE_2.png $WHERE_TO_APPEND ../assets/tilemaps/$NEW_MAP
if [ "$?" -eq "1" ]; then
    echo "Exited 1 from appenMap: maps must be of the same dimension"
    exit 0
fi
mkdir -p ../assets/tilemaps/.$NEW_MAP/
mv ../assets/tilemaps/$FILE_1.map ../assets/tilemaps/.$NEW_MAP/$FILE_1.map
mv ../assets/tilemaps/$FILE_2.map ../assets/tilemaps/.$NEW_MAP/$FILE_2.map
mv ../assets/tilemaps/$FILE_1.png ../assets/tilemaps/.$NEW_MAP/$FILE_1.png
mv ../assets/tilemaps/$FILE_2.png ../assets/tilemaps/.$NEW_MAP/$FILE_2.png

if [ "$WHERE_TO_APPEND" = "R"  ]; then
    echo "The map \"$FILE_2\" is been appended to the right of the map \"$FILE_1\"."
else
    echo "The map \"$FILE_2\" is been appended to the left of the map \"$FILE_1\"."
fi
echo "The new map \"$NEW_MAP\" is been created as assets/tilemaps/$NEW_MAP.png"
echo "The maps \"$FILE_1\" and \"$FILE_2\" are been moved into an hidden folder \"assets/tilemaps/.$NEW_MAP\""
    
exit 0
