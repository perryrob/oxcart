//===============================================================================
// MadgwickAHRS.h
//===============================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/open-source-imu-and-ahrs-algorithms/
//
// From the x-io website "Open-source resources available on this website are
// provided under the GNU General Public Licence unless an alternative licence
// is provided in source."
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
// 01/31/2017   perryr          integrated into oxcart
//
//===============================================================================
#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h
#include <math.h>
#include "oxalgo.h"
#include <stdint.h>
//-------------------------------------------------------------------------------
// Variable declaration
class Madgwick : public OxAlgo {
private:
    double beta;				// algorithm gain
    double q[4];
    double deltat;
    double roll;
    double pitch;
    double yaw;
    double gps_roll;
    uint64_t current_time;
    uint64_t last_time;
//-------------------------------------------------------------------------------
// Function declarations
public:
    Madgwick();
    void begin(uint64_t now_ms);
    void update(double ax, double ay, double az,
                double gx, double gy, double gz,
                double mx, double my, double mz,
                double gps_turn_rate=0.0, double TAS=0.0);
    
    double getRoll() { return roll;}
    double getGPSRoll() { return gps_roll;}
    double getPitch() {return pitch;}
    double getYaw() {return yaw; }
    void run_algo();
};
#endif
