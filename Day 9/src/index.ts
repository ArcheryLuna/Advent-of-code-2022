const fs = require('fs');
const path = require('path');

function PartOne(input: string[]) {

    for (let i = 0; i < input.length; i++) {
        const direction: string = input[i][0];
        const value: number = Number(input[i].slice(1));

        switch (direction.toLowerCase()) {
            case "r":
                console.log("right");
                break;
            case "l":
                console.log("left");
                break;
            case "u":
                console.log("up");
                break;
            case "d":
                console.log("down");
                break;
            default:
                console.log("Invalid direction");
                break;
        }
    }
}

function PartTwo(input: string[]) {

}

// Find the input file
function readInputFile() {
    const fileContents = fs.readFileSync(
        path.join(__dirname, "../src", "input.txt"),
        {
            encoding: 'utf-8'
        }
    ).replace(/\r/g, '').trim().split('\n');

    return fileContents;
}

const fileInput = readInputFile().map((line: string) => line.split(' '));

PartOne(fileInput);

PartTwo(fileInput);

// prompt the user to press the enter key
/**
 * process.stdin.setRawMode(true);
process.stdin.resume();
process.stdin.on('data', process.exit.bind(process, 0));
 */