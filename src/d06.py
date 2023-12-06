from functools import reduce
from pathlib import Path
import time
import math

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
                if has_won: break

        print(f'can win in {win} ways')
        winning_ways.append(win)

    print(winning_ways)
    return math.prod(winning_ways)

def part2(lines):
    times = [int(''.join(lines[0].split()[1:]))]
    distances = [int(''.join(lines[1].split()[1:]))]
    length = len(times)

    winning_ways: list[int] = []
    for hold in range(0, length):
        win, has_won = 0, False
        time, distance = times[hold], distances[hold]
        print(time, distance)

        hold_values = range(1, time)
        print(hold_values)
        for hold in hold_values:
            new_dist = hold * (time - hold)
            if new_dist > distance:
                win += 1
                has_won = True
            else:
                if has_won: break
        winning_ways.append(win)

    print(f'can win in {winning_ways} ways')
    return math.prod(winning_ways)

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
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
    print('elapsed: {}s'.format(elapsed/1000000000))
