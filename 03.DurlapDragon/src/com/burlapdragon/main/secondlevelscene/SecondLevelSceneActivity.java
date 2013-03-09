package com.burlapdragon.main.secondlevelscene;

import com.burlapdragon.main.R;

import android.os.Bundle;
import android.app.Activity;

public class SecondLevelSceneActivity extends Activity {
	// 游戏入口视图成员变量
	private SecondLevelSceneSurfaceView m_SecondSceneView;
	private SecondLevelSceneViewThread m_SecondSceneViewThread;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_second_level_scene);

		// 取得游戏入口视图
		m_SecondSceneView = (SecondLevelSceneSurfaceView) this
				.findViewById(R.id.SecondLevelSceneView);
		if (m_SecondSceneView == null)
			return;

		m_SecondSceneViewThread = m_SecondSceneView.getViewThread();
		if (m_SecondSceneViewThread == null)
			return;
	}
}
