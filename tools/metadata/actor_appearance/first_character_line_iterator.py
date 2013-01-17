"""
Given a transcript file, iterates through the first line each character said.
"""

import re

class ActorFirstLineIterator:
  def __init__(self):
    self.currentActor = None
    self.currentPhrase = None
    self.visitedActors = set()

  def loadTranscript(self, filePath):
    self.transcript = open(filePath, 'r')

  def getActorFirstLines(self):
    line = self.transcript.readline()
    while line != '':
      actor, phrase = self.parseLine_(line)
      if actor is None or actor in self.visitedActors:
        line = self.transcript.readline()
        continue
      self.visitedActors.add(actor)
      yield (actor, phrase)

  def parseLine_(self, line):
    if not line.startswith("<<"):
      return (None, None)
    colonIndex = line.find(':')
    if colonIndex < 0:
      return (None, None)
    actor = line[2:colonIndex]
    actor = line[2:colonIndex]
    phrase = line[colonIndex+2:-3]
    phrase = self.parseNonText_(phrase)
    actor = self.parseNonText_(actor)
    return (actor, phrase)

  def parseNonText_(self, phrase):
    phrase = re.sub("<.+>", "", phrase).strip()
    phrase = re.sub("\(.+\)", "", phrase).strip()
    return phrase
