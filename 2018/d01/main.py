from pathlib import Path
script_dir = Path(__file__).parent
file_path = script_dir / './input.txt'

lines = file_path.read_text().splitlines()

p1_res = sum(float(line) for line in lines)
print("p1: {0}".format(p1_res))

p2_freq = 0
seen_freqs = set()
done = False
while not done:
    for line in lines:
        print(p2_freq)
        if p2_freq in seen_freqs:
            print("p2: {0}".format(p2_freq))
            done = True
            break
        seen_freqs.add(p2_freq)
        p2_freq += float(line)
    print(len(seen_freqs))
