!
! All the definitions required to make the iconbar work.
!
set ui$bitmap_directory concat(c$projdir,"/icons")

!
! Display manager modules which this IconBar requires
!
require "init-config-menu"
require "cfg-tools"
require "send-wbounds"
require "put_component"
require "vor-popup"
require "ISS-Send-Locs"
require "ModelAdd"
require "template-menu"

!
! This is the iconbar menu itself.....
!
define widget iconbar menubar " "
	!
	! All this stuff tells the system to put it, unadorned by headers and
	! title bars, where we want it.  DM does "override" by itself now,
	! since this iconbar appears in the display config, so we don't
	! bother with it here.
	!
	noheader
	! size 230 80
	location 100 100
	! vertical
	! override
	!
	! Now we can define the menus themselves.
	!
	menu help bitmap iconbar-help
		title 'Zeb Help Access'
		line
		entry 'Introduction' 'help intro'
		entry 'On-line Topics' 'help index'
		entry 'Starting zeb' 'help start'
		entry 'Shutting Down' 'help shut-down'
		entry 'Keys and mouse buttons' 'help keys'
		entry 'The icon bar' 'help iconbar'
		entry 'Editing display configurations' 'help editing-configs'
		line
		entry 'Horizontal plots' 'help horizontal-plots'
		entry 'Skew-t plots' 'help skewt'
		entry 'XYGraph plots' 'help xy-graphs'
		entry 'Cross section plots' 'help cross-section'
	endmenu
	menu tools bitmap tools-big
		title 'Tools'
		line
		entry 'Time Control Tool' 'popup time'
		entry 'Printing Tool' 'popup hardcopy'
		entry 'Configuration Tool' 'popup ConfigEdit'
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
		entry 'Remove this configuration' 'cfg-remove'
		entry 'Restore to original' 'cfg-restore'
		line
		entry 'Shutdown Zebra' 'shutdown'
	endmenu
	menu configs bitmap configs
		title 'Display configurations'
		line
		entry 'Empty screen' 'display empty' (dm$config = 'empty')
		entry 'MM5 model' 'display mm5' (dm$config = 'mm5')
		entry 'MM5 cross sections' 'display mm5-xs' \
		      (dm$config = 'mm5-xs')
		entry 'Time-height and soundings' 'display iss-timeht' \
			(dm$config = 'iss-timeht')
		entry 'Sounding cross sections' 'display snd_xsect' \
		        (dm$config = 'snd_xsect')
		entry 'RUC model' 'display ruc' (dm$config = 'ruc')
		entry 'Oklahoma Mesonet' 'display ok-mesonet' \
			(dm$config = 'ok-mesonet')
		entry 'Wind Profiler Demo Network' 'display wpdn' \
			(dm$config = 'wpdn')
		entry 'SMOS Time Series' 'display smos-tseries' \
			(dm$config = 'smos-tseries')
		submenu 'UAV Configurations' uav-config-menu
!		entry 'ISS Line Plot' 'display iss-lineplot' \
!			(dm$config = 'iss-lineplot')
!		entry 'ISS LinePlot and TimeHeight' \
!			'display iss-lineplot-timeheight' \
!			(dm$config = 'iss-lineplot-timeheight')
!		entry 'ISS TimeHeight, SkewT, Temp' \
!			'display iss-timeheight-skew-temp' \
!			(dm$config = 'iss-timeheight-skew-temp')
		line
		submenu 'Saved Configurations' saved-config-menu
	endmenu
	menu surface bitmap surface
		title 'Surface Observations'
		line
		submenu 'Tower Platforms' tower-menu
		submenu 'NWS Hourly' nwssfchrly
		submenu 'Kansas Hourly' kansas-hourly
		submenu 'Kansas Daily' kansas-daily
		submenu 'Oklahoma 5-minute (a0)' oklahoma05a0
		submenu 'Oklahoma 5-minute (a1)' oklahoma05a1
		submenu 'Oklahoma 15-minute (a0)' oklahoma15a0
		submenu 'Oklahoma 15-minute (a1)' oklahoma15a1
		line
		submenu 'Wind Profiler Demo Network' 'wpdn-menu'
		submenu 'SMOS Instruments' 'smos-irgrid-menu'
		submenu 'EBBR Instruments' 'ebbr-irgrid-menu'
		line
		entry 'ISS Surface data' 'ISS-Send-Stations'
!		line
!		entry 'Arkansas River Basin Precip' 'beep'
	endmenu
	menu radiometric bitmap radiation
		title 'Radiation'
		line
		submenu 'AERI Central Facility' aeri-menu
		line
		submenu 'MWR Central Facility' mwr-cf-menu
		submenu 'MWR Boundary Facility One' mwr-b1-menu
		submenu 'MWR Boundary Facility Four' mwr-b4-menu
		submenu 'MWR Boundary Facility Five' mwr-b5-menu
		line
		submenu 'MFRSR' mfrsr-menu
		line
		entry 'SIROS' siros
		line
		entry 'MFR 10m Central Facility (a1)' \
		   'PutScalar Dsgpmfr10mC1.a1 mfr_up_hemisp_broadband pick'
		entry 'MFR 25m Central Facility (a1)' \
		   'PutScalar Dsgpmfr25mC1.a1 mfr_up_hemisp_broadband pick'
		line
		entry 'BSRN Central Facility (a1)' \
		   'PutScalar sgpbsrnC1.a1 nip pick'
		entry 'CF Whole Sky Imager' \
		   'PutScalar sgpwsicloudC1.c1 mean_cloud_height pick'
		entry 'CF Bellfort Laser Ceilometer (a1)' \
		   'PutScalar sgpblcC1.a1 cloud1 pick'
	endmenu
	menu model bitmap model
		title 'Model Grids'
		line
		entry 'RUC Contours' 'ModelAdd sgprucsX1.a1 pt yellow'
		entry 'RUC Wind Vectors' \
		   'ModelWindsAdd sgprucsX1.a1 yellow 50'
		entry 'RUC Analysis Contours' \
		   'ModelAdd sgprucsanalX1.a1 pt yellow'
		entry 'RUC Analysis Winds' \
		   'ModelWindsAdd sgprucsanalX1.a1 yellow 50'
		line
		entry 'MM5 Contours' 'ModelAdd mm5ncar pres green'
		entry 'MM5 Wind Vectors' 'ModelWindsAdd mm5ncar green 50'
		entry 'MM5 Surface Contours' \
		   'SfcModelAdd mm5ncar_sfc soil_temp brown'
		entry 'MM5 Surface Winds' \
		   'SfcModelWindsAdd mm5ncar_sfc brown 50'
		line
		entry 'NGM Contours' 'sendout p_ngm pick'
		entry 'NGM Wind Vectors' 'sendout p_ngm_winds pick'
	endmenu
	menu satellite bitmap satellite
		title 'Satellite Data'
		line
		entry 'GOES-Minnis' 'sendout c_goes_minnis pick'
		entry 'GOES-8' 'beep'
		entry 'AVHRR' 'beep'
		entry 'TOVS' 'beep'
	endmenu
	menu sone bitmap sonde
		title 'Sonde Instruments'
		line
		entry 'C1 Sonde (wrpn)' \
			'PutScalar sgpsondewrpnC1.a1 tdry pick'
		entry 'B1 Sonde (wrpn)' \
			'PutScalar sgpsondewrpnB1.a1 tdry pick'
		entry 'B4 Sonde (wrpn)' \
			'PutScalar sgpsondewrpnB4.a1 tdry pick'
		entry 'B5 Sonde (wrpn)' \
			'PutScalar sgpsondewrpnB5.a1 tdry pick'
		entry 'B6 Sonde (wrpn)' \
			'PutScalar sgpsondewrpnB6.a1 tdry pick'
	endmenu
	menu uav bitmap aircraft
		title 'UAV Platforms'
		line
		entry 'UAV Instrument Track' 'PutScalar uav met_temp pick'
		entry 'UAV Telemetry Track' \
		   'PutScalar sgpuavtrack alt pick'
		entry 'UAV TDDR Time Series' \
		   'PutScalar DsgpuavtddrUg1.a1 tddr_opd'
		line
		entry 'GOES vis (UAV project)' \
		   'putc2 p_goes_uav platform sgpgoesvis.tmp field vis'
		entry 'GOES ir (UAV project)' \
		   'putc2 p_goes_uav platform sgpgoesir.tmp field ir'
		line
		submenu 'NGM plots from UAV' ngm-uav-menu
	endmenu
	menu 'qme-vap' bitmap qme_vap
		title 'Quality Measurement Experiments'
		line
		submenu 'MWR Columns' qmemwrcol-menu
		submenu 'Sonde Wind Calculations' sondewndcalc-menu
		line
		entry 'Value Added Products' 'beep'
	endmenu
	menu 'overlays' bitmap overlays
		title 'Static Overlays'
		line
		entry 'State Lines' \
			'putc3 p_map platform state_lines color tan icon map'
		entry 'Cities' 'put_component c_city_labels'
		entry 'Roads' 'put_component c_ok-rd'
		entry 'Road Labels' 'put_component c_road_labels'
		entry 'Rivers' 'put_component c_ok-dn'
		entry 'Railroads' 'put_component c_ok-rr'
		entry 'Elevations' 'put_component c_ok-hy'
		line
		entry 'Central Facility' 'sendout p_cf_locns pick'
		entry 'Extended Facilities' 'sendout p_ef_locns pick'
		entry 'Boundary Facilities' 'sendout p_bf_locns pick'
		entry 'All Facilities' 'sendout p_all_locns pick'
		line
		entry 'ISS Sounding locations' 'ISS-Send-Locs sounding'
		entry 'ISS Profiler locations' 'ISS-Send-Locs profiler'
		entry 'ISS RASS locations' 'ISS-Send-Locs rass'
!		line
!		submenu 'VOR/DME' 'VORmenu'
!		entry 'CLASS stations' 'put_component c_sounding_loc'
!		entry 'NWS soundings' 'put_component c_nwssounding_loc'
!		entry 'Profilers' 'put_component c_profiler_loc'
		line
		submenu 'Radar Range Rings' RadarRings
!		submenu 'VOR/DME Range Rings' VORRings 
		entry 'X-Y Grid (km)' \
			'putc3 p_kmgrid x-spacing 300 y-spacing 300 color cyan'
		entry 'Lat/Lon Grid' \
			'putc3 p_llgrid x-spacing 300 y-spacing 300 color cyan'
		line
		entry 'Window Bounds' 'send-wbounds'
	endmenu
enddef


define widget uav-config-menu intmenu 'UAV configurations'
	title 'UAV Configurations'
	line
	entry 'UDF Track' 'display uav-track' (dm$config = 'uav-track')
	entry 'NGM Model' 'display NGM' (dm$config = 'NGM')
	entry 'NWS Surface Hourlies' 'display Mesonet' (dm$config = 'Mesonet')
	entry 'Profiler' 'display Profiler' (dm$config = 'Profiler')
	entry 'GOES Satellite' 'display Satellite' (dm$config = 'Satellite')
endmenu



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
	entry 'AERI' \
	   'shell "dsdwidget -a -t AERI\ Platforms aeri &"'
	entry 'MWR, WVR, and WSI' \
	   'shell "dsdwidget -a -t MWR,\ WVR,\ and\ WSI mwr wvr wsi &"'
	entry 'Mesonets' \
	   'shell "dsdwidget -a -t Mesonets mesoX sfchrlyX okmX &"'
	entry 'Satellites' \
	   'shell "dsdwidget -a -t Satellites goes avhrr &"'
	entry 'Models' \
	   'shell "dsdwidget -a -t Models sgpngm250 sgpeta mm5ncar sgpruc &"'
	line
	entry 'IDASS IOP Platforms' \
   'shell "dsdwidget -a -t NCAR\ IOP prof/ sounding/ surf/ wpdn mm5ncar &"'
	line
	entry 'Central Facility' \
   'shell "dsdwidget -a -t Central\ Facility\ Platforms C1 C2 CF E13 E14 &"'
	entry 'Boundary Facilities' \
	   'shell "dsdwidget -a -t Boundary\ Facilities B\[123456\] &"'
	entry 'Level a1 Platforms' \
	   'shell "dsdwidget -a -t Level\ a1\ Platforms \.a1\$ &"'
	entry 'Level a2 Platforms' \
	   'shell "dsdwidget -a -t Level\ a2\ Platforms \.a2\$ &"'
	entry 'Level c Platforms' \
	   'shell "dsdwidget -a -t Level\ c\ Platforms \.c\[012\]\$ &"'
endmenu


define widget aeri-menu intmenu 'aeri platforms'
	title 'AERI Central Facility'
	line
	entry 'AERI Summary' \
	   'PutScalar sgpaerisummaryC1.a1 wave_num_avg_rad_675 pick'
	entry 'AERI Channel 1' \
	   'PutScalar sgpaerich1C1.a1 hotBBTemp pick'
	entry 'AERI Channel 2' \
	   'PutScalar sgpaerich2C1.a1 hotBBTemp pick'
endmenu


define widget mfrsr-menu intmenu 'mfrsr'
	title 'MFRSR Plots'
	line
	entry 'MFRSR CAP plot' \
	   'putc2 p_station platform sgpmfrsrN1.a0 icon mfrsr'
	entry 'MFRSR Time Series' \
	   'PutScalar sgpmfrsrN1.a0/1 tot1 pick'
endmenu


define widget mwr-cf-menu intmenu 'central facility mwr platforms'
	title 'MWR Central Facility'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosC1.a1 vap pick'
	entry 'Line-of-Sight (a0)' 'PutScalar sgpmwrlosC1.a0 vap pick'
	entry 'Line-of-Sight (b2)' 'PutScalar sgpmwrlosC1.b2 vap pick'
	entry '1-minute averages (c1)' 'PutScalar sgp1mwravgC1.c1 vap pick'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgC1.c1 vap pick'
endmenu

define widget mwr-b1-menu intmenu 'B1 mwr platforms'
	title 'MWR Boundary Facility One'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosB1.a1 vap pick'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgB1.c1 vap pick'
endmenu

define widget mwr-b4-menu intmenu 'B4 mwr platforms'
	title 'MWR Boundary Facility Four'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosB4.a1 vap pick'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgB4.c1 vap pick'
endmenu

define widget mwr-b5-menu intmenu 'B5 mwr platforms'
	title 'MWR Boundary Facility Five'
	line
	entry 'Line-of-Sight (a1)' 'PutScalar sgpmwrlosB5.a1 vap pick'
	entry '5-minute averages (c1)' 'PutScalar sgp5mwravgB5.c1 vap pick'
endmenu

define widget qmemwrcol-menu intmenu 'mwr column qme platforms'
	title 'MWR Column QMEs (c1)'
	line
	entry 'Central Facility' \
	   'PutScalar sgpqmemwrcolC1.c1 mean_vap_mwr pick'
	entry 'Boundary Facility One' \
	   'PutScalar sgpqmemwrcolB1.c1 mean_vap_mwr pick'
	entry 'Boundary Facility Four' \
	   'PutScalar sgpqmemwrcolB4.c1 mean_vap_mwr pick'
	entry 'Boundary Facility Five' \
	   'PutScalar sgpqmemwrcolB5.c1 mean_vap_mwr pick'
endmenu


define widget sondewndcalc-menu intmenu 'sonde wind calcs'
	title 'Sonde Wind Calculation'
	line
	entry 'C1 Wind Calc' \
		'PutScalar DsgpsondewndcalcC1.c1 pres pick'
	entry 'B1 Wind Calc' \
		'PutScalar DsgpsondewndcalcB1.c1 pres pick'
	entry 'B4 Wind Calc' \
		'PutScalar DsgpsondewndcalcB4.c1 pres pick'
	entry 'B5 Wind Calc' \
		'PutScalar DsgpsondewndcalcB5.c1 pres pick'
	entry 'B6 Wind Calc' \
		'PutScalar DsgpsondewndcalcB6.c1 pres pick'
endmenu


define widget ngm-uav-menu intmenu 'ngm plots for the uav ngm platforms'
	title 'Nested Grid Model (UAV)'
	line
	entry 'Line Contours' \
		'putc1 p_uav_ngm representation "contour"' 
	entry 'Filled Contours' \
		'putc1 p_uav_ngm representation "filled-contour"' 
	entry 'Wind Vectors' \
		'sendout p_uav_ngm_vector pick'
endmenu


define widget siros intmenu 'siros'
	title 'SIROS Time Series'
	line
	entry 'Central Facility (also E13, Lamont)' \
		'putc1 c_siros platform DsgpsirosE13.a1'
	entry 'Extended Facility E9 (also Ashton)' \
		'putc1 c_siros platform DsgpsirosE9.a1'
	entry 'Extended Facility E15 (also Ringwood)' \
		'putc1 c_siros platform DsgpsirosE15.a1'
endmenu



define widget tower-menu intmenu 'tower platforms'
	title "Tower Platforms"
	line
	entry "1-minute (a0)" 'PutScalar Dsgp1twr21xC1.a0 temp pick'
	entry "1-minute (a1)" 'PutScalar Dsgp1twr21xC1.a1 temp pick'
	entry "30-minute (a0)" 'PutScalar Dsgp30twr21xC1.a0 temp pick'
	entry "30-minute (a1)" 'PutScalar Dsgp30twr21xC1.a1 temp pick'
	entry "Daily (a0)" 'PutScalar Dsgp1440twr21xC1.a0 temp pick'
endmenu


!----------------------------------------------------------------
! Mesonet submenus
!----------------------------------------------------------------

define widget wpdn-menu intmenu 'wpdn plots'
	title 'Wind Profiler Demo Network'
	line
	entry 'Station Plot - Low Mode Winds' \
	   'putc2 p_wpdn_station u-field u_wind_low v-field v_wind_low'
	entry 'Station Plot - High Mode Winds' \
	   'putc2 p_wpdn_station u-field u_wind_hi v-field v_wind_hi'
	line
	entry 'Gridded Wind Vectors (Low Mode)' \
	   'putc2 p_wpdn_winds u-field u_wind_low v-field v_wind_low'
	entry 'Gridded Wind Vectors (Low Mode)' \
	   'putc2 p_wpdn_winds u-field u_wind_hi v-field v_wind_hi'
	line
	entry 'Consensus Contours - Low Mode' \
	   'putc1 p_wpdn_contour field cons_n_low'
	entry 'Consensus Contours - High Mode' \
	   'putc1 p_wpdn_contour field cons_n_hi'
endmenu

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

define widget kansas-hourly intmenu 'kansas'
	title 'Kansas Hourly Mesonet'
	line
	entry 'Station Plot' \
	   'putc2 p_station platform sgpksuhrlymesoX1.b1 icon sfc_hourly'
	entry 'Contour Plot' \
	   'putc2 p_contour platform sgpksuhrlymesoX1.b1 icon grid_hourly'
	entry 'Gridded Wind Vectors' \
   'putc2 p_irg_winds platform sgpksuhrlymesoX1.b1 icon grid_hourly_vectors'
endmenu

define widget kansas-daily intmenu 'kansas'
	title 'Kansas Daily Mesonet'
	line
	entry 'Station Plot' \
	   'putc2 p_station platform sgpksudlymesoX1.b1 icon meso_stations'
	entry 'Contour Plot' \
	   'putc2 p_contour platform sgpksudlymesoX1.b1 icon mesonet'
	entry 'Gridded Wind Vectors' \
	   'putc2 p_irg_winds platform sgpksudlymesoX1.b1 icon meso_winds'
endmenu

define widget nwssfchrly intmenu 'nws surface hourlies'
	title 'NWS Hourly Surface Data'
	line
	entry 'Station Plot' 'sendout p_nws_station pick'
	entry 'Contour Plot' 'putc1 p_nws_contour representation contour'
	entry 'Gridded Wind Vectors' \
   'putc2 p_irg_winds platform sgpsfchrlyX1.a1 icon grid_hourly_vectors'
endmenu

define widget oklahoma05a0 intmenu 'oklahoma'
	title 'Oklahoma Mesonet 5-minute (a0)'
	line
	entry 'Station Plot' \
	   'putc2 p_station platform sgp05okmX1.a0 icon sfc_5min'
	entry 'Contour Plot' \
	   'putc2 p_contour platform sgp05okmX1.a0 icon grid_5min'
	entry 'Gridded Wind Vectors' \
	   'putc2 p_irg_winds platform sgp05okmX1.a0 icon grid_5min_vectors'
endmenu

define widget oklahoma05a1 intmenu 'oklahoma'
	title 'Oklahoma Mesonet 5-minute (a1)'
	line
	entry 'Station Plot' \
	   'putc2 p_station platform sgp05okmX1.a1 icon sfc_5min'
	entry 'Contour Plot' \
	   'putc2 p_contour platform sgp05okmX1.a1 icon grid_5min'
	entry 'Gridded Wind Vectors' \
	   'putc2 p_irg_winds platform sgp05okmX1.a1 icon grid_5min_vectors'
endmenu

define widget oklahoma15a1 intmenu 'oklahoma'
	title 'Oklahoma Mesonet 15-minute (a1)'
	line
	entry 'Station Plot' \
	   'putc2 p_station platform sgp15okmX1.a1 icon meso_stations'
	entry 'Contour Plot' \
	   'putc2 p_contour platform sgp15okmX1.a1 icon mesonet'
	entry 'Gridded Wind Vectors' \
	   'putc2 p_irg_winds platform sgp15okmX1.a1 icon meso_winds'
endmenu

define widget oklahoma15a0 intmenu 'oklahoma'
	title 'Oklahoma Mesonet 15-minute (a0)'
	line
	entry 'Station Plot' \
	   'putc2 p_station platform sgp15okmX1.a0 icon meso_stations'
	entry 'Contour Plot' \
	   'putc2 p_contour platform sgp15okmX1.a0 icon mesonet'
	entry 'Gridded Wind Vectors' \
	   'putc2 p_irg_winds platform sgp15okmX1.a0 icon meso_winds'
endmenu

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

!======================================================================

define widget siros_facilities intmenu 'Siros Facilities'
	title 'siros facilities'
	line
	entry 'Central Facility (also E13, Lamont)' 'put_component c_CF_siros'
	entry 'Extended Facility E9 (also Ashton)' 'put_component c_E9_siros'
	entry 'Extended Facility E15 (also Ringwood)' 'put_component c_E15_siros'
endmenu



!
! Radar range ring menu.
!
define widget RadarRings intmenu 'radar range rings'
	title 'Radar Range Rings'
	line
	entry 'CP3 Range Rings' 'putc1 p_rings platform cp3'
	entry 'CP4 Range Rings' 'putc1 p_rings platform cp4'
	entry 'MHR Range Rings' 'putc1 p_rings platform mhr'
	entry 'OKC Range Rings' 'putc1 p_rings platform okc'
	entry 'FDR Range Rings' 'putc1 p_rings platform fdr'
	entry 'CIM Range Rings' 'putc1 p_rings platform cim'
	entry 'HOT Range Rings' 'putc1 p_rings platform hot'
	entry 'CHILL Range Rings' 'putc1 p_rings platform chill'
endmenu

