package com.burlapdragon.main.firstlevelscene;

import com.burlapdragon.main.R;

import android.os.Bundle;
import android.app.Activity;

public class FirstLevelSceneActivity extends Activity {
	// 游戏入口视图成员变量
	private FirstLevelSceneSurfaceView m_FirstSceneView = null;
	private FirstLevelSceneViewThread m_FirstSceneViewThread = null;
	private int m_nMapTypeId = 0;
	private int m_nMapId = 0;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_first_level_scene);

		Bundle cbData = this.getIntent().getExtras();
		m_nMapTypeId = cbData.getInt("map_type_id");
		m_nMapTypeId = cbData.getInt("map_id");
		
		// 取得游戏入口视图
		m_FirstSceneView = (FirstLevelSceneSurfaceView) this
				.findViewById(R.id.FirstLevelSceneView);
		if (m_FirstSceneView == null)
			return;

		m_FirstSceneViewThread = m_FirstSceneView.getViewThread();
		if (m_FirstSceneViewThread == null)
			return;
	}
}
