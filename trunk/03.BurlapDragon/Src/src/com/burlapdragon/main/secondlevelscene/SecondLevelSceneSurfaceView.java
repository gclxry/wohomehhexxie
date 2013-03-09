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
	// 渲染线程
	private SecondLevelSceneViewThread m_SecondSceneViewThread;
	// Active主线程的Handler
	private SecondLevelSceneHandler m_ActiveHandler;

	// 构造函数
	public SecondLevelSceneSurfaceView(Context context, AttributeSet attrs) {
		// 调用基类构造
		super(context, attrs);

		// 设置回调
		SurfaceHolder sHolder = this.getHolder();
		sHolder.addCallback(this);

		// 创建渲染线程
		m_ActiveHandler = new SecondLevelSceneHandler(this);
		if (m_ActiveHandler == null)
			return;

		m_SecondSceneViewThread = new SecondLevelSceneViewThread(sHolder, context, m_ActiveHandler);
		if (m_SecondSceneViewThread == null)
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
	public SecondLevelSceneViewThread getViewThread() {
		return m_SecondSceneViewThread;
	}

	// implements Callback 后需要重载的函数
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		Log.v(this.getClass().getName(), "surfaceChanged()");

		m_SecondSceneViewThread.setSurfaceSize(width, height);
		m_SecondSceneViewThread.setRunning(true);

		// 判断渲染线程是否已经在运行了
		if (m_SecondSceneViewThread.isAlive()) {
			Log.v(this.getClass().getName(), "unpause gameThread");
			m_SecondSceneViewThread.unpause();
		} else {
			Log.v(this.getClass().getName(), "start gameThread");
			m_SecondSceneViewThread.start();
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
		m_SecondSceneViewThread.setRunning(false);
	}

	// 捕捉手机键盘被按下的事件
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		return m_SecondSceneViewThread.onKeyDown(keyCode, event);
	}

	// 捕捉手机键盘抬起的事件
	@Override
	public boolean onKeyUp(int keyCode, KeyEvent event) {
		return m_SecondSceneViewThread.onKeyUp(keyCode, event);
	}

	// 捕捉手机触摸屏的按下、抬起事件
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		return m_SecondSceneViewThread.onTouchEvent(event);
	}

	// 当SurfaceView得到或失去焦点时调用,使游戏暂停/恢复运行,
	@Override
	public void onWindowFocusChanged(boolean hasWindowFocus) {
		if (hasWindowFocus) {
			m_SecondSceneViewThread.unpause();
		} else {
			m_SecondSceneViewThread.pause();
		}
	}
}
