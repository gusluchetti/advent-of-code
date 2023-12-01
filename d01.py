import re

def main():
    file = open("./inputs/d01.txt", "r", encoding="utf-8")

    search = r'\d'
    include_written_nums = False
    p = re.compile(search)
    sum = 0

    for line in file:
        if (include_written_nums):
            digits = [0,1]
        else:
            digits = p.findall(line)

        print(line, digits)
        first = digits[0]
        last = digits[-1]
        new_num = int("{}{}".format(first, last))
        print(first, last, new_num)
        sum += new_num

    print(sum)


if __name__ == "__main__":
    main()
    pass

