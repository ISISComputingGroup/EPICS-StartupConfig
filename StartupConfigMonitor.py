import xml.etree.ElementTree as ET
import os
from epics import *

prefix = os.environ.get('MYPVPREFIX', None)

ioclist = []
iocrun = []
iocidle = []
iocunk = []  

welcome = "Welcome to the Startup Config Monitor."
menu1 = "Please select a function:\r\n\t(v)iew the current status of the IOCs\r\n\tsta(r)t an IOC\r\n\t(s)top an IOC\r\n\t(q)uit"
current = "The current status of the IOCs are:"
start = "Please enter the full name of the IOC to start:"
stop = "Please enter the full name of the IOC to stop:"
prompt = ">"
farewell = "Thank you for using the Startup Config Monitor.\r\nGoodbye."
unrecognised = "That is an unrecognised function."
iocerror_start = "It isn't possible to start that IOC."
iocerror_stop = "It isn't possible to stop that IOC."

def get_ioclist(file):
	tree = ET.parse(file)
	root = tree.getroot()
	for a in root:
		if a.tag == "iocname":
			ioclist.append(a.text)
		for b in a:
			if b.tag == "iocname":
				ioclist.append(b.text)
			for c in b:
				if c.tag == "iocname":
					ioclist.append(c.text)

def display_status():
	print current
	print("Available: %s" %ioclist)
	print("Running: %s" %iocrun)
	print("Idle: %s" %iocidle)
	print("Unknown: %s" %iocunk)
	
def update_status():
	del iocrun[:]
	del iocidle[:]
	del iocunk[:]
	for a in ioclist:
		p = prefix + a + ":STATUS"
		v = PV(p)
		if v.value == 0:
			iocrun.append(a)
		elif v.value == 1:
			iocidle.append(a)
		else:
			iocunk.append(a)

def stop_ioc(ioc):
	update_status()
	if ioc in iocrun:
		p = prefix + ioc + ":STOP"
		v = PV(p)
		v.value = 1
	else:
		print iocerror_stop
		
		
def start_ioc(ioc):
	update_status()
	if ioc in iocidle:
		p = prefix + ioc + ":START"
		v = PV(p)
		v.value = 1
	else:
		print iocerror_start

def get_input(message):
	print message
	selection = raw_input(prompt)
	return selection

print welcome			
get_ioclist("C:/EPICS/ISIS/StartupConfig/StartupConfigApp/src/ProtoConfig.xml")
update_status()
display_status()
while True:
	print menu1
	selection = raw_input(prompt)
	if selection == "q":
		print farewell
		exit(0)
	elif selection == "v":
		update_status()
		display_status()
	elif selection == "r":
		print start
		selection = raw_input(prompt)
		start_ioc(selection)
	elif selection == "s":
		print stop
		selection = raw_input(prompt)
		stop_ioc(selection)
	else:
		print unrecognised