from pathlib import Path
import time

def part1(file):
    for line in file:
        print(line)
    return 0

def part2(file):
    for line in file:
        print(line)
    return 0

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")

    p1 = part1(file)
    p2 = part2(file)
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
