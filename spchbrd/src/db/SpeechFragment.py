from google.appengine.ext import db

class SpeechFragment(db.Model):
      """Models an individual Guestbook entry with an author, content, and date."""

      #this probably needs to be changed
      speaker_id = db.StringProperty()
      meeting_id = db.StringProperty()
      text = db.StringProperty(multiline=True)
      time_stamp = db.DateProperty()
      agenda_item_id = db.StringProperty()
