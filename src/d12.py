from pathlib import Path
import time

def part1(lines):
    print(lines)
    return -1

def part2(lines):
    print(lines)
    return -1

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")
    lines = [line.strip() for line in file.readlines()]

    p1 = part1(lines)
    # p2 = part2(lines)
    return (p1, -1)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
