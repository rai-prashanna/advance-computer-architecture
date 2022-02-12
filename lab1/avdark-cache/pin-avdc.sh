#!/bin/bash
#
# Wrapper script to execute PIN with the AvDark cache simulator
# module.
#
# Course: Advanced Computer Architecture, Uppsala University
# Course Part: Lab assignment 1
#
# Author: Andreas Sandberg <andreas.sandberg@it.uu.se>
# Revision (2015, 2016, 2017, 2018, 2022): German Ceballos, Johan Janzen, Chris Sakalis, Per Ekemark
#

LAB_DIR=${LAB_DIR:-".."}
PIN_HOME=${PIN_HOME:-${LAB_DIR}/pin}

PIN=${PIN_HOME}/pin

TOOL="${LAB_DIR}/avdark-cache/obj-intel64/avdc.so"

if [ `basename $PWD` == "avdark-cache" ] && \
    [ -e "$PWD/obj-intel64/avdc.so" ]; then
    TOOL="$PWD/obj-intel64/avdc.so"
fi

if [ ! -e "${TOOL}" ]; then
    echo "Can't find the PIN module for the AvDark cache simulator." 1>&2
    echo "Make sure that you built the PIN module prior to using this script." 1>&2
    exit 1
fi

if [ ! -x "${PIN}" ]; then
    echo "Can't find PIN or the pin binary isn't executable" 1>&2
    exit 1
fi

$PIN -t "${TOOL}" $*
