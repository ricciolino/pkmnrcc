home = "../HOME"

stepSize = 64

hMap = 48
wMap = 48

hMapDown = 24
wMapDown = 24
xOffDown = 12

giovanottoPosX,giovanottoPosY,giovanottoIndexAnim = 22*stepSize,46*stepSize,3
f = io.open(home.."/.pkmnrcc/tsav/smeraldopoli2.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/smeraldopoli2.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    giovanottoPosX,giovanottoPosY,giovanottoIndexAnim = stepSize*tonumber(t["giovanottoPosX"]),stepSize*tonumber(t["giovanottoPosY"]),tonumber(t["giovanottoIndexAnim"])
    io.close(f)
end

colionePosX,colionePosY,colioneIndexAnim = (2+xOffDown)*stepSize,(9+hMap)*stepSize,1
colione3PosX,colione3PosY,colione3IndexAnim = (4+xOffDown)*stepSize,(4+hMap)*stepSize,3
colione4PosX,colione4PosY,colione4IndexAnim = (4+xOffDown)*stepSize,(10+hMap)*stepSize,2
colione5PosX,colione5PosY,colione5IndexAnim = (4+xOffDown)*stepSize,(9+hMap)*stepSize,1
f = io.open(home.."/.pkmnrcc/tsav/biancavilla.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/biancavilla.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    colionePosX,colionePosY,colioneIndexAnim = (tonumber(t["colionePosX"])+xOffDown)*stepSize,(tonumber(t["colionePosY"])+hMap)*stepSize,tonumber(t["colioneIndexAnim"])
    colione3PosX,colione3PosY,colione3IndexAnim = (tonumber(t["colione3PosX"])+xOffDown)*stepSize,(tonumber(t["colione3PosY"])+hMap)*stepSize,tonumber(t["colione3IndexAnim"])
    colione4PosX,colione4PosY,colione4IndexAnim = (tonumber(t["colione4PosX"])+xOffDown)*stepSize,(tonumber(t["colione4PosY"])+hMap)*stepSize,tonumber(t["colione4IndexAnim"])
    colione5PosX,colione5PosY,colione5IndexAnim = (tonumber(t["colione5PosX"])+xOffDown)*stepSize,(tonumber(t["colione5PosY"])+hMap)*stepSize,tonumber(t["colione5IndexAnim"])
    io.close(f)
end

smeraldopoli2 = {
    assets = {
    },
    map = {
        name = "smeraldopoli2",
        file = "../assets/tilemaps/smeraldopoli2",
        mapSizeX = wMap,
        mapSizeY = hMap
    },
    mapDown = {
        name = "biancavilla",
        file = "../assets/tilemaps/center",
        mapSizeX = wMapDown,
        mapSizeY = hMapDown,
        xOff = xOffDown * stepSize
    },
    entities = {
        [0] = {
            name = "giovanotto",
            layer = 1,
			isMainInMap = true,
            components = {
                transform = {
                    position = {
                        x = giovanottoPosX, -- 640
                        y = giovanottoPosY  -- 1408
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
					animationIndex = giovanottoIndexAnim -- 3
                },
                randInput = {
                    maxRndFrequency = 800,
                    minRndFrequency = 60
                },
                bound = {
                    xLeft = 22,
                    xRight = 22,
                    yUp = 45,
                    yDown = 46,
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
----------------------------------------------------------------------------------------------------
-- ADJACIENT MAPS SHOW CHARACTERS      -      right
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
        },
        [5] = {
            name = "pallet-town-player-home",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = 17*stepSize,
                        y = 51*stepSize
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
        [6] = {
            name = "pallet-town-gary-home",
            layer = 1,
            components = {
                staticTransform = {
                    position = {
                        x = 22*stepSize,
                        y = 51*stepSize
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
