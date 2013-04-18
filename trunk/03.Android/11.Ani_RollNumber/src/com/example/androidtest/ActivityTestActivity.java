
package com.example.androidtest;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;

public class ActivityTestActivity extends Activity {

    private static AnimationRollNumber mRollAni = null;
    private EditText mEdit = null;

    private RollMsgHandler mHandler = new RollMsgHandler();
    static class RollMsgHandler extends Handler {
        @Override
        public void handleMessage(Message msg) {
            if (mRollAni != null && msg.what == AnimationRollNumber.CONTINUE_ANIMATION){
                mRollAni.continueAnimation((AnimationRollNumber.NumberView)msg.obj);
            }
            super.handleMessage(msg);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);
        
        mRollAni = new AnimationRollNumber(this, mHandler);
        mEdit = (EditText) this.findViewById(R.id.editText1);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }
    
    public void onClick(View v){
        if (mRollAni == null || mEdit == null)
            return;

        String strInt = mEdit.getText().toString();
        int nToInt = Integer.valueOf(strInt);
        mRollAni.addNumber(nToInt);
    }
}
