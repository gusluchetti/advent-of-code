from pathlib import Path
import time

def part1(lines):
    total = 0
    for i, line in enumerate(lines):
        line_diffs: list[list[int]] = []
        line_diffs.append([int(x) for x in line.strip().split()])

        while not all([x == 0 for x in line_diffs[-1]]):
            diffs = []
            last = line_diffs[-1]
            for i in range(0, len(last)-1):
                diffs.append(last[i+1] - last[i])
            if len(diffs) > 0: line_diffs.append(diffs)
            else: line_diffs.append([0])

        print()
        for l in line_diffs:
            print(len(l), l)

        line_diffs[-1].append(0)
        new = sum([x[-1] for x in line_diffs])
        print(total, new, total + new)
        total += new

    return total

def part2(lines):
    new = []
    for i, line in enumerate(lines):
        line_diffs: list[list[int]] = []
        line_diffs.append([int(x) for x in line.strip().split()])

        while not all([x == 0 for x in line_diffs[-1]]):
            diffs = []
            last = line_diffs[-1]
            for i in range(0, len(last)-1):
                diffs.append(last[i+1] - last[i])
            if len(diffs) > 0: line_diffs.append(diffs)
            else: line_diffs.append([0])

        print()
        for i, l in enumerate(line_diffs):
            print(i, l)

        line_diffs[-1].append(0)
        n = line_diffs[i][0]
        for i in reversed(range(1, len(line_diffs))):
            n = line_diffs[i-1][0] - n
        new.append(n)
        print(new)

    return sum(new)

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'

    print('\npart 1')
    file = open(input, "r", encoding="utf-8")
    p1 = part1(file.readlines())

    print('\npart 2')
    file = open(input, "r", encoding="utf-8")
    p2 = part2(file.readlines())

    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1_000_000_000))
