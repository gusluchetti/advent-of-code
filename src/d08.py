from pathlib import Path
import time

def part1(lines):
    nodes = {}
    directions, *info = lines
    directions = directions.strip()
    for i in info:
        i = i.strip().split()
        if len(i) >= 1:
            cur = i[0]
            left = i[2][1:4]
            right = i[3][0:3]
            nodes[cur] = {'cur': cur, 'left': left, 'right': right}

    state = nodes['AAA']
    steps = 0
    done = False

    print(f'\nstarting...')
    print(nodes, len(nodes))
    print(directions,  len(directions))
    print(state, steps)

    while not done: 
        for d in directions:
            steps += 1
            match d:
                case 'L': state = nodes[state['left']]
                case 'R': state = nodes[state['right']]
            if state['cur'] == 'ZZZ':
                done = True
                break

    print(f'steps taken: {steps}')
    return steps 

def part2(lines):
    print(lines)
    return -1

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
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
