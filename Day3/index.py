def PartOne():
    ans = 0

    for line in open("./Day3/input.txt"):
        x = line.strip()
        y,z = x[:len(x)//2], x[len(x)//2:]
        for c in y:
            if c in z:
                if 'a'<=c<='z':
                    ans += ord(c)-ord('a') + 1
                else:
                    ans += ord(c)-ord('A') + 1 + 26
                break
    
    return ans

def PartTwo():
    print("Part Two")

# Part One
print(f"Part One: {PartOne()}")