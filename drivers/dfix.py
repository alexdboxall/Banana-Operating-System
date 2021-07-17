import sys
import re
import random

nextStr = 0
def fix(filename):
    global nextStr
    
    data = open(filename, 'r').read().replace('extern "C"', 'extern^^^C')

    if ('    "' in data and ('static' in data or '[]' in data)) or '\t"' in data or '{"' in data:
        print('***', filename)
                
    pattern = re.compile(r'"[^"\\]*(?:\\.[^"\\]*)*"', re.S)

    definitions = ''

    data = re.sub(r'"\n\s*"', '', data, 0, re.S)

    matches = re.findall(pattern, data)
    if matches:
        for match in matches:
            dummy = '~~~~~~~'
            includetest = data.replace(match, dummy)
            if str('#include' + dummy) in includetest:
                continue
            if str('#include ' + dummy) in includetest:
                continue
            if str('#include  ' + dummy) in includetest:
                continue
            if str('#include   ' + dummy) in includetest:
                continue
            if str('#include    ' + dummy) in includetest:
                continue
            if str('#include\t' + dummy) in includetest:
                continue
            if str('#include\t ' + dummy) in includetest:
                continue
            if str('#include \t' + dummy) in includetest:
                continue

            if str('@' + dummy) in includetest:
                data = data.replace('@' + match, match)
                continue

            try:
                if 'ACPI_MODULE_NAME' in data[data.index(match) - 30 : data.index(match)]:
                    continue
            except:
                pass
            
            name = '_STR{}_{}{}'.format(hex(random.randint(0, 65536))[2:].upper(), hex(nextStr)[2:].upper(), filename.replace('.', '').upper()[0:3])
            definitions += 'char {}[] = {};\n'.format(name, match.replace('\n', '\\\n'))
            nextStr += 1
            
            data = data.replace(match, name)

    data = definitions + '\n' + data

    if (' static' in data or '\tstatic' in data) and '//STATIC OKAY' not in data:
        data = '#error STATIC' + '\n' + data

    data = data.replace('\nstatic ', '\n')

    data = data.replace('extern^^^C', 'extern "C"')

    if '//MAIN SCRIPT' in data:
        data = '''void begin(void* a);
void start(void* a)
{
	begin(a);
}
''' + data
        
    open(filename + 'x', 'w').write(data)
    
argv = sys.argv[1:]

for arg in argv:
    fix(arg)
