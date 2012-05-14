#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "FFT.h"
#include "WindowFunction.h"

using namespace std;

#define FFT_LEN 1024

struct Data {
  vector<float> audio;
  vector<float> spectrum;

  Data()
      : spectrum(FFT_LEN) {
  }
};

const unsigned NumMaleSubjects = 4;
const unsigned NumFemaleSubjects = 0;
const unsigned NumSubjects = NumMaleSubjects + NumFemaleSubjects;
const unsigned NumTests = 10;

const char Tests[NumTests][8] = {
  "N-A.raw",
  "N-E.raw",
  "N-N.raw",
  "N-S.raw",
  "N-T.raw",
  "Q-A.raw",
  "Q-E.raw",
  "Q-N.raw",
  "Q-S.raw",
  "Q-T.raw"
};

void ReadRawAudioFile(Data& data, string file_name);
void OutputSubjectJSON(FILE* output, Data* data);

FILE* test;

int main() {
  FFT fft(FFT_LEN);

  Data data[NumSubjects][NumTests];

  puts("Reading data...");

  test = fopen("test.txt", "w");

  for (unsigned i = 0; i < NumMaleSubjects; i++) {
    for (unsigned j = 0; j < NumTests; j++) {
      stringstream ss;
      ss << i;
      string file_name = "../../../data/Male" + ss.str() + "/" + Tests[j];
      ReadRawAudioFile(data[i][j], file_name);
    }
  }

  for (unsigned i = 0; i < NumFemaleSubjects; i++) {
    for (unsigned j = 0; i < NumTests; j++) {
      stringstream ss;
      ss << i;
      string file_name = "../../../data/Female" + ss.str() + "/" + Tests[j];
      ReadRawAudioFile(data[i + NumMaleSubjects * NumTests][j], file_name);
    }
  }

  puts("Transforming data...");

  for (unsigned i = 0; i < NumSubjects; i++) {
    for (unsigned j = 0; j < NumTests; j++) {

      for (unsigned k = 0; k < data[i][j].audio.size(); k++) {
        fprintf(test, "%f,", data[i][j].audio[k]);
      }
      fputs("\n", test);

      WindowFunction::Hann(data[i][j].audio);
      fft.ComputeSpectrum(data[i][j].audio, data[i][j].spectrum);
    }
  }

  fclose(test);

  puts("Outputing data...");

  FILE* output = fopen("../../../data/tests.json", "w");
  fputs("{\n", output);

  for (unsigned i = 0; i < NumMaleSubjects; i++) {
    fprintf(output, "\t\"Male%d\": {\n", i);
    OutputSubjectJSON(output, data[i]);
    fputs("\t},\n", output);
  }

  for (unsigned i = 0; i < NumFemaleSubjects; i++) {
    fprintf(output, "\t\"Female%d\": {\n", i);
    OutputSubjectJSON(output, data[i + NumMaleSubjects*NumTests]);
    fputs("\t}", output);
    if (i < NumFemaleSubjects - 1) {
      fputs(",", output);
    }
    fputs("\n", output);
  }

  fputs("}\n", output);
  fclose(output);

  puts("Cleaning up...");
}

void ReadRawAudioFile(Data& data, string file_name) {
  ifstream file;
  file.open(file_name.c_str(), ios::binary);

  file.seekg(0, ios::end);
  data.audio = vector<float>((file.tellg() / sizeof(float)));
  file.seekg(0, ios::beg);

  file.read((char*)&data.audio[0], data.audio.size() * sizeof(float));

  file.close();
}

void OutputSubjectJSON(FILE* output, Data* data) {
  for (unsigned i = 0; i < NumTests; i++) {
    fprintf(output, "\t\t\"%c%c%c\": [\n", Tests[i][0], Tests[i][1],
            Tests[i][2]);

    fprintf(output, "\t\t\t%f", data[i].spectrum[0]);
    for (unsigned j = 1; j < FFT_LEN; j++) {
      fprintf(output, ",%f", data[i].spectrum[j]);
    }
    fputs("\n\t\t]", output);
    if (i < NumTests - 1) {
      fputs(",", output);
    }
    fputs("\n", output);
  }
}

