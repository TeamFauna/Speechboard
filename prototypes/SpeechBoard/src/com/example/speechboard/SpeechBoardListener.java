package com.example.speechboard;

import java.util.ArrayList;

import android.os.Bundle;
import android.speech.RecognitionListener;
import android.speech.SpeechRecognizer;
import android.util.Log;

/***
 * 
 * @author willhughes
 * 
 * This class handles the results from the sst mechanism
 *
 */
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
		if (error == 7 || error == 6 || error == 6) {
			mAct.onEndOfResults(null);
		}
	}

	public void onEvent(int eventType, Bundle params) {
		// Current doesn't do anything

	}

	public void onPartialResults(Bundle partialResults) {
		// Partial Results don't always return from google
		// If needed find a workaround.
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
