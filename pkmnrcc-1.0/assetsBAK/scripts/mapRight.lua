home = "../HOME"

stepSize = 64

hMap = 48
wMap = 24

hMapLeft = 24
wMapLeft = 24
yOffLeft = -6

cAolioneRPosX,cAolioneRPosY,cAolioneRIndexAnim = 2*stepSize,4*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/mapRight.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mapRight.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    cAolioneRPosX,cAolioneRPosY,cAolioneRIndexAnim = stepSize*tonumber(t["cAolioneRPosX"]),stepSize*tonumber(t["cAolioneRPosY"]),tonumber(t["cAolioneRIndexAnim"])
    io.close(f)
end

colionePosX,colionePosY,colioneIndexAnim = (2-wMapLeft)*stepSize,(9+yOffLeft)*stepSize,1
colione3PosX,colione3PosY,colione3IndexAnim = (4-wMapLeft)*stepSize,(4+yOffLeft)*stepSize,3
colione4PosX,colione4PosY,colione4IndexAnim = (4-wMapLeft)*stepSize,(10+yOffLeft)*stepSize,2
colione5PosX,colione5PosY,colione5IndexAnim = (4-wMapLeft)*stepSize,(9+yOffLeft)*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/biancavilla.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/biancavilla.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    colionePosX,colionePosY,colioneIndexAnim = (tonumber(t["colionePosX"])-wMapLeft)*stepSize,(tonumber(t["colionePosY"])+yOffLeft)*stepSize,tonumber(t["colioneIndexAnim"])
    colione3PosX,colione3PosY,colione3IndexAnim = (tonumber(t["colione3PosX"])-wMapLeft)*stepSize,(tonumber(t["colione3PosY"])+yOffLeft)*stepSize,tonumber(t["colione3IndexAnim"])
    colione4PosX,colione4PosY,colione4IndexAnim = (tonumber(t["colione4PosX"])-wMapLeft)*stepSize,(tonumber(t["colione4PosY"])+yOffLeft)*stepSize,tonumber(t["colione4IndexAnim"])
    colione5PosX,colione5PosY,colione5IndexAnim = (tonumber(t["colione5PosX"])-wMapLeft)*stepSize,(tonumber(t["colione5PosY"])+yOffLeft)*stepSize,tonumber(t["colione5IndexAnim"])
    io.close(f)
end

mapRight = {
    assets = {
    },
    map = {
        name = "mapRight",
        file = "../assets/tilemaps/right",
        mapSizeX = wMap,
        mapSizeY = hMap
    },
    mapLeft = {
        name = "biancavilla",
        file = "../assets/tilemaps/center",
        mapSizeX = wMapLeft,
        mapSizeY = hMapLeft,
        yOff = yOffLeft * stepSize
    },
    entities = {
        [0] = {
            name = "cAolioneR",
            layer = 1,
            isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = cAolioneRPosX, -- 128
                        y = cAolioneRPosY  -- 256
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
					animationIndex = cAolioneRIndexAnim -- 1
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 2,
                    xRight = 2,
                    yUp = 4,
                    yDown = 9,
                    color = {
                        r = 0,
                        g = 255,
                        b = 255,
                        a = 255
                    },
                    fontFamily = "charriot-14pt"
                }
            },
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS      -      left
----------------------------------------------------------------------------------------------------
            [1] = {
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
            [2] = {
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
            [3] = {
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
            [4] = {
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
}
