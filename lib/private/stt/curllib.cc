#include <stdio.h>
#include <string.h>
//#include <string>
#include <stdlib.h>
 
#include <curl/curl.h>

//using std::string;

size_t callback(void *ptr, size_t size, size_t count, void *stream) {
    printf("THIS IS THE RESPONSE\n");
    ptr->:
    return size*count;
}

int speech_to_text(char* audio, size_t audiolength) {
  CURL *curl;
  CURLcode res;
  int* response;
 
  struct curl_slist *headerlist=NULL;
  
  curl_global_init(CURL_GLOBAL_ALL);
 
  curl = curl_easy_init();
  headerlist = curl_slist_append(headerlist, "Expect:");
  headerlist = curl_slist_append(headerlist, "Content-Type: audio/x-flac; rate=16000");
  printf("%s\n", headerlist->data);
  if(curl) {
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
    printf("%d\n", (*response));
 
    curl_easy_cleanup(curl);
 
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
