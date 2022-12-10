def score(c):
    if 'a'<=c<='z':
        return ord(c)-ord('a')+1
    else:
        return ord(c)-ord('A')+1+26

def PartOne():
    ans = 0
    for lines in open('Day 3/input.txt'):
        x = lines.strip()
        y, z = x[:len(x)//2], x[len(x)//2:]
        for c in y:
            for c in z:
                ans += score(c)
                break
    return ans

def PartTwo():
    ans = 0
    x = [line for line in open('Day 3/input.txt')]
    i = 0
    while i < len(x):
        for c in x[i]:
            if c in x[i+1] and c in x[i+2]:
                ans += score(c)
                break
        i += 3
    return ans

print(f"Part One: {PartOne()}")
print(f"Part Two: {PartTwo()}")
