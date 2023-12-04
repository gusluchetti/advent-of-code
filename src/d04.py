from pathlib import Path
import time

def part1(lines):
    for line in lines:
        print(line)
    return 0

def part2(lines):
    return 0

    for line in lines:
        print(line)

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    lines: list[str] = open(input, "r", encoding="utf-8").readlines()

    p1 = part1(lines)
    p2 = part2(lines)
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
