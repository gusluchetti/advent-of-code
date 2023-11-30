const Directions = {
	Up: "U",
	Right: "R",
	Down: "D",
	Left: "L",
};

const assert = require("assert");
const fs = require("fs");
const readline = require("readline");

const keypad1 = [
	[1, 2, 3],
	[4, 5, 6],
	[7, 8, 9],
];

let y1 = 1;
let x1 = 1;
assert.equal(keypad1[y1][x1], 5, "starting keypad should be 5");

const keypad2 = [
	[null, null, 1, null, null],
	[null, 2, 3, 4, null],
	[5, 6, 7, 8, 9],
	[null, "A", "B", "C", null],
	[null, null, "D", null, null],
];

let y2 = 2;
let x2 = 0;
assert.equal(keypad1[y1][x1], 5, "starting keypad should be 5");

const password1 = [];
const password2 = [];

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
			console.log(y1, x1, keypad1[y1][x1]);
			console.log(y2, x2, keypad2[y2][x2]);
			console.log(line[i]);
			switch (line[i]) {
				case Directions.Up:
					if (y1 !== 0) y1--;
					if (y2 !== 0 && keypad2[y2 - 1][x2] != null) y2--;
					break;
				case Directions.Down:
					if (y1 !== 2) y1++;
					if (y2 !== 4 && keypad2[y2 + 1][x2] != null) y2++;
					break;
				case Directions.Left:
					if (x1 !== 0) x1--;
					if (x2 !== 0 && keypad2[y2][x2 - 1] != null) x2--;
					break;
				case Directions.Right:
					if (x1 !== 2) x1++;
					if (x2 !== 4 && keypad2[y2][x2 + 1] != null) x2++;
					break;

				default:
					break;
			}
		}
		password1[counter] = keypad1[y1][x1];
		password2[counter] = keypad2[y2][x2];
		counter++;
	}

	console.log(password1);
	console.log(password2);
}

processLineByLine();
