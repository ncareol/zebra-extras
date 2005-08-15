#!/bin/csh
setenv BATCH_IMAGE_SPOOL /net/www/docs/bamex/p3_images
setenv DS_DAEMON_HOST localhost
setenv ZEB_TOPDIR /opt/zebra
setenv ZEB_PROJDIR $ZEB_TOPDIR/project/rainex
setenv DATA_DIR /space/data/rainex
source $ZEB_PROJDIR/proj_env	# to get ZEB_SOCKET
setenv PATH /usr/X11R6/bin:$ZEB_TOPDIR/bin:$PATH  # to get Xvfb

set logfile = /tmp/${0:t}.log

# 
# use now as the plot time
# 
set plottime = `date -u +"%d-%b-%Y,%H:%M:00"`

#
# move the plot location to the current aircraft location
#
zstart -n -preserve -ds $ZEB_PROJDIR >& $logfile

dc_shiftloc --olat 25.000 --olon -70.000 --platform nrl_p3 \
	--dc     $ZEB_PROJDIR/dconfig/LFComposite_template.dc \
	--out_dc $ZEB_PROJDIR/dconfig/LFComposite.dc >& $logfile

if ($status) then
	echo Exiting on dc_shiftloc error
	exit 1
endif

#
# Plot
#
zplotbatch $plottime LFComposite auto >>& $logfile

#
# make a link to the latest image
#
sleep 10		# wait for the new png to be ready
cd $BATCH_IMAGE_SPOOL
set latest_img = latest_image.png

#
# look a few times until we find the new image available or we give up
#
@ try = 0
while ($try < 3)
   set new_img = `find . -name "*auto.png" -newer $latest_img | sort | tail -1`
   if ($new_img != "") break
   @ try++
   sleep 5
end

if ($new_img != "") then
	mv -f latest-4.png latest-5.png
	mv -f latest-3.png latest-4.png
	mv -f latest-2.png latest-3.png
	mv -f latest-1.png latest-2.png
	mv -f $latest_img latest-1.png
	ln -s $new_img $latest_img
else
	echo "No image available after $try tries"
endif