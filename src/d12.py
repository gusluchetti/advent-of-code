from pathlib import Path
import time
import regex as re


def part1(lines):
    print('\n')
    arrangements = 0
    for idx, line in enumerate(lines):
        split = line.split()
        pattern, values = split[0], [int(s) for s in split[1].split(",")]
        print(f'\narrangements after line {idx} : {arrangements}')
        print(pattern, values)

        question_marks = [q.span()[0] for q in re.finditer(r'\?', pattern)]
        hashes = [h.span()[0] for h in re.finditer(r'\#', pattern)] 
        print(question_marks, hashes)

        min_space = sum(values) + len(values) - 1 
        length = len(pattern)
        if min_space == length: 
            arrangements += 1
            continue

        spaces = [0]
        for j in range(1, len(values)):
            last = values[j-1]
            spaces.append(last + 1 + spaces[-1])
        print(spaces)

        while len(values) > 0:
            for i, p in enumerate(pattern):
                print(i)
                if p == "?":
                    value = values.pop(0)
                    start, end = max(0, i-1), min(len(pattern), i+value)
                    print(value, start, end)

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
