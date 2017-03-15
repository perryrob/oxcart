
import glob
import os

def file_ext_cmp(x,y):
    try:
        return int(int(y.split('.')[1]) - int(x.split('.')[1]))
    except:
        return 1

PATH='/tmp'

input_file = os.path.join(PATH,'mag_cal.txt')

OUTPUT = '/tmp/output.txt'

x_min = -1464
x_max = -1464
y_min = 441
y_max = 441
z_min = 16210
z_max = 16210


with open( input_file, 'r' ) as inf:
    for line in inf:
        line = line.split(' ')
        if int( line[0].strip() ) < x_min:
            x_min = int( line[0].strip() )
        if int( line[0].strip() ) > x_max:
            x_max = int( line[0].strip() )
        if int( line[1].strip() ) < y_min:
            y_min = int( line[1].strip() )
        if int( line[1].strip() ) > y_max:
            y_max = int( line[1].strip() )
        if int( line[2].strip() ) < z_min:
            z_min = int( line[2].strip() )
        if int( line[2].strip() ) > z_max:
            z_max = int( line[2].strip() )

x_hard = ((x_max-x_min) / 2.0) - x_max
y_hard = ((y_max-y_min) / 2.0) - y_max
z_hard = ((z_max-z_min) / 2.0) - z_max

print x_min,x_max,y_min,y_max,z_min,z_max,x_hard,y_hard,z_hard


with open( OUTPUT, 'w') as outf:
    with open( input_file, 'r' ) as inf:
        for line in inf:
            line = line.split(' ')
            outf.write( '%g %g %g\n' %  (float( line[0].strip() ) + x_hard,
                                       float( line[1].strip() ) + y_hard,
                                       float( line[2].strip() ) + z_hard))
                
        
        
