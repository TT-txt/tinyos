from random import shuffle
#code used to generate the random table lmao
rng = [i for i in range(256)]
shuffle(rng)
print("unsigned char rngTable[256] = {", end="")
for i in range(255):
    if i % 14 == 0:
        print("\n\t", end="");
    print(f"{rng[i]}, ", end="")
print(f"{rng[255]}", end="")
print("\n};")
