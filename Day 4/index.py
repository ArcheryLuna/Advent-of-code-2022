data = open("Day 4/input.txt").read().strip()
lines = [x.strip() for x in data.split("\n")]

def ManipulateFile(line):
    one, two = line.split(',')
    s1, e1 = one.split('-')
    s2, e2 = two.split('-')
    s1, e1, s2, e2 = [int(x) for x in [s1, e1, s2, e2]]
    return s1, e1, s2, e2

def PartOne():
    ans = 0
    for line in lines:
        s1, e1, s2, e2 = ManipulateFile(line)
        if s1<=s2 and e2<=e1 or s2<=s1 and e1<=e2:
            ans += 1
    return ans

def PartTwo():
    ans = 0
    for line in lines:
        s1, e1, s2, e2 = ManipulateFile(line)
        if not (e1 < s2 or e2 < s1):
            ans += 1
    return ans

#PartOne
print(f"Part One: {PartOne()}")

#PartTwo
print(f"Part Two: {PartTwo()}")