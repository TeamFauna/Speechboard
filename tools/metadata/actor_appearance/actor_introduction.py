"""
Prints the timestamp at which a character first says something.

Test with 'python actor_introduction_test.py'
"""

import re
from first_character_line_iterator import ActorFirstLineIterator
from phrase_timestamp import PhraseTimestampLookup

DEBUG = False

def printCharacters(resources, callback):
  actorFirstLineIterator = ActorFirstLineIterator()
  actorFirstLineIterator.loadTranscript(resources['transcript'])

  phraseLookup = PhraseTimestampLookup()
  phraseLookup.loadSubtitles(resources['subs'])

  for actor, line in actorFirstLineIterator.getActorFirstLines():
    timestamp = phraseLookup.getTimestamp(line)
    if timestamp < 0:
      if DEBUG: print 'ERROR', "couldn't find line \"%s\" said by %s" %(line, actor)
      pass
    else:
      callback(actor, timestamp)

if __name__ == "__main__":
  subs = 'data/TLOTR.The.Fellowship.of.the.Ring.2001.Extended.BluRay.1080p.DTSES6.1.2Audio.x264-CHD.srt'
  transcript = 'data/LOTR_1ex_transcript.txt'
  def onActor(actor, time):
    print actor, time
  printCharacters({'transcript': transcript, 'subs': subs}, onActor)
