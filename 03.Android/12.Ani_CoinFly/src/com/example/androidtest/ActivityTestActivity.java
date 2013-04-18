
package com.example.androidtest;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.graphics.Rect;
import android.view.Menu;
import android.view.View;

public class ActivityTestActivity extends Activity {

    private static AnimationCoinFly mAni = null;
    private FlyMsgHandler mHandle = new FlyMsgHandler();

    static class FlyMsgHandler extends Handler {
        @Override
        public void handleMessage(Message msg) {
            if (mAni != null && msg.what == AnimationCoinFly.BEGIN_SECOND_ANIMATION)
                mAni.beginSecondFly();
            super.handleMessage(msg);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);

        mAni = new AnimationCoinFly(this, mHandle);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    public void onFlyClick(View v) {
        View parentView = this.findViewById(R.id.tmpParentLayout);
        View endV = this.findViewById(R.id.endView);
        View fromV = this.findViewById(R.id.view1);
        Rect pRct = new Rect(parentView.getLeft(), parentView.getTop(), parentView.getRight(),
                parentView.getBottom());
        Rect endRct = new Rect(endV.getLeft(), endV.getTop(), endV.getRight(), endV.getBottom());
        mAni.beginFly(fromV, pRct, endRct);
    }
}
