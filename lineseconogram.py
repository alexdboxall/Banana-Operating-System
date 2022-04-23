#don't ask me why I made this program

import os
lines = 0
ext = ['java']

for path, subdirs, files in os.walk('C:/Users/Alex/git/repoecono/Econogram/src'):
    if '\\mlibc-master' in path or '\\mlibc-master' in subdirs:
        pass
    elif '\\libgui' in path or '\\libgui' in subdirs:
        pass
    else:
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
            print(n)
            j = len(open(n, 'rb').readlines())
            lines += j
        
print(lines, 'lines')
input()
