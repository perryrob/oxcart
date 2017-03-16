
from math import *

M_PI = pi
VARIATION = 10.0 * M_PI / 180.0

method=0

for c_yaw in range(0,360,4):
    ############################################################
    # Simulate sensor readings
    rad_yaw = -float(c_yaw) * M_PI / 180.0
    if rad_yaw > -M_PI: pass    
    if rad_yaw < -M_PI:
        rad_yaw = rad_yaw + 2.0 * M_PI 
    yaw = rad_yaw
    # End sensor sim.
    ############################################################
    # 0 - 180
    if yaw < 0 and yaw >= -M_PI:
        yaw = -1.0 * yaw
    # 180 - 360
    elif yaw <= M_PI:
        yaw = 2.0 * M_PI - yaw
    # okay above here
    ############################################################

    tmp_yaw = yaw + VARIATION

    if tmp_yaw < 0 :
        yaw = 2.0 * pi + tmp_yaw
    elif tmp_yaw > 0:
        if tmp_yaw > 2.0 * pi:
            yaw = tmp_yaw - 2.0 * pi
        else:
            yaw = tmp_yaw
            
    yaw *= 180.0 / M_PI;
    print c_yaw,rad_yaw,yaw
