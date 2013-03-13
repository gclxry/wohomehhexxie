package uif.burlapdragon.gameentry;

import uif.burlapdragon.R;
import uif.burlapdragon.gameentry.bigmap.ModeTollGateBigMapSelectActivity;
import uif.burlapdragon.gameentry.recommend.RecommendDownListActivity;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.view.Menu;
import android.view.View;

public class GameEntryActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_game_entry);
		
	}

	// 点击了新浪微博按钮
    public void onClickButtonSinaWeibo(View v)
    {
    }

	// 点击了新浪微博按钮
    public void onClickButtonRecommend(View v)
    {
    	Intent TGM_Intent = new Intent();
    	TGM_Intent.setClass(this, RecommendDownListActivity.class);
    	startActivity(TGM_Intent);
    	this.finish();
    }

    // 点击了通关模式按钮
    public void onClickButtonTollGateMode(View v)
    {
    	Intent TGM_Intent = new Intent();
    	TGM_Intent.setClass(this, ModeTollGateBigMapSelectActivity.class);
    	startActivity(TGM_Intent);
    	this.finish();
    }
    
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		return false;
	}
}
