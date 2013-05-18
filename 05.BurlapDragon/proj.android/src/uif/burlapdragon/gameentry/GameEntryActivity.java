package uif.burlapdragon.gameentry;

import sdk360.Activity360Friend;
import sdk360.AppMpc;
import sdk360.Sdk360Manager;
import sdk360.SdkUserBaseActivity;
import uif.burlapdragon.BurlapDragonApplication;
import uif.burlapdragon.R;
import uif.burlapdragon.gameentry.bigmap.ModeTollGateBigMapSelectActivity;
import uif.burlapdragon.gameentry.recommend.RecommendDownListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.view.View;

public class GameEntryActivity extends SdkUserBaseActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_game_entry);
	}
	
	@Override
	protected void onDestroy() {
	super.onDestroy();
	}

	// 点击了新浪微博按钮
    public void onClickButtonSinaWeibo(View v) {
        Intent TGM_Intent = new Intent();
        TGM_Intent.setClass(this, RecommendDownListActivity.class);
        startActivity(TGM_Intent);
    }

	// 点击了邀请朋友
    public void onClickButtonFriend(View v) {
        Intent intent = new Intent();
        intent.setClass(this, Activity360Friend.class);
        startActivity(intent);
    }

    // 点击了通关模式按钮
    public void onClickButtonTollGateMode(View v) {
    	Intent TGM_Intent = new Intent();
    	TGM_Intent.setClass(this, ModeTollGateBigMapSelectActivity.class);
    	startActivity(TGM_Intent);
    	this.finish();
    }

    // 点击了登录按钮
    public void onClickButtonLogon(View v){
        userLogon();
    }

    @Override
    public void onLoginResult(int errorCode) {
        // TODO Auto-generated method stub
        
    }

    @Override
    public void onHandleMessage(Message msg) {
        // TODO Auto-generated method stub
        
    }

}
