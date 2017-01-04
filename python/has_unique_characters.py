def has_unique_characters(str):
    if len(str) <= 1:
        return True
    
    hit = [False] * 256
    for val in str:
        idx = ord(val)
        if not hit[idx]:
            hit[idx] = True
        else:
            return False
    
    return True

for str in ['', 'a', 'ab']: print has_unique_characters(str)
for str in ['aa', 'aba']: print has_unique_characters(str)
