
# THIS NEEDS TO KEEP THE ORIGINAL BPB

data = open('D:/Users/Alex/Desktop/banana-os/newimage.img', 'rb').read().decode('latin-1')
notboot = data[512:]

# skip 11 bytes, 3 for the jump, 8 for the OEM name
bpb = data[3+8:0x047]
print(ord(bpb[28-3-8]))
bpb = bpb[:28-3-8] + chr(0) + bpb[29-3-8:]
print(ord(bpb[28-3-8]))
#in this case we aren't using partitioning so set hidden sectors to zero
#(the installer will set this for us when you partition on install)


boot = open('D:/Users/Alex/Desktop/Banana/kernel/STAGE1.BIN', 'rb').read().decode('latin-1') #+=

# 11 bytes, 3 for the jump, 8 for the OEM name
jumper = boot[0] + boot[1] + boot[2] + boot[3] + boot[4] + boot[5] + boot[6] + boot[7] + boot[8] + boot[9] + boot[10]

print("It should be", len(boot + notboot), "bytes long.")
print("And it is   ", len(jumper + bpb + boot[0x047:] + notboot), "bytes long.")

data = jumper + str(bpb) + boot[0x047:] + notboot
data = data[:0x34] + "FIRMWARELIB " + data[0x40:]
data = data[:0x42] + chr(0x28) + data[0x43:]

#open('E:/OS/Boot/banana.flp', 'wb').write(data.encode('latin-1'))
open('D:/Users/Alex/Desktop/banana-os/newimage.img', 'wb').write(data.encode('latin-1'))
