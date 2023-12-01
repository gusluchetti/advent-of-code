import regex as re

search_terms = {
  'one': 1,
  'two': 2,
  'three': 3,
  'four': 4,
  'five': 5,
  'six': 6,
  'seven': 7,
  'eight': 8,
  'nine': 9,
}

def get_line_nums(line, include_written_nums = False):
    search = r'\d'
    digits = []

    if (include_written_nums):
        more = '|'.join(list(search_terms.keys()))
        search += r'|{}'.format(more) 

    match = re.findall(search, line, overlapped=True)

    for m in match:
        num = search_terms.get(m)
        if (num != None): 
            digits.append(int(num))
        else: 
            digits.append(int(m))

    print('retrieved: {} -> {}'.format(match, digits))
    return digits

def main():
    file = open("./inputs/d01.txt", "r", encoding="utf-8")
    # file = open("./inputs/test_d01.txt", "r", encoding="utf-8")
    basic_sum = 0
    ext_sum = 0
    for line in file:
        line = line.strip()
        print(line)

        basic = get_line_nums(line)
        ext = get_line_nums(line, True)

        new_b = int("{}{}".format(basic[0], basic[-1]))
        new_e = int("{}{}".format(ext[0], ext[-1]))
        print('basic: {} + {} = {}'.format(basic_sum, new_b, basic_sum + new_b))
        print('extended: {} + {} = {}'.format(ext_sum, new_e, ext_sum + new_e))
        basic_sum += new_b
        ext_sum += new_e
        print()

    print(basic_sum, ext_sum)


if __name__ == "__main__":
    main()
    pass
