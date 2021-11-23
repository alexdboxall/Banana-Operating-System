import os

os.chdir('D:/Users/Alex/Desktop/Banana/packages')
directory = '.'
for filename in os.listdir(directory):
    if not filename.endswith('.py') and not filename.endswith('.cab'):
        try: os.unlink('{}.cab'.format(filename))
        except: pass

        '''x = 'tar --format ustar -cvf {}.pkg -C {} .'.format(filename, filename)
        os.system(x)'''

        x = 'python mkcab.py {}'.format(filename)
        os.system(x)
        