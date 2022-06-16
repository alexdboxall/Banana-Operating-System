fileList = ['disasm.lst', 'disacpica.txt', 'disclipdraw.txt', 'dissys.txt', 'disvesa.txt', 'disvga.txt', 'dislegacy.txt']
driverList = ['', 'acpica', 'clipdraw', 'system', 'vesa', 'vga', 'legacy']


lines = open('C:/Users/Alex/Desktop/banana-os/log3.txt').read().split('\n')

def getDriverBaseAddr(name):
    global lines
    for line in lines:
        try:
            if line.startswith('@<<: '):
                filepath = line.split(' ')[1].split('/')[-1].split('.')[0].strip()
                if filepath == name:
                    return int(line.split(' ')[2], 16)
        except Exception as e:
            print(e)
            pass
        
    return 0
    
addrLookupMap = dict()
funcName = ''

print('Building function map...')

for i, j in zip(fileList, driverList):
    additionalAddr = 0x0

    if i != 'disasm.lst':
        additionalAddr = getDriverBaseAddr(i.split('.')[0].split('dis')[1]) - 0x10000000
        if additionalAddr == -0x10000000:
            continue
    
    disasm = open('C:/Users/Alex/Desktop/Banana/disasms/' + i).readlines()
    for line in disasm:
        try:
            addr = int(line[0:8], 16)
            
            if line[8] == ' ':
                funcName = line.split('<')[1].split('>')[0]

            addrLookupMap[addr + additionalAddr] = funcName
            
        except Exception as e:
            pass

        
print('Scanning logs...')
        
counterDict = dict()

totalLines = len(lines)
currentLine = 0
prevPercent = 0

for line in lines:
    percentComplete = currentLine / totalLines * 100
    if int(percentComplete) != int(prevPercent):
        prevPercent = percentComplete
        print('{:.1f}% complete'.format(prevPercent))
        
    if line.startswith('@:> '):
        try:
            addr = int(line.split(' ')[1], 16)
            funcName = addrLookupMap[addr]
                    
            if funcName in counterDict:
                counterDict[funcName] += 1
            else:
                counterDict[funcName] = 1
                
            prevAddr = addr
            
        except:
            pass
        
    currentLine += 1

print('100% complete')
print('Sorting {} items...'.format(len(counterDict)))
sortedDict = sorted(counterDict.items(), key=lambda kv: kv[1], reverse=True)

for k, v in sortedDict:
    print('{:9d}  '.format(v) + k)

input()
