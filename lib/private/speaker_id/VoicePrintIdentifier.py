DIFFERENCE_THRESHOLD = 2

class VoicePrintIdentifier:
    voice_prints = []

    def identify(self, voice_print):
        if not self.voice_prints:
            self.voice_prints.append(voice_print)
            return 0

        for id, stored_voice_print in enumerate(self.voice_prints):
            diff = self.compare(stored_voice_print, voice_print)
            print "\tDEBUG", "comparing", str(id) + ":", diff
            if diff < DIFFERENCE_THRESHOLD:
                self.merge(stored_voice_print, voice_print)
                return id

        self.voice_prints.append(voice_print)
        return len(self.voice_prints) - 1


    def compare(self, voice_print1, voice_print2):
        assert(len(voice_print1) == len(voice_print2))
        total_diff = 0
        for i in range(len(voice_print1)):
            diff = voice_print1[i] - voice_print2[i]
            total_diff += diff * diff
        return total_diff


    def merge(self, voice_print1, voice_prints2):
        pass


if __name__ == "__main__":
    import json
    import random

    voice_prints_file = file("../../../data/tests.json")
    voice_prints_json = json.load(voice_prints_file)

    voice_prints = []
    for speaker_name in voice_prints_json:
        tests = voice_prints_json[speaker_name]
        for test_name in tests:
            test_data = {"speaker": speaker_name, "test": test_name, "data": tests[test_name]}
            voice_prints.append(test_data)
    random.shuffle(voice_prints)

    identifier = VoicePrintIdentifier()
    for voice_print in voice_prints:
        id = identifier.identify(voice_print["data"])
        print voice_print["speaker"], voice_print["test"] + ":", id
