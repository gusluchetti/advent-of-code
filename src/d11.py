from pathlib import Path
import time

def part1(lines: list[str]):
    lines = [l.strip() for l in lines]
    print(f'\nbefore expansion: {lines}')
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

    new_rows, new_cols = 0, 0
    for e in expand:
        t, index = e
        if t == 'r':
            print(f'new row', t, index)
            lines.insert(index+new_rows, '.' * row_length)
            new_rows += 1
        elif t == 'c':
            print(f'new col', t, index)
            for i in range(0, len(lines)):
                print(lines[i])
                lines[i] = lines[i][0:index+new_cols] + '.' + lines[i][index+new_cols:]
                print(lines[i])
            new_cols += 1
    print(f'\nafter expansion: {lines}')

    galaxies = []
    for y, row in enumerate(lines):
        for x, char in enumerate(row):
            if char == '#':
                galaxies.append((y, x))

    print(f'\n{lines}')

    min_distances = 0
    for i, gc in enumerate(galaxies):
        print(i+1, gc)
        others = galaxies[i+1:]
        print(others)
        for o in others:
            min_y = abs(gc[0] - o[0])  
            min_x = abs(gc[1] - o[1])  
            min_dist = min_y + min_x
            min_distances += min_dist
            print(f'min dist to {o} from {gc} = {min_dist}')

    return min_distances

def part2(lines):
    print(lines)
    return -1

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")

    p1 = part1(file.readlines())
    # p2 = part2(file.readlines())
    return (p1, -1)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
