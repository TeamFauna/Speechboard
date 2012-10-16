from google.appengine.ext import db

class Meeting(db.Model):
      """Models a meeting with users and agenda_items"""
      name = db.StringProperty()
