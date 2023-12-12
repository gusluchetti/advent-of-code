from pathlib import Path
import time
import regex as re


def part1(lines):
    print('\n')
    arrangements = 0
    for line in lines:
        print(f'\narrangements: {arrangements}')
        split = line.split()
        pattern, values = split[0], [int(s) for s in split[1].split(",")]
        print(pattern, values)

        length = len(pattern)
        min_space = sum(values) + len(values) - 1
        if min_space == length: 
            arrangements += 1
            continue

        question_marks = re.finditer(r'\?', pattern)
        hashes = re.finditer(r'\#', pattern)

        for h in hashes:
            print(h.span()[0])

        for q in question_marks:
            print(q.span()[0])

        for v in values:
            pass

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
