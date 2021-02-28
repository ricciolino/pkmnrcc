#!/bin/bash

cd tools/

printf "Type 1 to build a small map (24 x 24 tiles)\nType 2 to build a large map (48 x 48 tiles)\n"
while read OPTIONS; do
  case "$OPTIONS" in
    1) printf "building a small map...\n"; break ;;
    2) printf "building a large map...\n"; break ;;
    *) printf "Incorrect value option!\nType 1 to build a small map (24 x 24 tiles)\nType 2 to build a large map (48 x 48 tiles)\n" ;;
  esac
done

echo "Insert the name of the map:"
read MAP_NAME

# large map
if [ "$OPTIONS" -eq "2" ]; then

    echo "build the map merging 4 sub-maps like this:"
    echo ""
    echo "-----------------------------"
    echo "|             |             |"
    echo "|   map_1     |    map_2    |"
    echo "|             |             |"
    echo "|-------------|-------------|"
    echo "|             |             |"
    echo "|   map_3     |    map_4    |"
    echo "|             |             |"
    echo "-----------------------------"
    echo ""

    # mapUp
    echo "building map_1..."
    ./mapEditor.py map1
    if [ "$?" -eq "1" ]; then
        echo "exited 1 from mapEditor.py"
        exit 0
    fi
    echo "building map_2..."
    ./mapEditor.py map2
    if [ "$?" -eq "1" ]; then
        echo "exited 1 from mapEditor.py"
        rm map*.map map*.png
        exit 0
    fi
    ./appendMap map1.map map2.map R > /dev/null
    mv outAppendMap.txt mapUp.map
    rm map1.map map2.map
    python appendPNG.py map1.png map2.png R mapUp
    rm map1.png map2.png

    # mapDown
    echo "building map_3..."
    ./mapEditor.py map1
    if [ "$?" -eq "1" ]; then
        echo "exited 1 from mapEditor.py"
        rm map*.map map*.png
        exit 0
    fi
    echo "building map_4..."
    ./mapEditor.py map2
    if [ "$?" -eq "1" ]; then
        echo "exited 1 from mapEditor.py"
        rm map*.map map*.png
        exit 0
    fi
    ./appendMap map1.map map2.map R > /dev/null
    mv outAppendMap.txt mapDown.map
    rm map1.map map2.map
    python appendPNG.py map1.png map2.png R mapDown
    rm map1.png map2.png

    # merge mapUp and mapDown
    ./appendMap mapUp.map mapDown.map D > /dev/null
    mv outAppendMap.txt $MAP_NAME.map
    rm mapUp.map mapDown.map
    python appendPNG.py mapUp.png mapDown.png D $MAP_NAME
    rm mapUp.png mapDown.png

    # move $MAP_NAME.map and $MAP_NAME.png to assets folder
    echo "map saved as ./assets/tilemaps/$MAP_NAME.png"
    mv $MAP_NAME.map $MAP_NAME.png ../assets/tilemaps/
fi

# small map
if [ "$OPTIONS" -eq "1" ]; then
    ./mapEditor.py $MAP_NAME
    if [ "$?" -eq "1" ]; then
        echo "exited 1 from mapEditor.py"
        exit 0
    fi
    # move $MAP_NAME.map and $MAP_NAME.png to assets folder
    echo "map saved as ./assets/tilemaps/$MAP_NAME.png"
    mv $MAP_NAME.map $MAP_NAME.png ../assets/tilemaps/
fi

exit 0
