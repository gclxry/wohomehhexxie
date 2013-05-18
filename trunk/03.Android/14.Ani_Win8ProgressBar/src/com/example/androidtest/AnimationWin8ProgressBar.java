
package com.example.androidtest;

import android.app.Activity;
import android.content.Context;
import android.graphics.Rect;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.animation.AccelerateDecelerateInterpolator;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.TranslateAnimation;

public class AnimationWin8ProgressBar {

    // 继续下一个动画的消息
    public final static int WIN8_PROGRESS_BAR_MSG = 101;
    // 第一个运动结束后，每个点之间的间隔
    private final int POINT_SPACE_SIZE = 30;
    // 动画时间
    private final int ANIMATION_TIME = 800;
    // 初始点的大小
    private final int POINT_SIZE = 6;
    // 点的个数
    private final int POINT_CTNS = 5;
    // 每个运动粒子的时间间隔
    private final int POINT_SPACE_TIME = ((ANIMATION_TIME * 2) / POINT_CTNS);
    // 是否在动画中
    private boolean mInAni = false;

    private Rect mBaseRct = new Rect(0, 0, 0, 0);
    private Rect mBeginRct = new Rect(0, 0, 0, 0);
    private Rect[] mDstRct1List = new Rect[POINT_CTNS];
    private Rect mDstRct2 = new Rect(0, 0, 0, 0);

    private Context mContext;
    private Handler mHandler;

    private View[] mViewList = new View[POINT_CTNS];
    private Runnable[] mDstRunnable1 = new Runnable[POINT_CTNS];
    private Runnable[] mDstRunnable2 = new Runnable[POINT_CTNS];

    public AnimationWin8ProgressBar(Context context, Handler handler) {
        mContext = context;
        mHandler = handler;
    }

    public int dip2px(float dpValue) {
        if (mContext == null)
            return 0;

        final float scale = mContext.getResources().getDisplayMetrics().density;
        return (int) (dpValue * scale + 0.5f);
    }

    public boolean initAnimation() {
        if (mContext == null || mHandler == null)
            return false;

        Activity act = (Activity) mContext;
        if (act == null)
            return false;

        View baseView = act.findViewById(R.id.W8PB_Layout);
        if (baseView == null)
            return false;

        mBaseRct.left = baseView.getLeft();
        mBaseRct.right = baseView.getRight();
        mBaseRct.top = baseView.getTop();
        mBaseRct.bottom = baseView.getBottom();
        if (mBaseRct.width() <= 0)
            return false;

        addView(R.id.W8PB_V1, 0);
        addView(R.id.W8PB_V2, 1);
        addView(R.id.W8PB_V3, 2);
        addView(R.id.W8PB_V4, 3);
        addView(R.id.W8PB_V5, 4);

        int nPointSize = dip2px(POINT_SIZE);

        int nMidMoveSize = POINT_SPACE_SIZE * (POINT_CTNS - 1);
        for (int i = 0; i < POINT_CTNS; i++) {
            Rect dstRct = new Rect(0, 0, 0, 0);
            mDstRct1List[i] = dstRct;

            dstRct.left = (mBaseRct.width() - nPointSize) / 2 + nMidMoveSize / 2;
            dstRct.left = dstRct.left - POINT_SPACE_SIZE * i;
            dstRct.right = dstRct.left + nPointSize;
            dstRct.top = 0;
            dstRct.bottom = nPointSize;
        }

        mDstRct2.left = mBaseRct.width();
        mDstRct2.right = mDstRct2.left + nPointSize;
        mDstRct2.top = 0;
        mDstRct2.bottom = nPointSize;

        // 初始化每个点的起始位置
        initViewBeginPoint();
        return true;
    }

    // 初始化每个点的起始位置
    private void initViewBeginPoint() {
        int nPointSize = dip2px(POINT_SIZE);
        mBeginRct.left = mBeginRct.top = 0;
        mBeginRct.right = mBeginRct.bottom = nPointSize;
        for (int i = 0; i < POINT_CTNS; i++) {
            initViewPosition(mViewList[i]);
        }
    }

    private void initViewPosition(View v) {
        if (v == null)
            return;

        v.clearAnimation();
        v.setVisibility(View.INVISIBLE);
        v.layout(mBeginRct.left, mBeginRct.right, mBeginRct.top, mBeginRct.bottom);
    }

    private void addView(int nId, int nIndex) {
        if (mContext == null || mHandler == null || nIndex < 0 || nIndex >= POINT_CTNS)
            return;

        Activity act = (Activity) mContext;
        if (act == null)
            return;

        mViewList[nIndex] = act.findViewById(nId);
    }

    public void stopAnimation() {
        for (int i = 0; i < POINT_CTNS; i++) {
            View v = mViewList[i];
            if (v == null)
                continue;
            v.clearAnimation();
        }

        initViewBeginPoint();
        mInAni = false;
    }

    public boolean beginAnimation() {
        if (mContext == null || mHandler == null)
            return false;

        // 先初始化
        if (mBaseRct.width() <= 0) {
            if (!initAnimation())
                return false;
        }

        // 判断是否已经初始化
        if (mBaseRct.width() <= 0)
            return false;

        // 判断是否在动画中
        if (mInAni)
            return true;

        mInAni = true;
        begin_1_Animation(mViewList[0], 0);
        return true;
    }

    private void begin_1_Animation(final View v, final int nIndex) {
        if (v == null || nIndex < 0 || nIndex >= POINT_CTNS || mHandler == null)
            return;

        v.setVisibility(View.VISIBLE);
        if (mDstRunnable1[nIndex] == null) {
            mDstRunnable1[nIndex] = new Runnable() {
                @Override
                public void run() {
                    if (nIndex + 1 < POINT_CTNS) {
                        begin_1_Animation(mViewList[nIndex + 1], nIndex + 1);
                    }
                }
            };
        }

        TranslateAnimation tranAni = new TranslateAnimation(0, mDstRct1List[nIndex].left
                - mBeginRct.left, 0, 0);
        tranAni.setInterpolator(new AccelerateDecelerateInterpolator());
        tranAni.setDuration(ANIMATION_TIME);
        tranAni.setFillAfter(true);
        tranAni.setFillEnabled(true);

        tranAni.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
                // 开始下一个点的动画
                v.postDelayed(mDstRunnable1[nIndex], POINT_SPACE_TIME);
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {
                if (nIndex == POINT_CTNS - 1) {
                    Message msg = mHandler.obtainMessage(WIN8_PROGRESS_BAR_MSG);
                    msg.arg1 = 0;
                    msg.arg2 = 2;
                    msg.obj = mViewList[0];
                    mHandler.sendMessage(msg);
                }
            }
        });

        v.startAnimation(tranAni);
    }

    private void begin_2_Animation(final View v, final int nIndex) {
        if (v == null || nIndex < 0 || nIndex >= POINT_CTNS || mHandler == null)
            return;

        if (mDstRunnable2[nIndex] == null) {
            mDstRunnable2[nIndex] = new Runnable() {
                @Override
                public void run() {
                    if (nIndex + 1 < POINT_CTNS) {
                        begin_2_Animation(mViewList[nIndex + 1], nIndex + 1);
                    }
                }
            };
        }

        TranslateAnimation tranAni = new TranslateAnimation(mDstRct1List[nIndex].left
                - mBeginRct.left,
                mDstRct2.left - mBeginRct.left, 0, 0);
        tranAni.setDuration(ANIMATION_TIME);

        tranAni.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
                // 开始下一个点的动画
                v.postDelayed(mDstRunnable2[nIndex], POINT_SPACE_TIME);
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {
                v.setVisibility(View.INVISIBLE);
                if (nIndex == POINT_CTNS - 1) {
                    Message msg = mHandler.obtainMessage(WIN8_PROGRESS_BAR_MSG);
                    msg.arg1 = 0;
                    msg.arg2 = 1;
                    msg.obj = mViewList[0];
                    mHandler.sendMessage(msg);
                }
            }
        });

        v.startAnimation(tranAni);
    }

    public void onAnimationMessage(Message msg) {
        if (msg == null || msg.what != WIN8_PROGRESS_BAR_MSG || msg.obj == null || msg.arg1 < 0
                || msg.arg1 > POINT_CTNS)
            return;

        if (msg.arg2 == 2) {
            begin_2_Animation((View) msg.obj, msg.arg1);
        } else if (msg.arg2 == 1) {
            begin_1_Animation((View) msg.obj, msg.arg1);
        }
    }
}
