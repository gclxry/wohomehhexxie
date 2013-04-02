
package com.example.androidtest;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;

import com.ani.flyimageview.R;

public class ActivityTestActivity extends Activity {

    private AnimationFlyView mFly = new AnimationFlyView();
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);
        
        mFly.setFlyView(this.findViewById(R.id.FlyImageView));
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    public void onFlyBtnClick(View v){
        mFly.fly();
    }
}
