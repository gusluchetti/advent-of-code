from pathlib import Path
import time

def parse_numbers(line: str):
    line = line.strip().split(':')[1]
    all_nums = line.split('|')
    first: list[str] = [a for a in all_nums[0].strip().split()]
    second: list[str] = [a for a in all_nums[1].strip().split()]

    winning = [int(a) for a in first]
    nums = [int(b) for b in second]

    numbers: tuple[list[int], list[int]] = (winning, nums)
    return numbers
    

def part1(lines: list[str]):
    numbers = list(map(parse_numbers, lines))
    sum = 0
    for n in numbers:
        non_uniques = len(set(n[0]).intersection(n[1]))
        if non_uniques >= 1: sum += 2 ** (non_uniques - 1)

    return sum

def part2(lines: list[str]):
    card_instances: list[int] = [1 for _ in lines]
    numbers = list(map(parse_numbers, lines))

    for i, n in enumerate(numbers):
        index = i+1
        repeat = card_instances[i]
        commons = len(set(n[0]).intersection(n[1]))
        for i in range(index, index+commons):
            if i < len(card_instances): 
                card_instances[i] += 1*repeat

    return sum(card_instances)

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    lines: list[str] = open(input, "r", encoding="utf-8").readlines()

    p1 = part1(lines)
    p2 = part2(lines)
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
