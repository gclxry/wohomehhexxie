package com.burlapdragon.main.firstlevelscene;

import android.os.Handler;
import android.os.Message;

public class FirstLevelSceneHandler extends Handler {
	private FirstLevelSceneSurfaceView m_FirstSceneView;

	public FirstLevelSceneHandler(FirstLevelSceneSurfaceView setSurfaceView) {
		m_FirstSceneView = setSurfaceView;
	}

	@Override
	public void handleMessage(Message msg) {
		if (m_FirstSceneView == null)
			return;

		m_FirstSceneView.onHandleMessage(msg);
	}
}
