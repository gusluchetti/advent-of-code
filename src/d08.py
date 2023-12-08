from pathlib import Path
import time
import math

test_input = """LR\n
\n
11A = (11B, XXX)\n
11B = (XXX, 11Z)\n
11Z = (11B, XXX)\n
22A = (22B, XXX)\n
22B = (22C, 22C)\n
22C = (22Z, 22Z)\n
22Z = (22B, 22B)\n
XXX = (XXX, XXX)\n""".splitlines()

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
    print(nodes, len(nodes))

    state = nodes['AAA']
    steps = 0
    done = False

    print(f'\nstarting...')
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
    nodes = {}
    directions, *info = lines
    directions = directions.strip()
    for i in info:
        i = i.strip().split()
        if len(i) >= 1:
            cur = i[0]
            left, right = i[2][1:4], i[3][0:3]
            nodes[cur] = {'cur': cur, 'left': left, 'right': right}

    states = [v for _, v in nodes.items() if v['cur'][2] == 'A']
    steps = 0
    done = False
    print(f'\nstarting...')
    print(directions,  len(directions))
    print(states, len(states), steps)

    finished_mins = [0] * len(states)
    while not done: 
        for d in directions:
            steps += 1
            for i, s in enumerate(states):
                match d:
                    case 'L': states[i] = nodes[s['left']]
                    case 'R': states[i] = nodes[s['right']]
            finished = [state['cur'][2] == 'Z' for state in states]

            for i, f in enumerate(finished):
                if f: finished_mins[i] = steps

            if all([f != 0 for f in finished_mins]):
                done = True
                break

    print(finished_mins)
    return math.lcm(*finished_mins) 

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'

    file = open(input, "r", encoding="utf-8")
    p1 = part1(file.readlines())

    file = open(input, "r", encoding="utf-8")
    p2 = part2(file.readlines())

    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
