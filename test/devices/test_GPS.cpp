
#include "oxGPSDbus.h"
#include "devices/GPS.h"
#include <iostream>
#include <cassert>

using namespace std;

static void libgps_dump_state(struct gps_data_t *collect)
{
    if (collect->set & ONLINE_SET)
	(void)fprintf(stdout, "ONLINE: %lf\n", collect->online);
    if (collect->set & TIME_SET)
	(void)fprintf(stdout, "TIME: %lf\n", collect->fix.time);
    if (collect->set & LATLON_SET)
	(void)fprintf(stdout, "LATLON: lat/lon: %lf %lf\n",
		      collect->fix.latitude, collect->fix.longitude);
    if (collect->set & ALTITUDE_SET)
	(void)fprintf(stdout, "ALTITUDE: altitude: %lf  U: climb: %lf\n",
		      collect->fix.altitude, collect->fix.climb);
    if (collect->set & SPEED_SET)
	(void)fprintf(stdout, "SPEED: %lf\n", collect->fix.speed);
    if (collect->set & TRACK_SET)
	(void)fprintf(stdout, "TRACK: track: %lf\n", collect->fix.track);
    if (collect->set & CLIMB_SET)
	(void)fprintf(stdout, "CLIMB: climb: %lf\n", collect->fix.climb);
    if (collect->set & STATUS_SET)
	(void)fprintf(stdout, "STATUS: status: %d\n", collect->status);
    if (collect->set & MODE_SET)
	(void)fprintf(stdout, "MODE: mode: %d\n", collect->fix.mode);
    if (collect->set & DOP_SET)
	(void)fprintf(stdout,
		      "DOP: satellites %d, pdop=%lf, hdop=%lf, vdop=%lf\n",
		      collect->satellites_used, collect->dop.pdop,
		      collect->dop.hdop, collect->dop.vdop);
    if (collect->set & VERSION_SET)
	(void)fprintf(stdout, "VERSION: release=%s rev=%s proto=%d.%d\n",
		      collect->version.release,
		      collect->version.rev,
		      collect->version.proto_major,
		      collect->version.proto_minor);
    if (collect->set & POLICY_SET)
	(void)fprintf(stdout,
		      "POLICY: watcher=%s nmea=%s raw=%d scaled=%s timing=%s, devpath=%s\n",
		      collect->policy.watcher ? "true" : "false",
		      collect->policy.nmea ? "true" : "false",
		      collect->policy.raw,
		      collect->policy.scaled ? "true" : "false",
		      collect->policy.timing ? "true" : "false",
		      collect->policy.devpath);
    if (collect->set & SATELLITE_SET) {
	int i;

	(void)fprintf(stdout, "SKY: satellites in view: %d\n",
		      collect->satellites_visible);
	for (i = 0; i < collect->satellites_visible; i++) {
	    (void)fprintf(stdout, "    %2.2d: %2.2d %3.3d %3.0f %c\n",
			  collect->skyview[i].PRN,
			  collect->skyview[i].elevation,
			  collect->skyview[i].azimuth,
			  collect->skyview[i].ss,
			  collect->skyview[i].used ? 'Y' : 'N');
	}
    }
    if (collect->set & DEVICE_SET)
	(void)fprintf(stdout, "DEVICE: Device is '%s', driver is '%s'\n",
		      collect->dev.path, collect->dev.driver);

    if (collect->set & DEVICELIST_SET) {
	int i;
	(void)fprintf(stdout, "DEVICELIST:%d devices:\n",
		      collect->devices.ndevices);
	for (i = 0; i < collect->devices.ndevices; i++) {
	    (void)fprintf(stdout, "%d: path='%s' driver='%s'\n",
			  collect->devices.ndevices,
			  collect->devices.list[i].path,
			  collect->devices.list[i].driver);
	}
    }
}


int main(int argc, char *argv[] ) {

  OxGPSDbus bus;
  GPS gps;

  bus.add_device( &gps );

  bus.run();
  b::this_thread::sleep(b::posix_time::milliseconds(1000));
  bus.stop();

  libgps_dump_state( gps.get_data() );

  return 0;
}
