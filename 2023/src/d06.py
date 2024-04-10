import math
import time
from pathlib import Path


def part1(lines):
    times = [int(a) for a in lines[0].split()[1:]]
    distances = [int(b) for b in lines[1].split()[1:]]
    length = len(times)

    winning_ways: list[int] = []
    for i in range(0, length):
        win, has_won = 0, False
        time, distance = times[i], distances[i]
        print(time, distance)

        for i in range(1, time):
            remainder = time - i
            new_dist = i * remainder
            if new_dist > distance:
                win += 1
                has_won = True
            else:
                if has_won:
                    break

        print(f"can win in {win} ways")
        winning_ways.append(win)

    print(winning_ways)
    return math.prod(winning_ways)


def part2(lines):
    times = [int("".join(lines[0].split()[1:]))]
    distances = [int("".join(lines[1].split()[1:]))]
    length = len(times)

    s1, s2 = 0, 0
    for hold in range(0, length):
        time, distance = times[hold], distances[hold]
        print(time, distance)

        # quadratic formula
        # (7-1)*(1) = 7 - 1 = 6
        # (7-3)*(3) = 21 - 9 = 12
        # (7-6)*(6) = 42 - 36 = 12
        # (time-x)*(x) => time*x - x^2 = distance

        # (1)*x^2 + (-time)*x + (distance) = 0
        a, b, c = 1, -time, distance
        delta = b**2 - (4 * a * c)

        if delta > 0:
            root = math.sqrt(delta)
            s1 = math.floor((-b + root) / 2 * a)
            s2 = math.floor((-b - root) / 2 * a)
            print(s1 - s2)

    return s1 - s2


def main():
    input = Path(__file__).parent / f"../inputs/{Path(__file__).stem}.txt"
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'

    print()
    file = open(input, "r", encoding="utf-8")
    p1 = part1(file.readlines())

    file = open(input, "r", encoding="utf-8")
    p2 = part2(file.readlines())

    return (p1, p2)


if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print("elapsed: {}s".format(elapsed / 1000000000))
