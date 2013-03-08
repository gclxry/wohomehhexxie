package com.burlapdragon.main.gameentry;

import com.burlapdragon.main.R;
import com.burlapdragon.main.gameentry.bigmap.ModeTollGateBigMapSelectActivity;

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
	
	// ���������΢����ť
    public void onClickButtonSinaWeibo(View v)
    {
    }

    // �����ͨ��ģʽ��ť
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
