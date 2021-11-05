import random
for i in range(8):
    lower = 2**(7*i)
    upper = 2**(7*(i+1))-1
    crnt_set = set()
    while len(crnt_set) != 18:
        crnt_set.add(random.randint(lower+1, upper-1))
    string = repr([f'(uint64_t)1 << (7*{i})', f'((uint64_t)1 << (7*{i+1})) - 1'] + sorted(crnt_set)).replace("'",'')
    print('{' + string[1:-1] + '}', end=',\n')