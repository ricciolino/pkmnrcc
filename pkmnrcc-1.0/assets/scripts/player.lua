home = "../HOME"

stepSize = 64

playerPosX,playerPosY,playerIndexAnim = 1*stepSize,1*stepSize,1
f = io.open(home.."/.pkmnrcc/sav/game.sav","r")
if f ~= nil then
    t = {}
    for line in io.lines(home.."/.pkmnrcc/sav/game.sav") do
        for k, v in string.gmatch(line, "(%w+)=(%w+)") do
           t[k] = v
        end
    end
    if t["playerPosX"] ~= nil then playerPosX = stepSize*tonumber(t["playerPosX"]) end
    if t["playerPosY"] ~= nil then playerPosY = stepSize*tonumber(t["playerPosY"]) end
    if t["playerIndexAnim"] ~= nil then playerIndexAnim = tonumber(t["playerIndexAnim"]) end
    io.close(f)
end

player = {
    assets = {
    },
    entities = {
        [0] = {
            name = "player",
            layer = 1,
            isEssential = true,
            components = {
                transform = {
                    position = {
                        x = playerPosX,
                        y = playerPosY
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
					animationIndex = playerIndexAnim
                },
                input = {
                }
            }
        }
    }
}
