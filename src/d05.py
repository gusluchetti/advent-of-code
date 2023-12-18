import time
from io import TextIOWrapper
from pathlib import Path


def part1(file: TextIOWrapper):
    seeds, *maps = file.read().split("\n\n")
    seeds = [int(x) for x in seeds.split()[1:]]

    ranges = []
    for m in maps:
        r = []
        for line in m.splitlines()[1:]:
            r.append(list(map(int, line.split())))
        ranges.append(r)

    min_location = float("inf")
    for seed in seeds:
        mappings = [seed]
        for r in ranges:
            for dest, source, length in r:
                length -= 1
                if mappings[-1] in range(source, source + length + 1):
                    diff = source - dest
                    mappings.append(mappings[-1] - diff)
                    break
            else:
                mappings.append(mappings[-1])

        if min_location > mappings[-1]:
            min_location = mappings[-1]
        print(f"seed: {seed} | min: {min_location}")

    return min_location


def part2(file):
    seeds, *maps = file.read().split("\n\n")
    seed_ranges: list[range] = []
    seeds = [int(x) for x in seeds.split()[1:]]
    for i in range(0, len(seeds), 2):
        seed_ranges.append(range(seeds[i], seeds[i] + seeds[i + 1]))

    line_ranges = []
    for m in maps:
        r = []
        for line in m.splitlines()[1:]:
            r.append(list(map(int, line.split())))
        line_ranges.append(r)

    min_location_ranges = []
    while len(seed_ranges) > 0:
        sr = seed_ranges.pop()
        start, end = sr[0], sr[-1]
        print(f"start: {start} | end: {end}")
        for ranges in line_ranges:
            for r in ranges:
                dest, source, length = r[0], r[1], r[2]
                diff = source - dest
                print(f"{dest}, {source}, {length}")
                ov_s = max(start, source)
                ov_e = min(end, source + length)

                if ov_s < ov_e:
                    min_location_ranges.append(range(ov_s + diff, ov_e + diff))
                    if ov_s > start:
                        seed_ranges.append(range(start, ov_s))
                    if ov_e > end:
                        seed_ranges.append(range(end, ov_e))
                    break
            else:
                min_location_ranges.append(range(start, end))

            print(f"seed_ranges: {seed_ranges}")
            print(f"min_location_ranges: {min_location_ranges}")
            print()

    print(min_location_ranges)
    return -1


def main():
    input = Path(__file__).parent / f"../inputs/{Path(__file__).stem}.txt"
    input = Path(__file__).parent / f"../inputs/test_{Path(__file__).stem}.txt"

    file = open(input, "r", encoding="utf-8")
    p1 = part1(file)

    print()
    file = open(input, "r", encoding="utf-8")
    p2 = part2(file)

    return (p1, p2)


if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print("elapsed: {}s".format(elapsed / 1000000000))
