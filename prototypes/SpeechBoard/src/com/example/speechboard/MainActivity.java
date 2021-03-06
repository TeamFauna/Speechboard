/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.speechboard;

import com.example.speechboard.R;
import com.example.speechboard.SpeechBoardListener;

import android.accounts.Account;
import android.accounts.AccountManager;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.os.Bundle;
import android.os.Handler;
import android.speech.RecognizerIntent;
import android.util.Log;
import android.util.Patterns;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Spinner;
import android.widget.SpinnerAdapter;
import android.widget.TextView;
import android.widget.Toast;
import android.speech.SpeechRecognizer;
import android.speech.RecognitionListener;
import android.speech.RecognizerIntent;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.regex.Pattern;

import org.apache.http.HttpResponse;
import org.apache.http.NameValuePair;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.params.HttpParams;
import org.json.JSONObject;

/**
 * Sample code that invokes the speech recognition intent API.
 */
public class MainActivity extends Activity implements OnClickListener {

    private static final String TAG = "VoiceRecognition";

    private static final int VOICE_RECOGNITION_REQUEST_CODE = 1234;

    private ListView mList;
    
    private ArrayList<String> mResults;

    private Handler mHandler;

    private Spinner mSupportedLanguageView;
    
    private SpeechRecognizer mSpeaker;
    private RecognitionListener mListener;
    
    private boolean mRunning;
    
    private String mUser;
    

    /**
     * Called with the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mHandler = new Handler();

        // Inflate our UI from its XML layout description.
        setContentView(R.layout.activity_main);

        // Get display items for later interaction
        Button speakButton = (Button) findViewById(R.id.btn_speak);

        mList = (ListView) findViewById(R.id.list);
        mResults = new ArrayList<String>();
        mList.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1,
        		mResults));

        mSupportedLanguageView = (Spinner) findViewById(R.id.supported_languages);
        
        
        mSpeaker = SpeechRecognizer.createSpeechRecognizer(getApplicationContext());
        mListener = new SpeechBoardListener(this);
        mRunning = false;
        
        mSpeaker.setRecognitionListener(mListener);
        
        mUser = getAccountName();
        

        // Check to see if a recognition activity is present
        PackageManager pm = getPackageManager();
        List<ResolveInfo> activities = pm.queryIntentActivities(
                new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH), 0);
        if (activities.size() != 0) {
            speakButton.setOnClickListener(this);
        } else {
            speakButton.setEnabled(false);
            speakButton.setText("Recognizer not present");
        }

        // Most of the applications do not have to handle the voice settings. If the application
        // does not require a recognition in a specific language (i.e., different from the system
        // locale), the application does not need to read the voice settings.
        refreshVoiceSettings();
    }
    
    
    
    public static HttpResponse makeRequest(String path, List<NameValuePair> params) throws Exception 
    {

        //map is similar to a dictionary or hash

        //instantiates httpclient to make request
        DefaultHttpClient httpclient = new DefaultHttpClient();

        //url with the post data
        HttpPost httpost = new HttpPost(path);



        //passes the results to a string builder/entity
        //StringEntity se = new StringEntity(params.toString());

        UrlEncodedFormEntity ram = new UrlEncodedFormEntity(params);
        Log.d("ha", ram.toString());
        Log.d("ha", path.toString());
        
        //sets the post request as the resulting string
        //httpost.setEntity(se);
        httpost.setEntity(ram);
         
        //sets a request header so the page receving the request will know what to do with it
        //httpost.setHeader("Accept", "application/json");
        //httpost.setHeader("Content-type", "application/json");

        //Handles what is returned from the page 
        Log.d("ha", "sending http");
        HttpResponse response = httpclient.execute(httpost);
        return response;
    }
    
    private String getAccountName() {
    	String result = new String("Holder");
    	
    	Pattern emailPattern = Patterns.EMAIL_ADDRESS; // API level 8+
    	Account[] accounts = AccountManager.get(getBaseContext()).getAccounts();
    	for (Account account : accounts) {
    	    if (emailPattern.matcher(account.name).matches()) {
    	         result = account.name;
    	    }
    	}
    	Log.d("ha", "AccountName: " + result);
    	return result;
    }
  
    public void onEndOfResults(ArrayList<String> res) {
    	
    	if (mRunning == true) {
            startVoiceRecognitionService();
    	}
    	if (res != null) {
    		mResults.add(res.get(0));
    		mList.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1,
    				mResults));
    		
    		final String result = res.get(0);
    		
    		Thread thread = new Thread()
    		{
    		    @Override
    		    public void run() {
    		    	try {
    	    			List<NameValuePair> nameValuePairs = new ArrayList<NameValuePair>(2);  
    	    			nameValuePairs.add(new BasicNameValuePair("speaker", mUser));  
    	    			nameValuePairs.add(new BasicNameValuePair("text", result	)); 
    	    			/*JSONObject data = new JSONObject();
    	    			data.put("speaker", mUser);
    	    			data.put("text", res.get(0));*/
    	    			String path = "http://spchbrd.appspot.com/speech";
    	    			HttpResponse response = makeRequest(path, nameValuePairs);
    	    			
    	    			Log.d("ha", "response result: " + response.toString());
    	    		}
    	    		catch  (Exception e){
    	    			Log.d("ha", "Failed Send " + e.getMessage() + e.toString());
    	    		}             
    		    }
    		};
    		
    		thread.start();

 
    		
    	}
    }

    /**
     * Handle the click on the start recognition button.
     */
    public void onClick(View v) {
        if (v.getId() == R.id.btn_speak) {
        	if (mRunning) {
        		mRunning = false;
        		stopVoiceRecognitionService();
        		
        		((Button)v).setText("Start");
        	}
        	else {
        		mRunning = true;
        		((Button)v).setText("Stop");
        		startVoiceRecognitionService();
        	}
        }
    }
    private void stopVoiceRecognitionService() {
    	mSpeaker.stopListening();
    }
    private void startVoiceRecognitionService() {
    	mSpeaker.stopListening();
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);
    	//Intent intent = new Intent(RecognizerIntent.ACTION_WEB_SEARCH);

        // Specify the calling package to identify your application
        intent.putExtra(RecognizerIntent.EXTRA_CALLING_PACKAGE, getClass().getPackage().getName());

        // Display an hint to the user about what he should say.
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Speech recognition demo");
        
        // Continuous Listening
        //intent.putExtra(RecognizerIntent.EXTRA_RESULTS_PENDINGINTENT, RecognizerIntent.EXTRA_RESULTS_PENDINGINTENT_BUNDLE);

        //intent.putExtra(RecognizerIntent.EXTRA_PARTIAL_RESULTS, true);
        
        // Given an hint to the recognizer about what the user is going to say
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);

        // Specify how many results you want to receive. The results will be sorted
        // where the first result is the one with higher confidence.
        intent.putExtra(RecognizerIntent.EXTRA_MAX_RESULTS, 1);

        // Specify the recognition language. This parameter has to be specified only if the
        // recognition has to be done in a specific language and not the default one (i.e., the
        // system locale). Most of the applications do not have to set this parameter.
        if (!mSupportedLanguageView.getSelectedItem().toString().equals("Default")) {
            intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE,
                    mSupportedLanguageView.getSelectedItem().toString());
        }
        
        mSpeaker.startListening(intent);
    }

    /**
     * Fire an intent to start the speech recognition activity.
     */
    private void startVoiceRecognitionActivity() {
        Intent intent = new Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH);

        // Specify the calling package to identify your application
        intent.putExtra(RecognizerIntent.EXTRA_CALLING_PACKAGE, getClass().getPackage().getName());

        // Display an hint to the user about what he should say.
        intent.putExtra(RecognizerIntent.EXTRA_PROMPT, "Speech recognition demo");

        // Given an hint to the recognizer about what the user is going to say
        intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL,
                RecognizerIntent.LANGUAGE_MODEL_FREE_FORM);

        // Specify how many results you want to receive. The results will be sorted
        // where the first result is the one with higher confidence.
        intent.putExtra(RecognizerIntent.EXTRA_MAX_RESULTS, 100);

        // Specify the recognition language. This parameter has to be specified only if the
        // recognition has to be done in a specific language and not the default one (i.e., the
        // system locale). Most of the applications do not have to set this parameter.
        if (!mSupportedLanguageView.getSelectedItem().toString().equals("Default")) {
            intent.putExtra(RecognizerIntent.EXTRA_LANGUAGE,
                    mSupportedLanguageView.getSelectedItem().toString());
        }

        startActivityForResult(intent, VOICE_RECOGNITION_REQUEST_CODE);
    }

    /**
     * Handle the results from the recognition activity.
     */
    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (requestCode == VOICE_RECOGNITION_REQUEST_CODE && resultCode == RESULT_OK) {
            // Fill the list view with the strings the recognizer thought it could have heard
            ArrayList<String> matches = data.getStringArrayListExtra(
                    RecognizerIntent.EXTRA_RESULTS);
            float floats[] = data.getFloatArrayExtra(RecognizerIntent.EXTRA_CONFIDENCE_SCORES);
            
            ArrayList<String> finalStrs = new ArrayList<String>();
            
            for (int i = 0; i < matches.size(); i++) {
            	finalStrs.add((String)matches.get(i).concat(Float.toString(floats[i])));
            	
            }
            
            mList.setAdapter(new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1,
            		finalStrs));
            
            //mList2.setAdapter(new ArrayAdapter<Float>(this, android.R.layout.simple_list_item_1, floats ));
        }

        super.onActivityResult(requestCode, resultCode, data);
    }

    private void refreshVoiceSettings() {
        Log.i(TAG, "Sending broadcast");
        sendOrderedBroadcast(RecognizerIntent.getVoiceDetailsIntent(this), null,
                new SupportedLanguageBroadcastReceiver(), null, Activity.RESULT_OK, null, null);
    }

    private void updateSupportedLanguages(List<String> languages) {
        // We add "Default" at the beginning of the list to simulate default language.
        languages.add(0, "Default");

        SpinnerAdapter adapter = new ArrayAdapter<CharSequence>(this,
                android.R.layout.simple_spinner_item, languages.toArray(
                        new String[languages.size()]));
        mSupportedLanguageView.setAdapter(adapter);
    }

    private void updateLanguagePreference(String language) {
        TextView textView = (TextView) findViewById(R.id.language_preference);
        textView.setText(language);
    }

    /**
     * Handles the response of the broadcast request about the recognizer supported languages.
     *
     * The receiver is required only if the application wants to do recognition in a specific
     * language.
     */
    private class SupportedLanguageBroadcastReceiver extends BroadcastReceiver {

        @Override
        public void onReceive(Context context, final Intent intent) {
            Log.i(TAG, "Receiving broadcast " + intent);

            final Bundle extra = getResultExtras(false);

            if (getResultCode() != Activity.RESULT_OK) {
                mHandler.post(new Runnable() {
                    //@Override
                    public void run() {
                        showToast("Error code:" + getResultCode());
                    }
                });
            }

            if (extra == null) {
                mHandler.post(new Runnable() {
                    //@Override
                    public void run() {
                        showToast("No extra");
                    }
                });
            }

            if (extra.containsKey(RecognizerIntent.EXTRA_SUPPORTED_LANGUAGES)) {
                mHandler.post(new Runnable() {

                    //@Override
                    public void run() {
                        updateSupportedLanguages(extra.getStringArrayList(
                                RecognizerIntent.EXTRA_SUPPORTED_LANGUAGES));
                    }
                });
            }

            if (extra.containsKey(RecognizerIntent.EXTRA_LANGUAGE_PREFERENCE)) {
                mHandler.post(new Runnable() {

                    //@Override
                    public void run() {
                        updateLanguagePreference(
                                extra.getString(RecognizerIntent.EXTRA_LANGUAGE_PREFERENCE));
                    }
                });
            }
        }

        private void showToast(String text) {
            Toast.makeText(MainActivity.this, text, 1000).show();
        }
    }
}
