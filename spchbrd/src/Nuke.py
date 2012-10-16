import webapp2

from db.SpeechFragment import SpeechFragment

class  Nuke(webapp2.RequestHandler):
    def get(self):
        q = SpeechFragment.all()
        data = q.run(batch_size=1000)
        for entity in data:
            entity.delete()
        self.response.out.write("deleted everything!!! like a bau5.")
