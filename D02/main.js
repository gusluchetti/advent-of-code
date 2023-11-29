const Directions = {
	Up: "U",
	Right: "R",
	Down: "D",
	Left: "L",
};

const assert = require("assert");
const fs = require("fs");
const readline = require("readline");

const keypad = [
	[1, 2, 3],
	[4, 5, 6],
	[7, 8, 9],
];

let y = 1;
let x = 1;
assert.equal(keypad[y][x], 5, "starting keypad should be 5");

const password = [];

async function processLineByLine() {
	const fileStream = fs.createReadStream("input.txt");
	const rl = readline.createInterface({
		input: fileStream,
		crlfDelay: Infinity,
	});

	let counter = 0;
	for await (const line of rl) {
		console.log(line, "\n");
		for (let i = 0; i < line.length; i++) {
			switch (line[i]) {
				case Directions.Up:
					if (y !== 0) y--;
					break;
				case Directions.Down:
					if (y !== 2) y++;
					break;
				case Directions.Left:
					if (x !== 0) x--;
					break;
				case Directions.Right:
					if (x !== 2) x++;
					break;

				default:
					break;
			}
		}
		password[counter] = keypad[y][x];
		counter++;
	}

	console.log(password);
}

processLineByLine();
