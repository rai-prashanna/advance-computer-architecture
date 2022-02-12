#!/bin/bash

COURSE_HOME=/it/kurs/avdark/vt18
AVDARK_PIN_VERSION=pin-2.11-49306-gcc.3.4.6-ia32_intel64-linux

PIN_VERSION_DIR=${COURSE_DIR}/${AVDARK_PIN_VERSION}
PIN_CURRENT=./pin

if [ -e ${PIN_CURRENT} ]; then
    echo "There is already a PIN version installed in the lab directory"
else

    if [ -d ${COURSE_HOME}/${AVDARK_PIN_VERSION} ]
    then
  echo "Setting up a symlink to the current PIN version..."
  ln -s ${COURSE_HOME}/${AVDARK_PIN_VERSION} ${PIN_CURRENT}
    else
	echo "Can't find the system's PIN instalation."
	echo "Make sure you are using on of the specified department server."
	echo "Otherwise, ask a TA."
    fi

    echo "Done. Pin has been installed in: $PIN_CURRENT"
fi
