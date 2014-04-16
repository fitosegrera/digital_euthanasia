import urllib
import json

url = "http://json-generator.appspot.com/j/bPwemdWZFe?indent=4"
req = urllib.urlopen(url)
data = json.load(req)
print req
#print data["id"]