! $Id: IconBar.cpp,v 1.15 1997-06-02 22:55:21 granger Exp $
! 
! ------------------------------------------------------------------------
! DO NOT EDIT THIS FILE if it resides in the top level of the project
! configuration.  This file is generated from a cpp source file in the
! ./src directory!
! ------------------------------------------------------------------------
!
! All the definitions required to make the iconbar work.
!

! I put the iconbar icons in the project icon directory, copying those needed
! from the library icon directory.  This avoids copying project icons into
! the library directory or hard-coding the library directory path in the
! iconbar; both those options are unsatisfactory.
!
set ui$bitmap_directory "./icons"

!
! Display manager modules which this IconBar requires
!
require "init-config-menu"
require "cfg-tools"

set isssurf 'redrock_s,saltfork_s'

!
! This is the iconbar menu itself.....
!
define widget iconbar menubar " "
	!
	! The main menubar, unadorned by headers and title bars.
	!
	noheader

	!
	! Define the menus themselves.
	!
	menu help bitmap iconbar-help
		title 'Zebra Help Access'
		line
		entry 'Introduction' 'help intro'
		entry 'On-line Help Index' 'help index'
		entry 'Starting Zebra' 'help start'
		entry 'Shutting Down' 'help shut-down'
		entry 'Keys and Mouse Buttons' 'help keys'
		entry 'The Icon Bar' 'help iconbar'
		entry 'Editing Display Configurations' 'help editing-configs'
		line
		entry 'Horizontal plots' 'help horizontal-plots'
		entry 'Skew-t plots' 'help skewt'
		entry 'XYGraph plots' 'help xy-graphs'
		entry 'Cross section plots' 'help cross-section'
		line
		entry 'ARM Help Index' 'help arm-index'
		entry 'ARM Display Index' 'help arm-displays'
		entry 'ARM Icon Bar' 'help arm-iconbar'
		entry 'Simple tutorial' 'help arm-tutorial'
		entry 'ARM Home Page' 'help "http://www.arm.gov/"'
	endmenu

	menu tools bitmap tools-big
		title 'Tools'
		line
		entry 'Time Control Tool...' 'popup time'
		entry 'Printing Tool...' 'popup hardcopy'
		entry 'Configuration Tool...' 'popup ConfigEdit'
		entry 'XTerm Shell Tool' 'shell \
  "xterm -T ZebraShell -bg grey90 -fg purple -fn 8x13bold -e zstart -shell &"'
		submenu 'Data Listings' dslistings
		entry 'Data Store Management' 'shell "dsmanage &"'
		line
		entry 'Begin new configuration...' 'popup newconfig'
		submenu 'Add new window' 'template-menu'
		entry 'Kill window by cursor' 'point-and-shoot'
		entry 'Add window named...' 'popup NewWindow'
		entry 'Kill window named...' 'popup ZorchWindow'
		line
		entry 'Save this configuration' 'cfgsave #dm$config'
		entry 'Save this configuration as...' 'popup SaveConfig'
#ifdef notdef
		entry 'Remove this configuration' 'cfg-remove'
#endif
		entry 'Restore configuration' 'cfg-restore'
		line
		entry 'Event Logger' 'shell "EventLogger -w &"'
		line
		entry 'Shutdown Zebra' 'shutdown'
	endmenu

	menu configs bitmap configs
		title 'Display configurations'
		line
		entry 'Empty screen' 'display empty' (dm$config = 'empty')
		entry 'SMOS Time Series' 'display smos-tseries' \
			(dm$config = 'smos-tseries')
		entry 'Siros Time Series' \
			'display sw-tseries' (dm$config = 'sw-tseries')
		entry 'Sonde multi-facility plots' 'display sondes' \
			(dm$config = 'sondes')
		entry 'Sonde single-facility plots' 'display sonde-profile' \
			(dm$config = 'sonde-profile')
		entry '915 MHz Profiles' \
			'display Profiler915' (dm$config = 'Profiler915')
		entry '50 MHz Profiles' \
			'display Profiler50' (dm$config = 'Profiler50')
!		entry 'BLC and MFR Time Series' \
!			'display tseries' (dm$config = 'tseries')
		line
		submenu 'Saved Configurations' saved-config-menu
	endmenu

	menu radiometric bitmap radiation
		title 'Radiation'
		line
		submenu 'SIROS' siros
	endmenu

	menu sonde bitmap sonde
		title 'Sonde Instruments'
		line
		entry 'C1 Sonde (wrpn)' \
			'require PutSonde; PutSonde sgpsondewrpnC1.a1 tdry'
		entry 'B1 Sonde (wrpn)' \
			'require PutSonde; PutSonde sgpsondewrpnB1.a1 tdry'
		entry 'B4 Sonde (wrpn)' \
			'require PutSonde; PutSonde sgpsondewrpnB4.a1 tdry'
		entry 'B5 Sonde (wrpn)' \
			'require PutSonde; PutSonde sgpsondewrpnB5.a1 tdry'
		entry 'B6 Sonde (wrpn)' \
			'require PutSonde; PutSonde sgpsondewrpnB6.a1 tdry'
	endmenu

#ifdef notdef
!	menu 'qme-vap' bitmap qme_vap
!		title 'Quality Measurement Experiments'
!		line
!		submenu 'MWR Columns' qmemwrcol-menu
!		submenu 'Sonde Wind Calculations' sondewndcalc-menu
!		line
!		entry 'Value Added Products' 'beep'
!	endmenu
#endif

	menu 'overlays' bitmap overlays
		title 'Static Overlays'
		line
		entry 'OK State Lines' \
			'putc3 p_map platform ok/state color tan icon map'
		entry 'OK County Lines' \
			'putc3 p_map platform ok/county color tan icon map'
		entry 'OK Roads' \
			'putc3 p_map platform ok/road color gray70 icon roads'
		entry 'OK Lakes & Rivers' \
			'putc3 p_map platform ok/water color blue icon rivers'
		entry 'OK Federal Areas' \
			'putc3 p_map platform ok/fed color yellow icon map'
		line
		entry 'KS State Lines' \
			'putc3 p_map platform ks/state color tan icon map'
		entry 'KS County Lines' \
			'putc3 p_map platform ks/county color tan icon map'
		entry 'KS Roads' \
			'putc3 p_map platform ks/road color gray70 icon roads'
		entry 'KS Lakes & Rivers' \
			'putc3 p_map platform ks/water color blue icon rivers'
		entry 'KS Federal Areas' \
			'putc3 p_map platform ks/fed color yellow icon map'
		line
		entry 'Roads' 'putc0 c_ok-rd'
		entry 'Road Labels' 'putc0 c_road_labels'
		entry 'City Labels' 'putc0 p_city_labels'
		entry 'US State Boundaries' \
			'putc3 p_map platform state_lines color tan icon map'
#ifdef notdef
		entry 'Rivers' 'putc0 c_ok-dn'
		entry 'Railroads' 'putc0 c_ok-rr'
#endif
#ifdef notdef
		entry 'Elevations' 'putc0 c_ok-hy'
#endif
		line
		entry 'Central Facility' 'sendout p_cf_locns pick'
		entry 'Extended Facilities' 'sendout p_ef_locns pick'
		entry 'Boundary Facilities' 'sendout p_bf_locns pick'
#ifdef notdef
		entry 'All Facilities' 'sendout p_all_locns pick'
#endif
		line

#ifdef notdef
		entry 'ISS Sounding locations' \
			'require ISS-Send-Locs; ISS-Send-Locs sounding'
		entry 'ISS Profiler locations' \
			'require ISS-Send-Locs; ISS-Send-Locs profiler'
		entry 'ISS RASS locations' \
			'require ISS-Send-Locs; ISS-Send-Locs rass'
		line
		submenu 'VOR/DME' 'VORmenu'
		entry 'CLASS stations' 'putc0 c_sounding_loc'
		entry 'NWS soundings' 'putc0 c_nwssounding_loc'
		entry 'Profilers' 'putc0 c_profiler_loc'
		line
		submenu 'VOR/DME Range Rings' VORRings 
#endif

		submenu 'Radar Range Rings' RadarRings
		entry 'X-Y Grid (km)' \
			'putc3 p_kmgrid x-spacing 300 y-spacing 300 color cyan'
		entry 'Lat/Lon Grid' \
			'putc3 p_llgrid x-spacing 300 y-spacing 300 color cyan'
		line
		entry 'Window Bounds' 'require send-wbounds; send-wbounds'
	endmenu
enddef


!-----------------------------------
! Customize the window template menu
!
require "cfg-tools"

define widget template-menu intmenu 'window templates'
	title 'Window Templates'
	line
	entry 'Constant altitude plot' \
		'create-window cap cap-template big'
	entry 'GOES-8 Satellite' 'create-window cap goes-template big'
	entry 'UAV Map' 'create-window cap uav-map big'
	entry 'Skew-t plot' \
		'create-window skewt skewt-template sounding'
	entry 'Sonde Winds Profile' \
		'create-window theight th-sonde-template xyplot'
	entry 'Sonde Temperature Profile' \
		'create-window theight th-temp-template xyplot'
	entry '915 MHz Wind profile' \
		'create-window wind-profile 915wind-template xyplot'
	entry '915 MHz Temperatures' \
		'create-window temp-profile 915temp-template xyplot'
	entry '50 MHz Wind profile' \
		'create-window wind-profile 50wind-template xyplot'
	entry '50 MHz Temperatures' \
		'create-window temp-profile 50temp-template xyplot'
	entry 'MFR Time Series' \
		'create-window tseries mfr-template xyplot'
	entry 'BLC Cloud Heights' \
		'create-window tseries blc-template xyplot'
	entry 'Time-series plot' \
		'create-window tseries tseries-template xyplot'
	entry 'Time-height plot' \
		'create-window theight time-height-template xyplot'
	entry 'Simple line plot' \
		'create-window lineplot lineplot-template xyplot'
#ifndef UAV
	entry 'Wind profile' 'create-window wind wind-template xyplot'
	entry 'RASS profile' 'create-window rass rass-template xyplot'
	entry 'XY Graph' 'create-window xygraph xygraph-template xyplot'
	entry 'Vertical cross-section' \
		'create-window xsect xsect-template default'
#endif
	entry 'Real-time clock' 'create-clock'
endmenu
!-------------------------------------



!
! DataStore widget listings
!
define widget dslistings intmenu 'dsdwidget listings'
	title 'Data Store Widget Listings'
	line
	entry 'All Platforms' \
	   'shell "dsdwidget -a -t All\ Platforms &"'
	entry 'EBBR Platforms' \
	   'shell "dsdwidget -a -t EBBR\ Platforms ebbr &"'
	entry 'SMOS and Tower' \
	   'shell "dsdwidget -a -t Surface\ and\ Tower smos twr21 &"'
	entry 'RASS Profiles' \
	   'shell "dsdwidget -a -t RASS\ Profiles rwpwind rwptemp &"'
	entry 'Soundings' \
	   'shell "dsdwidget -a -t Soundings sonde &"'
	entry 'MPL and BLC' \
	   'shell "dsdwidget -a -t MPL\ and\ BLC mpl blc &"'
	entry 'MFR and MFRSR' \
	   'shell "dsdwidget -a -t MFR\ and\ MFRSR mfr &"'
	entry 'SIROS Platforms' \
	   'shell "dsdwidget -a -t SIROS\ Platforms siros &"'
	entry 'MWR, WVR, and WSI' \
	   'shell "dsdwidget -a -t MWR,\ WVR,\ and\ WSI mwr wvr wsi &"'
#ifdef notdef
	entry 'Mesonets' \
	   'shell "dsdwidget -a -t Mesonets mesoX sfchrlyX okmX nwssurf &"'
	entry 'Satellites' \
	   'shell "dsdwidget -a -t Satellites goes avhrr &"'
	entry 'Models' \
	   'shell "dsdwidget -a -t Models sgpngm250 sgpeta mm5ncar sgpruc &"'
#endif
#ifdef notdef
	line
	entry 'IDASS IOP Platforms' \
   'shell "dsdwidget -a -t NCAR\ IOP prof/ sounding/ surf/ wpdn mm5ncar &"'
#endif
	line
	entry 'Central Facility' \
   'shell "dsdwidget -a -t Central\ Facility\ Platforms C1 C2 CF E13 E14 &"'
	entry 'Boundary Facilities' \
	   'shell "dsdwidget -a -t Boundary\ Facilities B\[123456\] &"'
	entry 'Level a0 Platforms' \
	   'shell "dsdwidget -a -t Level\ a0\ Platforms \.a0\$ &"'
	entry 'Level a1 Platforms' \
	   'shell "dsdwidget -a -t Level\ a1\ Platforms \.a1\$ &"'
	entry 'Level a2 Platforms' \
	   'shell "dsdwidget -a -t Level\ a2\ Platforms \.a2\$ &"'
	entry 'Level b Platforms' \
	   'shell "dsdwidget -a -t Level\ b\ Platforms \.b\[012\]\$ &"'
	entry 'Level c Platforms' \
	   'shell "dsdwidget -a -t Level\ c\ Platforms \.c\[012\]\$ &"'
endmenu


define widget aeri-menu intmenu 'aeri platforms'
	title 'AERI Central Facility'
	line
	entry 'AERI Summary' \
	   'PutScalar sgpaerisummaryC1.a1 wave_num_avg_rad_675'
	entry 'AERI Line-by-Line Clouds' \
	   'PutScalar sgpaerilblcloudsC1.c1 mean_cloud1_cbh'
	entry 'AERI Channel 1' \
	   'PutScalar sgpaerich1C1.a1 hotBBTemp'
	entry 'AERI Channel 2' \
	   'PutScalar sgpaerich2C1.a1 hotBBTemp'
endmenu


define widget mfrsr-menu intmenu 'mfrsr'
	title 'MFRSR Plots'
	line
	entry 'MFRSR CAP plot' \
	   'putc2 p_station platform sgpmfrsrN1.a0 icon mfrsr'
	entry 'MFRSR Time Series' \
	   'PutScalar sgpmfrsrN1.a0/1 tot1'
endmenu


define widget mwr-cf-menu intmenu 'central facility mwr platforms'
	title 'MWR Central Facility'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosC1.a1 vap'
	entry 'Line-of-Sight (a0)' 'PutScalar sgpmwrlosC1.a0 vap'
	entry 'Line-of-Sight (b2)' 'PutScalar sgpmwrlosC1.b2 vap'
	entry '1-minute averages (c1)' 'PutScalar sgp1mwravgC1.c1 vap'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgC1.c1 vap'
endmenu


define widget mwr-b1-menu intmenu 'B1 mwr platforms'
	title 'MWR Boundary Facility One'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosB1.a1 vap'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgB1.c1 vap'
endmenu

define widget mwr-b4-menu intmenu 'B4 mwr platforms'
	title 'MWR Boundary Facility Four'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosB4.a1 vap'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgB4.c1 vap'
endmenu

define widget mwr-b5-menu intmenu 'B5 mwr platforms'
	title 'MWR Boundary Facility Five'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosB5.a1 vap'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgB5.c1 vap'
endmenu

define widget qmemwrcol-menu intmenu 'mwr column qme platforms'
	title 'MWR Column QMEs (c1)'
	line
	entry 'Central Facility' \
	   'PutScalar sgpqmemwrcolC1.c1 mean_vap_mwr'
	entry 'Boundary Facility One' \
	   'PutScalar sgpqmemwrcolB1.c1 mean_vap_mwr'
	entry 'Boundary Facility Four' \
	   'PutScalar sgpqmemwrcolB4.c1 mean_vap_mwr'
	entry 'Boundary Facility Five' \
	   'PutScalar sgpqmemwrcolB5.c1 mean_vap_mwr'
endmenu


define widget sondewndcalc-menu intmenu 'sonde wind calcs'
	title 'Sonde Wind Calculation'
	line
	entry 'C1 Wind Calc' \
		'PutScalar DsgpsondewndcalcC1.c1 pres'
	entry 'B1 Wind Calc' \
		'PutScalar DsgpsondewndcalcB1.c1 pres'
	entry 'B4 Wind Calc' \
		'PutScalar DsgpsondewndcalcB4.c1 pres'
	entry 'B5 Wind Calc' \
		'PutScalar DsgpsondewndcalcB5.c1 pres'
	entry 'B6 Wind Calc' \
		'PutScalar DsgpsondewndcalcB6.c1 pres'
endmenu


define widget siros intmenu 'siros'
	title 'SIROS Time Series'
	line
	entry 'Central Facility (also E13, Lamont)' \
		'putc1 c_siros platform sgpsirosE13.a1'
	entry 'Extended Facility E1 (Larned)' \
		'putc1 c_siros platform sgpsirosE1.a1'
	entry 'Extended Facility E2 (Hillsboro)' \
		'putc1 c_siros platform sgpsirosE2.a1'
	entry 'Extended Facility E3 (Le Roy)' \
		'putc1 c_siros platform sgpsirosE3.a1'
	entry 'Extended Facility E4 (Plevna)' \
		'putc1 c_siros platform sgpsirosE4.a1'
	entry 'Extended Facility E5 (Halstead)' \
		'putc1 c_siros platform sgpsirosE5.a1'
	entry 'Extended Facility E6 (Towanda)' \
		'putc1 c_siros platform sgpsirosE6.a1'
	entry 'Extended Facility E7 (Elk Falls)' \
		'putc1 c_siros platform sgpsirosE7.a1'
	entry 'Extended Facility E8 (Coldwater)' \
		'putc1 c_siros platform sgpsirosE8.a1'
	entry 'Extended Facility E9 (also Ashton)' \
		'putc1 c_siros platform sgpsirosE9.a1'
	entry 'Extended Facility E10 (also Tyro)' \
		'putc1 c_siros platform sgpsirosE10.a1'
	entry 'Extended Facility E11 (also Byron)' \
		'putc1 c_siros platform sgpsirosE11.a1'
	entry 'Extended Facility E12 (also Pawhuska)' \
		'putc1 c_siros platform sgpsirosE12.a1'
	entry 'Extended Facility E13 (also Lamont)' \
		'putc1 c_siros platform sgpsirosE13.a1'
	entry 'Extended Facility E15 (also Ringwood)' \
		'putc1 c_siros platform sgpsirosE15.a1'
	entry 'Extended Facility E16 (also Vici)' \
		'putc1 c_siros platform sgpsirosE16.a1'
	entry 'Extended Facility E18 (also Morris)' \
		'putc1 c_siros platform sgpsirosE18.a1'
	entry 'Extended Facility E20 (also Meeker)' \
		'putc1 c_siros platform sgpsirosE20.a1'
	entry 'Extended Facility E22 (also Cordell)' \
		'putc1 c_siros platform sgpsirosE22.a1'
	entry 'Extended Facility E24 (also Cyril)' \
		'putc1 c_siros platform sgpsirosE24.a1'
	entry 'Extended Facility E8' \
		'putc1 c_siros platform sgpsirosE8.a1'
	entry 'Extended Facility E11' \
		'putc1 c_siros platform sgpsirosE11.a1'
	entry 'Extended Facility E13' \
		'putc1 c_siros platform sgpsirosE13.a1'
	entry 'Extended Facility E15 (also Ringwood)' \
		'putc1 c_siros platform sgpsirosE15.a1'
	entry 'Extended Facility E16' \
		'putc1 c_siros platform sgpsirosE16.a1'
endmenu


define widget tower-menu intmenu 'tower platforms'
	title "Tower Platforms"
	line
	entry "1-minute (a0)" 'PutScalar Dsgp1twr21xC1.a0 temp'
	entry "1-minute (a1)" 'PutScalar Dsgp1twr21xC1.a1 temp'
	entry "30-minute (a0)" 'PutScalar Dsgp30twr21xC1.a0 temp'
	entry "30-minute (a1)" 'PutScalar Dsgp30twr21xC1.a1 temp'
	entry "Daily (a0)" 'PutScalar Dsgp1440twr21xC1.a0 temp'
endmenu


!----------------------------------------------------------------
! Mesonet submenus
!----------------------------------------------------------------


define widget smos-irgrid-menu intmenu 'smos irgrids'
	title 'SMOS Network Plots'
	line
	entry 'Station Plot' \
	   'putc3 p_station platform #smos_plats icon smos field temp'
	entry 'Contour Plot' \
	   'putc3 p_contour platform #smos_plats icon smos field temp'
	entry 'Gridded Wind Vectors' \
	   'putc2 p_irg_winds platform #smos_plats icon smos'
endmenu

define widget ebbr-irgrid-menu intmenu 'ebbr irgrids'
	title 'EBBR Network Plots'
	line
	entry 'Station Plot' \
	   'putc3 p_station platform #ebbr_plats icon ebbr field pres'
	entry 'Contour Plot' \
	   'putc3 p_contour platform #ebbr_plats icon ebbr field pres'
	entry 'Gridded Wind Vectors' \
	   'putc2 p_irg_winds platform #ebbr_plats icon ebbr'
endmenu



#ifdef notdef
!
! Make these irgrid mesonets containing the given platform for all
! of the facilities which possess that platform
!
define widget facnet intmenu 'facility mesonet'
	title 'Facility Mesonet by Instrument'
	line
	entry 'SMOS 30-minute' 'beep'
	entry 'SMOS 1-minute' 'beep'
	entry 'EBBR' 'beep'
endmenu

define widget siros_facilities intmenu 'Siros Facilities'
	title 'siros facilities'
	line
	entry 'Central Facility (also E13, Lamont)' 'putc0 c_CF_siros'
	entry 'Extended Facility E9 (also Ashton)' 'putc0 c_E9_siros'
	entry 'Extended Facility E15 (also Ringwood)' 'putc0 c_E15_siros'
endmenu
#endif /* notdef */

!
! Radar range ring menu.
!
define widget RadarRings intmenu 'radar range rings'
	title 'Radar Range Rings'
	line
	entry 'OKC Range Rings' 'putc1 p_rings platform okc'
	entry 'FDR Range Rings' 'putc1 p_rings platform fdr'
	entry 'CIM Range Rings' 'putc1 p_rings platform cim'
endmenu

