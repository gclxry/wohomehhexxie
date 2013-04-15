
package com.example.androidtest;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.widget.Button;

public class ActivityTestActivity extends Activity {

    private Button mBtn = null;
    private int count = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);

        mBtn = (Button) this.findViewById(R.id.button1);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    public void onButtonClick(View v) {
        if (mBtn == null)
            return;

        applyRotation(0, 180);
    }

    private void applyRotation(float start, float end) {
        // 计算中心点
        final float centerX = mBtn.getWidth() / 2.0f;
        final float centerY = mBtn.getHeight() / 2.0f;
        final Rotate3dAnimation rotation = new Rotate3dAnimation(start, end,
                centerX, centerY, 0.0f, false);
        
        rotation.setDuration(500);
        rotation.setFillAfter(true);
        rotation.setInterpolator(new AccelerateInterpolator());
        
        // 设置监听
        rotation.setAnimationListener(new DisplayNextView());
        mBtn.startAnimation(rotation);
    }

    private final class DisplayNextView implements Animation.AnimationListener {

        @Override
        public void onAnimationStart(Animation animation) {
        }

        // 动画结束
        @Override
        public void onAnimationEnd(Animation animation) {
            mBtn.post(new SwapViews());
        }

        @Override
        public void onAnimationRepeat(Animation animation) {
        }
    }

    private final class SwapViews implements Runnable {
        public void run() {
            final float centerX = mBtn.getWidth() / 2.0f;
            final float centerY = mBtn.getHeight() / 2.0f;
            Rotate3dAnimation rotation = null;
            mBtn.requestFocus();
            rotation = new Rotate3dAnimation(180, 0, centerX, centerY, 0.0f,
                    false);
            rotation.setDuration(500);
            rotation.setFillAfter(true);
            rotation.setInterpolator(new DecelerateInterpolator());
            // 开始动画
            mBtn.startAnimation(rotation);
            mBtn.setText(String.valueOf(count++));
        }
    }
}
