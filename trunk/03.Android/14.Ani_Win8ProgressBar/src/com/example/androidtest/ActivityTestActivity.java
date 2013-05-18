
package com.example.androidtest;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.View;

public class ActivityTestActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);
    }

    private FlyMsgHandler mHandle = new FlyMsgHandler(this);
    private AnimationWin8ProgressBar mAni = new AnimationWin8ProgressBar(this, mHandle);

    static class FlyMsgHandler extends Handler {
        private ActivityTestActivity mAct = null;
        FlyMsgHandler(ActivityTestActivity act){
            mAct = act;
        }
        @Override
        public void handleMessage(Message msg) {
            mAct.onAnimationMessage(msg);
            super.handleMessage(msg);
        }
    }
    
    private void onAnimationMessage(Message msg){
        if (mAni != null && msg.what == AnimationWin8ProgressBar.WIN8_PROGRESS_BAR_MSG)
            mAni.onAnimationMessage(msg);
    }

    @Override
    public void onWindowFocusChanged(boolean hasFocus) {
        if (mAni != null)
            mAni.initAnimation();
        
        super.onWindowFocusChanged(hasFocus);
    }
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    public void onBegin(View v){
        if (mAni == null)
            return;
        
        mAni.beginAnimation();
    }

    public void onStop(View v){
        if (mAni == null)
            return;
        
        mAni.stopAnimation();
    }
}
