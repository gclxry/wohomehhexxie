
package com.example.androidtest;

import java.util.ArrayList;
import java.util.List;

import com.ani.pathmenu.R;

import android.app.Activity;
import android.content.Context;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationSet;
import android.view.animation.DecelerateInterpolator;
import android.view.animation.OvershootInterpolator;
import android.view.animation.RotateAnimation;
import android.view.animation.TranslateAnimation;

public class AnimationPathMenu implements OnClickListener {

    private View mBaseMenu = null;
    private List<AnimationViewItem> mMenuItemList = new ArrayList<AnimationViewItem>();
    private int mMenuWidth = 120;

    private Context mContext = null;
    private Activity mActivity = null;
    private boolean mIsOpen = false;

    public class AnimationViewItem {
        View viewObj = null;
        int nOffsetX = 0;
        int nOffsetY = 0;
    }

    public AnimationPathMenu(Context context, Activity activity) {
        mContext = context;
        mActivity = activity;

        Init();
    }

    public void Init() {
        if (mActivity == null)
            return;

        mBaseMenu = mActivity.findViewById(R.id.PM_BaseMenu);

        View menuItem = mActivity.findViewById(R.id.PM_MenuItem1);
        appendMenuItem(menuItem, 0, 6);

        menuItem = mActivity.findViewById(R.id.PM_MenuItem2);
        appendMenuItem(menuItem, 1, 6);

        menuItem = mActivity.findViewById(R.id.PM_MenuItem3);
        appendMenuItem(menuItem, 2, 6);

        menuItem = mActivity.findViewById(R.id.PM_MenuItem4);
        appendMenuItem(menuItem, 3, 6);

        menuItem = mActivity.findViewById(R.id.PM_MenuItem5);
        appendMenuItem(menuItem, 4, 6);

        menuItem = mActivity.findViewById(R.id.PM_MenuItem6);
        appendMenuItem(menuItem, 5, 6);

        mBaseMenu.setOnClickListener(this);
    }

    private void appendMenuItem(View menuItem, int nNo, int nCtns) {

        AnimationViewItem aniMenuItem = new AnimationViewItem();
        aniMenuItem.viewObj = menuItem;

        if (nNo == 0) {
            aniMenuItem.nOffsetX = 0;
            aniMenuItem.nOffsetY = -mMenuWidth;
        } else if (nNo == (nCtns - 1)) {
            aniMenuItem.nOffsetX = mMenuWidth;
            aniMenuItem.nOffsetY = 0;
        } else {
            aniMenuItem.nOffsetX = getItemOffset(true, nNo, nCtns, mMenuWidth);
            aniMenuItem.nOffsetY = -(getItemOffset(false, nNo, nCtns, mMenuWidth));
        }
        
        menuItem.setOnClickListener(new OnClickListener(){
            @Override
            public void onClick(View v) {
                // 按下了小菜单
                beginMenuAnimation(false);
            }
        });

        mMenuItemList.add(aniMenuItem);
    }

    @Override
    public void onClick(View v) {
        if (mBaseMenu == v) {
            beginMenuAnimation(!mIsOpen);
        }
    }

    // nNo : 第几个
    // nCtns：一共有多少个点
    // nLen：半径
    private int getItemOffset(boolean bIsX, int nNo, int nCtns, int nLen) {
        if (nNo == 0 || nCtns <= 0)
            return 0;

        double dbRd = Math.PI / (((double) (nCtns - 1)) * 2.0d) * (double) nNo;
        double dbSinCos = 0.0d;
        if (bIsX) {
            dbSinCos = Math.sin(dbRd) * (double) nLen;
        } else {
            dbSinCos = Math.cos(dbRd) * (double) nLen;
        }

        return (int) dbSinCos;
    }

    private void beginMenuAnimation(boolean bIsOpen) {
        if (bIsOpen) {
            for (AnimationViewItem aniView : mMenuItemList)
                openAnimation(aniView);
        } else {
            for (AnimationViewItem aniView : mMenuItemList)
                closeAnimation(aniView);
        }
    }

    private void openAnimation(final AnimationViewItem aniView) {
        if (aniView == null || aniView.viewObj == null || aniView.viewObj.getAnimation() != null)
            return;

        mIsOpen = true;
        // 旋转动画
        RotateAnimation rotateAni = new RotateAnimation(0f, 360f, Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF, 0.5f);
        rotateAni.setDuration(500);

        // X轴、Y轴移动动画
        TranslateAnimation tranAni = new TranslateAnimation(0, aniView.nOffsetX, 0,
                aniView.nOffsetY);
        tranAni.setInterpolator(new OvershootInterpolator());
        tranAni.setDuration(500);

        // 动画集合
        AnimationSet aniSet = new AnimationSet(false);
        aniSet.addAnimation(rotateAni);
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
                int left = aniView.viewObj.getLeft() + aniView.nOffsetX;
                int top = aniView.viewObj.getTop() + aniView.nOffsetY;
                int width = aniView.viewObj.getWidth();
                int height = aniView.viewObj.getHeight();
                aniView.viewObj.clearAnimation();
                aniView.viewObj.layout(left, top, left + width, top + height);
            }
        });

        // 开始动画
        aniView.viewObj.startAnimation(aniSet);
    }

    private void closeAnimation(final AnimationViewItem aniView) {
        if (aniView == null || aniView.viewObj == null || aniView.viewObj.getAnimation() != null)
            return;

        mIsOpen = false;
        // 旋转动画
        RotateAnimation rotateAni = new RotateAnimation(0f, 360f, Animation.RELATIVE_TO_SELF, 0.5f,
                Animation.RELATIVE_TO_SELF, 0.5f);
        rotateAni.setDuration(500);

        // X轴、Y轴移动动画
        TranslateAnimation tranAni = new TranslateAnimation(0, -aniView.nOffsetX, 0,
                -aniView.nOffsetY);
        tranAni.setInterpolator(new DecelerateInterpolator());
        tranAni.setDuration(500);

        // 动画集合
        AnimationSet aniSet = new AnimationSet(false);
        aniSet.addAnimation(rotateAni);
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
                int left = aniView.viewObj.getLeft() - aniView.nOffsetX;
                int top = aniView.viewObj.getTop() - aniView.nOffsetY;
                int width = aniView.viewObj.getWidth();
                int height = aniView.viewObj.getHeight();
                aniView.viewObj.clearAnimation();
                aniView.viewObj.layout(left, top, left + width, top + height);
            }
        });

        // 开始动画
        aniView.viewObj.startAnimation(aniSet);
    }
}
