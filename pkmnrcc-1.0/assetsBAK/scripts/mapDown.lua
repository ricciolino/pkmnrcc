home = "../HOME"

stepSize = 64

hMap = 24
wMap = 24

hMapUp = 24
wMapUp = 24
xOffUp = 0

scienziatoPosX,scienziatoPosY,scienziatoIndexAnim = 8*stepSize,2*stepSize,3
f = io.open(home.."/.pkmnrcc/tsav/mapDown.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mapDown.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    scienziatoPosX,scienziatoPosY,scienziatoIndexAnim = stepSize*tonumber(t["scienziatoPosX"]),stepSize*tonumber(t["scienziatoPosY"]),tonumber(t["scienziatoIndexAnim"])
    io.close(f)
end

colionePosX,colionePosY,colioneIndexAnim = (2+xOffUp)*stepSize,(9-hMapUp)*stepSize,1
colione3PosX,colione3PosY,colione3IndexAnim = (4+xOffUp)*stepSize,(4-hMapUp)*stepSize,3
colione4PosX,colione4PosY,colione4IndexAnim = (4+xOffUp)*stepSize,(10-hMapUp)*stepSize,2
colione5PosX,colione5PosY,colione5IndexAnim = (4+xOffUp)*stepSize,(9-hMapUp)*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/biancavilla.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/biancavilla.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    colionePosX,colionePosY,colioneIndexAnim = (tonumber(t["colionePosX"])+xOffUp)*stepSize,(tonumber(t["colionePosY"])-hMapUp)*stepSize,tonumber(t["colioneIndexAnim"])
    colione3PosX,colione3PosY,colione3IndexAnim = (tonumber(t["colione3PosX"])+xOffUp)*stepSize,(tonumber(t["colione3PosY"])-hMapUp)*stepSize,tonumber(t["colione3IndexAnim"])
    colione4PosX,colione4PosY,colione4IndexAnim = (tonumber(t["colione4PosX"])+xOffUp)*stepSize,(tonumber(t["colione4PosY"])-hMapUp)*stepSize,tonumber(t["colione4IndexAnim"])
    colione5PosX,colione5PosY,colione5IndexAnim = (tonumber(t["colione5PosX"])+xOffUp)*stepSize,(tonumber(t["colione5PosY"])-hMapUp)*stepSize,tonumber(t["colione5IndexAnim"])
    io.close(f)
end

mapDown = {
    assets = {
    },
    map = {
        name = "mapDown",
        file = "../assets/tilemaps/down",
        mapSizeX = wMap,
        mapSizeY = hMap
    },
    mapUp = {
        name = "biancavilla",
        file = "../assets/tilemaps/center",
        mapSizeX = wMapUp,
        mapSizeY = hMapUp,
        xOff = xOffUp * stepSize
    },
    entities = {
        [0] = {
            name = "scienziato",
            layer = 1,
            components = {
                transform = {
                    position = {
                        x = scienziatoPosX,-- 512
                        y = scienziatoPosY -- 128
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
					animationIndex = scienziatoIndexAnim
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 7,
                    xRight = 9,
                    yUp = 2,
                    yDown = 2,
                    color = {
                        r = 0,
                        g = 0,
                        b = 0,
                        a = 255
                    },
                    fontFamily = "charriot-14pt"
                }

            }
        },
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS      -      Up
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
