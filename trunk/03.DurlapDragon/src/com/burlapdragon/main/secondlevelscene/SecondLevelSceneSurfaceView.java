package com.burlapdragon.main.secondlevelscene;

import android.content.Context;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.SurfaceHolder.Callback;

public class SecondLevelSceneSurfaceView extends SurfaceView implements Callback {
	// ��Ⱦ�߳�
	private SecondLevelSceneViewThread m_SecondSceneViewThread;
	// Active���̵߳�Handler
	private SecondLevelSceneHandler m_ActiveHandler;

	// ���캯��
	public SecondLevelSceneSurfaceView(Context context, AttributeSet attrs) {
		// ���û��๹��
		super(context, attrs);

		// ���ûص�
		SurfaceHolder sHolder = this.getHolder();
		sHolder.addCallback(this);

		// ������Ⱦ�߳�
		m_ActiveHandler = new SecondLevelSceneHandler(this);
		if (m_ActiveHandler == null)
			return;

		m_SecondSceneViewThread = new SecondLevelSceneViewThread(sHolder, context, m_ActiveHandler);
		if (m_SecondSceneViewThread == null)
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
	public SecondLevelSceneViewThread getViewThread() {
		return m_SecondSceneViewThread;
	}

	// implements Callback ����Ҫ���صĺ���
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		Log.v(this.getClass().getName(), "surfaceChanged()");

		m_SecondSceneViewThread.setSurfaceSize(width, height);
		m_SecondSceneViewThread.setRunning(true);

		// �ж���Ⱦ�߳��Ƿ��Ѿ���������
		if (m_SecondSceneViewThread.isAlive()) {
			Log.v(this.getClass().getName(), "unpause gameThread");
			m_SecondSceneViewThread.unpause();
		} else {
			Log.v(this.getClass().getName(), "start gameThread");
			m_SecondSceneViewThread.start();
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
		m_SecondSceneViewThread.setRunning(false);
	}

	// ��׽�ֻ����̱����µ��¼�
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		return m_SecondSceneViewThread.onKeyDown(keyCode, event);
	}

	// ��׽�ֻ�����̧����¼�
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		return m_SecondSceneViewThread.onKeyUp(keyCode, event);
	}

	// ��׽�ֻ��������İ��¡�̧���¼�
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		return m_SecondSceneViewThread.onTouchEvent(event);
	}

	// ��SurfaceView�õ���ʧȥ����ʱ����,ʹ��Ϸ��ͣ/�ָ�����,
	@Override
	public void onWindowFocusChanged(boolean hasWindowFocus) {
		if (hasWindowFocus) {
			m_SecondSceneViewThread.unpause();
		} else {
			m_SecondSceneViewThread.pause();
		}
	}
}
