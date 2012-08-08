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
import jinja2
import os
from google.appengine.ext import db

templates = jinja2.Environment(
    loader=jinja2.FileSystemLoader(os.path.dirname(__file__)))
    
    
class Fragment(db.Model):
      """Models an individual Guestbook entry with an author, content, and date."""
      speaker = db.StringProperty()
      content = db.StringProperty(multiline=True)
      time_stamp = db.DateTimeProperty(auto_now_add=True)

class MainHandler(webapp2.RequestHandler):
    def get(self):
        template = templates.get_template('index.html')
        self.response.out.write(template.render({})) #we have no template vars yet
        
class SpeechHander(webapp2.RequestHandler):
    def get(self):
        self.response.headers['Content-Type'] = 'text/json'
        self.response.out.write("implementing this!")

app = webapp2.WSGIApplication([('/', MainHandler), ("/speech", SpeechHandler)],
                              debug=True)
