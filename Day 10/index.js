const { readFileSync } = require("fs");

const program = readFileSync("input.txt", { encoding: "utf-8" })
  .replace(/\r/g, "")
  .trim()
  .split("\n")
  .map((line) => {
    const input = line.split(" ");
    const res = {};
    res.op = input[0];
    if (res.op === "addx") {
      res.value = parseInt(input[1]);
    }
    return res;
  });

class CPU {
  constructor(program) {
    this.program = program;
    this.currentLine = 0;
    this.cycle = 1;
    this.wait = 0;
    this.registers = {
      X: 1,
    };
  }

  runCycle() {
    if (this.currentLine >= this.program.length) {
      return false;
    }
    this.cycle++;

    const line = this.program[this.currentLine];

    switch (line.op) {
      case "noop":
        this.currentLine++;
        break;

      case "addx":
        if (this.wait === 0) {
          this.wait = 1;
        } else {
          this.wait--;
          if (this.wait === 0) {
            this.registers.X += line.value;
            this.currentLine++;
          }
        }
        break;

      default:
        throw new Error("unkown op: " + line.op);
    }

    return true;
  }
}

function part1() {
  const cpu = new CPU(program);
  let sum = 0;
  while (true) {
    if (!cpu.runCycle()) {
      break;
    }
    if (cpu.cycle % 40 === 20) {
      sum += cpu.cycle * cpu.registers.X;
    }
  }
  return sum;
}

class CRT {
  constructor(width = 40, height = 6) {
    this.width = width;
    this.height = height;
    this.currentIndex = 0;

    this.content = new Array(this.height)
      .fill(0)
      .map((_) => new Array(this.width).fill(" "));
  }

  runCycle(spritePosition) {
    const x = this.currentIndex % this.width;
    const y = Math.floor(this.currentIndex / this.width);

    if (y >= this.height) {
      return;
    }

    if (Math.abs(x - spritePosition) < 2) {
      this.content[y][x] = "#";
    } else {
      this.content[y][x] = ".";
    }

    this.currentIndex++;
  }

  printScreen() {
    console.log(this.content.map((line) => line.join("")).join("\n"));
  }
}

function part2() {
  const cpu = new CPU(program);
  const crt = new CRT();
  while (true) {
    crt.runCycle(cpu.registers.X);
    if (!cpu.runCycle()) {
      break;
    }
  }
  crt.printScreen();
}

console.log(`Part 1: ${part1()}`);
console.log('Part 2:')
part2();
