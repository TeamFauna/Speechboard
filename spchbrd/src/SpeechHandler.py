import webapp2
import os
import json

from db.SpeechFragment import SpeechFragment

class SpeechHandler(webapp2.RequestHandler):
    def get(self):
        if self.request.get("test"):
            self.post()
            return
        self.response.headers['Content-Type'] = 'text/json'
        id = self.request.get("id")
        q = SpeechFragment.all()
        #q.filter("id > " id)
        data = q.run(batch_size=1000)
        raw_out = []
        for offset, frag in enumerate(data):
            raw_out.append({"speaker": frag.speaker_id, "text": frag.text, "id": offset})
        out = json.dumps(raw_out)
        
        #out = '[{"speaker": "Noah","text": "I love poop","id": 3}]'
        self.response.out.write(out)
    def post(self):
        self.response.headers['Content-Type'] = 'text/json'
        speaker = self.request.get("speaker")
        text = self.request.get("text")
        if speaker == "" or text == "":
            self.write_response(False, "No speaker or text specified!")
            return
        fragment = SpeechFragment(speaker_id=speaker, text=text)
        fragment.put()
        self.write_response(True)
        
    def write_response(self, success, message=""):
        self.response.out.write(json.dumps({"success": success, "message": message}))
