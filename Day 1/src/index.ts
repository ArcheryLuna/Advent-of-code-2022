const fs = require("fs");
const path = require("path");

function readInputFile() {

    const fileContents = fs.readFileSync(
        path.join(__dirname, "../src", "input.txt"),
        {
            encoding: 'utf-8'
        }
    ).replace(/\r/g, '').trim().split('\n\n');

    return fileContents;
}


function GetTheLargest() {
    const array = readInputFile();
    let arrayOfTotal = [];

    for (let i = 0; i < array.length; i++) {
        const element = array[i].split('\n').map(Number);

        // Add each element to the sum
        let sum = 0;
        for (let j = 0; j < element.length; j++) {
            sum += element[j];
        }
        arrayOfTotal.push(sum);
    }
    return arrayOfTotal;
}

function PartTwo() {
    const arrayOfTotal = GetTheLargest();

    const sortedArray = arrayOfTotal.sort((a, b) => b - a);

    const sumOfThree = sortedArray.slice(0, 3).reduce((a, b) => a + b, 0);
    return sumOfThree
}

// Part One
console.log("Part One: ");
console.log(Math.max(...GetTheLargest()));

// Part Two
console.log("Part Two: ");
console.log(PartTwo());
