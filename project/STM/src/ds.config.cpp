! $Id: ds.config.cpp,v 1.6 1995-09-10 14:56:31 granger Exp $
!
! ------------------------------------------------------------------------
! DO NOT EDIT THIS FILE if it resides in the top level of the project
! configuration.  This file is generated from a cpp source file in the
! ./src directory!
! ------------------------------------------------------------------------
!
! Data store configuration file.
!
! Platform parameters:
!	organization 	The expected organization of the data
!		3dgrid		three dimensional regular grid
!		2dgrid		two-dimensional regular grid
!		irgrid		two-dimensional irregular grid (PAM)
!		scalar		basic scalar point data
!		nspace		multi-dimensional data
!		outline		Boundaries
!	filetype
!		netcdf, boundary, raster, compressed_raster, zeb,
!		grib, grib_sfc, grads
!
!	keep 		The minimum time period of data to keep on the disk if
!			at all possible.
!	maxsamples 	The maximum number of data samples to put into one
!		      	disk file.
!	mobile		Indicates that the data collection platform moves
!			through space.  For soundings, aircraft.
!	composite	This "platform" is a grouping of several smaller
!			platforms.  Only irgrid platforms -- groupings of
!			stationary scalar platforms -- are supported now.
!	directory	The directory in which to find data for this
!			platform.
!	model		Model data existing at both issue and forecast times
!

#ifdef UAV
#define REALTIME	/* use realtime settings if this is for UAV */
#endif

!
! Path to the data directory.
!
if (getenv("DATAHOME") <> "UNDEFINED")
	set datadir concat(getenv("DATAHOME"), "/sgp/platforms")
else
	set datadir DEFDATADIR
endif

! Set to write cache files upon a normal exit, 
! and trust those cache files when starting
!
set CacheOnExit true
#ifdef REALTIME
set LDirConst false
set LFileConst false
#else
set LDirConst true
set LFileConst true
#endif

! Create local data directories only as needed
! 
set DelayDataDirs true

! No remote data directories to speak of
!
set DisableRemote true

#ifdef REALTIME

!
! Set to cache every 5 minutes
!
every 300 'cache dirty'

#ifdef notdef
!
! Clean excess NetCDF files 
! 
every 10 checkandclean
#endif

#endif /* REALTIME */

!
! Set our tables to the sizes we know we'll need
!
#ifdef UAV
! UAV needs smaller sizes
set PTableSize 50
set CTableSize 50
set DFTableSize 1500
#else
! The full ARM dataset definition is naturally huge
set PTableSize 800
set CTableSize 100
set DFTableSize 3500
#endif

!========================================================================
! Optional platforms
!========================================================================

set facility_nodes 	0
set sgp30ebbr_a0 	0
set sgp15ebbr_a0 	0
set sgp30ebbr_b2 	0
set smos_daily 		0
set siros_b1 		0
set sonde_all_modes 	0
set sgpmwrtip 		0
set sgpmwrlosB_a0	0
set sgpmwslosB_b2 	0
set spgwvrlos		0

!========================================================================
! Facility nodes
!========================================================================

class Facility
	abstract
	virtual
	filetype	netcdf
	organization	scalar
endclass

class CentralFacility Facility
	virtual
endclass

class BoundaryFacility Facility
	virtual
endclass

class ExtendedFacility Facility
	virtual
endclass

if (facility_nodes)
!
! Facility instances serve as nodes in the hierarchy of
! sites and instruments.  Facility<->subplat connection represents
! co-location.
!
instance ExtendedFacility E1 E2 E3 E4 E5 E6 E7 E8 E9 E10 E11 E12 E13 E14
instance ExtendedFacility E15 E16 E17 E18 E19 E20 E21 E22 E23 E24 E25 E99

instance BoundaryFacility B1 B2 B3 B4 B5 B6

instance CentralFacility C1

endif

!========================================================================
! Profiler
!========================================================================

class Profiler
	organization	nspace
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass Profiler

class Profiler915 Profiler
endclass

#ifdef UAV

instance Profiler915 Dsgp915rwpwindC1.a2 Dsgp915rwptempC1.a2
instance Profiler50 Dsgp50rwpwindC1.a2 Dsgp50rwptempC1.a2

#else
class Profiler915-Wind-A0 Profiler915
	maxsamples	1008
endclass

instance Profiler915 Dsgp915rwptempC1.a0 Dsgp915rwptempC1.a1
instance Profiler915 Dsgp915rwptempC1.b1 Dsgp915rwptempC1.a2

instance Profiler915 Dsgp915rwpwindC1.a1 Dsgp915rwpwindC1.b1 
instance Profiler915 Dsgp915rwpwindC1.a2
instance Profiler915-Wind-A0 Dsgp915rwpwindC1.a0

class Profiler50 Profiler
endclass

class Profiler50-Wind-A0 Profiler50
	maxsamples	504
endclass

instance Profiler50 Dsgp50rwptempC1.b1 Dsgp50rwptempC1.a2 Dsgp50rwptempC1.a1
instance Profiler50 Dsgp50rwptempC1.a0

instance Profiler50 Dsgp50rwpwindC1.b1 Dsgp50rwpwindC1.a2 Dsgp50rwpwindC1.a1
instance Profiler50-Wind-A0 Dsgp50rwpwindC1.a0

#endif /* UAV */

#ifndef UAV
!========================================================================
! EBBR -- E-Bowen Broadband Radiometer?
!========================================================================

class EBBR
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass EBBR

! E4
instance EBBR sgp5ebbrE4.a0 Dsgp15ebbrE4.a1 sgp30ebbrE4.a1

! E7 
instance EBBR sgp5ebbrE7.a0 Dsgp15ebbrE7.a1 sgp30ebbrE7.a1

! E8
instance EBBR sgp5ebbrE8.a0 Dsgp15ebbrE8.a1 sgp30ebbrE8.a1

! E9
instance EBBR sgp5ebbrE9.a0 Dsgp15ebbrE9.a1 sgp30ebbrE9.a1

! E12
instance EBBR sgp5ebbrE12.a0 Dsgp15ebbrE12.a1 sgp30ebbrE12.a1

! E13
instance EBBR sgp5ebbrE13.a0 Dsgp15ebbrE13.a1 sgp30ebbrE13.a1

! E15
instance EBBR sgp5ebbrE15.a0 Dsgp15ebbrE15.a1 sgp30ebbrE15.a1

! E20
instance EBBR sgp5ebbrE20.a0 Dsgp15ebbrE20.a1 sgp30ebbrE20.a1

! E22
instance EBBR sgp5ebbrE22.a0 Dsgp15ebbrE22.a1 sgp30ebbrE22.a1

! E26
instance EBBR sgp5ebbrE26.a0 Dsgp15ebbrE26.a1 sgp30ebbrE26.a1

!
! No 30-minute a0 data
!
if (sgp30ebbr_a0) 
	instance EBBR sgp30ebbrE4.a0
	instance EBBR sgp30ebbrE7.a0
	instance EBBR sgp30ebbrE8.a0
	instance EBBR sgp30ebbrE9.a0
	instance EBBR sgp30ebbrE12.a0
	instance EBBR sgp30ebbrE13.a0
	instance EBBR sgp30ebbrE15.a0
	instance EBBR sgp30ebbrE20.a0
	instance EBBR sgp30ebbrE22.a0
	instance EBBR sgp30ebbrE26.a0
endif

!
! No ebbr 15-minute a0 data
!
if (sgp15ebbr_a0)
	instance EBBR sgp15ebbrE26.a0 sgp15ebbrE22.a0 sgp15ebbrE20.a0 
	instance EBBR sgp15ebbrE13.a0 sgp15ebbrE12.a0 sgp15ebbrE9.a0
	instance EBBR sgp15ebbrE7.a0 sgp15ebbrE4.a0 sgp15ebbrE15.a0
	instance EBBR sgp15ebbrE8.a0
endif

!
! No data for 30-minute ebbr b2 level yet
!
if (sgp30ebbr_b2)
	instance EBBR Dsgp30ebbrE15.b2 Dsgp30ebbrE13.b2 Dsgp30ebbrE12.b2
	instance EBBR Dsgp30ebbrE9.b2 Dsgp30ebbrE8.b2 Dsgp30ebbrE7.b2
	instance EBBR Dsgp30ebbrE4.b2 Dsgp30ebbrE26.b2 Dsgp30ebbrE22.b2
	instance EBBR Dsgp30ebbrE20.b2
endif

#endif /* ! UAV */

#ifndef UAV
!===================================================================
! Tower platforms
!===================================================================

class Tower
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

instance Tower Dsgp1twr21xC1.a1 Dsgp1twr21xC1.a0 Dsgp30twr21xC1.a1
instance Tower Dsgp30twr21xC1.a0 Dsgp1440twr21xC1.a0

#endif /* ! UAV */

!=====================================================================
! SMOS -- Surface Meteorology Observation System?
!=====================================================================

class SMOS
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

class SMOS-Daily SMOS
	maxsamples	1
endclass

#ifndef UAV

! E4
instance SMOS sgp1smosE4.a0 sgp1smosE4.a1
instance SMOS sgp30smosE4.a0 sgp30smosE4.a1

! E7
instance SMOS sgp1smosE7.a0 sgp1smosE7.a1
instance SMOS sgp30smosE7.a0 sgp30smosE7.a1

! E8
instance SMOS sgp1smosE8.a0 sgp1smosE8.a1
instance SMOS sgp30smosE8.a0 sgp30smosE8.a1

! E9
instance SMOS sgp1smosE9.a0 sgp1smosE9.a1
instance SMOS sgp30smosE9.a0 sgp30smosE9.a1
#endif /* ! UAV */

! E13
instance SMOS sgp1smosE13.a0 sgp1smosE13.a1 
instance SMOS sgp30smosE13.a0 sgp30smosE13.a1

#ifndef UAV

! E15
instance SMOS sgp1smosE15.a0 sgp1smosE15.a1
instance SMOS sgp30smosE15.a0 sgp30smosE15.a1

! E20
instance SMOS sgp1smosE20.a0 sgp1smosE20.a1
instance SMOS sgp30smosE20.a0 sgp30smosE20.a1

! E99
instance SMOS sgp1smosE99.a0 sgp1smosE99.a1
instance SMOS sgp30smosE99.a0 sgp30smosE99.a1

!
! No data for daily platforms yet
!
if (smos_daily)
	instance SMOS-Daily Dsgp1440smosE99.a0
	instance SMOS-Daily Dsgp1440smosE20.a0
	instance SMOS-Daily Dsgp1440smosE15.a0
	instance SMOS-Daily Dsgp1440smosE13.a0
	instance SMOS-Daily Dsgp1440smosE9.a0
	instance SMOS-Daily Dsgp1440smosE7.a0
	instance SMOS-Daily Dsgp1440smosE4.a0
	instance SMOS-Daily Dsgp1440smosE8.a0
endif
#endif /* ! UAV */

#ifndef UAV
!===================================================================
! BSRN
!===================================================================

class BSRN
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

class BSRN-Calc BSRN
	organization	scalar
	filetype	netCDF
	maxsamples	2000
	daysplit
endclass

instance BSRN sgpbsrnC1.a1 sgpbsrnC1.a0
instance BSRN-Calc sgpbsrncalcC1.c1

#endif /* ! UAV */

!====================================================================
! MFR -- Multi-filter Radiometer
!====================================================================

class MFR
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

#ifndef UAV
instance MFR Dsgpmfr10mC1.a1
#endif
instance MFR Dsgpmfr25mC1.a1

!=====================================================================
! MPL -- Micropulse LIDAR
!=====================================================================

class MPL
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

#ifndef UAV
instance MPL DsgpmplC1.a0
#endif
instance MPL DsgpmplcbhC1.c1

!======================================================================
! BLC -- Bellfort Laser Ceilometer
!======================================================================

class BLC
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

#ifndef UAV
instance BLC sgpblcC1.a0
#endif
instance BLC sgpblcC1.a1

#ifndef UAV
!=====================================================================
! LBL
!=====================================================================

class LBL
	organization	scalar
	filetype	netCDF
	maxsamples	10000
endclass

instance LBL sgplblch1C1.c1
instance LBL sgplblch1aC1.c1 sgplblch1bC1.c1 sgplblch2C1.c1
#endif

!=====================================================================
! SIROS 
!=====================================================================

class SIROS
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

class SIROS-Depth SIROS
	maxsamples	2
endclass

instance SIROS DsgpsirosE4.a1 DsgpsirosE7.a1
instance SIROS DsgpsirosE9.a1 DsgpsirosE13.a1
instance SIROS DsgpsirosE15.a1 DsgpsirosE20.a1
instance SIROS DsgpsirosE22.a1

#ifndef UAV
instance SIROS-Depth DsgpsirosopdepthE4.c1 DsgpsirosopdepthE7.c1
instance SIROS-Depth DsgpsirosopdepthE9.c1 DsgpsirosopdepthE13.c1
instance SIROS-Depth DsgpsirosopdepthE15.c1 DsgpsirosopdepthE20.c1
instance SIROS-Depth DsgpsirosopdepthE22.c1

!
! No b1 data yet
!
if (siros_b1)
	instance SIROS DsgpsirosE4.b1 DsgpsirosE7.b1 DsgpsirosE9.b1
	instance SIROS DsgpsirosE13.b1 DsgpsirosE15.b1 DsgpsirosE20.b1 
	instance SIROS DsgpsirosE22.b1
endif
#endif /* ! UAV */

#ifndef UAV
!=====================================================================
! MFRSR -- Multi-filter Rotating Shadowband Radiometer
!=====================================================================

class MFRSR
	organization	irgrid
	filetype	netCDF
	maxsamples	10000	
	regular		15
	daysplit
	composite
endclass

class MFRSR-Subplat MFRSR
	organization	scalar
endclass

subplats MFRSR MFRSR-Subplat 1

instance MFRSR sgpmfrsrN1.a0

#endif /* ! UAV */

!====================================================================
! Sondes
!====================================================================

class Sonde
	organization	scalar
	filetype	netCDF
	maxsamples	4000
	mobile
endclass

#ifdef UAV

instance Sonde sgpsondewrpnC1.a1 
instance Sonde sgpsondewrpnB1.a1 
instance Sonde sgpsondewrpnB4.a1
instance Sonde sgpsondewrpnB5.a1 
instance Sonde sgpsondewrpnB6.a1

#else
!----- C1
instance Sonde sgpsondeC1.a1
instance Sonde sgpsondewrpnC1.a1 
instance Sonde DsgpsondewndcalcC1.c1

if (sonde_all_modes)
instance Sonde DsgpsondewnpnC1.a0 DsgpsondewnpnC1.a1 DsgpsondewnprC1.a0
instance Sonde DsgpsondewnprC1.a1 DsgpsondewrprC1.a0 DsgpsondewrprC1.a1
instance Sonde DsgpsondewrpnC1.a0 
endif

!----- B1
instance Sonde sgpsondewrpnB1.a1 
instance Sonde DsgpsondewndcalcB1.c1

if (sonde_all_modes)
instance Sonde DsgpsondewnpnB1.a0 DsgpsondewnpnB1.a1 DsgpsondewnprB1.a0
instance Sonde DsgpsondewnprB1.a1 DsgpsondewrprB1.a0 DsgpsondewrprB1.a1
instance Sonde DsgpsondewrpnB1.a0 
endif

!----- B4
instance Sonde sgpsondewrpnB4.a1
instance Sonde DsgpsondewndcalcB4.c1

if (sonde_all_modes)
instance Sonde DsgpsondewnpnB4.a0 DsgpsondewnpnB4.a1 DsgpsondewnprB4.a0
instance Sonde DsgpsondewnprB4.a1 DsgpsondewrprB4.a0 DsgpsondewrprB4.a1
instance Sonde DsgpsondewrpnB4.a0 
endif

!----- B5
instance Sonde sgpsondewrpnB5.a1 
instance Sonde DsgpsondewndcalcB5.c1

if (sonde_all_modes)
instance Sonde DsgpsondewnpnB5.a0 DsgpsondewnpnB5.a1 DsgpsondewnprB5.a0
instance Sonde DsgpsondewnprB5.a1 DsgpsondewrprB5.a0 DsgpsondewrprB5.a1
instance Sonde DsgpsondewrpnB5.a0 
endif

!----- B6
instance Sonde sgpsondewrpnB6.a1
instance Sonde DsgpsondewndcalcB6.c1

if (sonde_all_modes)
instance Sonde DsgpsondewnpnB6.a0 DsgpsondewnpnB6.a1 DsgpsondewnprB6.a0
instance Sonde DsgpsondewnprB6.a1 DsgpsondewrprB6.a0 DsgpsondewrprB6.a1
instance Sonde DsgpsondewrpnB6.a0 
endif

#endif /* UAV */

!=======================================================================
! MWR -- Microwave Radiometer
!=======================================================================

class MWR
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

class MWR-LOS MWR
endclass

#ifdef UAV

instance MWR-LOS sgpmwrlosC1.a1

#else

class MWR-Average MWR
	regular		300
	maxsamples	288
endclass

class MWR-TIP MWR
endclass

class MWR-Column MWR
endclass

class MWR-Profile MWR
	maxsamples	2140
endclass

! C1
instance MWR-LOS sgpmwrlosC1.a0 sgpmwrlosC1.a1 DsgpmwrlosC1.b2
instance MWR-Average sgp1mwravgC1.c1 sgp5mwravgC1.c1
instance MWR-Column sgpqmemwrcolC1.c1
instance MWR-Profile sgpmwrprofC1.c1

! B1
instance MWR-LOS sgpmwrlosB1.a1
instance MWR-Average sgp5mwravgB1.c1
instance MWR-Column sgpqmemwrcolB1.c1

! B4
instance MWR-LOS sgpmwrlosB4.a1
instance MWR-Average sgp5mwravgB4.c1
instance MWR-Column sgpqmemwrcolB4.c1

! B5
instance MWR-LOS sgpmwrlosB5.a1
instance MWR-Average sgp5mwravgB5.c1
instance MWR-Column sgpqmemwrcolB5.c1

if (spgmwrlosB_b2)
	instance MWR-LOS DsgpmwrlosB1.b2
	instance MWR-LOS DsgpmwrlosB4.b2
	instance MWR-LOS DsgpmwrlosB5.b2
endif

if (sgpmwrlosB_a0)
	instance MWR-LOS DsgpmwrlosB1.a0
	instance MWR-LOS DsgpmwrlosB4.a0
	instance MWR-LOS DsgpmwrlosB5.a0
endif

if (sgpmwrtip)
	instance MWR-TIP sgpmwrtipC1.a0 sgpmwrtipC1.a1
	instance MWR-TIP DsgpmwrtipB1.a0 DsgpmwrtipB1.a1
	instance MWR-TIP DsgpmwrtipB4.a0 DsgpmwrtipB4.a1
	instance MWR-TIP DsgpmwrtipB5.a0 DsgpmwrtipB5.a1
endif
#endif /* UAV */

#ifndef UAV
!======================================================================
! AERI
!======================================================================

class AERI
        organization	scalar
        filetype	netCDF
        maxsamples	10000
        daysplit
endclass

instance AERI sgpaerich1C1.a1 sgpaerich2C1.a1 sgpaerisummaryC1.a1
instance AERI sgpqmeaerilblC1.c1 sgpqmeaerimeansC1.c1 sgpaerilbldiffC1.c1
instance AERI sgpaerilblcloudsC1.c1

#endif /* ! UAV */

#ifndef UAV
!======================================================================
! WVR
!======================================================================

class WVR
	organization	scalar
	filetype	netCDF
	maxsamples	5000
	composite
	daysplit
endclass

if (spgwvrlos)
	instance WVR sgpwvrlosC1.a1
endif

#endif /* ! UAV */

#ifndef UAV
!======================================================================
! WSI Cloud
!======================================================================

class WSI
	organization	scalar
	filetype	netCDF
	maxsamples	10000
	daysplit
endclass

instance WSI sgpwsicloudC1.c1

#endif /* ! UAV */

!======================================================================
! Mesonets
!======================================================================

!
! Every mesonet platform must be a composite irregular grid, and the
! filetype will usually be netcdf.  Maxsamples is up to the subclass.
!
class Mesonet
	abstract
	organization	irgrid
	filetype	netcdf
	composite
endclass Mesonet

#ifndef UAV
!=======================================================================
! Kansas Mesonet
!=======================================================================

class KSMesonet Mesonet
	maxsamples	600
endclass

class KSMesonet-Station KSMesonet
	organization	scalar
endclass

class KSMesonet-Hourly KSMesonet
	subplats KSMesonet-Station kh1 kh2 kh3 kh4
endclass

class KSMesonet-Daily KSMesonet
	subplats KSMesonet-Station kd1 kd2 kd3 kd4
endclass

instance KSMesonet-Hourly sgpksuhrlymesoX1.b1
instance KSMesonet-Daily sgpksudlymesoX1.b1

#endif /* ! UAV */

!======================================================================
! NWS hourly surface network
!======================================================================

class NWSMesonet Mesonet
	maxsamples	24
	daysplit
endclass

class NWS-Station NWSMesonet
	organization	scalar
endclass

subplats NWSMesonet NWS-Station 3km adm bvo cnk cnu csm ddc eha emp end flv
subplats NWSMesonet NWS-Station foe fri fsi gag gck gld hbr hlc hut hys iab
subplats NWSMesonet NWS-Station ict ixd lbl lts mhk mlc ojc okc p28 pnc pwa
subplats NWSMesonet NWS-Station rsl sln tik top tul wdg

instance NWSMesonet sgpsfchrlyX1.a1

#ifndef UAV
!====================================================================
! Oklahoma Mesonet
!====================================================================

class OKMesonet Mesonet
endclass

class OKMesonet-Station OKMesonet
	organization	scalar
endclass

subplats OKMesonet OKMesonet-Station ADAX ALTU ALVA ANTL
subplats OKMesonet OKMesonet-Station ARDM ARNE BEAV BESS
subplats OKMesonet OKMesonet-Station BIXB BLAC BOIS BOWL
subplats OKMesonet OKMesonet-Station BREC BRIS BBOW BUFF
subplats OKMesonet OKMesonet-Station BURB BURN BUTL BYAR
subplats OKMesonet OKMesonet-Station CALV CAMA CENT CHAN
subplats OKMesonet OKMesonet-Station CHER CHEY CHIC CLAR
subplats OKMesonet OKMesonet-Station CLAY CLOU COOK COPA
subplats OKMesonet OKMesonet-Station DURA ELRE ERIC EUFA
subplats OKMesonet OKMesonet-Station FAIR FORA FTCB FREE
subplats OKMesonet OKMesonet-Station GOOD GRAN GUTH HASK
subplats OKMesonet OKMesonet-Station HINT HOBA HOLL HOOK
subplats OKMesonet OKMesonet-Station HUGO IDAB JAYX KENT
subplats OKMesonet OKMesonet-Station KETC KING LAHO LANE
subplats OKMesonet OKMesonet-Station MADI MANG MARE MARS
subplats OKMesonet OKMesonet-Station MAYR MCAL MEDF MEDI
subplats OKMesonet OKMesonet-Station MIAM MINC MTHE NEWK
subplats OKMesonet OKMesonet-Station NORM NOWA OILT OKEM
subplats OKMesonet OKMesonet-Station OKMU PAUL PAWN PERK
subplats OKMesonet OKMesonet-Station PRYO PUTN REDR RETR
subplats OKMesonet OKMesonet-Station RING SALL SEIL SHAW
subplats OKMesonet OKMesonet-Station SKIA SLAP SPEN STIG
subplats OKMesonet OKMesonet-Station STIL STUA SULP TAHL
subplats OKMesonet OKMesonet-Station TALI TIPT TISH TULL
subplats OKMesonet OKMesonet-Station VINI WALT WASH WATO
subplats OKMesonet OKMesonet-Station WAUR WEAT WEBB WEST
subplats OKMesonet OKMesonet-Station WILB WIST WOOD WYNO
subplats OKMesonet OKMesonet-Station NINN ACME APAC

class OKMesonet-05 OKMesonet
	maxsamples	144
endclass

class OKMesonet-15 OKMesonet
	maxsamples	144
endclass

instance OKMesonet-05 sgp05okmX1.a0 sgp05okmX1.a1
instance OKMesonet-15 sgp15okmX1.a0 sgp15okmX1.a1

#endif /* ! UAV */

#ifndef UAV 
!======================================================================
! Wind Profiler Demonstration Network
!======================================================================

class WPDN-Profiler Profiler
endclass

class WPDN Mesonet
!
! When plotting...
!
	organization	irgrid
!
! When creating...
!
!	organization	nspace

	subplats WPDN-Profiler  1  2  3  4  5  6  7  8  9 10 11 12 13 14
	subplats WPDN-Profiler 15 16 17 18 19 20 21 22 23 24 25 26 27 28
	subplats WPDN-Profiler 29 30 31 32 33 34
endclass

instance WPDN Dsgp60wpdnwndsX1.a1

#endif /* ! UAV */

#ifdef notdef
!======================================================================
! Arkansas red basin river precipitation
!======================================================================

!instance ? sgpabrfcpcpX1.c1
#endif

#ifndef UAV
!======================================================================
! GOES Minnis
!======================================================================

class GOES-Minnis
	organization	nspace
	filetype	netcdf
endclass

instance GOES-Minnis sgpgoesminnisX1.c1
#endif /* ! UAV */

#ifndef UAV
!======================================================================
! Models
!======================================================================

class ModelGrid
	organization	3dgrid
	filetype	netCDF
	maxsamples	4
	model
	daysplit
endclass

class NGM ModelGrid
endclass

instance NGM sgpngm250X1.c1 Dsgpngm250derivX1.c1

class ETA ModelGrid
endclass

instance ETA sgpeta90X1.c1

class GRIBModel
	organization	nspace
	filetype	grib
	model
endclass

!
! Surface grids are handled as separate platforms which share the
! same files as the volume platforms.  Hence the copyparent attribute.
!
class GRIBSurface
	organization	nspace
	filetype	grib_sfc
	instancedir	copyparent
	model
endclass

instance GRIBModel sgprucsX1.a1 sgprucsanalX1.a1

instance GRIBModel mm5ncar
subplats mm5ncar GRIBSurface mm5ncar_sfc

#endif /* ! UAV */

#ifndef UAV
!=====================================================================
! MAPS
!=====================================================================

class MAPS
	organization	scalar
	filetype	netCDF
	maxsamples	8
	daysplit
endclass

class MAPS-All MAPS
	maxsamples	1
endclass

instance MAPS Dsgpmaps60X1.c1
instance MAPS-All Dsgpallmaps60X1.c1

#endif /* ! UAV */

!=======================================================================
! Platform NULLplatform is a nonexistant platform that nevertheless must
! exist in order for some BW-using modules' _retriever.info and/or
! _maker.info files to work. Nothing should actually ever be written here
! and the directory doesn't need to exist.  As long as DelayDataDirs
! is true, the directory will never be created.

platform NULLplatform
	organization	scalar
	filetype	netCDF
	maxsamples	1000
	daysplit
endplatform

!=========================================================================
! Satellite
!
! All satellite images are regular grids in HDF from the SeaSpace converter
!
class Satellite
	directory	satellite
	instancedir	subdirclass
	inheritdir	copy
	organization	2dgrid
	filetype	hdf
endclass

class SatelliteOverlay Satellite
	organization	image
endclass

instance Satellite sgpavhrr12X1.a1 sgpavhrr12radX1.a1
instance Satellite sgpavhrr14X1.a1 sgpavhrr14radX1.a1
instance Satellite sgpgoes8X1.a1 sgpgoes8visX1.a1

#ifdef notdef	/* testing purposes only; no longer used */

instance Satellite g7ir8merc g7irmerc g7radir8merc g7radirmerc g7vismerc
instance Satellite n9avhrrmerc n9avhrrradmerc

!
! Overlay images, which all have only byte fields
!
instance SatelliteOverlay avhrr_sgp.state_lines avhrr_sgp.lat_lon
instance SatelliteOverlay goes_ir_sgp.state_lines goes_ir_sgp.lat_lon
instance SatelliteOverlay goes_vis_sgp.state_lines goes_vis_sgp.lat_lon

#endif

#ifdef notdef
!
! NGM model
!
platform sgpngm250X1.ns.issue
	organization	nspace
	filetype	netCDF
	maxsamples	4
	daysplit
endplatform

platform sgpngm250X1.ns.valid
	organization	nspace
	filetype	netCDF
	maxsamples	4
	daysplit
endplatform
#endif

!
! UAV aircraft tracks
!
platform sgpuavtrack
	organization	scalar
	filetype	netcdf
	maxsamples	(6*3600)
	mobile
endplatform

#ifdef notdef
!
! UAV on-board radiometer package; files lack location information so their
! data are only good for xygraphs and not tracks.
!
platform DsgpuavtddrUg1.a1
	organization	nspace
	filetype	netcdf
	maxsamples	65000
endplatform
#endif

!======================================================================
! MRC platforms
!======================================================================

class AircraftTrack
	organization	scalar
	filetype	netcdf
	maxsamples	21600
	mobile
endclass

instance AircraftTrack uav-now uav chase-now chase

class Boundary
	filetype	zeb
	organization	outline
endclass	

instance Boundary moa ifp

#ifndef UAV
!=======================================================================
! IDASS '93 IOP ISS Platforms
!=======================================================================

!
! ISSish stuff.  Profiler and RASS are identical, but might as well keep
! them separate.  These classes are distinct from the Profiler and RASS
! classes above since ISS uses a different netCDF layout.
!
class ISS-Profiler
	organization	1dgrid
	filetype	netcdf
	maxsamples	100
	daysplit
endclass

class ISS-RASS
	organization	1dgrid
	filetype	netcdf
	maxsamples	100
	daysplit
endclass

class ISS-Sounding
      	organization	scalar
	filetype	netcdf
	maxsamples	5000
	mobile
endclass

instance ISS-Sounding sounding/saltfork sounding/dodge sounding/kingfisher 
instance ISS-Sounding sounding/kingman sounding/norman sounding/pawhuska 
instance ISS-Sounding sounding/sgp sounding/topeka

instance ISS-RASS rass/saltfork_r rass/redrock_r

instance ISS-Profiler prof/saltfork_h prof/redrock_h prof/redrock_l 
instance ISS-Profiler prof/redrockw_h prof/redrockw_l 
instance ISS-Profiler prof/redrockr_h prof/redrockr_l 
instance ISS-Profiler prof/redrockp_h prof/redrockp_l 
instance ISS-Profiler prof/redrock_mom

!
! Single surface stations
!
class Surface
      	organization	scalar
	filetype	netcdf
	maxsamples	720
endclass

instance Surface surf/saltfork_s surf/redrock_s 

#endif /* ! UAV */

!
! The null placeholder platform.
!
platform null
	organization	scalar
	filetype	zeb
endplatform


