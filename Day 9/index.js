const fs = require('fs');

function readInput() {
    const fileContents = fs.readFileSync(
        "input.txt",
        {
            encoding: 'utf-8'
        }
    ).replace(/\r/g, '').trim().split('\n').map((line) => {
        const [letter, number] = line.split(" ");
        return {
            direction: letter,
            totalMoves: parseInt(number),
        };
    });
    return fileContents;
}

const movesDefinition = {
    R: {
      x: 1,
      y: 0,
    },
    L: {
      x: -1,
      y: 0,
    },
    U: {
      x: 0,
      y: -1,
    },
    D: {
      x: 0,
      y: 1,
    }
};

class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    move(direction) {
        const delta = movesDefinition[direction];
        this.x += delta.x;
        this.y += delta.y;
    }

    follow(point) {
        const distance = Math.max(
            Math.abs(this.x - point.x),
            Math.abs(this.y - point.y)
        );
        if (distance > 1) {
            const directionX = point.x - this.x;
            this.x += Math.abs(directionX) === 2 ? directionX / 2 : directionX;
            const directionY = point.y - this.y;
            this.y += Math.abs(directionY) === 2 ? directionY / 2 : directionY;
        }
}
}

function recallVisited(x, y, visited) {
    visited.add(`${x}-${y}`);
}

function PartOne() {
    const input = readInput();
    const visited = new Set();
    const head = new Point(0, 0);
    const tail = new Point(0, 0);
    recallVisited(0, 0, visited);

    for ( var line of input ) {
        for(let i =0; i < line.totalMoves; i++) {
            head.move(line.direction);
            tail.follow(head);
            recallVisited(tail.x, tail.y, visited);
        }
    }
    
    return visited.size;
}

function partTwo() {
    const input = readInput();
    const knots = new Array(10).fill(0).map((_) => new Point(0, 0));
    const visited = new Set();
    recallVisited(0, 0, visited);

    for (const line of input) {
        for (let i = 0; i < line.totalMoves; i++) {
        knots[0].move(line.direction);
        for (let knot = 1; knot < knots.length; knot++) {
            const point = knots[knot];
            point.follow(knots[knot - 1]);
        }
        const tail = knots[knots.length - 1];
        recallVisited(tail.x, tail.y, visited);
        }
    }
    return visited.size;
}

console.log(`Part One: ${PartOne()}`);
console.log(`Part Two: ${partTwo()}`);