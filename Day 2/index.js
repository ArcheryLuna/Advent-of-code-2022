const fs = require("fs");
const path = require("path");

function readInputFile() {
    const fileContents = fs.readFileSync(
        "input.txt",
        {
            encoding: 'utf-8'
        }
    ).replace(/\r/g, '').trim().split('\n').map((line) => line.split(' '));
    return fileContents;
}

const Movements = {
    "rock": 1,
    "paper": 2,
    "scissors": 3
}

const mapInput = {
    "A": Movements.rock,
    "B": Movements.paper,
    "C": Movements.scissors,
    "X": Movements.rock,
    "Y": Movements.paper,
    "Z": Movements.scissors
}

function scoring(ourMove, yourMove) {

    // Yugioh Its time to dddddduuuuuuel
    if(ourMove === yourMove) return ourMove + 3;
    if((ourMove === Movements.rock && yourMove === Movements.scissors) || 
    (ourMove === Movements.scissors && yourMove === Movements.paper) || 
    (ourMove === Movements.paper && yourMove === Movements.rock)) return ourMove + 6;

    return ourMove;
}

function PartOne() {
    const array = readInputFile();

    const output = array.map((line) => {
        const yourMove = mapInput[line[0]];
        const ourMove = mapInput[line[1]];

        return scoring(ourMove, yourMove);
    });

    return output.reduce((a, b) => a + b, 0);
}

const Solutions = {
    A: {
        X: Movements.scissors,
        Y: Movements.rock,
        Z: Movements.paper,
      },
      B: {
        X: Movements.rock,
        Y: Movements.paper,
        Z: Movements.scissors,
      },
      C: {
        X: Movements.paper,
        Y: Movements.scissors,
        Z: Movements.rock,
      },
}


function PartTwo() {
    const array = readInputFile();

    const output = array.map((line) => {
        const yourMove = mapInput[line[0]];
        const ourMove = Solutions[line[0]][line[1]];

        return scoring(ourMove, yourMove);
    });

    return output.reduce((a, b) => a + b, 0);
}

// Part One
console.log("Part One: ", PartOne());
// Part Two
console.log("Part Two: ", PartTwo());