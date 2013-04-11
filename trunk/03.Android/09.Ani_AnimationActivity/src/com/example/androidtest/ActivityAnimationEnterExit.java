package com.example.androidtest;

import com.ani.animationactivity.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;

public class ActivityAnimationEnterExit extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_animation_enter_exit);
    }

    public void onBackBtnClick(View v){

        Intent intent = new Intent();
        intent.setClass(this, ActivityTestActivity.class);
        startActivity(intent);
        this.finish();
    }
}
