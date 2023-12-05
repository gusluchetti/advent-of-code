from io import TextIOWrapper
from pathlib import Path
import time

def part1(file: TextIOWrapper):
    values = file.read().split('\n\n')
    seeds = [int(x) for x in values[0].split()[1:]]
    finals: list[int] = [] # in this case, locations

    for s in seeds:
        print(f'\nseed: {s}')
        next, _ = s, s
        for idx, map in enumerate(values[1:]):
            info, diff = map.split(), 0

            for i in range(2,len(info)-1, 3):
                dest, source, range_len = int(info[i]), int(info[i+1]), int(info[i+2]) 
                diff = source - dest
                _ = next
                if next >= source and next <= source + range_len - 1:
                    next = next - diff
                    break
                else:
                    diff = 0

            print(f'seed {s} on map {idx} | diff = {diff} -> {next}')

        finals.append(next)
        print(f'seed {s} finalized at {next}')

    return min(finals)

def part2(file):
    values = file.read().split('\n\n')
    seeds = [int(x) for x in values[0].split()[1:]]
    finals: list[int] = [] # in this case, locations

    for s in seeds:
        print(f'\nseed: {s}')
        next, _ = s, s
        for idx, map in enumerate(values[1:]):
            info, diff = map.split(), 0

            for i in range(2,len(info)-1, 3):
                dest, source, range_len = int(info[i]), int(info[i+1]), int(info[i+2]) 
                diff = source - dest
                _ = next
                if next >= source and next <= source + range_len - 1:
                    next = next - diff
                    break
                else:
                    diff = 0

            print(f'{diff:+} -> {next}')

        finals.append(next)
        print(f'seed {s} finalized at {next}')

    return min(finals)

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'

    file = open(input, "r", encoding="utf-8")
    p1 = part1(file)

    file = open(input, "r", encoding="utf-8")
    p2 = part2(file)

    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
