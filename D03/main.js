const assert = require("assert");
const fs = require("fs");
const readline = require("readline");

const triangles = [];
let rowTriangles = 0;
let colTriangles = 0;

async function processLineByLine() {
	const fileStream = fs.createReadStream("input.txt");
	const rl = readline.createInterface({
		input: fileStream,
		crlfDelay: Infinity,
	});

	function isValidTriangle(sides) {
		if (sides[0] + sides[1] <= sides[2]) {
			return false;
		} else if (sides[1] + sides[2] <= sides[0]) {
			return false;
		} else if (sides[0] + sides[2] <= sides[1]) {
			return false;
		} else {
			return true;
		}
	}

	for await (const line of rl) {
		const triangle = line
			.split(" ")
			.filter((n) => n)
			.map((n) => Number(n));
		triangles.push(triangle);

		const sides = [triangle[0], triangle[1], triangle[2]];
		if (isValidTriangle(sides)) {
			rowTriangles++;
		}
	}

	console.log(triangles);
	for (let i = 0; i < 3; i++) {
		for (let j = 0; j < triangles.length; j = j + 3) {
			const sides = [triangles[j][i], triangles[j + 1][i], triangles[j + 2][i]];
			console.log(sides);
			if (isValidTriangle(sides)) {
				colTriangles++;
			}
		}
	}

	console.log(rowTriangles);
	console.log(colTriangles);
}

processLineByLine();
