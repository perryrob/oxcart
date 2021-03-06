/* gpsd_config.h.  Generated by scons, do not hand-hack.  */

#ifndef GPSD_CONFIG_H

#define VERSION "3.17~dev"

#define GPSD_URL "http://catb.org/gpsd"

/* #undef HAVE_LIBUSB */

#define HAVE_LIBRT 1

/* #undef HAVE_DBUS */

/* #undef ENABLE_BLUEZ */

#define HAVE_LINUX_CAN_H 1

#define HAVE_STDATOMIC_H 1

#define HAVE_BUILTIN_ENDIANNESS 1

/* #undef HAVE_ENDIAN_H */

/* #undef HAVE_SYS_ENDIAN_H */

#define HAVE_DAEMON 1

/* #undef HAVE_STRLCPY */

/* #undef HAVE_STRLCAT */

#define HAVE_CLOCK_GETTIME 1

#define HAVE_STRPTIME 1

#define HAVE_GMTIME_R 1

/* AIVDM support */
/* #undef AIVDM_ENABLE */

/* Ashtech support */
/* #undef ASHTECH_ENABLE */

/* application binaries directory */
#define BINDIR "bin"

/* BlueZ support for Bluetooth devices */
/* #undef BLUEZ_ENABLE */

/* client debugging support */
/* #undef CLIENTDEBUG_ENABLE */

/* control socket for hotplug notifications */
/* #undef CONTROL_SOCKET_ENABLE */

/* allow gpsctl/gpsmon to change device settings */
/* #undef CONTROLSEND_ENABLE */

/* build with code coveraging enabled */
/* #undef COVERAGING_ENABLE */

/* enable DBUS export support */
/* #undef DBUS_EXPORT_ENABLE */

/* include debug information in build */
/* #undef DEBUG_ENABLE */

/* documents directory */
#define DOCDIR "share/doc"

/* DeLorme EarthMate Zodiac support */
/* #undef EARTHMATE_ENABLE */

/* EverMore binary support */
/* #undef EVERMORE_ENABLE */

/* fixed serial port speed */
/* #undef FIXED_PORT_SPEED */

/* fixed serial port stop bits */
/* #undef FIXED_STOP_BITS */

/* force daemon to listen on all addressses */
/* #undef FORCE_GLOBAL_ENABLE */

/* Jackson Labs Fury and Firefly support */
/* #undef FURY_ENABLE */

/* San Jose Navigation FV-18 support */
/* #undef FV18_ENABLE */

/* Garmin kernel driver support */
/* #undef GARMIN_ENABLE */

/* Garmin Simple Text support */
/* #undef GARMINTXT_ENABLE */

/* Geostar Protocol support */
/* #undef GEOSTAR_ENABLE */

/* GPSClock support */
/* #undef GPSCLOCK_ENABLE */

/* gpsd itself */
#define GPSD_ENABLE 1

/* privilege revocation group */
#define GPSD_GROUP "dialout"

/* privilege revocation user */
#define GPSD_USER "nobody"

/* gspd client programs */
/* #undef GPSDCLIENTS_ENABLE */

/* implicit linkage is supported in shared libs */
/* #undef IMPLICIT_LINK_ENABLE */

/* header file directory */
#define INCLUDEDIR "include"

/* build IPv6 support */
/* #undef IPV6_ENABLE */

/* Spectratime iSync LNRClok/GRCLOK support */
/* #undef ISYNC_ENABLE */

/* iTrax hardware support */
/* #undef ITRAX_ENABLE */

/* fetch up-to-date data on leap seconds. */
/* #undef LEAPFETCH_ENABLE */

/* system libraries */
#define LIBDIR "lib"

/* build C++ bindings */
/* #undef LIBGPSMM_ENABLE */

/* special Linux PPS hack for Raspberry Pi et al */
#define MAGIC_HAT_ENABLE 1

/* build help in man and HTML formats */
/* #undef MANBUILD_ENABLE */

/* manual pages directory */
#define MANDIR "share/man"

/* maximum allowed clients */
#define MAX_CLIENTS 64

/* maximum allowed devices */
#define MAX_DEVICES 4

/* turn off every option not set on the command line */
/* #undef MINIMAL_ENABLE */

/* MTK-3301 support */
/* #undef MTK3301_ENABLE */

/* Navcom NCT support */
/* #undef NAVCOM_ENABLE */

/* build with ncurses */
#define NCURSES_ENABLE 1

/* build support for handling TCP/IP data sources */
/* #undef NETFEED_ENABLE */

/* NMEA0183 support */
#define NMEA0183_ENABLE 1

/* NMEA2000/CAN support */
/* #undef NMEA2000_ENABLE */

/* float ops are expensive, suppress error estimates */
/* #undef NOFLOATS_ENABLE */

/* don't symbol-strip binaries at link time */
/* #undef NOSTRIP_ENABLE */

/* NTP time hinting support */
#define NTP_ENABLE 1

/* NTP time hinting via shared memory */
#define NTPSHM_ENABLE 1

/* NTRIP support */
/* #undef NTRIP_ENABLE */

/* OceanServer support */
/* #undef OCEANSERVER_ENABLE */

/* Motorola OnCore chipset support */
/* #undef ONCORE_ENABLE */

/* Disciplined oscillator support */
#define OSCILLATOR_ENABLE 1

/* build support for passing through JSON */
/* #undef PASSTHROUGH_ENABLE */

/* pkgconfig file directory */
#define PKGCONFIG "lib/pkgconfig"

/* PPS time syncing support */
#define PPS_ENABLE 1

/* installation directory prefix */
#define PREFIX "/usr/local"

/* build with profiling enabled */
/* #undef PROFILING_ENABLE */

/* build Python support and modules. */
/* #undef PYTHON_ENABLE */

/* coverage command for Python progs */
#define PYTHON_COVERAGE "coverage run"

/* Python module directory prefix */
/* #undef PYTHON_LIBDIR */

/* build QT bindings */
/* #undef QT_ENABLE */

/* version for versioned Qt */
/* #undef QT_VERSIONED */

/* allow gpsd to change device settings */
/* #undef RECONFIGURE_ENABLE */

/* rtcm104v2 support */
/* #undef RTCM104V2_ENABLE */

/* rtcm104v3 support */
/* #undef RTCM104V3_ENABLE */

/* system binaries directory */
#define SBINDIR "sbin"

/* build shared libraries, not static */
/* #undef SHARED_ENABLE */

/* export via shared memory */
#define SHM_EXPORT_ENABLE 1

/* SiRF chipset support */
/* #undef SIRF_ENABLE */

/* Skytraq chipset support */
/* #undef SKYTRAQ_ENABLE */

/* run tests with realistic (slow) delays */
/* #undef SLOW_ENABLE */

/* data export over sockets */
#define SOCKET_EXPORT_ENABLE 1

/* squelch gpsd_log/gpsd_hexdump to save cpu */
/* #undef SQUELCH_ENABLE */

/* Novatel SuperStarII chipset support */
/* #undef SUPERSTAR2_ENABLE */

/* system configuration directory */
#define SYSCONFDIR "etc"

/* cross-development system root */
/* #undef SYSROOT */

/* systemd socket activation */
/* #undef SYSTEMD_ENABLE */

/* cross-development target */
/* #undef TARGET */

/* target Python version as command */
#define TARGET_PYTHON "python"

/* time-service configuration */
#define TIMESERVICE_ENABLE 1

/* latency timing support */
/* #undef TIMING_ENABLE */

/* True North Technologies support */
/* #undef TNT_ENABLE */

/* DeLorme TripMate support */
/* #undef TRIPMATE_ENABLE */

/* Trimble TSIP support */
/* #undef TSIP_ENABLE */

/* u-blox Protocol support */
/* #undef UBLOX_ENABLE */

/* udev rules directory */
#define UDEVDIR "/lib/udev"

/* libusb support for USB devices */
/* #undef USB_ENABLE */

/* include xgps and xgpsspeed. */
/* #undef XGPS_ENABLE */

/* Magic device which, if present, means to grab a static /dev/pps0 for KPPS */
#define MAGIC_HAT_GPS	"/dev/ttyAMA0"
/* Generic device which, if present, means to grab a static /dev/pps0 for KPPS */
#define MAGIC_LINK_GPS	"/dev/gpsd0"

/* Some libcs do not have strlcat/strlcpy. Local copies are provided */
#ifndef HAVE_STRLCAT
# ifdef __cplusplus
extern "C" {
# endif
#include <string.h>
size_t strlcat(/*@out@*/char *dst, /*@in@*/const char *src, size_t size);
# ifdef __cplusplus
}
# endif
#endif
#ifndef HAVE_STRLCPY
# ifdef __cplusplus
extern "C" {
# endif
#include <string.h>
size_t strlcpy(/*@out@*/char *dst, /*@in@*/const char *src, size_t size);
# ifdef __cplusplus
}
# endif
#endif
#ifndef HAVE_CLOCK_GETTIME
# ifdef __cplusplus
extern "C" {
# endif
#ifndef CLOCKID_T_DEFINED
typedef int clockid_t;
#define CLOCKID_T_DEFINED
# endif
/*
 * OS X 10.5 and later use _STRUCT_TIMESPEC (like other OSes)
 * 10.4 uses _TIMESPEC
 * 10.3 and earlier use _TIMESPEC_DECLARED
 */
#if !defined(_STRUCT_TIMESPEC) &&     !defined(_TIMESPEC) &&     !defined(_TIMESPEC_DECLARED) &&     !defined(__timespec_defined)
#define _STRUCT_TIMESPEC
struct timespec {
    time_t  tv_sec;
    long    tv_nsec;
};
#endif
/* OS X does not have clock_gettime */
#define CLOCK_REALTIME 0
int clock_gettime(clockid_t, struct timespec *);
# ifdef __cplusplus
}
# endif
#endif

#define GPSD_CONFIG_H
#endif /* GPSD_CONFIG_H */
