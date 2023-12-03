from io import TextIOWrapper
from pathlib import Path
import time

schematic = []

def part1(schematic: list[str]):
    for i, line in enumerate(schematic):
        for j, char in enumerate(line):
            if (char.isdigit() == False and char != "."):
                print(f'{char} @ {(i, j)} is a symbol')

            pass

    return 0

def part2(schematic: list[str]):
    return 0

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")

    for line in file:
        line = line.strip()
        schematic.append(line)

    p1 = part1(schematic)
    p2 = part2(schematic)
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
