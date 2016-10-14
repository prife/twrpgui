#!/bin/bash

ADB=fadb

function push_file() {
    local TMPDIR=/data/local/tmp
    local target=$(basename $1)
    local targetdir=$2

    $ADB push $1 $TMPDIR
    $ADB shell su 0 cp $TMPDIR/$target $targetdir
    $ADB shell su 0 rm $TMPDIR/$target
}

TWRES_PATH=/data/local/tmp/twres/

push_file appdemo/theme/portrait.xml $TWRES_PATH
push_file appdemo/theme/ui.xml $TWRES_PATH

#cd ~/workplace/aosp/android6.0/
cd ~/workplace/freemeos/droi6737/pcb
$ADB push out/target/product/q5c61q_gs_gmo/system/bin/testui /data/local/tmp
