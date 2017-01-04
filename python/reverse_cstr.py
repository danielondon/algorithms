def reverse(cstr):
    if len(cstr) <= 2:
        return
    
    c_len = len(cstr) - 1
    mid_idx = c_len // 2
    for idx in range(mid_idx):
        shift_to_idx = c_len - 1 - idx
        cstr[idx], cstr[shift_to_idx] = cstr[shift_to_idx], cstr[idx]

for str in ['', '', 'a', 'ab', 'abc']: 
    cstr = list(str + chr(0))
    reverse(cstr)
    print cstr
     