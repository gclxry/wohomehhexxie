
package com.example.androidtest;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.OvershootInterpolator;
import android.view.animation.TranslateAnimation;

import com.ani.drawerview.R;

public class ActivityTestActivity extends Activity {

    private View mTopView = null;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);
        
        mTopView = this.findViewById(R.id.TopLayout);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    private boolean mbOpen = false;
    public void onTopButtonClick(View v){
        mbOpen = !mbOpen;
        if (mbOpen)
            horizontalMoveView(0.8f);
        else
            horizontalMoveView(-0.8f);
    }
    
    

    // 水平移动View，带有缓冲阻尼震荡效果
    public void horizontalMoveView(final float fCut) {
        if (mTopView == null)
            return;

        TranslateAnimation animation = new TranslateAnimation(
                Animation.RELATIVE_TO_PARENT, 0f,
                Animation.RELATIVE_TO_PARENT, fCut,
                Animation.RELATIVE_TO_PARENT, 0f,
                Animation.RELATIVE_TO_PARENT, 0f);
        animation.setInterpolator(new DecelerateInterpolator());
        animation.setDuration(300);

        animation.setAnimationListener(new Animation.AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {
                if (mTopView == null)
                    return;
                
                View pV = (View) mTopView.getParent();
                float fLeft = (float)pV.getWidth() * fCut;
                // 动画结束了，需要将View直接定位到动画的最后一帧，不然，就又回去了
                int left = mTopView.getLeft() + (int) fLeft;
                int top = mTopView.getTop();
                int width = mTopView.getWidth();
                int height = mTopView.getHeight();
                mTopView.clearAnimation();
                mTopView.layout(left, top, left + width, top + height);
            }
        });

        mTopView.startAnimation(animation);
    }
}
