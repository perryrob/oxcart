//=============================================================================================
// MadgwickAHRS.c
//=============================================================================================
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
// 19/02/2012	SOH Madgwick	Magnetometer measurement is normalised
// 01/31/2017   perryr          integrated into oxcart
//
//===============================================================================

//-------------------------------------------------------------------------------
// Header files
#include "constants.h"
#include "oxapp.h"
#include "algo/MadgwickAHRS.h"
#include <math.h>

//------------------------------------------------------------------------------
// Definitions

#define GyroMeasError M_PI * (15.0f / 180.0f)
#define beta sqrt(3.0f / 4.0f) * GyroMeasError   // compute beta

//==============================================================================
// Functions

//------------------------------------------------------------------------------
// AHRS algorithm update
// Preferred rate is 100 Hz
Madgwick::Madgwick() : OxAlgo("Madgwick",10) {
  reset();
}
void Madgwick::reset() {
	q[0] = 1.0f;
	q[1] = 0.0f;
	q[2] = 0.0f;
	q[3] = 0.0f;
	deltat = 0;
    last_time = 0;
}
void Madgwick::begin( uint64_t now_ms ) {
  deltat = (now_ms - last_time) * 0.001;
  current_time = now_ms;
  last_time = current_time;
}
void Madgwick::update(double ax, double ay, double az, 
                      double gx, double gy, double gz, 
                      double mx, double my, double mz, 
                      double gps_turn_rate, double TAS, 
                      double longitudinal_accel,
                      double pitch_rate)
 {
   // short name local variable for readability
   double q1 = q[0], q2 = q[1], q3 = q[2], q4 = q[3];   
   double norm;
   double hx, hy, _2bx, _2bz;
   double s1, s2, s3, s4;
   double qDot1, qDot2, qDot3, qDot4;
   
   // Auxiliary variables to avoid repeated arithmetic
   double _2q1mx;
   double _2q1my;
   double _2q1mz;
   double _2q2mx;
   double _4bx;
   double _4bz;
   double _2q1 = 2.0f * q1;
   double _2q2 = 2.0f * q2;
   double _2q3 = 2.0f * q3;
   double _2q4 = 2.0f * q4;
   double _2q1q3 = 2.0f * q1 * q3;
   double _2q3q4 = 2.0f * q3 * q4;
   double q1q1 = q1 * q1;
   double q1q2 = q1 * q2;
   double q1q3 = q1 * q3;
   double q1q4 = q1 * q4;
   double q2q2 = q2 * q2;
   double q2q3 = q2 * q3;
   double q2q4 = q2 * q4;
   double q3q3 = q3 * q3;
   double q3q4 = q3 * q4;
   double q4q4 = q4 * q4;
   double rad_a = gps_turn_rate * TAS;

   gps_roll = atan( rad_a / SI_GRAVITY ) * RAD_DEG;

   ax -= longitudinal_accel;
   ay += rad_a;
   if (fabs(az) != 0.0) {
     az = az/fabs(az) * SI_GRAVITY;
   }
   az += pitch_rate * TAS;

   // Normalise accelerometer measurement
   norm = sqrt(ax * ax + ay * ay + az * az);
   if (norm == 0.0f) return; // handle NaN
   norm = 1.0f/norm;
   ax *= norm;
   ay *= norm;
   az *= norm;
   
   // Normalise magnetometer measurement
   norm = sqrt(mx * mx + my * my + mz * mz);
   if (norm == 0.0f) return; // handle NaN
   norm = 1.0f/norm;
   mx *= norm;
   my *= norm;
   mz *= norm;
   
   // Reference direction of Earth's magnetic field
   _2q1mx = 2.0f * q1 * mx;
   _2q1my = 2.0f * q1 * my;
   _2q1mz = 2.0f * q1 * mz;
   _2q2mx = 2.0f * q2 * mx;
   hx = mx * q1q1 - _2q1my * q4 + _2q1mz * q3 + mx * q2q2 + _2q2 * my * q3 + _2q2 * mz * q4 - mx * q3q3 - mx * q4q4;
   hy = _2q1mx * q4 + my * q1q1 - _2q1mz * q2 + _2q2mx * q3 - my * q2q2 + my * q3q3 + _2q3 * mz * q4 - my * q4q4;
   _2bx = sqrt(hx * hx + hy * hy);
   _2bz = -_2q1mx * q3 + _2q1my * q2 + mz * q1q1 + _2q2mx * q4 - mz * q2q2 + _2q3 * my * q4 - mz * q3q3 + mz * q4q4;
   _4bx = 2.0f * _2bx;
   _4bz = 2.0f * _2bz;
   
   // Gradient decent algorithm corrective step
   s1 = -_2q3 * (2.0f * q2q4 - _2q1q3 - ax) + _2q2 * (2.0f * q1q2 + _2q3q4 - ay) - _2bz * q3 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q4 + _2bz * q2) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q3 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
   s2 = _2q4 * (2.0f * q2q4 - _2q1q3 - ax) + _2q1 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q2 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + _2bz * q4 * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q3 + _2bz * q1) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q4 - _4bz * q2) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
   s3 = -_2q1 * (2.0f * q2q4 - _2q1q3 - ax) + _2q4 * (2.0f * q1q2 + _2q3q4 - ay) - 4.0f * q3 * (1.0f - 2.0f * q2q2 - 2.0f * q3q3 - az) + (-_4bx * q3 - _2bz * q1) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (_2bx * q2 + _2bz * q4) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + (_2bx * q1 - _4bz * q3) * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
   s4 = _2q2 * (2.0f * q2q4 - _2q1q3 - ax) + _2q3 * (2.0f * q1q2 + _2q3q4 - ay) + (-_4bx * q4 + _2bz * q2) * (_2bx * (0.5f - q3q3 - q4q4) + _2bz * (q2q4 - q1q3) - mx) + (-_2bx * q1 + _2bz * q3) * (_2bx * (q2q3 - q1q4) + _2bz * (q1q2 + q3q4) - my) + _2bx * q2 * (_2bx * (q1q3 + q2q4) + _2bz * (0.5f - q2q2 - q3q3) - mz);
   norm = sqrt(s1 * s1 + s2 * s2 + s3 * s3 + s4 * s4);    // normalise step magnitude
   norm = 1.0f/norm;
   s1 *= norm;
   s2 *= norm;
   s3 *= norm;
   s4 *= norm;
   
   // Compute rate of change of quaternion
   qDot1 = 0.5f * (-q2 * gx - q3 * gy - q4 * gz) - beta * s1;
   qDot2 = 0.5f * (q1 * gx + q3 * gz - q4 * gy) - beta * s2;
   qDot3 = 0.5f * (q1 * gy - q2 * gz + q4 * gx) - beta * s3;
   qDot4 = 0.5f * (q1 * gz + q2 * gy - q3 * gx) - beta * s4;
   
   // Integrate to yield quaternion
   q1 += qDot1 * deltat;
   q2 += qDot2 * deltat;
   q3 += qDot3 * deltat;
   q4 += qDot4 * deltat;
   norm = sqrt(q1 * q1 + q2 * q2 + q3 * q3 + q4 * q4);    // normalise quaternion
   norm = 1.0f/norm;
   q[0] = q1 * norm;
   q[1] = q2 * norm;
   q[2] = q3 * norm;
   q[3] = q4 * norm;
   
   yaw   = atan2(2.0f * (q[1] * q[2] + q[0] * q[3]), q[0] * q[0] + q[1] * q[1] - q[2] * q[2] - q[3] * q[3]);   
   pitch = -asin(2.0f * (q[1] * q[3] - q[0] * q[2]));
   roll  = atan2(2.0f * (q[0] * q[1] + q[2] * q[3]), q[0] * q[0] - q[1] * q[1] - q[2] * q[2] + q[3] * q[3]);
   
   pitch *= -RAD_DEG;
   yaw   *= RAD_DEG; 
   yaw   -= 10.0; // Approx. Declination at Tucson, AZ
   roll  *= RAD_DEG;
 }
 
void Madgwick::run_algo() {
  begin( OxApp::get_time_ms() );
  update( OxApp::l_accel->get_val(X),
          OxApp::l_accel->get_val(Y),
          OxApp::l_accel->get_val(Z),
          OxApp::l_gyro->get_val(X),
          OxApp::l_gyro->get_val(Y),
          OxApp::l_gyro->get_val(Z),
          OxApp::l_mag->get_val(X),
          OxApp::l_mag->get_val(Y),
          OxApp::l_mag->get_val(Z),
          OxApp::l_gps_fix->get_val(TRACK_CHANGE),
          OxApp::algo_press->get_val(TAS),
          OxApp::algo_misc_rate->get_val(GPS_ACCELERATION)
          );

  OxApp::algo_mad_quat->set_val(A,q[0]);
  OxApp::algo_mad_quat->set_val(B,q[1]);
  OxApp::algo_mad_quat->set_val(C,q[2]);
  OxApp::algo_mad_quat->set_val(D,q[3]);

  OxApp::algo_mad_euler->set_val(ROLL,roll);
  OxApp::algo_mad_euler->set_val(GPS_ROLL,gps_roll);
  OxApp::algo_mad_euler->set_val(PITCH,
         pitch + OxApp::manual_double_vals->get_val(PITCH_ADJUSTMENT));
  OxApp::algo_mad_euler->set_val(YAW,yaw);
}
