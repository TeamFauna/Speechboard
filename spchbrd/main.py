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
      id = db.DateTimeProperty(auto_now_add=True)

class MainHandler(webapp2.RequestHandler):
    def get(self):
        self.response.out.write(open("index.html").read()) #we have no template vars yet
        
class SpeechHandler(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/json'
        #out = json.dumps()
        out = '[{"speaker": "Noah","text": "I love poop","id": 3}]'
        self.response.out.write(out)
    def post(self):
        self.response.headers['Content-Type'] = 'text/json'
        raw_json = self.request.get("json")
        try:
            input = json.loads(raw_json)
        except ValueError, error:
            write_response(False, str(error))
            return 
        #convert json into database object  
        write_response(True)
        
    def write_response(success, message=""):
        self.response.out.write(json.dumps({"success": success, "message": message}))

app = webapp2.WSGIApplication([('/', MainHandler), ("/speech", SpeechHandler)],
                              debug=True)
