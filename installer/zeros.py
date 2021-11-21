f = open('C:/Users/Alex/Desktop/banana-os/basicimage.img', 'rb').read().decode('latin-1')
out = open('Floppy/ZEROS.SYS', 'wb')

CHUNK_SIZE = 512
sectors = map(''.join, zip(*[iter(f)]*CHUNK_SIZE))
print('Must be an exact int:', (2600 * 512) / CHUNK_SIZE)

tru = 0
fal = 0

byte = 0

disknum = 1
written = 0
compressedImage = open('Floppy/DATA{}.BIN'.format(disknum), 'wb')

filled = ''

i = 0
dummysector = ''
for s in sectors:
    dummysector = s
    z = all(ord(v) == 0 for v in s)
    i += 1
    if z: tru += 1
    else: fal += 1

    if not z:
        filled += hex(i) + '\n'
        compressedImage.write(s.encode('latin-1'))
        written += 1
        if written == (2600 * 512) / CHUNK_SIZE:
            written = 0
            compressedImage.close()
            disknum += 1
            compressedImage = open('Floppy/DATA{}.BIN'.format(disknum), 'wb')

    byte <<= 1
    byte |= z

    if i & 7 == 0:
        out.write(chr(byte).encode('latin-1'))
        byte = 0

print('TOTAL', i)
print('BLANK', tru)
print('FILLD', fal)

print('% BNK', round(tru * 100 / i))

#just to be safe, write some zeros (this means non-zero sectors)
'''for i in range(100):
    out.write(chr(0).encode('latin-1'))
'''

for i in range((16 - (16 * 512 // CHUNK_SIZE)) * 1024):
    out.write(chr(0).encode('latin-1'))

out.close()

while written < (2600 * 512) / CHUNK_SIZE:
    written += 1
    compressedImage.write(s.encode('latin-1'))

#512 -> 16 * 512
#1024 -> 8 * 512
#2048 -> 4 * 512

    
compressedImage.close()

open('filled.txt', 'w').write(filled)
