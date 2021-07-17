from shutil import copyfile

array = [
    ['Banana/System/VGASET.COM', 'VGASET.COM'],
    ['Banana/System/VESASET.COM', 'VESASET.COM'],
	['Banana/System/EDID.COM', 'EDID.COM'],
	['Banana/System/APM.COM', 'APM.COM'],
    ['Banana/System/firsttme.exe', 'firsttme.exe'],
    ['Banana/System/shell.exe', 'shell.exe'],
    ['Banana/System/vgachrlk.bin', 'vgachrlk.bin'],
    ['Banana/System/vgafont.bin', 'vgafont.bin'],
    ['Banana/System/BOOTSET.CFG', 'BOOTSET.CFG'],
    ['Banana/System/DRVPCI.SYS', 'DRVPCI.SYS'],
    ['Banana/System/DRVPCIV.SYS', 'DRVPCIV.SYS'],
    ['../COPYRIGHT', 'COPYRIGH.T'],
    ['../LICENSE', 'LICENSE'],
	    
    ['Banana/Applications/System/cmd.exe', 'cmd.exe'],
    ['Banana/Applications/System/te.exe', 'te.exe'],
    ['Banana/Applications/System/tree.exe', 'tree.exe'],
    ['Banana/Applications/System/about.exe', 'about.exe'],
    ['Banana/Applications/System/taskmgr.exe', 'taskmgr.exe'],
    ['Banana/Applications/System/control.exe', 'control.exe'],
    ['Banana/Applications/System/print.exe', 'print.exe'],

    ['Banana/Drivers/isa.sys', 'isa.sys'],
    ['Banana/Drivers/parallel.sys', 'parallel.sys'],
    ['Banana/Drivers/serial.sys', 'serial.sys'],
    ['Banana/Drivers/vga.sys', 'vga.sys'],
    ['Banana/Drivers/vesa.sys', 'vesa.sys'],
    ['Banana/Drivers/floppy.sys', 'floppy.sys'],
    ['Banana/Drivers/sb16.sys', 'sb16.sys'],

    ['Banana/Fonts/Basic/SYSTEM.FNT', 'SYSTEM.FNT'],
]

x = open('D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/COREBKUP.SYS', 'w')
x.write('C:/Banana/System/COREBKUP.SYS' + '\n')
x.write('COREBKUP.SYS' + '\n')

x.write('C:/Banana/BANANABT' + '\n')
x.write('BANANABT' + '\n')
x.write('C:/Banana/System/KERNEL32.EXE' + '\n')
x.write('KERNEL32.EXE' + '\n')
x.write('C:/Banana/System/KERNEL64.EXE' + '\n')
x.write('KERNEL64.EXE' + '\n')
x.write('C:/Banana/FIRMWARE.LIB' + '\n')
x.write('FIRMWARE.LIB' + '\n')
x.write('C:/Banana/System/tramp.exe' + '\n')
x.write('tramp.exe' + '\n')

for name, bkup in array:
    print(name, bkup)
    copyfile('D:/Users/Alex/Desktop/Banana/sysroot/{}'.format(name), 'D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/Core File Backups/{}'.format(bkup))
    x.write('C:/{}\n{}\n'.format(name, bkup))

x.close()

copyfile('T:/Banana/BANANABT', \
         'D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/Core File Backups/BANANABT')

copyfile('T:/Banana/System/KERNEL32.EXE', \
         'D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/Core File Backups/KERNEL32.EXE')

copyfile('T:/Banana/System/KERNEL64.EXE', \
         'D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/Core File Backups/KERNEL64.EXE')

copyfile('T:/Banana/System/tramp.exe', \
         'D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/Core File Backups/tramp.exe')

copyfile('T:/Banana/FIRMWARE.LIB', \
         'D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/Core File Backups/FIRMWARE.LIB')

copyfile('D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/COREBKUP.SYS', \
         'D:/Users/Alex/Desktop/Banana/sysroot/Banana/System/Core File Backups/COREBKUP.SYS')
    
