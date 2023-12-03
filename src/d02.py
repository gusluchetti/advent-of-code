from io import TextIOWrapper
from pathlib import Path
import time

def part1(file: TextIOWrapper):
    sum = 0
    amount, color = 0, ""
    for i, line in enumerate(file):
        valid_game = True
        sets = line.split(':')[1].split(';')
        print(f'\nid: {i+1}')

        for j, set in enumerate(sets):
            rgb = { 'red': 12, 'green': 13, 'blue': 14 }
            print(f'set {j}')

            for a in set.split(','):
                a = a.strip().split(' ')
                amount, color = int(a[0]), a[1]
                print(amount, color)
                rgb[color] -= amount
                if rgb[color] < 0:
                    valid_game = False
                    print(f'game w/ id {i} is invalid!')
                    break;

        if valid_game:
            sum += i+1
            print(f'cur sum: {sum}')

    return sum

def part2(file: TextIOWrapper):
    sum = 0
    amount, color = 0, ""
    for i, line in enumerate(file):
        min = { 'red': 0, 'green': 0, 'blue': 0 }
        sets = line.split(':')[1].split(';')
        print(f'\nid: {i+1}')

        for j, set in enumerate(sets):
            print(f'set {j}')
            for a in set.split(','):
                a = a.strip().split(' ')
                amount, color = int(a[0]), a[1]
                if amount > min[color]:
                    print(f'fewest {color} balls needed is {amount}')
                    min[color] = amount

        sum += (min['red'] * min['green'] * min['blue']) 
        print(f'cur sum: {sum}')

    return sum

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")

    p1 = part1(file)
    p2 = part2(file)
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
