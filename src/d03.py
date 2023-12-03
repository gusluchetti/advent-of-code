import time
import regex as re
from pathlib import Path

schematic = []

def part1(schematic: list[str]):
    symbols: list[tuple[int, int]] = []
    width = len(schematic[0]) 
    height = len(schematic)
    print(f'\ninfo = w: {width}, h: {height}')

    for i, line in enumerate(schematic):
        for j, char in enumerate(line):
            if (char.isdigit() == False and char != "."):
                symbols.append((i, j))
    print(f'symbols positions: {symbols}')

    filtered: list[tuple[int, int]] = []
    sum = 0
    for i, line in enumerate(schematic):
        print(line)
        spans = []

        for r in re.finditer(r'\d+', line):
            spans = r.spans() if r else [] 
            for span in spans:
                start, end = span
                adj: list[tuple[int, int]] = []
                for x in range(start-1, end+1):
                    adj.append((i-1, x))
                    adj.append((i+1, x))
                adj.append((i, start-1))
                adj.append((i, end))

                filtered = [a for a in adj if (a[0] >= 0 and a[0] < width - 1 and
                    a[1] >= 0 and a[1]< height - 1)] 

                if any(n in filtered for n in symbols):
                    sum += int(r[0])

    return sum

def part2(schematic: list[str]):
    gears: list[tuple[int, int]] = []
    width = len(schematic[0]) 
    height = len(schematic)
    print(f'\ninfo = w: {width}, h: {height}')

    for i, line in enumerate(schematic):
        for j, char in enumerate(line):
            if (char == "*"):
                gears.append((i, j))
    print(f'gears positions: {gears}')

    filtered: list[tuple[int, int]] = []
    sum = 0
    for i, line in enumerate(schematic):
        print(line)
        spans = []
        for r in re.finditer(r'\d+', line):
            spans = r.spans() if r else [] 
            for span in spans:
                start, end = span
                adj: list[tuple[int, int]] = []
                for x in range(start-1, end+1):
                    adj.append((i-1, x))
                    adj.append((i+1, x))
                adj.append((i, start-1))
                adj.append((i, end))

                filtered = [a for a in adj if (a[0] >= 0 and a[0] < width - 1 and
                    a[1] >= 0 and a[1]< height - 1)] 
                print(filtered)


    return sum

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")

    for line in file:
        line = line.strip()
        schematic.append(line)

    # p1 = part1(schematic)
    p1 = 0
    p2 = part2(schematic)
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
