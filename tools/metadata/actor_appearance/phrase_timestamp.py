"""
Given a phrase, returns the time in milliseconds it was said.
"""

import re

DEBUG = False

class PhraseTimestampLookup:
  def loadSubtitles(self, filePath):
    self.subs = open(filePath, 'r').read().lower()

  def getTimestamp(self, phrase):
    for matchIndex in self.findPotentialMatches_(phrase.lower()):
      if matchIndex > 0:
        return self.getTimestampForIndex_(matchIndex)
    return -1 # phrase not found :(

  def findPotentialMatches_(self, fullPhrase):
    for phrase in self.getSubPhrases_(fullPhrase):
      yield self.exactMatch_(phrase)
      yield self.noEndingPunctMatch_(phrase)
      yield self.noPunctMatch_(phrase)
      yield self.charOnlyMatch_(phrase)

  def getSubPhrases_(self, phrase):
    yield phrase
    for length in [30, 20, 10]:
      yield phrase[length:]
      yield phrase[:-length]
      yield phrase[int(length * .5):int(length * 1.5)]
      yield phrase[length:length*2]
      yield phrase[length*2:length*3]
      yield phrase[length*3:length*4]
      yield phrase[length*4:length*5]

  def exactMatch_(self, phrase):
    return self.subs.find(phrase)

  def noEndingPunctMatch_(self, phrase):
    return self.subs.find(re.sub("[.?!]", "", phrase))

  def noPunctMatch_(self, phrase):
    return self.subs.find(re.sub("[.,?!]", "", phrase))

  def charOnlyMatch_(self, phrase):
    return self.subs.find(re.sub("[;:'\".,?!]", "", phrase))

  def getTimestampForIndex_(self, index):
    timeEnd = self.subs.rfind(' --> ', 0, index)
    time = self.subs[timeEnd-12:timeEnd]
    try:
      return self.getMilliseconds_(int(time[0:2]), int(time[3:5]), int(time[6:8]), int(time[9:12]))
    except:
      if DEBUG: print 'ERROR', "\"%s\" should be a timestamp" % (time)
      return -1

  def getMilliseconds_(self, hours, mins, secs, millisecs):
    return ((hours * 60 + mins) * 60 + secs) * 1000 + millisecs
