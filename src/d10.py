import time
from pathlib import Path

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
    path = []
    grid_length = len(lines[0])
    start = (-1, -1)

    for y, l in enumerate(lines):
        for x, s in enumerate(l):
            if s == "S":
                start = (y, x)

    path.append(start)
    count = 0
    bad = []
    while path.count(start) < 2:
        count += 1
        y, x = path[-1]

        top, right, bot, left = ".", ".", ".", "."
        if y - 1 >= 0:
            top = lines[y - 1][x]
        if x + 1 < grid_length:
            right = lines[y][x + 1]
        if y + 1 < grid_length:
            bot = lines[y + 1][x]
        if x - 1 >= 0:
            left = lines[y][x - 1]

        top_pos = (y - 1, x)
        right_pos = (y, x + 1)
        bot_pos = (y + 1, x)
        left_pos = (y, x - 1)
        adj = [top_pos, right_pos, bot_pos, left_pos]
        new = [a not in path and a not in bad for a in adj]

        if new[3] and LEFT.__contains__(left):
            path.append(left_pos)
        elif new[2] and BOTTOM.__contains__(bot):
            path.append(bot_pos)
        elif new[1] and RIGHT.__contains__(right):
            path.append(right_pos)
        elif new[0] and TOP.__contains__(top):
            path.append(top_pos)
        else:
            bad.append(path.pop(-1))
            pass

        if any([a == "S" for a in [top, right, bot, left]]) and len(path) != 3:
            cur = lines[y][x]
            if top == "S" and BOTTOM.__contains__(cur):
                break
            if right == "S" and LEFT.__contains__(cur):
                break
            if bot == "S" and TOP.__contains__(cur):
                break
            if left == "S" and RIGHT.__contains__(cur):
                break

    print(f"\nfinished")
    print(path, len(path))
    print(bad)
    longest = int((len(path) + 1) / 2)
    return longest


def part2(lines):
    print(lines)
    return -1


def main():
    input = Path(__file__).parent / f"../inputs/{Path(__file__).stem}.txt"
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
    print("elapsed: {}s".format(elapsed / 1000000000))
