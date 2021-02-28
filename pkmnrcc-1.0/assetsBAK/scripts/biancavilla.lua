home = "../HOME"

stepSize = 64

hMap = 24
wMap = 24

hMapUp = 48
wMapUp = 48
xOffUp = -12

hMapLeft = 24
wMapLeft = 24
yOffLeft = 0

hMapDown = 24
wMapDown = 24
xOffDown = 0

hMapRight = 48
wMapRight = 24
yOffRight = 6

colionePosX,colionePosY,colioneIndexAnim = 2*stepSize,9*stepSize,1
colione3PosX,colione3PosY,colione3IndexAnim = 4*stepSize,4*stepSize,3
colione4PosX,colione4PosY,colione4IndexAnim = 4*stepSize,10*stepSize,2
colione5PosX,colione5PosY,colione5IndexAnim = 4*stepSize,9*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/biancavilla.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/biancavilla.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    colionePosX,colionePosY,colioneIndexAnim = stepSize*tonumber(t["colionePosX"]),stepSize*tonumber(t["colionePosY"]),tonumber(t["colioneIndexAnim"])
    colione3PosX,colione3PosY,colione3IndexAnim = stepSize*tonumber(t["colione3PosX"]),stepSize*tonumber(t["colione3PosY"]),tonumber(t["colione3IndexAnim"])
    colione4PosX,colione4PosY,colione4IndexAnim = stepSize*tonumber(t["colione4PosX"]),stepSize*tonumber(t["colione4PosY"]),tonumber(t["colione4IndexAnim"])
    colione5PosX,colione5PosY,colione5IndexAnim = stepSize*tonumber(t["colione5PosX"]),stepSize*tonumber(t["colione5PosY"]),tonumber(t["colione5IndexAnim"])
    io.close(f)
end

bimboPosX,bimboPosY,bimboIndexAnim = (22-wMapLeft)*stepSize,(8+yOffLeft)*stepSize,2
bimbo2PosX,bimbo2PosY,bimbo2IndexAnim = (22-wMapLeft)*stepSize,(5+yOffLeft)*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/mapLeft.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mapLeft.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    bimboPosX,bimboPosY,bimboIndexAnim = stepSize*(tonumber(t["bimboPosX"])-wMapLeft),stepSize*(tonumber(t["bimboPosY"])+yOffLeft),tonumber(t["bimboIndexAnim"])
    bimbo2PosX,bimbo2PosY,bimbo2IndexAnim = stepSize*(tonumber(t["bimbo2PosX"])-wMapLeft),stepSize*(tonumber(t["bimbo2PosY"])+yOffLeft),tonumber(t["bimbo2IndexAnim"])
    io.close(f)
end

giovanottoPosX,giovanottoPosY,giovanottoIndexAnim = (22+xOffUp)*stepSize,(46-hMapUp)*stepSize,3
f = io.open(home.."/.pkmnrcc/tsav/smeraldopoli2.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/smeraldopoli2.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    giovanottoPosX,giovanottoPosY,giovanottoIndexAnim = (tonumber(t["giovanottoPosX"])+xOffUp)*stepSize,(tonumber(t["giovanottoPosY"])-hMapUp)*stepSize,tonumber(t["giovanottoIndexAnim"])
    io.close(f)
end

cAolioneRPosX,cAolioneRPosY,cAolioneRIndexAnim = (2+wMapRight)*stepSize,(4+yOffRight)*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/mapRight.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mapRight.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    cAolioneRPosX,cAolioneRPosY,cAolioneRIndexAnim = stepSize*(tonumber(t["cAolioneRPosX"])+wMap),stepSize*(tonumber(t["cAolioneRPosY"])+yOffRight),tonumber(t["cAolioneRIndexAnim"])
    io.close(f)
end

scienziatoPosX,scienziatoPosY,scienziatoIndexAnim = (8+xOffDown)*stepSize,(2+hMapDown)*stepSize,3
f = io.open(home.."/.pkmnrcc/tsav/mapDown.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mapDown.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    scienziatoPosX,scienziatoPosY,scienziatoIndexAnim = stepSize*(tonumber(t["scienziatoPosX"])+xOffDown),stepSize*(tonumber(t["scienziatoPosY"])+hMap),tonumber(t["scienziatoIndexAnim"])
    io.close(f)
end

biancavilla = {
    assets = {
        [0] = { type="texture", id = "pallet-town-player-home", file = "../assets/images/pallet-town-player-home.png" },
    },
    map = {
        name = "biancavilla",
        file = "../assets/tilemaps/center",
        mapSizeX = wMap,
        mapSizeY = hMap
    },
    mapUp = {
        name = "smeraldopoli2",
        file = "../assets/tilemaps/smeraldopoli2",
        mapSizeX = wMapUp,
        mapSizeY = hMapUp,
        xOff = xOffUp * stepSize
    },
    mapLeft = {
        name = "mapLeft",
        file = "../assets/tilemaps/left",
        mapSizeX = wMapLeft,
        mapSizeY = hMapLeft,
        yOff = yOffLeft * stepSize
    },
    mapDown = {
        name = "mapDown",
        file = "../assets/tilemaps/down",
        mapSizeX = wMapDown,
        mapSizeY = hMapDown,
        xOff = xOffDown * stepSize
    },
    mapRight = {
        name = "mapRight",
        file = "../assets/tilemaps/right",
        mapSizeX = wMapRight,
        mapSizeY = hMapRight,
        yOff = yOffRight * stepSize
    },
    entities = {
        [0] = {
            name = "colione",
            layer = 1,
			isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = colionePosX, -- 128
                        y = colionePosY -- 576
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                    velocitySize = 1
                },
                sprite = {
                    textureAssetId = "scientist-texture",
                    animated = true,
                    frameCount = 4,
                    hasDirections = true,
                    fixed = false,
                    animationIndex = colioneIndexAnim -- 1
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 0,
                    xRight = 3,
                    yUp = 8,
                    yDown = 10,
                    color = {
                        r = 0,
                        g = 0,
                        b = 255,
                        a = 255
                    },
                    fontFamily = "charriot-14pt"
                }
            }
        },
        [1] = {
            name = "colione3",
            layer = 1,
			isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = colione3PosX, -- 256
                        y = colione3PosY  -- 256
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                    velocitySize = 1
                },
                sprite = {
                    textureAssetId = "scientist-texture",
                    animated = true,
                    frameCount = 4,
                    hasDirections = true,
                    fixed = false,
                    animationIndex = colione3IndexAnim -- 3
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 3,
                    xRight = 5,
                    yUp = 3,
                    yDown = 5,
                    color = {
                        r = 0,
                        g = 255,
                        b = 0,
                        a = 255
                    },
                    fontFamily = "charriot-14pt"
                }
            }
        },
        [2] = {
            name = "colione4",
            layer = 1,
			isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = colione4PosX, -- 256
                        y = colione4PosY  -- 640
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                    velocitySize = 1
                },
                sprite = {
                    textureAssetId = "scientist-texture",
                    animated = true,
                    frameCount = 4,
                    hasDirections = true,
                    fixed = false,
                    animationIndex = colione4IndexAnim -- 2
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 3,
                    xRight = 5,
                    yUp = 9,
                    yDown = 11,
                    color = {
                        r = 255,
                        g = 0,
                        b = 0,
                        a = 255
                    },
                    fontFamily = "charriot-14pt"
                }
            }
        },
        [3] = {
            name = "colione5",
            layer = 1,
			isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = colione5PosX, -- 256
                        y = colione5PosY  -- 576
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                    velocitySize = 1
                },
                sprite = {
                    textureAssetId = "scientist-texture",
                    animated = true,
                    frameCount = 4,
                    hasDirections = true,
                    fixed = false,
                    animationIndex = colione5IndexAnim -- 1
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 3,
                    xRight = 5,
                    yUp = 8,
                    yDown = 10,
                    color = {
                        r = 255,
                        g = 0,
                        b = 255,
                        a = 255
                    },
                    fontFamily = "charriot-14pt"
                }
            }
        },
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS    -    left
----------------------------------------------------------------------------------------------------
        [4] = {
            name = "bimbo",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = bimboPosX,
                        y = bimboPosY
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = bimboIndexAnim
                }
            }
        },
        [5] = {
            name = "bimbo2",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = bimbo2PosX,
                        y = bimbo2PosY
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = bimbo2IndexAnim
                }
            }
        },
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS    -    up
----------------------------------------------------------------------------------------------------
        [6] = {
            name = "giovanotto",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = giovanottoPosX,
                        y = giovanottoPosY
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = giovanottoIndexAnim
                }
            }
        },
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS    -    Right
----------------------------------------------------------------------------------------------------
        [7] = {
            name = "cAolioneR",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = cAolioneRPosX,
                        y = cAolioneRPosY
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = cAolioneRIndexAnim
                }
            }
        },
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS    -    Down
----------------------------------------------------------------------------------------------------
        [8] = {
            name = "scienziato",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = scienziatoPosX,
                        y = scienziatoPosY
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = scienziatoIndexAnim
                }
            }
        },
----------------------------------------------------------------------------------------------------
-- HOUSES AND OTHER STATIC ENTITIES
----------------------------------------------------------------------------------------------------
        [9] = {
            name = "pallet-town-player-home",
            layer = 0,
            components = {
                staticTransform = {
                    position = {
                        x = 5*stepSize,
                        y = 3*stepSize
                    },
                    width = 128,
                    height = 96,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "pallet-town-player-home",
                    fixed = false,
                    animationIndex = 0
                }
            }
        },
        [10] = {
            name = "pallet-town-gary-home",
            layer = 0,
            components = {
                staticTransform = {
                    position = {
                        x = 10*stepSize,
                        y = 3*stepSize
                    },
                    width = 128,
                    height = 96,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "pallet-town-player-home",
                    fixed = false,
                    animationIndex = 0
                }
            }
        }
    }
}
