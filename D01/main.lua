local pp = require("pl.pretty")

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
visited = {}
table.insert(visited, { x = 0, y = 0 })

for inst in string.gmatch(file, "[R,L]%d+") do
    print()
    print(inst)
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

    print('start', plane.x, plane.y)
    if dir_index == 1 then
        for i = 1, number do
            local item = { x = plane.x, y = plane.y + i }
            if table[item] ~= nil then
                print('intersection: ', item)
            end
            table.insert(visited, item)
        end
        plane.y = plane.y + number
    elseif dir_index == 2 then
        for i = 1, number do
            local item = { x = plane.x + i, y = plane.y }
            if table[item] ~= nil then
                print('intersection: ', item)
            end
            table.insert(visited, item)
        end
        plane.x = plane.x + number
    elseif dir_index == 3 then
        for i = 1, number do
            local item = { x = plane.x, y = plane.y - i }
            if table[item] ~= nil then
                print('intersection: ', item)
            end
            table.insert(visited, item)
        end
        plane.y = plane.y - number
    elseif dir_index == 4 then
        for i = 1, number do
            local item = { x = plane.x - i, y = plane.y }
            if table[item] ~= nil then
                print('intersection: ', item)
            end
            table.insert(visited, item)
        end
        plane.x = plane.x - number
    end
    print('end', plane.x, plane.y)
end

pp.dump(visited)
print(math.abs(plane.x) + math.abs(plane.y))
