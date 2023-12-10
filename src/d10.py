from pathlib import Path
import time

# | is a vertical pipe connecting north and south.
# - is a horizontal pipe connecting east and west.
# L is a 90-degree bend connecting north and east.
# J is a 90-degree bend connecting north and west.
# 7 is a 90-degree bend connecting south and west.
# F is a 90-degree bend connecting south and east.
# . is ground; there is no pipe in this tile.
# S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.

TOP = "|7F"
RIGHT = "-J7"
BOTTOM = "|JL"
LEFT = "-FL"

def part1(lines):
    lines = [l.strip() for l in lines]
    queue, seen = [], []
    grid_length = len(lines[0])
    start = (-1, -1)

    for y, l in enumerate(lines):
        print(l)
        for x, s in enumerate(l): 
            if s == 'S': start = (y,x)
    print(f'{start}')

    seen.append((start))
    queue.append((start, 0))

    last = queue[0]
    while len(queue) > 0:
            q = queue.pop(0)
            y, x = q[0]
            distance = q[1]

            top, right, bot, left = '.', '.', '.', '.'
            if y-1 >= 0: top = lines[y-1][x]
            if x+1 < grid_length: right = lines[y][x+1]
            if y+1 < grid_length: bot = lines[y+1][x]
            if x-1 >= 0: left = lines[y][x-1]

            if distance <= 100:
                print(f'at {q}')
                print(top, right, bot, left)

            new = (-1, -1)
            if TOP.__contains__(top):
                new = (y-1,x)
                if (new) not in seen:
                    queue.append((new, distance+1))
                    seen.append((new))
            if RIGHT.__contains__(right):
                new = (y,x+1)
                if (new) not in seen:
                    queue.append((new, distance+1))
                    seen.append((new))
            if BOTTOM.__contains__(bot):
                new = (y+1,x)
                if (new) not in seen:
                    queue.append((new, distance+1))
                    seen.append((new))
            if LEFT.__contains__(left):
                new = (y,x-1)
                if (new) not in seen:
                    queue.append((new, distance+1))
                    seen.append((new))

            last = q

    return last[1]

def part2(lines):
    print(lines)
    return -1

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")

    p1 = part1(file.readlines())
    # p2 = part2(file.readlines())
    return (p1, -1)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
