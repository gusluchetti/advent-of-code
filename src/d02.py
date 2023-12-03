from pathlib import Path
import time

def part1(file):
    sum = 0
    amount, color = 0, ""
    for i, line in enumerate(file):
        print(line)
        valid_game = True
        sets = line.split(':')[1].split(';')

        for set in sets:
            rgb = { 'red': 12, 'green': 13, 'blue': 14 }

            for a in set.split(','):
                a = a.strip().split(' ')
                amount, color = int(a[0]), a[1]
                rgb[color] -= amount
                if rgb[color] < 0:
                    valid_game = False
                    break;

            if not valid_game:
                break;

        if valid_game:
            sum += i+1

    return sum

def part2(file):
    sum = 0
    amount, color = 0, ""
    for line in file:
        min = { 'red': 0, 'green': 0, 'blue': 0 }
        sets = line.split(':')[1].split(';')

        for j, set in enumerate(sets):
            for a in set.split(','):
                a = a.strip().split(' ')
                amount, color = int(a[0]), a[1]
                if amount > min[color]:
                    min[color] = amount

        sum += (min['red'] * min['green'] * min['blue']) 

    return sum

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    
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
