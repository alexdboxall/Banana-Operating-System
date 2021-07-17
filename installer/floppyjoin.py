
data = open('DISK1.IMG', 'rb').read().decode('latin-1')

notboot = data[512:]
boot = open('Floppy/FBOOTSEC.BIN', 'rb').read().decode('latin-1')

out = boot + notboot

open('DISK1.IMG', 'wb').write(out.encode('latin-1'))



for i in range(1, 9):
    data = open('DISK{}.IMG'.format(i + 1), 'rb').read().decode('latin-1')
    data = data[:511] + chr(i + 1) + data[512:]
    open('DISK{}.IMG'.format(i + 1), 'wb').write(data.encode('latin-1'))
