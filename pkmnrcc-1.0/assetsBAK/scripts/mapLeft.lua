home = "../HOME"

stepSize = 64

hMap = 24
wMap = 24

hMapRight = 24
wMapRight = 24
yOffRight = 0

bimboPosX,bimboPosY,bimboIndexAnim = 22*stepSize,8*stepSize,2
bimbo2PosX,bimbo2PosY,bimbo2IndexAnim = 22*stepSize,5*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/mapLeft.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mapLeft.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    bimboPosX,bimboPosY,bimboIndexAnim = stepSize*tonumber(t["bimboPosX"]),stepSize*tonumber(t["bimboPosY"]),tonumber(t["bimboIndexAnim"])
    bimbo2PosX,bimbo2PosY,bimbo2IndexAnim = stepSize*tonumber(t["bimbo2PosX"]),stepSize*tonumber(t["bimbo2PosY"]),tonumber(t["bimbo2IndexAnim"])
    io.close(f)
end

colionePosX,colionePosY,colioneIndexAnim = (2+wMapRight)*stepSize,(9+yOffRight)*stepSize,1
colione3PosX,colione3PosY,colione3IndexAnim = (4+wMapRight)*stepSize,(4+yOffRight)*stepSize,3
colione4PosX,colione4PosY,colione4IndexAnim = (4+wMapRight)*stepSize,(10+yOffRight)*stepSize,2
colione5PosX,colione5PosY,colione5IndexAnim = (4+wMapRight)*stepSize,(9+yOffRight)*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/biancavilla.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/biancavilla.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    colionePosX,colionePosY,colioneIndexAnim = (tonumber(t["colionePosX"])+wMap)*stepSize,(tonumber(t["colionePosY"])+yOffRight)*stepSize,tonumber(t["colioneIndexAnim"])
    colione3PosX,colione3PosY,colione3IndexAnim = (tonumber(t["colione3PosX"])+wMap)*stepSize,(tonumber(t["colione3PosY"])+yOffRight)*stepSize,tonumber(t["colione3IndexAnim"])
    colione4PosX,colione4PosY,colione4IndexAnim = (tonumber(t["colione4PosX"])+wMap)*stepSize,(tonumber(t["colione4PosY"])+yOffRight)*stepSize,tonumber(t["colione4IndexAnim"])
    colione5PosX,colione5PosY,colione5IndexAnim = (tonumber(t["colione5PosX"])+wMap)*stepSize,(tonumber(t["colione5PosY"])+yOffRight)*stepSize,tonumber(t["colione5IndexAnim"])
    io.close(f)
end

mapLeft = {
    assets = {
    },
    map = {
        name = "mapLeft",
        file = "../assets/tilemaps/left",
        mapSizeX = wMap,
        mapSizeY = hMap
    },
    mapRight = {
        name = "biancavilla",
        file = "../assets/tilemaps/center",
        mapSizeX = wMapRight,
        mapSizeY = hMapRight,
        yOff = yOffRight * stepSize
    },
    entities = {
        [0] = {
            name = "bimbo",
            layer = 1,
			isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = bimboPosX, -- 1408
                        y = bimboPosY  -- 512
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
					animationIndex = bimboIndexAnim -- 2
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 20,
                    xRight = 22,
                    yUp = 7,
                    yDown = 9,
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
            name = "bimbo2",
            layer = 1,
			isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = bimbo2PosX, -- 1408
                        y = bimbo2PosY  -- 320
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
					animationIndex = bimbo2IndexAnim -- 1
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 20,
                    xRight = 22,
                    yUp = 4,
                    yDown = 6,
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
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS      -      right
----------------------------------------------------------------------------------------------------
        [2] = {
            name = "colione",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = colionePosX,
                        y = colionePosY 
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = colioneIndexAnim
                }
            }
        },
        [3] = {
            name = "colione3",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = colione3PosX,
                        y = colione3PosY 
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = colione3IndexAnim
                }
            }
        },
        [4] = {
            name = "colione4",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = colione4PosX,
                        y = colione4PosY
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = colione4IndexAnim
                }
            }
        },
        [5] = {
            name = "colione5",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = colione5PosX,
                        y = colione5PosY
                    },
                    width = 32,
                    height = 32,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "scientist-texture",
                    fixed = false,
                    animationIndex = colione5IndexAnim
                }
            }
        }
    }
}
