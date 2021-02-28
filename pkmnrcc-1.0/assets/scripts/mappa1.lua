-- This file has been created by an automatic tool generator.
-- The following table's fields has been setted:
--   - layer = 1
--   - isMainInMap = true
--   - textureAssetId = scientist-texture
--   - textureAssetId = pallet-town-player-home (per quelle con staticTransform e staticSprite components)
--   - animated = true
--   - frameCount = 4
--   - hasDirections = true
--   - fixed = false
--   - maxRndFrequency = 800
--   - minRndFrequency = 60
--   - bounds have black color and an offset of 1
-- Change them to customize the location.

home = "../HOME"

stepSize = 64

hMap = 24
wMap = 24




hMapUp = 24
wMapUp = 24
xOffUp = 0

casa1PosX,casa1PosY,casa1IndexAnim = 1*stepSize,3*stepSize,0
f = io.open(home.."/.pkmnrcc/tsav/mappa1.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mappa1.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    io.close(f)
end




casa2PosX,casa2PosY,casa2IndexAnim = (2+xOffUp)*stepSize,(17-hMapUp)*stepSize,0
f = io.open(home.."/.pkmnrcc/tsav/mappa2.tsav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/tsav/mappa2.tsav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    io.close(f)
end

mappa1 = {
    assets = {
    },
    map = {
        name = "mappa1",
        file = "../assets/tilemaps/mappa1",
        mapSizeX = wMap,
        mapSizeY = hMap
    },
    mapUp = {
        name = "mappa2",
        file = "../assets/tilemaps/mappa2",
        mapSizeX = wMapUp,
        mapSizeY = hMapUp,
        xOff = xOffUp * stepSize
    },
    entities = {
        [0] = {
            name = "casa1",
            layer = 0,
            isMainInMap = true,
            components = {
                staticTransform = {
                    position = {
                        x = casa1PosX,
                        y = casa1PosY
                    },
                    width = 256/2,
                    height = 192/2,
                    scale = 2,
                },
                staticSprite = {
                    textureAssetId = "pallet-town-player-home",
                    fixed = false,
                    animationIndex = 0
                }
            }
        },
-- ADJACIENT MAPS SHOW CHARACTERS    -    up
        [1] = {
            name = "casa2",
            layer = 0,
            components = {
                staticTransform = {
                    position = {
                        x = casa2PosX,
                        y = casa2PosY
                    },
                    width = 256/2,
                    height = 192/2,
                    scale = 2
                },
                staticSprite = {
                    textureAssetId = "pallet-town-player-home",
                    fixed = false,
                    animationIndex = 0
                }
            }
        },
    }
}
