package com.example.speechboard;

import java.util.ArrayList;

import android.os.Bundle;
import android.speech.RecognitionListener;
import android.speech.SpeechRecognizer;
import android.util.Log;

public class SpeechBoardListener implements RecognitionListener {

	private MainActivity mAct;
	public SpeechBoardListener(MainActivity activity) {
		mAct = activity;
	}
	
	public void onBeginningOfSpeech() {
		// TODO Auto-generated method stub
		Log.d("ha", "onBeginningOfSpeech");
	}

	public void onBufferReceived(byte[] buffer) {
		// TODO Auto-generated method stub
		//Log.d("ha", "onBufferReceived");

	}

	public void onEndOfSpeech() {
		// TODO Auto-generated method stub
		Log.d("ha", "onEndOfSpeech");

	}

	public void onError(int error) {
		// TODO Auto-generated method stub
		Log.d("ha", "onError " + Integer.toString(error));
		if (error == 7) {
			mAct.onEndOfResults(null);
		}
	}

	public void onEvent(int eventType, Bundle params) {
		// TODO Auto-generated method stub
		//Log.d("ha", "onEvent");

	}

	public void onPartialResults(Bundle partialResults) {
		// TODO Auto-generated method stub

		/*Log.d("ha", "onPartialResults");
		if(partialResults != null){
			ArrayList<String> res = partialResults.getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION);
			
			if (res != null){
				Log.d("ha", "PartialResults: " + res.toString());
			}
			else {
				Log.d("ha", "pr res is null");
			}
		}
		else {
			Log.d("ha", "pr is null");
		}*/
	}

	public void onReadyForSpeech(Bundle params) {
		// TODO Auto-generated method stub

		Log.d("ha", "onReadyForSpeech");
	}

	public void onResults(Bundle results) {
		// TODO Auto-generated method stub

		Log.d("ha", "onResults");
		
		ArrayList<String> res = results.getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION);
		
		Log.d("ha", "Results: " + res.toString());
		
		mAct.onEndOfResults(res);
		
	}

	public void onRmsChanged(float rmsdB) {
		// TODO Auto-generated method stub

		//Log.d("ha", "onRmsChanged");
	}

}
