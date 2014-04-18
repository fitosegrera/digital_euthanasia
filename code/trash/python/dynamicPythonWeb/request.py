#
#Calls the online digital_euthanasia script
#created by fito_segrera
#04/17/2014
#

import urllib2

loop = 1
while loop < 2:
	opener = urllib2.build_opener()
	opener.addheaders = [{'User-agent', 'Mozilla/5.0'}]
	url = "http://fii.to/cgi-bin/dynamicWeb.py"
	ourUrl = opener.open(url).read()
	print ourUrl