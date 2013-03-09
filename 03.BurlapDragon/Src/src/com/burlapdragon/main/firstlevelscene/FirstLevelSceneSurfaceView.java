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
	// 渲染线程
	private FirstLevelSceneViewThread m_FirstSceneViewThread;
	// Active主线程的Handler
	private FirstLevelSceneHandler m_ActiveHandler;

	// 构造函数
	public FirstLevelSceneSurfaceView(Context context, AttributeSet attrs) {
		// 调用基类构造
		super(context, attrs);

		// 设置回调
		SurfaceHolder sHolder = this.getHolder();
		sHolder.addCallback(this);

		// 创建渲染线程
		m_ActiveHandler = new FirstLevelSceneHandler(this);
		if (m_ActiveHandler == null)
			return;

		m_FirstSceneViewThread = new FirstLevelSceneViewThread(sHolder, context, m_ActiveHandler);
		if (m_FirstSceneViewThread == null)
			return;

		// 设置可获得焦点,确保能捕获到KeyEvent
		this.setFocusable(true);
		// 保持屏幕常亮
		this.setKeepScreenOn(true);
	}

	public void onHandleMessage(Message msg) {
		switch (msg.what) {
		case 100:
			break;
		}
	}

	// 导出线程对象
	public FirstLevelSceneViewThread getViewThread() {
		return m_FirstSceneViewThread;
	}

	// implements Callback 后需要重载的函数
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		Log.v(this.getClass().getName(), "surfaceChanged()");

		m_FirstSceneViewThread.setSurfaceSize(width, height);
		m_FirstSceneViewThread.setRunning(true);

		// 判断渲染线程是否已经在运行了
		if (m_FirstSceneViewThread.isAlive()) {
			Log.v(this.getClass().getName(), "unpause gameThread");
			m_FirstSceneViewThread.unpause();
		} else {
			Log.v(this.getClass().getName(), "start gameThread");
			m_FirstSceneViewThread.start();
		}
	}

	// implements Callback 后需要重载的函数
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		Log.v(this.getClass().getName(), "surfaceCreated()");
	}

	// implements Callback 后需要重载的函数
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		Log.v(this.getClass().getName(), "surfaceDestroyed");
		m_FirstSceneViewThread.setRunning(false);
	}

	// 捕捉手机键盘被按下的事件
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		return m_FirstSceneViewThread.onKeyDown(keyCode, event);
	}

	// 捕捉手机键盘抬起的事件
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		return m_FirstSceneViewThread.onKeyUp(keyCode, event);
	}

	// 捕捉手机触摸屏的按下、抬起事件
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		return m_FirstSceneViewThread.onTouchEvent(event);
	}

	// 当SurfaceView得到或失去焦点时调用,使游戏暂停/恢复运行,
	@Override
	public void onWindowFocusChanged(boolean hasWindowFocus) {
		if (hasWindowFocus) {
			m_FirstSceneViewThread.unpause();
		} else {
			m_FirstSceneViewThread.pause();
		}
	}
}
