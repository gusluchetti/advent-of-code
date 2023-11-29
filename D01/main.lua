io.input("./input.txt")
local file = io.read("a");
print(file)

-- N, E, S, W
-- array starts with 1
local directions = { 1, 2, 3, 4 }
local dir_index = 1;

local plane = {};
plane.x = 0
plane.y = 0

for inst in string.gmatch(file, "[R,L]%d+") do
    print("index: ", dir_index, inst)
    if string.find(inst, "R") then
        if dir_index == 4 then
            dir_index = 1
        elseif dir_index < 4 then
            dir_index = directions[dir_index + 1]
        end
    elseif string.find(inst, "L") then
        if dir_index == 1 then
            dir_index = 4
        elseif dir_index > 1 then
            dir_index = directions[dir_index - 1]
        end
    end

    local number = string.match(inst, "%d+")
    if dir_index == 1 then
        plane.y = plane.y + number
    elseif dir_index == 2 then
        plane.x = plane.x + number
    elseif dir_index == 3 then
        plane.y = plane.y - number
    elseif dir_index == 4 then
        plane.x = plane.x - number
    end

    print(plane.x, plane.y)
end

print(math.abs(plane.x) + math.abs(plane.y))
