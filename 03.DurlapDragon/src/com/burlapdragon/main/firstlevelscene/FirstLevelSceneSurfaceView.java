package com.burlapdragon.main.firstlevelscene;

import android.content.Context;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.SurfaceHolder.Callback;

public class FirstLevelSceneSurfaceView extends SurfaceView implements Callback {
	// ��Ⱦ�߳�
	private FirstLevelSceneViewThread m_FirstSceneViewThread;
	// Active���̵߳�Handler
	private FirstLevelSceneHandler m_ActiveHandler;

	// ���캯��
	public FirstLevelSceneSurfaceView(Context context, AttributeSet attrs) {
		// ���û��๹��
		super(context, attrs);

		// ���ûص�
		SurfaceHolder sHolder = this.getHolder();
		sHolder.addCallback(this);

		// ������Ⱦ�߳�
		m_ActiveHandler = new FirstLevelSceneHandler(this);
		if (m_ActiveHandler == null)
			return;

		m_FirstSceneViewThread = new FirstLevelSceneViewThread(sHolder, context, m_ActiveHandler);
		if (m_FirstSceneViewThread == null)
			return;

		// ���ÿɻ�ý���,ȷ���ܲ���KeyEvent
		this.setFocusable(true);
		// ������Ļ����
		this.setKeepScreenOn(true);
	}

	public void onHandleMessage(Message msg) {
		switch (msg.what) {
		case 100:
			break;
		}
	}

	// �����̶߳���
	public FirstLevelSceneViewThread getViewThread() {
		return m_FirstSceneViewThread;
	}

	// implements Callback ����Ҫ���صĺ���
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		Log.v(this.getClass().getName(), "surfaceChanged()");

		m_FirstSceneViewThread.setSurfaceSize(width, height);
		m_FirstSceneViewThread.setRunning(true);

		// �ж���Ⱦ�߳��Ƿ��Ѿ���������
		if (m_FirstSceneViewThread.isAlive()) {
			Log.v(this.getClass().getName(), "unpause gameThread");
			m_FirstSceneViewThread.unpause();
		} else {
			Log.v(this.getClass().getName(), "start gameThread");
			m_FirstSceneViewThread.start();
		}
	}

	// implements Callback ����Ҫ���صĺ���
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.v(this.getClass().getName(), "surfaceCreated()");
	}

	// implements Callback ����Ҫ���صĺ���
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.v(this.getClass().getName(), "surfaceDestroyed");
		m_FirstSceneViewThread.setRunning(false);
	}

	// ��׽�ֻ����̱����µ��¼�
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		return m_FirstSceneViewThread.onKeyDown(keyCode, event);
	}

	// ��׽�ֻ�����̧����¼�
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		return m_FirstSceneViewThread.onKeyUp(keyCode, event);
	}

	// ��׽�ֻ��������İ��¡�̧���¼�
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		return m_FirstSceneViewThread.onTouchEvent(event);
	}

	// ��SurfaceView�õ���ʧȥ����ʱ����,ʹ��Ϸ��ͣ/�ָ�����,
	@Override
	public void onWindowFocusChanged(boolean hasWindowFocus) {
		if (hasWindowFocus) {
			m_FirstSceneViewThread.unpause();
		} else {
			m_FirstSceneViewThread.pause();
		}
	}
}
