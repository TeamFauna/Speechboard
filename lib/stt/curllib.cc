/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2011, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at http://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/ 
/* Example code that uploads a file name 'foo' to a remote script that accepts
 * "HTML form based" (as described in RFC1738) uploads using HTTP POST.
 *
 * The imaginary form we'll fill in looks like:
 *
 * <form method="post" enctype="multipart/form-data" action="examplepost.cgi">
 * Enter file: <input type="file" name="sendfile" size="40">
 * Enter file name: <input type="text" name="filename" size="30">
 * <input type="submit" value="send" name="submit">
 * </form>
 *
 * This exact source code has not been verified to work.
 */ 
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#include <curl/curl.h>
 
int main(int argc, char *argv[])
{
  CURL *curl;
  CURLcode res;
 
  struct curl_slist *headerlist=NULL;
  
  FILE* audioFile = fopen("hello.flac", "rb");
  fseek(audioFile, 0, SEEK_END);
  size_t audiolength = ftell(audioFile);
  fseek(audioFile, 0, SEEK_SET);

  char* audio = (char*)malloc(audiolength*sizeof(char));
  fread(audio, audiolength, sizeof(char), audioFile);
  printf("START\n");
 
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

    printf("%d\n",curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist));
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,(void*)audio );
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, audiolength);

    printf("Sending\n");
    res = curl_easy_perform(curl);

    printf("Response\n");
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
 
    /* free slist */ 
    curl_slist_free_all (headerlist);
  }
  return 0;
}
