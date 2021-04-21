

# limitation :pattern count of each char to be max 1

text = "912873129"
pat = "123"
window_found = False
prev_min = 0
prev_max = 0
prev_pos = -1
lookup_tab = dict()

# detect first window formation when all characters are found
# change window whenever new character was the previous minimum
# if new window smaller than previous smallest, change current min window 

for pos, c in enumerate(text):
    if c in pat:
        prev_pos = lookup_tab.get(c, -1)
        lookup_tab[c] = pos

        if window_found == True:
            cur_max = pos
            if prev_pos == cur_min: # new min needed
                cur_min = min(list([lookup_tab[k] for k in lookup_tab.keys()]))
                print('new min on update of ', c, ' is ', cur_min)
            if cur_max - cur_min < prev_max - prev_min:
                prev_min = cur_min
                prev_max = cur_max

        elif len(lookup_tab) == len(pat):
            cur_min = prev_min = min(list([lookup_tab[k] for k in lookup_tab.keys()]))
            cur_max = prev_max = max(list([lookup_tab[k] for k in lookup_tab.keys()]))
            window_found = True
           
        
print(prev_min, prev_max)

