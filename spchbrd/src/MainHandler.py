import webapp2

class MainHandler(webapp2.RequestHandler):
    def get(self):
        self.response.out.write(open("index.html").read()) #we have no template vars yet
