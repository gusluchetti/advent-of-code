local pp = require("pl.pretty")

io.input("./input.txt")
local file = io.read("a");
print(file)

-- N, E, S, W
-- array starts with 1
local directions = { 1, 2, 3, 4 }
local dir_index = 1;

local plane = { x = 0, y = 0 };

local visited = {}
visited["0,0"] = 0

local first = false
local first_dist = 0;
function visited_contains(key)
    if visited[key] ~= nil then
        if first == false then
            print('intersection: ', key)
            pp.dump(visited)
            first_dist = visited[key]
            first = true
        end
    end
end

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
            local key = string.format("%d,%d", plane.x, plane.y + i)
            visited_contains(key)
            local sum = math.abs(plane.x) + math.abs(plane.y + i)
            visited[key] = sum
        end
        plane.y = plane.y + number
    elseif dir_index == 2 then
        for i = 1, number do
            local key = string.format("%d,%d", plane.x + i, plane.y)
            visited_contains(key)
            local sum = math.abs(plane.x + i) + math.abs(plane.y)
            visited[key] = sum
        end
        plane.x = plane.x + number
    elseif dir_index == 3 then
        for i = 1, number do
            local key = string.format("%d,%d", plane.x, plane.y - i)
            visited_contains(key)
            local sum = math.abs(plane.x) + math.abs(plane.y - i)
            visited[key] = sum
        end
        plane.y = plane.y - number
    elseif dir_index == 4 then
        for i = 1, number do
            local key = string.format("%d,%d", plane.x - i, plane.y)
            visited_contains(key)
            local sum = math.abs(plane.x - i) + math.abs(plane.y)
            visited[key] = sum
        end
        plane.x = plane.x - number
    end
    print('end', plane.x, plane.y)
end

local distance = math.abs(plane.x) + math.abs(plane.y)
print(distance)   -- part 1
print(first_dist) -- part 2
