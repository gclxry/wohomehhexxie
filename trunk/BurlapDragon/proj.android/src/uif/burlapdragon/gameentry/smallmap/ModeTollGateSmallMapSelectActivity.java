package uif.burlapdragon.gameentry.smallmap;

import uif.burlapdragon.R;
import uif.burlapdragon.gameentry.GameEntryActivity;
import uif.burlapdragon.gameentry.bigmap.ModeTollGateBigMapSelectActivity;
import uif.burlapdragon.playgame.PlayInCocos2DActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.view.KeyEvent;
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
    	TGMS_Intent.setClass(this, PlayInCocos2DActivity.class);

		Bundle cbData = new Bundle();
		cbData.putInt("map_type_id", msg.arg1);
		cbData.putInt("map_id", msg.arg2);
		TGMS_Intent.putExtras(cbData);
		
    	startActivity(TGMS_Intent);
    	this.finish();
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {

		// 如果是返回键,直接返回到桌面
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			showBigMapActivity();
		}

		return super.onKeyDown(keyCode, event);
	}

	private void showBigMapActivity() {
		Intent TGMS_Intent = new Intent();
		TGMS_Intent.setClass(this, ModeTollGateBigMapSelectActivity.class);
		startActivity(TGMS_Intent);
	}
}
