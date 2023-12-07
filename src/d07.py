from pathlib import Path
from enum import IntEnum
from functools import cmp_to_key
import time

joker_enabled = False

strength = {
    '2': 0,
    '3': 1,
    '4': 2,
    '5': 3,
    '6': 4,
    '7': 5,
    '8': 6,
    '9': 7,
    'T': 8,
    'J': 9,
    'Q': 10,
    'K': 11,
    'A': 12
}

class HAND(IntEnum):
    HIGH_CARD = 0
    ONE_PAIR = 1
    TWO_PAIR = 2
    THREE_OF_A_KIND = 3
    FULL_HOUSE = 4
    FOUR_OF_A_KIND = 5
    FIVE_OF_A_KIND = 6

def custom_hand_sort(h1, h2):
    # -1 -> first before second
    # +1 -> second before first
    # 0 -> equal

    global joker_enabled
    if joker_enabled: strength["J"] = -1

    if h1["type"] > h2["type"]: return +1
    if h1["type"] < h2["type"]: return -1
    else:
        for i in range(0, 5):
            if strength[h1["hand"][i]] > strength[h2["hand"][i]]:
                return +1
            if strength[h2["hand"][i]] > strength[h1["hand"][i]]:
                return -1
            else:
                continue

    return 0

def get_hand_type(hand: str):
    global joker_enabled
    map = {}
    for card in hand:
        if not map.get(card): map[card] = 0
        repeated = hand.count(card)
        map[card] = repeated

    if joker_enabled:
        num_jokers = map.get("J")
        if num_jokers: 
            map["J"] = 0
            for _ in range(0, num_jokers):
                max_key = max(map, key=lambda k: map[k])
                if map[max_key] <= 4: map[max_key] += 1
                else: num_jokers += 1

    c_vals = list(map.values())
    hand_type = HAND.HIGH_CARD
    match max(c_vals):
        case 2:
            if c_vals.count(2) == 1: hand_type = HAND.ONE_PAIR
            else: hand_type = HAND.TWO_PAIR
        case 3:
            if c_vals.count(3) >= 1 and c_vals.count(2) >= 1: 
               hand_type = HAND.FULL_HOUSE
            else: hand_type = HAND.THREE_OF_A_KIND
        case 4: hand_type = HAND.FOUR_OF_A_KIND
        case 5: hand_type = HAND.FIVE_OF_A_KIND

    return hand_type

def part1(file):
    global joker_enabled 
    joker_enabled = False

    hands = []
    for line in file.readlines():
        hand, bid = line.strip().split()
        hands.append({
            'type': get_hand_type(hand), 
            'hand': hand, 
            'bid': int(bid)
        })

    hands = sorted(hands, key=cmp_to_key(custom_hand_sort))
    sum = 0
    for idx, h in enumerate(hands):
        rank = idx+1
        sum += rank * h["bid"]
        print(f'{rank}: {h}')
    return sum 

def part2(file):
    global joker_enabled 
    joker_enabled = True

    hands = []
    for line in file.readlines():
        hand, bid = line.strip().split()
        hands.append({
            'type': get_hand_type(hand), 
            'hand': hand, 
            'bid': int(bid)
        })

    hands = sorted(hands, key=cmp_to_key(custom_hand_sort))
    sum = 0
    print()
    for idx, h in enumerate(hands):
        rank = idx+1
        sum += rank * h["bid"]
        print(f'{rank}: {h}')
    return sum 

def main():
    input = Path(__file__).parent / f'../inputs/{Path(__file__).stem}.txt'
    # input = Path(__file__).parent / f'../inputs/test_{Path(__file__).stem}.txt'

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
