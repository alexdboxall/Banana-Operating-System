#don't ask me why I made this program

import os
lines = 0
ext = ['c', 'h', 'cpp', 'hpp', 'asm', 's', 'py', 'bat', 'Makefile']

for path, subdirs, files in os.walk(os.getcwd()):
    if '\\mlibc-master' in path or '\\mlibc-master' in subdirs:
        pass
    elif '\\libgui' in path or '\\libgui' in subdirs:
        pass
    else:
        if '\\.git' in path: continue
        if '\\.git' in subdirs: continue
        if '\\.vs' in path: continue
        if '\\.vs' in subdirs: continue
        if '\\Debug' in path: continue
        if '\\Debug' in subdirs: continue
        if '\\tools' in path: continue
        if '\\tools' in subdirs: continue
        if '\\other' in path: continue
        if '\\other' in subdirs: continue
        if '\\libraries' in path: continue
        if '\\libraries' in subdirs: continue

    #print(path)
	
    for name in files:
        if name.split('.')[-1] in ext:
            n = os.path.join(path, name)
            if '\\libraries' in n:
                continue
            print(n)
            j = len(open(n, 'rb').readlines())
            lines += j
        
print(lines, 'lines')
print('Windows 3.1 is', round(2500000 / lines, 2), 'times larger.')
print('Windows 95 is', round(15000000 / lines, 2), 'times larger.')
print('Windows XP is', round(45000000 / lines, 2), 'times larger.')
input()
