#don't ask me why I made this program

import os
lines = 0
ext = ['c', 'h', 'cpp', 'hpp', 'asm', 's']

for path, subdirs, files in os.walk(os.getcwd()):

    if '\.git' in path: continue
    if '\.git' in subdirs: continue
    if '\.vs' in path: continue
    if '\.vs' in subdirs: continue
    if '\Debug' in path: continue
    if '\Debug' in subdirs: continue
    if '\tools' in path: continue
    if '\tools' in subdirs: continue
    if '\libraries' in path: continue
    if '\libraries' in subdirs: continue

    print(path)
	
    for name in files:
        if name.split('.')[-1] in ext:
            j = len(open(os.path.join(path, name), 'rb').readlines())
            lines += j
        
print(lines, 'lines')
print('Windows 3.1 is', round(2500000 / lines, 2), 'times larger.')
print('Windows 95 is', round(15000000 / lines, 2), 'times larger.')
input()
