package com.burlapdragon.main.gameentry.smallmap;

import com.burlapdragon.main.R;
import com.burlapdragon.main.firstlevelscene.FirstLevelSceneActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.FrameLayout;

public class ModeTollGateSmallMapSelectActivity extends Activity {

	// 中间的可以滚动的视图
	private ModeTollGateSmallMapView m_nSmallMapView = null;
	private ModeTollGateSmallMapHandler m_Handler = null;
	private int m_nMapTypeId = 0;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_mode_tollgate_small_map_select);

		m_Handler = new ModeTollGateSmallMapHandler(this);
		
		FrameLayout midView = (FrameLayout) this
				.findViewById(R.id.TGMSML_MidLayout);
		
		Bundle cbData = this.getIntent().getExtras();
		m_nMapTypeId = cbData.getInt("map_type_id");
		m_nSmallMapView = new ModeTollGateSmallMapView(this, m_Handler, m_nMapTypeId);

		// 设置布局样式，充满父视图
		FrameLayout.LayoutParams layoutP = new FrameLayout.LayoutParams(
				FrameLayout.LayoutParams.MATCH_PARENT,
				FrameLayout.LayoutParams.MATCH_PARENT);

		midView.addView(m_nSmallMapView, layoutP);
	}

	public void onHandleMessage(Message msg) {
		if (msg.what == ModeTollGateSmallMapView.OPEN_GAME){
			openGame(msg);
		}
	}

	private void openGame(Message msg) {
    	Intent TGMS_Intent = new Intent();
    	TGMS_Intent.setClass(this, FirstLevelSceneActivity.class);

		Bundle cbData = new Bundle();
		cbData.putInt("map_type_id", msg.arg1);
		cbData.putInt("map_id", msg.arg2);
		TGMS_Intent.putExtras(cbData);
		
    	startActivity(TGMS_Intent);
    	this.finish();
	}
}
