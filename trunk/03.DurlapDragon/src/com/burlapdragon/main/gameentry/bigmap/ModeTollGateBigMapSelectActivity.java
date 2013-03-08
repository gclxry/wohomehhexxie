// ͨ��ģʽ���ͼѡ�������
package com.burlapdragon.main.gameentry.bigmap;

import com.burlapdragon.main.R;
import com.burlapdragon.main.gameentry.smallmap.ModeTollGateSmallMapSelectActivity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Message;
import android.widget.FrameLayout;

public class ModeTollGateBigMapSelectActivity extends Activity {

	// �м�Ŀ��Թ�������ͼ
	private ModeTollGateBigMapView m_nBigMapView = null;
	private ModeTollGateBigMapHandler m_Handler = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_mode_tollgate_big_map_select);

		m_Handler = new ModeTollGateBigMapHandler(this);

		FrameLayout midView = (FrameLayout) this
				.findViewById(R.id.TGMBML_M_MidLayout);
		m_nBigMapView = new ModeTollGateBigMapView(this, m_Handler);

		// ���ò�����ʽ����������ͼ
		FrameLayout.LayoutParams layoutP = new FrameLayout.LayoutParams(
				FrameLayout.LayoutParams.MATCH_PARENT,
				FrameLayout.LayoutParams.MATCH_PARENT);

		midView.addView(m_nBigMapView, layoutP);
	}

	public void onHandleMessage(Message msg) {
		if (msg.what == ModeTollGateBigMapView.OPEN_SMALL_MAP_VIEW) {
			// �򿪶�����ͼ����
			showSmallMapActivity(msg);
		}
	}

	private void showSmallMapActivity(Message msg) {
		Intent TGMS_Intent = new Intent();
		TGMS_Intent.setClass(this, ModeTollGateSmallMapSelectActivity.class);

		Bundle cbData = new Bundle();
		cbData.putInt("map_type_id", msg.arg1);
		TGMS_Intent.putExtras(cbData);

		startActivity(TGMS_Intent);
		this.finish();
	}
}
