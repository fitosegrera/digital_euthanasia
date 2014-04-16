from SparkCloudAPI import SparkCore
myCore = SparkCore('fitosegrera@gmail.com', 'Fito1015', '53ff6d065067544831330587')

print "----------------------------------------------------------"
print "Access Token: " + myCore.getAccessToken() #prints only the access token
#print myCore.getAllTokens() #prints the acces token, expiration date and client

print myCore.sendFunctionRequest('switchLED', 'on') #turn led ON
#print myCore.sendFunctionRequest('switchLED', 'off') #turn led OFF

i = 1;

while i <= 10:
	print myCore.readVariable('someVariable') #gets the name of a variable (replace 'someVariable' for the name of the variable)
	print myCore.readVariable('number')