from pathlib import Path
import time

def part1(lines: list[str], expansion: int = 1):
    lines = [l.strip() for l in lines]
    row_length = len(lines[0])

    expand = []
    for i, row in enumerate(lines): 
        if not row.__contains__('#'):
            expand.append(('r', i))
    for col_idx in range(0, row_length): 
        column = [line[col_idx] for line in lines]
        joined = ''.join(column)
        if not joined.__contains__('#'):
            expand.append(('c', col_idx))

    galaxies = []
    for y, row in enumerate(lines):
        for x, char in enumerate(row):
            if char == '#':
                galaxies.append((y, x))

    min_distances = 0
    for i, gc in enumerate(galaxies):
        others = galaxies[i+1:]
        for o in others:
            cy, cx = gc
            oy, ox = o

            y_range = range(min(cy, oy), max(cy, oy)+1)
            relevant = [e for e in expand if e[0] == 'r' and e[1] in y_range]
            min_y = abs(cy - oy) + (len(relevant)*expansion)  

            x_range = range(min(cx, ox), max(cx, ox)+1)
            relevant = [e for e in expand if e[0] == 'c' and e[1] in x_range]
            min_x = abs(cx - ox) + (len(relevant)*expansion)  

            min_dist = min_y + min_x
            min_distances += min_dist

    return min_distances

def part2(lines: list[str], expansion: int = 1):
    lines = [l.strip() for l in lines]
    row_length = len(lines[0])

    expand = []
    for i, row in enumerate(lines): 
        if not row.__contains__('#'):
            expand.append(('r', i))
    for col_idx in range(0, row_length): 
        column = [line[col_idx] for line in lines]
        joined = ''.join(column)
        if not joined.__contains__('#'):
            expand.append(('c', col_idx))

    galaxies = []
    for y, row in enumerate(lines):
        for x, char in enumerate(row):
            if char == '#':
                galaxies.append((y, x))

    min_distances = 0
    for i, gc in enumerate(galaxies):
        others = galaxies[i+1:]
        for o in others:
            cy, cx = gc
            oy, ox = o

            y_range = range(min(cy, oy), max(cy, oy)+1)
            relevant = [e for e in expand if e[0] == 'r' and e[1] in y_range]
            min_y = abs(cy - oy) + (len(relevant)*expansion)  

            x_range = range(min(cx, ox), max(cx, ox)+1)
            relevant = [e for e in expand if e[0] == 'c' and e[1] in x_range]
            min_x = abs(cx - ox) + (len(relevant)*expansion)  

            min_dist = min_y + min_x
            min_distances += min_dist

    return min_distances

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'

    file = open(input, "r", encoding="utf-8")
    p1 = part1(file.readlines(), 1)

    file = open(input, "r", encoding="utf-8")
    p2 = part2(file.readlines(), 1_000_000 - 1)
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
