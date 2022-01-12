#!/bin/bash

if [[ $EUID -ne 0 ]]; then
   echo "This program must be run as root" 
   exit 1
fi

LD_LIBRARY_PATH=nethogs/src ./trigger $@
