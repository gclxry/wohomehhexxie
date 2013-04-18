
package com.example.androidtest;

import android.os.Bundle;
import android.app.Activity;
import android.graphics.Rect;
import android.view.Menu;
import android.view.View;

public class ActivityTestActivity extends Activity {
    
    private AnimationCoinFly mAni = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);
        
        mAni = new AnimationCoinFly(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    public void onFlyClick(View v){
        View parentView = this.findViewById(R.id.tmpParentLayout);
        View endV = this.findViewById(R.id.endView);
        View fromV = this.findViewById(R.id.view1);
        Rect pRct = new Rect(parentView.getLeft(), parentView.getTop(), parentView.getRight(), parentView.getBottom());
        Rect endRct = new Rect(endV.getLeft(), endV.getTop(), endV.getRight(), endV.getBottom());
        mAni.beginFly(fromV, pRct, endRct);
    }
}
