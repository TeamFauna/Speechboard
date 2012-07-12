package com.example.speechboardserver;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState); 
        setContentView(R.layout.activity_main);
                        
        String text = "";
        String rawJson = readRawTextFile(getApplicationContext(), R.raw.response);                
        try {
        	JSONObject json = new JSONObject(rawJson);
        	JSONArray phrases = json.getJSONArray("phrases");
        	for (int i = 0; i < phrases.length(); i++) {
        		JSONObject phraseObj = phrases.getJSONObject(i);
        		if (i != 0) text += ' ';
            	text += phraseObj.getString("text");                                        
        	}
		} catch (JSONException e) {
			Log.d("## Speechboard", "failed to load Json!");
			e.printStackTrace();
		}                       
        
        TextView t = (TextView)findViewById(R.id.dialog);
        t.setText(text);
     }    

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_main, menu);
        return true;
    }
    
    public static String readRawTextFile(Context ctx, int resId)
    {
         InputStream inputStream = ctx.getResources().openRawResource(resId);

            ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();

            int i;
             try {
              i = inputStream.read();
              while (i != -1)
                 {
                  byteArrayOutputStream.write(i);
                  i = inputStream.read();
                 }
                 inputStream.close();
             } catch (IOException e) {
                 return null;
             }
                return byteArrayOutputStream.toString();
    }
}