#!../../bin/windows-x64-debug/isis_example

## You may have to change isis_example to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/isis_example.dbd"
isis_example_registerRecordDeviceDriver pdbbase

## Configure IPPorts
REP1

## Load record instances
REP2

cd ${TOP}/iocBoot/${IOC}
iocInit

## Configure Sequencers
REP3
