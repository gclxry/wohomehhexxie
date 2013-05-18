
package com.example.androidtest;

import java.util.ArrayList;

import android.app.Activity;
import android.content.Context;
import android.graphics.Rect;
import android.util.Log;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.TranslateAnimation;

public class AnimationRollNumber {

    // 显示的数字的位数
    private final int NUMBER_COUNTS = 6;
    private final int MOVE_VIEW_COUNTS = 2;
    // 数字宽度和高度
    private int mNumSize = 0;
    // 个位数动画时间
    private final int ROLL_TIME = 1000;
    // 索引
    private final int OFFSET_G = 0;
    private final int OFFSET_S = 1;
    private final int OFFSET_B = 2;
    private final int OFFSET_Q = 3;
    private final int OFFSET_W = 4;
    private final int OFFSET_SW = 5;
    // 当前显示的数字
    private int mCurNum = 0;
    // 动画数字列表
    private int mAniNumList[] = new int[NUMBER_COUNTS];
    // 10个数字的Rect的位置，位于图片中的
    private Rect[] mNumRctInImg = new Rect[10];

    private Context mContext = null;

    // 所有数字的列表信息
    private ArrayList<OneNumberList> mAllNumList = new ArrayList<OneNumberList>();

    // 数字中的一位数字信息
    public class OneNumberList {
        // 最终要显示的数字
        public int nDstNum = 0;
        // 从哪个数字开始滚动
        public int nFromNum = 0;
        // 滚动一个数字的动画时间
        public int nAniTime = 0;
        public int nLastShowViewIndex = 0;
        public NumberView[] vList = new NumberView[MOVE_VIEW_COUNTS];
    }

    public class NumberView {
        public Rect fromRct = new Rect(0, 0, 0, 0);
        public Rect dstRct = new Rect(0, 0, 0, 0);
        public View numView = null;
        public int nAniTime = 0;
        public boolean bEndHide = true;
        public boolean bAniEnd = true;

        public void setViewImage(int nResId) {
            if (numView == null)
                return;
            numView.setBackgroundResource(nResId);
        }
    }

    public AnimationRollNumber(Context context) {
        mContext = context;
    }

    public void initAnimation() {
        if (mContext == null || mAllNumList == null || mAllNumList.size() > 0)
            return;

        Activity acti = (Activity) mContext;
        if (acti == null)
            return;

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
        
        mNumSize = v1_1.getWidth();

        Log.v("TTTTT", "*****=====******** height = ----------------------- " + mNumSize);

        for (int i = 0; i < 10; i++) {
            Rect rct = new Rect(0, 0, 0, 0);
            rct.left = 0;
            rct.right = mNumSize;
            rct.top = mNumSize * i;
            rct.bottom = rct.top + mNumSize;
            mNumRctInImg[i] = rct;
        }

        for (int i = 0; i < NUMBER_COUNTS; i++) {
            OneNumberList oneView = new OneNumberList();
            mAllNumList.add(oneView);
        }

        appendView(mAllNumList.get(OFFSET_G), v1_1, v2_1, OFFSET_G);
        appendView(mAllNumList.get(OFFSET_S), v1_2, v2_2, OFFSET_S);
        appendView(mAllNumList.get(OFFSET_B), v1_3, v2_3, OFFSET_B);
        appendView(mAllNumList.get(OFFSET_Q), v1_4, v2_4, OFFSET_Q);
        appendView(mAllNumList.get(OFFSET_W), v1_5, v2_5, OFFSET_W);
        appendView(mAllNumList.get(OFFSET_SW), v1_6, v2_6, OFFSET_SW);
    }

    private void appendView(OneNumberList oneNumList, View v1, View v2, int nIndex) {
        if (v1 == null || v2 == null || nIndex < 0 || nIndex > NUMBER_COUNTS)
            return;

        NumberView newView1 = new NumberView();
        newView1.numView = v1;
        newView1.numView.setVisibility(View.VISIBLE);
        newView1.bEndHide = false;

        NumberView newView2 = new NumberView();
        newView2.numView = v2;
        newView2.numView.setVisibility(View.INVISIBLE);
        newView2.bEndHide = true;

        oneNumList.vList[0] = newView1;
        oneNumList.vList[1] = newView2;
    }

    // 初始化到0
    public void clearToZero() {
        mCurNum = 0;
        RollToNumber(mCurNum);
    }
    
    // 重新显示数字
    public void resetNumber() {
        RollToNumber(0);
        RollToNumber(mCurNum);
    }

    // 增加/减少一个数字，可以是正数，也可以是负数
    public void cutNumber(int nCutNum) {
        if (nCutNum == 0)
            return;

        mCurNum = mCurNum + nCutNum;
        RollToNumber(mCurNum);
    }

    // 设置一个数字，可以增加，也可以减少
    public void setNumber(int nDstNum) {
        if (nDstNum == mCurNum)
            return;

        mCurNum = nDstNum;
        RollToNumber(mCurNum);
    }

    // 停止所有动画，并直接跳到最终状态
    private void stopAnimation(){
        for (int i = 0; i < mAllNumList.size(); i++){
            OneNumberList numItem = mAllNumList.get(i);
            if (numItem == null)
                continue;

            stopOneAnimation(numItem.vList[0]);
            stopOneAnimation(numItem.vList[1]);
        }
    }

    private void stopOneAnimation(NumberView numView){
        if (numView == null || numView.numView == null || numView.bAniEnd)
            return;

        numView.bAniEnd = true;
        numView.numView.clearAnimation();

        numView.numView.setVisibility(numView.bEndHide ? View.INVISIBLE : View.VISIBLE);
        numView.numView.layout(numView.dstRct.left, numView.dstRct.top,
                numView.dstRct.right, numView.dstRct.bottom);

        Log.v("TTTTT", "width = ----------------------- " + numView.dstRct.width());
        Log.v("TTTTT", "height = ----------------------- " + numView.dstRct.height());
        
        numView.numView.invalidate();
    }

    private void RollToNumber(int nDstNum) {
        // 先停止所有动画
        stopAnimation();
        
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

        int nRet = RollAnimationByIndex(mAniNumList[OFFSET_SW], OFFSET_SW, true);
        // 是否需要强制滚动，即便数字是一样的
        boolean bNotNeedRoll = (nRet == 0);
        nRet = RollAnimationByIndex(mAniNumList[OFFSET_W], OFFSET_W, bNotNeedRoll);
        bNotNeedRoll = bNotNeedRoll ? (nRet == 0) : false;
        nRet = RollAnimationByIndex(mAniNumList[OFFSET_Q], OFFSET_Q, bNotNeedRoll);
        bNotNeedRoll = bNotNeedRoll ? (nRet == 0) : false;
        nRet = RollAnimationByIndex(mAniNumList[OFFSET_B], OFFSET_B, bNotNeedRoll);
        bNotNeedRoll = bNotNeedRoll ? (nRet == 0) : false;
        nRet = RollAnimationByIndex(mAniNumList[OFFSET_S], OFFSET_S, bNotNeedRoll);
        bNotNeedRoll = bNotNeedRoll ? (nRet == 0) : false;
        nRet = RollAnimationByIndex(mAniNumList[OFFSET_G], OFFSET_G, bNotNeedRoll);
    }

    private int RollAnimationByIndex(int nDstOneNum, int nIndex, boolean bNotNeedRoll) {

        if (nIndex < 0 || nIndex >= NUMBER_COUNTS)
            return -1;

        OneNumberList oneNumList = mAllNumList.get(nIndex);
        if (oneNumList == null)
            return -1;

        // 不强制滚动的话，只要数字一样就返回
        if (bNotNeedRoll) {
            if (oneNumList.nDstNum == nDstOneNum)
                return 0;
        }

        NumberView numView1 = oneNumList.vList[0];
        NumberView numView2 = oneNumList.vList[1];

        if (numView1 == null || numView1.numView == null ||
                numView2 == null || numView2.numView == null)
            return -1;

        // 滚动开始数和目标数
        oneNumList.nFromNum = oneNumList.nDstNum;
        oneNumList.nDstNum = nDstOneNum;

        // 滚动次数
        int nLoopCtns = 0;
        if (oneNumList.nFromNum == oneNumList.nDstNum) {
            nLoopCtns = 10;
        } else if (oneNumList.nFromNum > oneNumList.nDstNum) {
            nLoopCtns = oneNumList.nDstNum + 10 - oneNumList.nFromNum;
        } else if (oneNumList.nFromNum < oneNumList.nDstNum) {
            nLoopCtns = oneNumList.nDstNum - oneNumList.nFromNum;
        }

        // 每次的滚动时间
        oneNumList.nAniTime = ROLL_TIME;
        oneNumList.nAniTime = oneNumList.nAniTime / nLoopCtns;

        // 先初始化每个view的位置
        if (oneNumList.nLastShowViewIndex > 0 && oneNumList.nLastShowViewIndex < MOVE_VIEW_COUNTS) {
            NumberView cV = oneNumList.vList[0];
            oneNumList.vList[0] = oneNumList.vList[oneNumList.nLastShowViewIndex];
            oneNumList.vList[oneNumList.nLastShowViewIndex] = cV;
        }

        numView1 = oneNumList.vList[0];
        numView2 = oneNumList.vList[1];

        numView1.fromRct.left = numView1.numView.getLeft();
        numView1.fromRct.top = numView1.numView.getTop();
        numView1.fromRct.right = numView1.numView.getRight();
        numView1.fromRct.bottom = numView1.numView.getBottom();

        Log.v("TTTTT", "******kk*ff******** width = ----------------------- " + numView1.fromRct.width());
        Log.v("TTTTT", "*****kk**ff******** height = ----------------------- " + numView1.fromRct.height());

        numView2.fromRct.left = numView1.numView.getLeft();
        numView2.fromRct.top = numView1.numView.getBottom();
        numView2.fromRct.right = numView1.numView.getRight();
        numView2.fromRct.bottom = numView2.fromRct.top + 10 * mNumSize;

        numView2.numView.layout(numView2.fromRct.left, numView2.fromRct.top,
                numView2.fromRct.right, numView2.fromRct.bottom);

        if (oneNumList.nDstNum == oneNumList.nFromNum) {
            rollViewToTopEnd(numView1, oneNumList.nAniTime);
            rollViewToTopShow(numView2, oneNumList.nDstNum);
            oneNumList.nLastShowViewIndex = 1;
        } else if (oneNumList.nDstNum > oneNumList.nFromNum) {
            onlyOneViewRoll(numView1, oneNumList.nDstNum);
            oneNumList.nLastShowViewIndex = 0;
        } else if (oneNumList.nDstNum < oneNumList.nFromNum) {
            rollViewToTopEnd(numView1, oneNumList.nAniTime);
            rollViewToTopShow(numView2, oneNumList.nDstNum);
            oneNumList.nLastShowViewIndex = 1;
        }

        return 1;
    }

    // 两个View滚动时，其中一个滚到顶端，并且显示
    private void rollViewToTopShow(final NumberView numView, int nDstNum) {
        if (numView == null)
            return;

        numView.nAniTime = ROLL_TIME;

        Rect dstRct = mNumRctInImg[nDstNum];
        numView.dstRct.left = numView.fromRct.left;
        numView.dstRct.right = numView.fromRct.right;
        numView.dstRct.top = -dstRct.top;
        numView.dstRct.bottom = numView.dstRct.top + 10 * mNumSize;

        Log.v("TTTTT", "*******dd******** width = ----------------------- " + numView.dstRct.width());
        Log.v("TTTTT", "*******dd******** height = ----------------------- " + numView.dstRct.height());
        Log.v("TTTTT", "*******ff******** width = ----------------------- " + numView.fromRct.width());
        Log.v("TTTTT", "*******ff******** height = ----------------------- " + numView.fromRct.height());

        numView.bEndHide = false;
        startAnimation(numView, numView.fromRct, numView.dstRct);
    }

    // 两个View滚动时，其中一个滚到最顶端，同时隐藏
    private void rollViewToTopEnd(final NumberView numView, final int nOneNumAniTime) {
        if (numView == null)
            return;

        numView.dstRct.left = numView.fromRct.left;
        numView.dstRct.right = numView.fromRct.right;
        numView.dstRct.bottom = 0;
        numView.dstRct.top = numView.dstRct.bottom - 10 * mNumSize;
        
        numView.nAniTime = ((numView.fromRct.top - numView.dstRct.top) / mNumSize) * nOneNumAniTime;

        numView.bEndHide = true;
        startAnimation(numView, numView.fromRct, numView.dstRct);
    }

    // 就一个单一的View在滚动
    private void onlyOneViewRoll(final NumberView numView, final int nDstNum) {
        if (numView == null || nDstNum < 0 || nDstNum >= 10)
            return;

        numView.nAniTime = ROLL_TIME;
        
        Rect dstRct = mNumRctInImg[nDstNum];
        numView.dstRct.left = numView.fromRct.left;
        numView.dstRct.right = numView.fromRct.right;
        numView.dstRct.top = -dstRct.top;
        numView.dstRct.bottom = numView.dstRct.top + 10 * mNumSize;

        numView.bEndHide = false;
        startAnimation(numView, numView.fromRct, numView.dstRct);
    }

    private void startAnimation(final NumberView numView, final Rect fromRct, final Rect dstRct) {
        if (numView == null)
            return;

        // 动画集合
        TranslateAnimation tranAni = new TranslateAnimation(0, 0, 0, dstRct.bottom - fromRct.bottom);
        tranAni.setInterpolator(new DecelerateInterpolator());
        //tranAni.setInterpolator(new OvershootInterpolator());
        tranAni.setDuration(numView.nAniTime);

        tranAni.setAnimationListener(new AnimationListener() {
            @Override
            public void onAnimationStart(Animation animation) {
                numView.bAniEnd = false;
            }

            @Override
            public void onAnimationRepeat(Animation animation) {
            }

            @Override
            public void onAnimationEnd(Animation animation) {
                stopOneAnimation(numView);
            }
        });

        // 开始动画
        numView.numView.startAnimation(tranAni);
    }
}
