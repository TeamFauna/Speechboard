import re
from first_character_line_iterator import ActorFirstLineIterator
from phrase_timestamp import PhraseTimestampLookup
import actor_introduction

DEBUG = True

"""Print the timestamp at which a character first appears"""
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


def test():
  DEBUG = True
  def assertEquals (a, b):
    if a != b:
      print 'FAILED', "expected \"%s\" to equal \"%s\"" % (a, b)

  def assertNotReached():
    print 'FAILED', "expect to not reach this statement"

  pippinTime = ((3 * 60 + 6) * 60 + 13) * 1000 + 800
  merryTime = pippinTime
  legolasTime = ((3 * 60 + 7) * 60 + 27) * 1000 + 400
  aragornTime = legolasTime

  def testActorFirstLineIterator():
    actorFirstLineIterator = ActorFirstLineIterator()
    (actor, line) = actorFirstLineIterator.parseLine_('sduihfsduhfs')
    assertEquals(actor, None)

    (actor, phrase) = actorFirstLineIterator.parseLine_('<<Sally: I like farts>>\n')
    assertEquals(actor, 'Sally')
    assertEquals(phrase, 'I like farts')

    (actor, phrase) = actorFirstLineIterator.parseLine_('<<Sally: <farting> I like farts (loudly)>>\n')
    assertEquals(actor, 'Sally')
    assertEquals(phrase, 'I like farts')

    actorFirstLineIterator.loadTranscript('data/test_transcript.txt')
    results = [result for result in actorFirstLineIterator.getActorFirstLines()]

    assertEquals(results[0][0], 'Pippin')
    assertEquals(results[0][1], 'Hey!')

    assertEquals(results[1][0], 'Merry')
    assertEquals(results[1][1], 'Over here!')

    assertEquals(results[2][0], 'Legolas')
    assertEquals(results[2][1], 'The Horn of Gondor!')

    assertEquals(results[3][0], 'Aragorn')
    assertEquals(results[3][1], 'Boromir!')

    assertEquals(len(results), 4)

  def testPhraseTimestampLookup():
    phraseLookup = PhraseTimestampLookup()
    phraseLookup.loadSubtitles('data/test_subs.txt')

    assertEquals(phraseLookup.getTimestampForIndex_(32), pippinTime)

    assertEquals(phraseLookup.getTimestamp('Hey!'), pippinTime)
    assertEquals(phraseLookup.getTimestamp("Boromir"), aragornTime)

  def integrationTest():
    actorOrder = ['Pippin', 'Merry', 'Legolas', 'Aragorn']
    timeOrder = [pippinTime, merryTime, legolasTime, aragornTime]
    def onResult(actor, time):
      assertEquals(actor in actorOrder, True)
      assertEquals(time in timeOrder, True)

    printCharacters({'transcript': 'data/test_transcript.txt', 'subs': 'data/test_subs.txt'}, onResult)

  testActorFirstLineIterator()
  testPhraseTimestampLookup()
  integrationTest()

if __name__ == "__main__":
  test()
