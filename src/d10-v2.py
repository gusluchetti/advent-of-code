from pathlib import Path
import time

# | is a vertical pipe connecting north and south.
# - is a horizontal pipe connecting east and west.
# L is a 90-degree bend connecting north and east.
# J is a 90-degree bend connecting north and west.
# 7 is a 90-degree bend connecting south and west.
# F is a 90-degree bend connecting south and east.
# . is ground; there is no pipe in this tile.

TOP = "|7F"
BOTTOM = "|JL"
RIGHT = "-J7"
LEFT = "-FL"

def part1(lines):
    lines = [l.strip() for l in lines]
    print(lines)
    grid_length = len(lines[0])
    start = (-1, -1)

    for y, l in enumerate(lines):
        for x, s in enumerate(l): 
            if s == 'S': start = (y,x)

    queue = [(start, 0)]
    y, x = start

    cur = lines[y][x]

    top, right, bot, left = '.', '.', '.', '.'
    if y-1 >= 0: 
        top = lines[y-1][x]
        if TOP.__contains__(top):
            new = (y-1, x), 1
            queue.append(new)
    if x+1 < grid_length: 
        right = lines[y][x+1]
        if RIGHT.__contains__(right):
            queue.append((y, x+1))
    if y+1 < grid_length: 
        bot = lines[y+1][x]
        if BOTTOM.__contains__(bot):
            queue.append((y+1, x))
    if x-1 >= 0: 
        left = lines[y][x-1]
        if LEFT.__contains__(left):
            queue.append((y, x-1))

    adj = [top, right, bot, left]
    print(cur, adj)
    print(queue)

    last = start
    count = 0

    while len(queue) > 0:
        count += 1
        y, x = queue.pop(-1)
        break

    print(f'\nfinished!')
    return -1

def part2(lines):
    print(lines)
    return -1

def main():
    input = Path(__file__).parent / f'../inputs/d10.txt'
    input = Path(__file__).parent / f'../inputs/test_d10.txt'
    file = open(input, "r", encoding="utf-8")

    p1 = part1(file.readlines())
    if p1 != 6867:
        print('wrong answer :(')
    else:
        print('yay! :)')

    # p2 = part2(file.readlines())
    return (p1, -1)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
