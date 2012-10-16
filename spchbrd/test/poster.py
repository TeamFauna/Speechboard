import urllib
import urllib2

url = 'http://localhost:8080/speech'
values = {'speaker':'willhughes01@gmail.com',
    'text':'teeeeeeesssst'}

data = urllib.urlencode(values)
req = urllib2.Request(url,data)
response = urllib2.urlopen(req)
the_page = response.read()

print the_page
