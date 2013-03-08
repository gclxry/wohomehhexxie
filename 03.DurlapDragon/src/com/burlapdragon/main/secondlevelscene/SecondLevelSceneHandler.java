package com.burlapdragon.main.secondlevelscene;

import android.os.Handler;
import android.os.Message;

public class SecondLevelSceneHandler extends Handler {
	private SecondLevelSceneSurfaceView m_SecondSceneView;

	public SecondLevelSceneHandler(SecondLevelSceneSurfaceView setSurfaceView) {
		m_SecondSceneView = setSurfaceView;
	}

	@Override
	public void handleMessage(Message msg) {
		if (m_SecondSceneView == null)
			return;

		m_SecondSceneView.onHandleMessage(msg);
	}
}
