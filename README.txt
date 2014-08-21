Updated: K Baker 31 July 2013

NOTE
There is an assumption that the SVN checkout directory in use is C:\EPICS - if this is not the case the paths below will need altering to appropriate values

Instructions
To alter the IOCs in use the XML file needs to be altered by hand, and can be found in:
C:\EPICS\ISIS\StartupConfig\StartupConfigApp\src\ProtoConfig.xml

To start all the IOCs (via procserv), the ISIS_example IOC (which monitors the VIs via Procserv), and the Python interface to allow for listing of available, running, idle and unknown IOC Statuses just run StartMonitorIOC.bat.

Please be aware that the various connections can take a couple of minutes to sort themselves out so the data in the python interface may not be immediately accurate as the IOC may not have connected to the procserv properly yet and is awaiting a retry.