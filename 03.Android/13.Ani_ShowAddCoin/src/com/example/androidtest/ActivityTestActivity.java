
package com.example.androidtest;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;

public class ActivityTestActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    private AnimationPutBigClear mPutBig = new AnimationPutBigClear(this, R.id.textView1);
    
    public void onClickTx(View v){
        if (mPutBig == null)
            return;
        
        mPutBig.showText("+ 10");
    }
}
