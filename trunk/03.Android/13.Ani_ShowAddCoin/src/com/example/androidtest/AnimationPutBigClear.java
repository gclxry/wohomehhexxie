package com.example.androidtest;

import android.app.Activity;
import android.content.Context;
import android.graphics.Rect;
import android.view.View;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationSet;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.ScaleAnimation;
import android.view.animation.TranslateAnimation;
import android.widget.TextView;

public class AnimationPutBigClear {

    private final int SHOW_TIME_ANI = 3000;
    private TextView mAniView = null;
    private Rect mFromRct = new Rect(0, 0, 0, 0);
    private boolean mbAnimationEnd = true;
    private Context mContext = null;
    private int mTextViewId = 0;
    
    public AnimationPutBigClear(Context context, int nTextViewId) {
        mContext = context;
        mTextViewId = nTextViewId;
    }
    
    public void showText(String strText){
        if (mContext == null || strText == null || strText.length() <= 0 || mTextViewId == 0)
            return;
        
        if (mAniView == null){
            Activity act = (Activity)mContext;
            if (act == null)
                return;
            mAniView = (TextView) act.findViewById(mTextViewId);
            
            if (mAniView != null){
                mFromRct.left = mAniView.getLeft();
                mFromRct.right = mAniView.getRight();
                mFromRct.top = mAniView.getTop();
                mFromRct.bottom = mAniView.getBottom();
            }
        }
        
        if (mAniView == null)
            return;
        
        stopAnimation();
        mAniView.setText(strText);
        //mAniView.layout(mFromRct.left, mFromRct.top, mFromRct.right, mFromRct.bottom);
        mAniView.setVisibility(View.VISIBLE);

        // 动画集合
        AnimationSet aniSet = new AnimationSet(false);

        // 渐变动画
        AlphaAnimation alphaAni = new AlphaAnimation(0.3f, 1.0f);
        alphaAni.setDuration(SHOW_TIME_ANI);
        aniSet.addAnimation(alphaAni);
        
        // 放大缩小动画
        ScaleAnimation scaleAni = new ScaleAnimation(1.0f, 2.0f, 1.0f, 2.0f);
        scaleAni.setDuration(SHOW_TIME_ANI);
        aniSet.addAnimation(scaleAni);

        // Y轴移动动画
        TranslateAnimation tranAni = new TranslateAnimation(0, 0,  0, -70);
        //tranAni.setInterpolator(new DecelerateInterpolator());
        tranAni.setDuration(SHOW_TIME_ANI);
        aniSet.addAnimation(tranAni);
        
        aniSet.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
                mbAnimationEnd = false;
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {
                stopAnimation();
            }
        });

        // 开始动画
        mAniView.startAnimation(aniSet);
    }
    
    private void stopAnimation(){
        if (mbAnimationEnd)
            return;
        mbAnimationEnd = true;

        mAniView.clearAnimation();
        mAniView.setVisibility(View.INVISIBLE);
    }
}
