
package com.example.androidtest;

import java.util.ArrayList;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.graphics.Rect;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.animation.AccelerateInterpolator;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.RotateAnimation;
import android.view.animation.TranslateAnimation;
import android.view.animation.Animation.AnimationListener;

public class AnimationCoinFly {

    public final static int BEGIN_SECOND_ANIMATION = 100;
    
    private final String TAG = "gamehome.AnimationCoinFly";
    // 出现的硬币的最大数量
    private final int MAX_COIN_COUNT = 10;
    // 出现的硬币的最小数量
    private final int MINI_COIN_COUNT = 7;
    // 硬币的最大滑动时间
    private final int MAX_FLY_TIME = 600;
    // 硬币的最小滑动时间
    private final int MINI_FLY_TIME = 300;
    // 最大旋转角度
    private final int MAX_REVOLVE = 360;
    // 抛出金币最小距离
    private final int MINI_RUN_SIZE = 40;
    // 飞行的View列表
    private ArrayList<FlyView> mViewList = new ArrayList<FlyView>();
    // 随机数
    private Random mRandom = new Random();
    private Context mContext = null;
    private View mFlyParentView = null;
    private Handler mHandler = null;

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
        // 是否正在动画中
        public boolean bInAni = false;
        // 是否被选中进行动画
        public boolean bNeedAni = false;
    }
    
    public AnimationCoinFly(Context context, Handler handler) {
        mContext = context;
        mHandler = handler;
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
                View v9 = acti.findViewById(R.id.FC_Coin9);
                View v10 = acti.findViewById(R.id.FC_Coin10);

                if (mFlyParentView != null && v1 != null && v2 != null &&
                        v3 != null && v4 != null && v5 != null &&
                        v6 != null && v7 != null && v8 != null &&
                        v9 != null && v10 != null) {
                    appendFlyView(v1);
                    appendFlyView(v2);
                    appendFlyView(v3);
                    appendFlyView(v4);
                    appendFlyView(v5);
                    appendFlyView(v6);
                    appendFlyView(v7);
                    appendFlyView(v8);
                    appendFlyView(v9);
                    appendFlyView(v10);
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

        if (tmpView == null || mViewList.size() < MAX_COIN_COUNT
                || mFlyParentView == null || firstFlyRct.isEmpty())
            return;

        int nViewCtns = 0;
        while (nViewCtns < MINI_COIN_COUNT || nViewCtns > MAX_COIN_COUNT) {
            nViewCtns = mRandom.nextInt() % (MAX_COIN_COUNT + 1);
        }

        int nLeft = tmpView.getLeft();
        int nRight = tmpView.getRight();
        int nTop = tmpView.getTop() + firstFlyRct.top;
        int nBottom = nTop + tmpView.getHeight();

        int nBigLeft = nLeft - MINI_RUN_SIZE;
        int nBigTop = firstFlyRct.height() - tmpView.getHeight();

        // 初始化飞行数据
        for (int i = 0; i < mViewList.size(); i++) {
            FlyView flyV = mViewList.get(i);
            if (flyV == null || flyV.flyView == null)
                continue;

            flyV.bNeedAni = (i < nViewCtns);
            flyV.bInAni = false;
            flyV.flyView.layout(nLeft, nTop, nRight, nBottom);
            flyV.flyView.setVisibility(flyV.bNeedAni ? View.VISIBLE : View.INVISIBLE);

            flyV.fromRect.left = nLeft;
            flyV.fromRect.right = nRight;
            flyV.fromRect.top = nTop;
            flyV.fromRect.bottom = nBottom;

            flyV.dstRect1.left = -1;
            while (flyV.dstRect1.left < 0) {
                flyV.dstRect1.left = mRandom.nextInt() % nBigLeft;
            }
            flyV.dstRect1.right = flyV.dstRect1.left + tmpView.getWidth();
            flyV.dstRect1.top = -1;
            while (flyV.dstRect1.top < 0) {
                flyV.dstRect1.top = mRandom.nextInt() % nBigTop;
            }
            flyV.dstRect1.top = flyV.dstRect1.top + firstFlyRct.top;
            flyV.dstRect1.bottom = flyV.dstRect1.top + tmpView.getHeight();

            flyV.fFlyRevolve = 0.0f;
            flyV.bFlyWithRevolve = ((mRandom.nextInt() % 2) == 0);
            if (flyV.bFlyWithRevolve) {
                flyV.fFlyRevolve = -1.0f;
                while (flyV.fFlyRevolve < 0.0f) {
                    flyV.fFlyRevolve = (float) (mRandom.nextInt() % (MAX_REVOLVE + 1));
                }
            }

            flyV.nFlyTime = 0;
            while (flyV.nFlyTime < MINI_FLY_TIME || flyV.nFlyTime > MAX_FLY_TIME) {
                flyV.nFlyTime = mRandom.nextInt() % (MAX_FLY_TIME + 1);
            }

            flyV.dstRect2.left = dstRct.left;
            flyV.dstRect2.right = dstRct.right;
            flyV.dstRect2.top = dstRct.top;
            flyV.dstRect2.bottom = dstRct.bottom;
        }

        // 开始飞行
        for (int i = 0; i < mViewList.size(); i++) {
            FlyView flyV = mViewList.get(i);
            beginFirstFly(flyV);
        }
    }

    private void beginFirstFly(final FlyView flyV) {
        if (flyV == null || flyV.flyView == null || !flyV.bNeedAni)
            return;

        // 动画集合
        AnimationSet aniSet = new AnimationSet(false);

        if (flyV.bFlyWithRevolve) {
            // 旋转动画
            RotateAnimation rotateAni = new RotateAnimation(0f, 360.0f, Animation.RELATIVE_TO_SELF,
                    0.5f,
                    Animation.RELATIVE_TO_SELF, 0.5f);
            rotateAni.setInterpolator(new DecelerateInterpolator());
            rotateAni.setDuration(flyV.nFlyTime);
            aniSet.addAnimation(rotateAni);
        }

        // X轴、Y轴移动动画
        TranslateAnimation tranAni = new TranslateAnimation(0, flyV.dstRect1.left
                - flyV.fromRect.left,
                0, flyV.dstRect1.top - flyV.fromRect.top);
        tranAni.setInterpolator(new DecelerateInterpolator());
        tranAni.setDuration(flyV.nFlyTime);
        aniSet.addAnimation(tranAni);
        
        aniSet.setFillAfter(true);
        aniSet.setFillEnabled(true);

        aniSet.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {

                flyV.bInAni = false;

                int nCtns = 0;
                for (int i = 0; i < mViewList.size(); i++) {
                    FlyView flyV = mViewList.get(i);
                    if (flyV.bInAni)
                        break;

                    nCtns++;
                }

                if (nCtns == mViewList.size() && mHandler != null) {
                    Message msg = mHandler.obtainMessage(BEGIN_SECOND_ANIMATION);
                    mHandler.sendMessage(msg);
                }
            }
        });

        // 开始动画
        flyV.bInAni = true;
        flyV.flyView.startAnimation(aniSet);
    }

    public void beginSecondFly() {
        for (int i = 0; i < mViewList.size(); i++) {
            FlyView flyV = mViewList.get(i);
            beginSecondFlyByView(flyV);
        }
    }

    private void beginSecondFlyByView(final FlyView flyV) {
        if (flyV == null || flyV.flyView == null || !flyV.bNeedAni)
            return;

        flyV.bInAni = true;
        // 先矫正当前的控件的位置
        flyV.flyView.layout(flyV.dstRect1.left, flyV.dstRect1.top, flyV.dstRect1.right,
                flyV.dstRect1.bottom);
        
        // 动画集合
        AnimationSet aniSet = new AnimationSet(false);

        // 渐变动画
        AlphaAnimation alphaAni = new AlphaAnimation(1.0f, 0.2f);
        alphaAni.setDuration(flyV.nFlyTime);
        aniSet.addAnimation(alphaAni);

        // X轴、Y轴移动动画
        int nLeftMove = flyV.dstRect2.left - flyV.dstRect1.left;
        TranslateAnimation tranAni = new TranslateAnimation(0, nLeftMove,
                0, flyV.dstRect2.top - flyV.dstRect1.top);
        tranAni.setInterpolator(new AccelerateInterpolator());
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
                flyV.bInAni = false;
                flyV.flyView.setVisibility(View.INVISIBLE);
            }
        });

        // 开始动画
        flyV.bInAni = true;
        flyV.flyView.startAnimation(aniSet);
    }
}
