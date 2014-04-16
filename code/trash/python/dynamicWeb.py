#!/usr/bin/python   
print('Content-type: text/html\r\n\r')

import urllib2
import simplejson

url = "http://json-generator.appspot.com/j/bPwemdWZFe?indent=4"

if __name__ == '__main__':
	req = urllib2.Request(url)
	data = urllib2.build_opener()
	f = data.open(req)
	json = simplejson.load(f)

	for item in json:
		print item.get('id')

		try:
			print item.get('friends')[0]
		except:
			print "NO DATA FOUND..."

			if item.get('id') == 0:
				print "IT WORKS!!!"

#print "<TITLE>Digital EUthanasia Scrip</TITLE>"
#print "<H1>This is my first CGI script</H1>"
