TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#==================================================
# build a support library

PROD_IOC += StartupConfig

# xxxRecord.h will be created from xxxRecord.dbd
#DBDINC += xxxRecord
# install StartupConfig.dbd into <top>/dbd
DBD += StartupConfig.dbd

# specify all source files to be compiled and added to the library
#StartupConfig_SRCS += xxx
StartupConfig_SRCS += launch.cpp tinyxml2.cpp XMLParse.cpp

StartupConfig_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

