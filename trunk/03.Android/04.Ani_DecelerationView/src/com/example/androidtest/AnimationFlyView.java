
package com.example.androidtest;

import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.TranslateAnimation;

public class AnimationFlyView implements Animation.AnimationListener {

    AnimationSet animationSet = null;
    TranslateAnimation translateAnimationx = null;
    TranslateAnimation translateAnimationy = null;
    private View mFlyView = null;

    public void setFlyView(View flyView) {
        mFlyView = flyView;
    }

    public void fly() {
        if (mFlyView == null)
            return;

        // 此处必须设为false
        // true表示应用AnimationSet的Interpolator效果，false表示应用各个动画对象自己的Interpolator效果
        animationSet = new AnimationSet(false);

        // X轴匀速运动
        translateAnimationx = new TranslateAnimation(
                Animation.ABSOLUTE, 0,
                Animation.ABSOLUTE, 220,
                Animation.ABSOLUTE, 0,
                Animation.ABSOLUTE, -280);
        translateAnimationx.setDuration(1000);
        translateAnimationx.setInterpolator(new DecelerateInterpolator());
        translateAnimationx.setAnimationListener(this);
        
        // Y轴回滚运动
//        translateAnimationy = new TranslateAnimation(
//                Animation.ABSOLUTE, 0,
//                Animation.ABSOLUTE, 0,
//                Animation.ABSOLUTE, 0,
//                Animation.ABSOLUTE, 600);
//        translateAnimationy.setDuration(1000);
//        translateAnimationy.setInterpolator(new AnimationFlyViewInterpolator());
        animationSet.addAnimation(translateAnimationx);
        //animationSet.addAnimation(translateAnimationy);

        mFlyView.setAnimation(animationSet);
        animationSet.start();
    }

    @Override
    public void onAnimationStart(Animation animation) {
        // TODO Auto-generated method stub

    }

    @Override
    public void onAnimationEnd(Animation animation) {
        // TODO Auto-generated method stub

    }

    @Override
    public void onAnimationRepeat(Animation animation) {
        // TODO Auto-generated method stub

    }

}
