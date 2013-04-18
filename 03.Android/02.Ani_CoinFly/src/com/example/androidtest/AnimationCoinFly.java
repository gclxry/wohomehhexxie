
package com.example.androidtest;

import java.util.ArrayList;
import java.util.Random;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.graphics.Rect;
import android.util.Log;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.RotateAnimation;
import android.view.animation.TranslateAnimation;
import android.view.animation.Animation.AnimationListener;

public class AnimationCoinFly {

    private final String TAG = "gamehome.AnimationCoinFly";
    // 出现的硬币的最大数量
    private int mCoinMaxCtns = 8;
    // 出现的硬币的最小数量
    private int mCoinMiniCtns = 5;
    // 硬币的最大滑动时间
    private int mMaxFlyTime = 500;
    // 硬币的最小滑动时间
    private int mMiniFlyTime = 200;
    // 最大旋转角度
    private int mRevolve = 90;
    // 飞行的View列表
    private ArrayList<FlyView> mViewList = new ArrayList<FlyView>();
    // 随机数
    private Random mRandom = new Random();
    private Context mContext = null;
    private View mFlyParentView = null;

    public class FlyView {
        // 飞行的View
        public View flyView = null;
        // 最初显示的位置
        public Rect fromRect = new Rect(0, 0, 0, 0);
        // 第一次飞行的目标矩形
        public Rect dstRect1 = new Rect(0, 0, 0, 0);
        // 第一次飞行是否旋转
        public boolean bFlyWithRevolve = false;
        // 第一次飞行的时间
        public int nFlyTime = 0;
        // 第一次飞行的旋转角度
        public float fFlyRevolve = 0.0f;
        // 第二次飞行的目标矩形
        public Rect dstRect2 = new Rect(0, 0, 0, 0);
    }

    public AnimationCoinFly(Context context) {
        mContext = context;
        if (mContext != null) {
            Activity acti = (Activity) mContext;
            if (acti != null) {
                mFlyParentView = acti.findViewById(R.id.FC_BaseLayout);
                View v1 = acti.findViewById(R.id.FC_Coin1);
                View v2 = acti.findViewById(R.id.FC_Coin2);
                View v3 = acti.findViewById(R.id.FC_Coin3);
                View v4 = acti.findViewById(R.id.FC_Coin4);
                View v5 = acti.findViewById(R.id.FC_Coin5);
                View v6 = acti.findViewById(R.id.FC_Coin6);
                View v7 = acti.findViewById(R.id.FC_Coin7);
                View v8 = acti.findViewById(R.id.FC_Coin8);

                if (mFlyParentView != null && v1 != null && v2 != null &&
                        v3 != null && v4 != null && v5 != null &&
                        v6 != null && v7 != null && v8 != null) {
                    appendFlyView(v1);
                    appendFlyView(v2);
                    appendFlyView(v3);
                    appendFlyView(v4);
                    appendFlyView(v5);
                    appendFlyView(v6);
                    appendFlyView(v7);
                    appendFlyView(v8);
                }
            }
        }
    }

    private void appendFlyView(View v) {
        if (v == null)
            return;

        FlyView flyV = new FlyView();
        flyV.flyView = v;
        flyV.flyView.setVisibility(View.INVISIBLE);
        mViewList.add(flyV);
    }

    @SuppressLint("NewApi")
    public void beginFly(View tmpView, Rect firstFlyRct, Rect dstRct) {

        if (tmpView == null || mViewList.size() < mCoinMaxCtns
                || mFlyParentView == null || firstFlyRct.isEmpty())
            return;

        int nViewCtns = 0;
        while (nViewCtns < mCoinMiniCtns || nViewCtns > mCoinMaxCtns) {
            nViewCtns = mRandom.nextInt() % (mCoinMaxCtns + 1);
        }
        
        int nLeft = tmpView.getLeft();
        int nRight = tmpView.getRight();
        int nTop = tmpView.getTop() + firstFlyRct.top;
        int nBottom = nTop + tmpView.getHeight();

        int nBigLeft = nLeft;
        int nBigTop = firstFlyRct.height() - tmpView.getHeight();

        // 初始化飞行数据
        for (int i = 0; i < mViewList.size(); i++) {
            FlyView flyV = mViewList.get(i);
            if (flyV == null || flyV.flyView == null)
                continue;

            flyV.flyView.layout(nLeft, nTop, nRight, nBottom);
            flyV.flyView.setVisibility(View.VISIBLE);

            flyV.fromRect.left = nLeft;
            flyV.fromRect.right = nRight;
            flyV.fromRect.top = nTop;
            flyV.fromRect.bottom = nBottom;

            flyV.dstRect1.left = -1;
            while (flyV.dstRect1.left < 0){
                flyV.dstRect1.left = mRandom.nextInt() % nBigLeft;
            }
            flyV.dstRect1.right = flyV.dstRect1.left + tmpView.getWidth();
            flyV.dstRect1.top = -1;
            while (flyV.dstRect1.top < 0){
                flyV.dstRect1.top = mRandom.nextInt() % nBigTop;
            }
            flyV.dstRect1.top = flyV.dstRect1.top + firstFlyRct.top;
            flyV.dstRect1.bottom = flyV.dstRect1.top + tmpView.getHeight();

            flyV.fFlyRevolve = 0.0f;
            flyV.bFlyWithRevolve = ((mRandom.nextInt() % 2) == 0);
            if (flyV.bFlyWithRevolve) {
                flyV.fFlyRevolve = -1.0f;
                while (flyV.fFlyRevolve < 0.0f){
                    flyV.fFlyRevolve = (float) (mRandom.nextInt() % (mRevolve + 1));
                }
            }

            flyV.nFlyTime = 0;
            while (flyV.nFlyTime < mMiniFlyTime || flyV.nFlyTime > mMaxFlyTime) {
                flyV.nFlyTime = mRandom.nextInt() % (mMaxFlyTime + 1);
            }

            flyV.dstRect2.left = dstRct.left;
            flyV.dstRect2.right = dstRct.right;
            flyV.dstRect2.top = dstRct.top;
            flyV.dstRect2.bottom = dstRct.bottom;
        }

        // 开始飞行
        for (int i = 0; i < nViewCtns; i++) {
            FlyView flyV = mViewList.get(i);
            beginFirstFly(i, flyV);
        }
    }

    private void beginFirstFly(int nNo, final FlyView flyV) {
        if (flyV == null || flyV.flyView == null)
            return;

        // 动画集合
        AnimationSet aniSet = new AnimationSet(false);

        if (flyV.bFlyWithRevolve){
            // 旋转动画
            RotateAnimation rotateAni = new RotateAnimation(0f, flyV.fFlyRevolve, Animation.RELATIVE_TO_SELF, 0.5f,
                    Animation.RELATIVE_TO_SELF, 0.5f);
            rotateAni.setDuration(flyV.nFlyTime);
            aniSet.addAnimation(rotateAni);
        }

        // X轴、Y轴移动动画
        int nLeftMove = flyV.dstRect1.left - flyV.fromRect.left;
        Log.v(TAG, "nNo=" + nNo + ", nLeftMove=" + nLeftMove);
        TranslateAnimation tranAni = new TranslateAnimation(0, nLeftMove,
                0, flyV.dstRect1.top - flyV.fromRect.top);
        tranAni.setInterpolator(new DecelerateInterpolator());
        tranAni.setDuration(flyV.nFlyTime);
        aniSet.addAnimation(tranAni);

        aniSet.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {
                // 动画结束了，需要将View直接定位到动画的最后一帧，不然，就又回去了
                flyV.flyView.clearAnimation();
                flyV.flyView.layout(flyV.dstRect1.left, flyV.dstRect1.top, flyV.dstRect1.right, flyV.dstRect1.bottom);
            }
        });

        // 开始动画
        flyV.flyView.startAnimation(aniSet);
    }
}
