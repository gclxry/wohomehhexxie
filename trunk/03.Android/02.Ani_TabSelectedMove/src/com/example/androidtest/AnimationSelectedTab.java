
package com.example.androidtest;

import android.app.TabActivity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.TabHost;
import android.widget.TabHost.OnTabChangeListener;
import android.widget.TextView;

@SuppressWarnings("deprecation")
public class AnimationSelectedTab extends TabActivity implements OnTabChangeListener {

    // 从TabActivity上面获取放置Tab的TabHost
    private TabHost mTabHost = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_animation_selected_tab);

        mTabHost = this.getTabHost();
        mTabHost.setBackgroundColor(Color.argb(100, 255, 255, 0));
        
        mTabHost.addTab(mTabHost.newTabSpec("First").setIndicator(createTabView(R.drawable.ic_launcher, "FirstTab")).setContent(R.id.AST_FirstLayout));
        mTabHost.addTab(mTabHost.newTabSpec("Second").setIndicator(createTabView(R.drawable.ic_launcher, "SecondTab")).setContent(R.id.AST_SecondLayout));
        mTabHost.addTab(mTabHost.newTabSpec("Third").setIndicator(createTabView(R.drawable.ic_launcher, "ThirdTab")).setContent(R.id.AST_ThirdLayout));
    }

    public void onTabChanged(String tabId) {
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
}
