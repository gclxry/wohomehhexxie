
package com.example.androidtest;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

import com.ani.animationactivity.R;

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

    public void onGotoBtnClick(View v) {
        Intent intent = new Intent();
        intent.setClass(this, ActivityAnimationEnterExit.class);
        startActivity(intent);
        this.finish();
        // 设置切换动画，从右边进入，左边退出
        //overridePendingTransition(R.anim.in_from_right, R.anim.out_to_left);
    }
}
