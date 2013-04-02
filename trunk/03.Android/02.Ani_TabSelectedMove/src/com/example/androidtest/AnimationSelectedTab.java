
package com.example.androidtest;

import java.util.HashMap;

import android.app.TabActivity;
import android.graphics.Color;
import android.graphics.Rect;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.OvershootInterpolator;
import android.view.animation.TranslateAnimation;
import android.widget.ImageView;
import android.widget.TabHost;
import android.widget.TabHost.OnTabChangeListener;
import android.widget.TextView;
import com.ani.tabselectedmove.R;

@SuppressWarnings("deprecation")
public class AnimationSelectedTab extends TabActivity implements OnTabChangeListener {

    private String TAG = "AnimationSelectedTab";
    // 从TabActivity上面获取放置Tab的TabHost
    private TabHost mTabHost = null;
    // 移动的图片
    private View mMoveView = null;
    // tab列表
    private HashMap<String, View> mTabMap = new HashMap<String, View>();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_animation_selected_tab);
        
        View tabViewItem1 = createTabView(R.drawable.ic_launcher, "FirstTab");
        mTabMap.put("First", tabViewItem1);
        
        View tabViewItem2 = createTabView(R.drawable.ic_launcher, "SecondTab");
        mTabMap.put("Second", tabViewItem2);

        View tabViewItem3 = createTabView(R.drawable.ic_launcher, "ThirdTab");
        mTabMap.put("Third", tabViewItem3);
        
        mTabHost = this.getTabHost();
        mTabHost.setOnTabChangedListener(this);
        mTabHost.setBackgroundColor(Color.argb(100, 255, 255, 0));

        mTabHost.addTab(mTabHost.newTabSpec("First").setIndicator(tabViewItem1)
                .setContent(R.id.AST_FirstLayout));

        mTabHost.addTab(mTabHost.newTabSpec("Second").setIndicator(tabViewItem2)
                .setContent(R.id.AST_SecondLayout));
        

        mTabHost.addTab(mTabHost.newTabSpec("Third").setIndicator(tabViewItem3)
                .setContent(R.id.AST_ThirdLayout));

        mMoveView = this.findViewById(R.id.AST_MoveImage);
    }

    @Override
    public void onTabChanged(String tabId) {
        beginHorizontalAnimation(tabId);
    }

    // 开始水平移动动画
    public void beginHorizontalAnimation(String tabId) {
        // 查找被选中的View，为了得到移动的目标
        View selView = mTabMap.get(tabId);
        if (selView == null || mMoveView == null)
            return;
        
        // 这两个为空，说明是刚初始化tab，不用移动tab动画
        if (selView.getWidth() <= 0 || selView.getHeight() <= 0)
            return;
        
        // 开始动画
        horizontalMoveView(0, selView.getLeft() - mMoveView.getLeft());
    }

    private View createTabView(int nIconId, String strText) {
        if (nIconId <= 0 || strText == null)
            return null;

        View view = LayoutInflater.from(this).inflate(R.layout.tab_selected_item, null);
        TextView tv = (TextView) view.findViewById(R.id.AST_TabItemTextView);
        ImageView iv = (ImageView) view.findViewById(R.id.AST_TabItemIconImg);
        tv.setText(strText);
        iv.setImageResource(nIconId);
        return view;
    }

    // 水平移动View，带有缓冲阻尼震荡效果
    public void horizontalMoveView(final float p1, final float p2) {
        if (mMoveView == null)
            return;

        TranslateAnimation animation = new TranslateAnimation(p1, p2, 0, 0);
        animation.setInterpolator(new OvershootInterpolator());
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
                if (mMoveView == null)
                    return;
                
                // 动画结束了，需要将View直接定位到动画的最后一帧，不然，就又回去了
                int left = mMoveView.getLeft() + (int) (p2 - p1);
                int top = mMoveView.getTop();
                int width = mMoveView.getWidth();
                int height = mMoveView.getHeight();
                mMoveView.clearAnimation();
                mMoveView.layout(left, top, left + width, top + height);
            }
        });

        mMoveView.startAnimation(animation);
    }
}
