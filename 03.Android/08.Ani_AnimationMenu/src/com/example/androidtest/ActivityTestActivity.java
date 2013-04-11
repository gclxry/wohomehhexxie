
package com.example.androidtest;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.View;

import com.ani.animationmenu.R;

public class ActivityTestActivity extends Activity {

    private AnimationPopupMenu mPopupMenu = null;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_activity_test);
        
        View baseView = this.findViewById(R.id.BaseLayout);
        View btnView = this.findViewById(R.id.button1);
        mPopupMenu = new AnimationPopupMenu(this, baseView, btnView);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.activity_activity_test, menu);
        return true;
    }

    public void onShowButtonClick(View v){
        mPopupMenu.showPopupMenu();
    }
}
