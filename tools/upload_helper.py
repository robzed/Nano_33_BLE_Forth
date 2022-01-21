#!

import serial
import time
import sys

filenames = [ "../blocks.fth", "../blocks_test.fth" ]
#filenames = [ "../blocks_test.fth" ]

def write_chars(ser, data):
    for value in data:
        c = bytes([value])
        ser.write(c)
        if value != 10 and value != 13:
            rx = ser.read(1)
            if rx != c:
                print("Fail", rx, c)
                sys.exit(1)

def parse_line(ser, lineout):
    #ser.write(bytes(lineout, 'utf8'))
    write_chars(ser, bytes(lineout, 'utf8'))
    time.sleep(0.1)
    waiting = ser.in_waiting
    #print(waiting)
    data = ser.read(waiting);
    data_decoded = data.decode('utf8')
    data = data_decoded.strip()
    slineout = lineout.strip()
    # We should get one of the following:
    #  - 'ok' then a stack diagram ... this is fine
    #  - nothing (part way through a definition)
    #  - an error ... we should abort
    
    #if not data.startswith(slineout):
    #    print("Wrong or no echo")
    #    return False
    
    #data = data[len(slineout):].strip()
    status = True
    if data.startswith('ok'):
        #time.sleep(0.05)
        #data = ser.readline().decode('utf8').strip()
        #print("RXstack ", data)
        #if data != 'Stack<10>':
        #    print('unexpected stackdata');
        #    return False
        rx_status = "ok"
    elif data == '':
        # accept no OK and no error (timeout condition
        rx_status = ".."
    else:
        print("unexpected", repr(data))
        rx_status = "??"
        status = False

    print("  RX %s " % rx_status, repr(data_decoded),"     ")

    return status

# picocom --baud 115200 --imap lfcrlf /dev/cu.usbmodem1421201
def main():
    ser = serial.Serial(port = '/dev/cu.usbmodem1421201', baudrate=115200)
    ser.inter_byte_timeout = 0.02
    ser.timeout = 1
    print("Opened by", ser.name)
#    while True:
#        data = ser.read()
#        print(data)
    success = parse_line(ser, "\n")
    if success: success = parse_line(ser, "\n")
    
    for filename in filenames:
        print("---------------------------------")
        print("   LOAD ", filename)
        print("---------------------------------")

        f = open(filename, 'r')
        line_count = 1
        for line in f:
            sline = line.strip()
            #print(line)
            if sline == '' or sline.startswith('\\'):
                if sline != '':
                    print('   Skip ', line.rstrip())
            else:
                # last line might not contain a Newline, so add
                if not line.endswith('\n'):
                    line = line + '\n'
                print('TX %4d ' % line_count, repr(line))
                success = parse_line(ser, line)
                if not success:
                    break
                #if line_count == 20:
                #    break
            line_count += 1
        f.close()
        if not success:
            break
        
    print("---------------------------------")
    if success:
        print("Finished Succesfully")
    else:
        print("Finished with Failure")
    ser.close() 



main()
