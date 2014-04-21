#!/usr/bin/python   
################################################################################
#DEADMAN'S_SWITCH
#Read data from the digital_euthanasia wearable piece check if the user is dead; 
#if true, then COMMIT DIGITAL EUTHANASIA...
#created by fito_segrera
#04/17/2014
################################################################################
print('Content-type: text/html\r\n\r')

import urllib2 #For calling webpage
import simplejson #For reading json objects
import smtplib #For sending e-mails 

fromaddr = 'fitosegrera@gmail.com' #gmail account that from where the email is sent 
toaddrs  = 'segrr140@newschool.edu' #email that will recieve 
msg = 'IT IS MY ULTIMATE WILL TO COMMIT DIGITAL EUTHANASIA...' #message 

# Credentials (if needed)  
username = 'fitosegrera'  
password = 'Fito1015'  

url = "https://api.spark.io/v1/devices/53ff6d065067544831330587/result?access_token=547bae3d9ab1cfeef5e92ee9e2901ff617eb8f22"

req = urllib2.Request(url)
data = urllib2.build_opener()
f = data.open(req)
json = simplejson.load(f)
dataClean = json['result']
print json['result']
if dataClean == '1': #As a debugger if the potentiometer's value reaches 100 the system sends an email...
	print "User #293679 is diseased... This is his ultimate will of commiting DIGITAL EUTHANASIA!!"
	# The actual mail send  
	server = smtplib.SMTP('smtp.gmail.com:587')  
	server.starttls()  
	server.login(username,password)  
	server.sendmail(fromaddr, toaddrs, msg)  
	server.quit() 

#########################################################################################
## THE FOLLOWING LINES REFER TO THE JSON OBJECT AS POSTED BY THE SPARK CORE AT THE API ##
#########################################################################################
#"cmd": "VarReturn",
#"name": "result",
#"result": "{\"data1\":23,\"data2\":26,}",
#"coreInfo": {
#"last_app": "",
#"last_heard": "2014-02-17T20:37:53.300Z",
#"connected": true,
#"deviceID": "YOUR-DEVICE-ID-HERE"
#}

#########################################################
## THE FOLLOWING LINES WRITE DIRECTLY TO THE HTML FILE ##
#########################################################
#print "<TITLE>Digital EUthanasia Scrip</TITLE>"
#print "<H1>This is my first CGI script</H1>"