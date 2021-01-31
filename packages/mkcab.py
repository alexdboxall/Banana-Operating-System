import os
import zlib
import sys

def scanFolder(folder):
    # 0xFF = go up 1 level
    # 0xFE = go up 2 levels
    # 0xFD = go up 4 levels
    # 0xFC = go up 8 levels
    # 0xFB = create file
    # 0x00 = end
    
    out = ''
    for file in os.listdir(folder):
        isDir = False
        path = '{}/{}'.format(folder, file)
        try:
            os.listdir(path)
            isDir = True
        except:
            pass

        if isDir:
            out += '{}{}'.format(chr(len(file)), file)
            out += scanFolder(path)
        else:
            fileheader = [chr(0xFB)]
            fileheader.append(chr(len(file) & 0xFF))

            for c in file:
                fileheader.append(c)

            data = open(path, 'rb').read().decode('latin-1')
            compressedData = zlib.compress(data.encode('latin-1'), level=9).decode('latin-1')

            compress = len(compressedData) < len(data)
            
            if compress:
                data = compressedData

            length = len(data)

            fileheader.append(chr((length >> 0) & 0xFF))
            fileheader.append(chr((length >> 8) & 0xFF))
            fileheader.append(chr((length >> 16) & 0xFF))

            checksum = ord('N') << 16 | ord('Y') << 8 | ord('I') 
            for c in data:
                i = ord(c)
                checksum = (checksum + i) & 0xFFFFFF

            
            hidden = False
            system = False
            readonly = False
            highlength = (length >> 24) & 0xF
            fileheader.append(chr(highlength |
                              (0x10 if hidden   else 0x00) |
                              (0x20 if system   else 0x00) |
                              (0x40 if readonly else 0x00) |
                              (0x80 if compress else 0x00)))

            fileheader.append(chr((checksum >> 0) & 0xFF))
            fileheader.append(chr((checksum >> 8) & 0xFF))
            fileheader.append(chr((checksum >> 16) & 0xFF))

            checksum2 = 0
            for c in fileheader:
                i = ord(c)
                checksum2 = (checksum2 + i) & 0xFF

            fileheader.append(chr(checksum2))

            print('Compressing' if compress else 'Not compressing')

            out += ''.join(fileheader)
            out += data
            
            
    return out + chr(0xFF)
            
def makeCab(folder):
    data = scanFolder(folder)
    data += chr(0x00)

    checksum = 0x1234
    out = 'BCAB' + chr(0x00) + chr(checksum & 0xFF) + chr(checksum >> 8)
    out += data
    
    open('{}.cab'.format(folder), 'wb').write(out.encode('latin-1'))

makeCab(sys.argv[1])
