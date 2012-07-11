#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
 

using std::string;

string* callback(void *ptr, size_t size, size_t count, void *stream) {
    return (string*)stream;
}

string speech_to_text(char* audio, size_t audiolength) {
  CURL *curl;
  CURLcode res;
  string response;
 
  struct curl_slist *headerlist=NULL;
  
  curl_global_init(CURL_GLOBAL_ALL);
 
  curl = curl_easy_init();
  /* initalize custom header list (stating that Expect: 100-continue is not
     wanted */ 
  headerlist = curl_slist_append(headerlist, "Expect:");
  headerlist = curl_slist_append(headerlist, "Content-Type: audio/x-flac; rate=16000");
  printf("%s\n", headerlist->data);
  if(curl) {
    /* what URL that receives this POST */ 
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/speech-api/v1/recognize?xjerr=1&client=chromium&lang=en-US");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,(void*)audio );
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, audiolength);


    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    
    printf("Sending\n");
    res = curl_easy_perform(curl);

    printf("Response\n");
    printf("%s\n", response.c_str());
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    /* free slist */ 
    curl_slist_free_all (headerlist);
  }
  return 0;

}
 
int main(int argc, char *argv[])
{
  FILE* audioFile = fopen("hello.flac", "rb");
  fseek(audioFile, 0, SEEK_END);
  size_t audiolength = ftell(audioFile);
  fseek(audioFile, 0, SEEK_SET);

  char* audio = (char*)malloc(audiolength*sizeof(char));
  fread(audio, audiolength, sizeof(char), audioFile);

  speech_to_text(audio, audiolength);

  return 0;
}
