from pathlib import Path
from enum import Enum
import time

class Hand_Types(Enum):
    HIGH_CARD = 0
    ONE_PAIR = 1
    TWO_PAIR = 2
    THREE_OF_A_KIND = 3
    FULL_HOUSE = 4
    FOUR_OF_A_KIND = 5
    FIVE_OF_A_KIND = 6

def get_hand_type(hand: str):
    map = {}
    for card in hand:
        if not map.get(card): map[card] = 0
        repeated = hand.count(card)
        map[card] = repeated
    print(map)
    card_values = list(map.values())
    if max(card_values) == 1:
        return Hand_Types.HIGH_CARD
        
    if max(card_values) == 2:
        if card_values.count(2) == 1:
            return Hand_Types.ONE_PAIR
        if card_values.count(2) == 2:
            return Hand_Types.TWO_PAIR

    if max(card_values) == 3:
        if card_values.count(2) == 1:
            return Hand_Types.ONE_PAIR
        if card_values.count(2) == 2:
            return Hand_Types.TWO_PAIR

    return 0

def part1(lines):
    for line in lines:
        hand, bid = line.strip().split()
        bid = int(bid)
        print(hand, bid)
        hand_type = get_hand_type(hand)
        print(hand_type)
    return -1

def part2(lines):
    print(lines)
    return -1

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'
    file = open(input, "r", encoding="utf-8")

    p1 = part1(file.readlines())
    # p2 = part2(file.readlines())
    p2 = -1
    return (p1, p2)

if __name__ == "__main__":
    t = time.perf_counter_ns()
    (p1, p2) = main()
    elapsed = time.perf_counter_ns() - t
    print(p1, p2)
    print('elapsed: {}s'.format(elapsed/1000000000))
