
package com.example.androidtest;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.TranslateAnimation;
import android.view.animation.Animation.AnimationListener;

public class AnimationRollNumber {

    public final static int CONTINUE_ANIMATION = 101;
    // 显示的数字的位数
    private final int NUMBER_COUNTS = 6;
    // 个位数动画时间
    private final int ROLL_TIME = 600;
    private final int ROLL_TIME_STEP = 0;
    // 索引
    private final int OFFSET_G = 0;
    private final int OFFSET_S = 1;
    private final int OFFSET_B = 2;
    private final int OFFSET_Q = 3;
    private final int OFFSET_W = 4;
    private final int OFFSET_SW = 5;
    // 当前显示的数字
    private int mCurNum = 0;
    // 当前是否为增加动画
    private boolean mbUpAni = true;
    // 动画数字列表
    private int mAniNumList[] = new int[NUMBER_COUNTS];

    private Context mContext = null;
    private Handler mHandler = null;

    // 存储0-9图片的十张图的资源id
    private int mNumImgResIdList[] = new int[10];
    private ArrayList<NumberView> mViewList1 = new ArrayList<NumberView>();
    private ArrayList<NumberView> mViewList2 = new ArrayList<NumberView>();

    public class NumberView {
        public View numView = null;
        public int nCurNum = 0;
        public int nLoopCtns = 0;
        public int nAniTime = 0;
        public int nIndex = 0;
        public boolean bAniEnd = true;
        public NumberView braView = null;
        // 是否为上升动画
        public boolean bIsUpAni = true;
        // 是否为辅助动画View
        public boolean bHelpView = false;
        // 位置

        public void setViewImage(int nResId) {
            if (numView == null)
                return;
            numView.setBackgroundResource(nResId);
        }
    }

    public AnimationRollNumber(Context context, Handler handler) {
        mContext = context;
        mHandler = handler;

        mNumImgResIdList[0] = R.drawable.num_0;
        mNumImgResIdList[1] = R.drawable.num_1;
        mNumImgResIdList[2] = R.drawable.num_2;
        mNumImgResIdList[3] = R.drawable.num_3;
        mNumImgResIdList[4] = R.drawable.num_4;
        mNumImgResIdList[5] = R.drawable.num_5;
        mNumImgResIdList[6] = R.drawable.num_6;
        mNumImgResIdList[7] = R.drawable.num_7;
        mNumImgResIdList[8] = R.drawable.num_8;
        mNumImgResIdList[9] = R.drawable.num_9;

        if (mContext != null) {
            Activity acti = (Activity) mContext;
            if (acti != null) {
                View v1_1 = acti.findViewById(R.id.RN_G_1);
                View v1_2 = acti.findViewById(R.id.RN_S_1);
                View v1_3 = acti.findViewById(R.id.RN_B_1);
                View v1_4 = acti.findViewById(R.id.RN_Q_1);
                View v1_5 = acti.findViewById(R.id.RN_W_1);
                View v1_6 = acti.findViewById(R.id.RN_SW_1);

                View v2_1 = acti.findViewById(R.id.RN_G_2);
                View v2_2 = acti.findViewById(R.id.RN_S_2);
                View v2_3 = acti.findViewById(R.id.RN_B_2);
                View v2_4 = acti.findViewById(R.id.RN_Q_2);
                View v2_5 = acti.findViewById(R.id.RN_W_2);
                View v2_6 = acti.findViewById(R.id.RN_SW_2);

                appendView(v1_1, v2_1, OFFSET_G);
                appendView(v1_2, v2_2, OFFSET_S);
                appendView(v1_3, v2_3, OFFSET_B);
                appendView(v1_4, v2_4, OFFSET_Q);
                appendView(v1_5, v2_5, OFFSET_W);
                appendView(v1_6, v2_6, OFFSET_SW);
            }
        }
    }

    private void appendView(View v1, View v2, int nIndex) {
        if (v1 == null || v2 == null)
            return;

        NumberView newView1 = new NumberView();
        newView1.numView = v1;
        newView1.nIndex = nIndex;
        newView1.bHelpView = false;
        newView1.nCurNum = 0;
        newView1.setViewImage(mNumImgResIdList[0]);

        NumberView newView2 = new NumberView();
        newView2.numView = v2;
        newView2.nIndex = nIndex;
        newView2.bHelpView = true;
        newView2.nCurNum = 0;
        newView2.setViewImage(mNumImgResIdList[0]);

        newView1.braView = newView2;
        newView2.braView = newView1;

        mViewList1.add(newView1);
        mViewList2.add(newView2);
    }

    public void clearToZero() {

    }

    public void addNumber(int nNum) {
        if (nNum == 0)
            return;

        mbUpAni = (nNum > 0);
        mCurNum = mCurNum + nNum;
        if (mbUpAni)
            upAnimation(mCurNum);
    }

    public void setToNumber(int nNum) {
        int nCutNum = nNum - mCurNum;
        if (nCutNum == 0 || mHandler == null)
            return;

        mCurNum = nNum;
        mbUpAni = nCutNum > 0;
        if (mbUpAni)
            upAnimation(mCurNum);
    }

    private void upAnimation(int nDstNum) {
        if (nDstNum <= 0)
            return;

        mAniNumList[OFFSET_SW] = nDstNum / 100000;
        nDstNum = nDstNum % 100000;
        mAniNumList[OFFSET_W] = nDstNum / 10000;
        nDstNum = nDstNum % 10000;
        mAniNumList[OFFSET_Q] = nDstNum / 1000;
        nDstNum = nDstNum % 1000;
        mAniNumList[OFFSET_B] = nDstNum / 100;
        nDstNum = nDstNum % 100;
        mAniNumList[OFFSET_S] = nDstNum / 10;
        nDstNum = nDstNum % 10;
        mAniNumList[OFFSET_G] = nDstNum;

        upAnimationByIndex(mAniNumList[OFFSET_G], OFFSET_G);
        upAnimationByIndex(mAniNumList[OFFSET_S], OFFSET_S);
        upAnimationByIndex(mAniNumList[OFFSET_B], OFFSET_B);
        upAnimationByIndex(mAniNumList[OFFSET_Q], OFFSET_Q);
        upAnimationByIndex(mAniNumList[OFFSET_W], OFFSET_W);
        upAnimationByIndex(mAniNumList[OFFSET_SW], OFFSET_SW);
    }

    private void upAnimationByIndex(int nToNum, int nIndex) {
        if (nToNum == 0 || nIndex < 0 || nIndex >= NUMBER_COUNTS || mHandler == null)
            return;

        NumberView viewN1 = mViewList1.get(nIndex);
        NumberView viewN2 = mViewList2.get(nIndex);
        if (viewN1 == null || viewN1.numView == null || viewN2 == null || viewN2.numView == null)
            return;

        if (nToNum == viewN1.nCurNum)
            return;

        viewN1.bIsUpAni = true;
        viewN1.nAniTime = ROLL_TIME + nIndex * ROLL_TIME_STEP;
        viewN1.nLoopCtns = (nToNum > viewN1.nCurNum) ? (nToNum - viewN1.nCurNum)
                : (nToNum + 10 - viewN1.nCurNum);
        viewN1.nAniTime = viewN1.nAniTime / viewN1.nLoopCtns;

        viewN2.bIsUpAni = true;
        viewN2.nLoopCtns = viewN1.nLoopCtns;
        viewN2.nAniTime = viewN1.nAniTime;

        viewN2.nCurNum = viewN1.nCurNum + 1;
        if (viewN2.nCurNum > 9)
            viewN2.nCurNum = 0;
        viewN2.setViewImage(mNumImgResIdList[viewN2.nCurNum]);

        beginUpAnimation(viewN1);
        beginUpAnimation(viewN2);
    }

    private void beginUpAnimation(final NumberView viewN) {
        if (mHandler == null)
            return;

        // 动画集合
        AnimationSet aniSet = new AnimationSet(false);

        // X轴、Y轴移动动画
        TranslateAnimation tranAni = new TranslateAnimation(0, 0, 0, -viewN.numView.getHeight());
        // tranAni.setInterpolator(new AccelerateInterpolator());
        tranAni.setDuration(viewN.nAniTime);
        aniSet.addAnimation(tranAni);

        aniSet.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
                viewN.bAniEnd = false;
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {
                if (viewN.bAniEnd)
                    return;
                
                viewN.bAniEnd = true;
                numberAddOne(viewN);

                if (viewN.nLoopCtns > 0 && !viewN.bHelpView) {
                    // 先停止辅助View的动画
                    numberAddOne(viewN.braView);
                    Message msg = mHandler.obtainMessage(CONTINUE_ANIMATION);
                    msg.obj = viewN;
                    mHandler.sendMessage(msg);
                }
            }

            private void numberAddOne(NumberView viewN) {
                if (viewN != null && viewN.numView != null) {
                    viewN.numView.clearAnimation();
                    viewN.nCurNum++;
                    if (viewN.nCurNum > 9)
                        viewN.nCurNum = 0;
                    viewN.setViewImage(mNumImgResIdList[viewN.nCurNum]);
                    viewN.nLoopCtns--;
                }
            }
        });

        // 开始动画
        viewN.numView.startAnimation(aniSet);
    }

    public void continueAnimation(NumberView viewN) {
        if (viewN == null)
            return;

        beginUpAnimation(viewN);
        beginUpAnimation(viewN.braView);
    }
}
