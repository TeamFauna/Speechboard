#!/usr/bin/env python
#
# Copyright 2007 Google Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
import webapp2
import os
import json

from google.appengine.ext import db

    
class Fragment(db.Model):
      """Models an individual Guestbook entry with an author, content, and date."""
      speaker = db.StringProperty()
      text = db.StringProperty(multiline=True)

class MainHandler(webapp2.RequestHandler):
    def get(self):
        self.response.out.write(open("index.html").read()) #we have no template vars yet
        
class SpeechHandler(webapp2.RequestHandler):
    def get(self):
        if self.request.get("test"):
            self.post()
            return
        self.response.headers['Content-Type'] = 'text/json'
        id = self.request.get("id")
        q = Fragment.all()
        #q.filter("id > " id)
        data = q.run(batch_size=1000)
        raw_out = []
        for offset, frag in enumerate(data):
            raw_out.append({"speaker": frag.speaker, "text": frag.text, "id": offset})
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
        fragment = Fragment(speaker=speaker, text=text)
        fragment.put()
        self.write_response(True)
        
    def write_response(self, success, message=""):
        self.response.out.write(json.dumps({"success": success, "message": message}))

app = webapp2.WSGIApplication([('/', MainHandler), ("/speech", SpeechHandler)],
                              debug=True)
