from pathlib import Path
script_dir = Path(__file__).parent
file_path = script_dir / './input.txt'

freq = 0
lines = file_path.read_text().splitlines()

freq = sum(float(line) for line in lines)

print(freq)
