#include <cstdio>

#include "FFT.h"
#include "WindowFunction.h"

#define FFT_LEN 1024

struct Data {
  float* audio;
  unsigned length;
  float spectrum[FFT_LEN];

  Data()
      : audio(NULL)
      , length(0) {
  }
};

const unsigned NumMaleSubjects = 4;
const unsigned NumFemaleSubjects = 0;
const unsigned NumSubjects = NumMaleSubjects + NumFemaleSubjects;
const unsigned NumTests = 10;

const char Tests[NumTests][8] = {
  "N-A.raw",
  "N-E.raw",
  "N-M.raw",
  "N-S.raw",
  "N-T.raw",
  "Q-A.raw",
  "Q-E.raw",
  "Q-N.raw",
  "Q-S.raw",
  "Q-T.raw"
};

void ReadRawAudioFile(Data& data, char* file_name);
void OutputSubjectJSON(FILE* output, Data* data);

int main() {
  FFT fft(FFT_LEN);

  Data data[NumSubjects][NumTests];

  for (unsigned i = 0; i < NumMaleSubjects; i++) {
    for (unsigned j = 0; j < NumTests; j++) {
      char file_name[64];
      sprintf(file_name, "../../../data/Male%d/%s", i, Tests[j]);
      ReadRawAudioFile(data[i][j], file_name);
    }
  }

  for (unsigned i = 0; i < NumFemaleSubjects; i++) {
    for (unsigned j = 0; i < NumTests; j++) {
      char file_name[64];
      sprintf(file_name, "../../../data/Female%d/%s", i, Tests[j]);
      ReadRawAudioFile(data[i + NumMaleSubjects * NumTests][j], file_name);
    }
  }

  for (unsigned i = 0; i < NumSubjects; i++) {
    for (unsigned j = 0; j < NumTests; j++) {
      WindowFunction::Hann(data[i][j].audio, data[i][j].length);
      fft.ComputeSpectrum(data[i][j].audio, data[i][j].length,
                          data[i][j].spectrum);
    }
  }

  FILE* output = fopen("../../../data/tests.json", "w");
  fputs("{\n", output);

  for (unsigned i = 0; i < NumMaleSubjects; i++) {
    fprintf(output, "\t'Male%d': {\n", i);
    OutputSubjectJSON(output, data[i]);
    fputs("\t},\n", output);
  }

  for (unsigned i = 0; i < NumFemaleSubjects; i++) {
    fprintf(output, "\t'Female%d': {\n", i);
    OutputSubjectJSON(output, data[i + NumMaleSubjects*NumTests]);
    fputs("\t},\n", output);
  }

  fputs("}\n", output);
  fclose(output);

  for (unsigned i = 0; i < NumSubjects; i++) {
    for (unsigned j = 0; j < NumTests; j++) {
      delete[] data[i][j].audio;
    }
  }
}

void ReadRawAudioFile(Data& data, char* file_name) {
  FILE* file = fopen(file_name, "rb");
  
  fseek(file, 0, SEEK_END);
  data.length = ftell(file) / sizeof(float);
  fseek(file, 0, SEEK_SET);

  data.audio = new float[data.length];
  fread(data.audio, sizeof(float), data.length, file);

  fclose(file);
}

void OutputSubjectJSON(FILE* output, Data* data) {
  for (unsigned i = 0; i < NumTests; i++) {
    fprintf(output, "\t\t'test': '%c%c%c',\n", Tests[i][0], Tests[i][1],
            Tests[i][2]);

    fputs("\t\t'data': [\n\t\t\t", output);
    for (unsigned j = 0; j < data[i].length; j++) {
      fprintf(output, "%d,", data[i].audio[j]);
    }
    fputs("\n\t\t],\n", output);
  }
}

