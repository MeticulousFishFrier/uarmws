#to send a file of gcode to the printer
from printrun.printcore import printcore
from printrun import gcoder
import time
#gcodeFileName = '/home/xueyelin/Thermite_Boom_Boom/Code/Examples/test2Offset.gcode'
gcodeFileName = '/home/xueyelin/Thermite_Boom_Boom/Code/ROS/uarmws/src/swiftpro/python_test/test.gcode'

p=printcore('/dev/ttyACM1',115200) # or p.printcore('COM3',115200) on Windows
time.sleep(1)
gcode=[i.strip() for i in open(gcodeFileName)] # or pass in your own array of gcode lines instead of reading from a file
gcode = gcoder.LightGCode(gcode)
p.startprint(gcode) # this will start a print

while(p.printing is True):
    print(p.sent[-1])
    #p.disconnect()