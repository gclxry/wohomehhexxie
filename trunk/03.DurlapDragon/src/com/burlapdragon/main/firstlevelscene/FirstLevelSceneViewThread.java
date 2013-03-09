package com.burlapdragon.main.firstlevelscene;

import com.burlapdragon.common.CommonDefines;
import com.burlapdragon.main.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.os.SystemClock;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import utility.method.*;
import com.burlapdragon.common.*;

// 渲染线程
public class FirstLevelSceneViewThread extends Thread {
	private SurfaceHolder m_sHolder = null;
	// 上下文,方便获取到应用的各项资源,如图片、音乐、字符串等
	private Context m_Context = null;
	// UI线程的Handler
	private FirstLevelSceneHandler m_ActiveHandler = null;
	// 游戏是否暂停
	private boolean m_bIsPaused = false;
	// 游戏线程运行开关
	private boolean m_bRunning = false;
	// 当前surface/canvas的高度,在surfaceChanged方法中被设置
	private int m_nCanvasHeight = 0;
	// 当前surface/canvas的宽度,在surfaceChanged方法中被设置
	private int m_nCanvasWidth = 0;
	private Paint m_paint = null;
	// 一个活动单元格的尺寸
	private Rect m_CellSize = null;
	// 鼠标手势判断
	private CheckDirectionEvent m_DObj = null;

	// 背景地图
	private Bitmap m_bmpBackgroundMap = null;
	private Rect m_BkMapRect = null;
	private Rect m_tmpRect = null;
	
	// 龙节
	private DragonManager m_DragonManager = null;


	// 自定义构造函数，接受Active的UI线程的相关参数
	public FirstLevelSceneViewThread(SurfaceHolder holder, Context context,
			FirstLevelSceneHandler handler) {
		m_sHolder = holder;
		m_Context = context;
		m_ActiveHandler = handler;
		doStart();
	}

	// 初始化游戏开始时的参数
	private void doStart() {
		
		// 创建Paint
		m_paint = new Paint();
		// 设置抗锯齿效果
		// m_paint.setAntiAlias(true);
		// 设置画刷的颜色
		// m_paint.setColor(Color.BLUE);

		m_CellSize = new Rect(0, 0 ,0 ,0);
		m_tmpRect = new Rect(0, 0, 0, 0);
		m_BkMapRect = new Rect(0, 0, 0, 0);
		m_DObj = new CheckDirectionEvent();
		
		m_DragonManager = new DragonManager(m_Context);
	}

	// 游戏结束的参数
	private void doEnd() {
		// TODO
	}

	// 设置surface/canvas的宽度和高度
	public void setSurfaceSize(int nWidth, int nHeight) {
		synchronized (m_sHolder) {
			m_nCanvasWidth = nWidth;
			m_nCanvasHeight = nHeight;
			
			m_CellSize.right = m_nCanvasWidth / CommonDefines.FIRST_LEVEL_CELL_H_CTNS;
			m_CellSize.bottom = m_nCanvasHeight / CommonDefines.FIRST_LEVEL_CELL_V_CTNS;

			if (m_bmpBackgroundMap == null){
				m_bmpBackgroundMap = Plotting.decodeResourceBySize(
						m_Context.getResources(), R.drawable.plain_00, m_nCanvasWidth, m_nCanvasHeight);
				
				if (m_bmpBackgroundMap != null){
					m_BkMapRect.left = m_BkMapRect.top = 0;
					m_BkMapRect.right = m_bmpBackgroundMap.getWidth();
					m_BkMapRect.bottom = m_bmpBackgroundMap.getHeight();
				}
			}
			
			// 初始化Manager
			if (m_DragonManager != null && !m_DragonManager.isInit()){
				Rect rct = new Rect(0, 0, m_nCanvasWidth, m_nCanvasHeight);
				m_DragonManager.initManager(m_CellSize.right, m_CellSize.bottom, rct);
			}
		}
	}

	// 设置游戏线程运行开关
	public void setRunning(boolean bRunning) {
		m_bRunning = bRunning;
	}

	public boolean onKeyDown(int keyCode, KeyEvent event) {
		synchronized (m_sHolder) {
			return true;
		}
	}

	public boolean onKeyUp(int keyCode, KeyEvent event) {
		synchronized (m_sHolder) {
			return true;
		}
	}

	public boolean onTouchEvent(MotionEvent event) {
		synchronized (m_sHolder) {
			// 先过滤多点触摸
			int nIndex = event.getActionIndex();
			if (nIndex != 0)
				return true;


			// 只取得触摸的有效值
			int nMotion = event.getActionMasked();
			if (nMotion == MotionEvent.ACTION_DOWN) {
			} else if (nMotion == MotionEvent.ACTION_UP) {
			} else if (nMotion == MotionEvent.ACTION_MOVE) {
			}

			int nD = CheckDirectionEvent.DIRECTION_NONE;
			nD = m_DObj.onTouchEventCheck(event, 0);
			switch (nD) {
			case CheckDirectionEvent.DIRECTION_UP:
				break;

			case CheckDirectionEvent.DIRECTION_DOWN:
				break;

			case CheckDirectionEvent.DIRECTION_LEFT:
				break;

			case CheckDirectionEvent.DIRECTION_RIGHT:
				break;

			default:
				break;
			}

			return true;
		}
	}

	// 暂停游戏逻辑
	public void pause() {
		synchronized (m_sHolder) {
			m_bIsPaused = true;
		}
	}

	// 恢复运行游戏逻辑
	public void unpause() {
		// 如果游戏中有时间,别忘记应将其在这里调整到正常
		synchronized (m_sHolder) {
			m_bIsPaused = false;
		}
	}

	// 线程的执行函数
	@Override
	public void run() {
		while (m_bRunning) {
			if (m_bIsPaused) {
				try {
					Thread.sleep(CommonDefines.GAME_ONE_FRAME_TIME);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				continue;
			}
			
			long lBeginTime = SystemClock.uptimeMillis();
			onBeforeDrawLogic();

			Canvas runCanvas = null;
			try {
				runCanvas = m_sHolder.lockCanvas(null);
				synchronized (m_sHolder) {
					doDraw(runCanvas);
				}
			} finally {
				if (runCanvas != null) {
					m_sHolder.unlockCanvasAndPost(runCanvas);
				}
			}

			onAfterDrawLogic();
			long lEndTime = SystemClock.uptimeMillis();
			long lSleepTime = lEndTime - lBeginTime;
			
			// 一帧的时间超了
			if ((int)lSleepTime >= CommonDefines.GAME_ONE_FRAME_TIME)
				continue;
			
			int nSleep = (int)(CommonDefines.GAME_ONE_FRAME_TIME - lSleepTime);

			try {
				Thread.sleep(nSleep);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		// 线程结束
		doEnd();
	}

	// 游戏绘画
	private void doDraw(Canvas runCanvas) {
		runCanvas.drawColor(Color.BLACK);
		
		if (m_bmpBackgroundMap == null || m_DragonManager == null)
			return;

		m_tmpRect.left = m_tmpRect.top = 0;
		m_tmpRect.right = m_nCanvasWidth;
		m_tmpRect.bottom = m_nCanvasHeight;
		runCanvas.drawBitmap(m_bmpBackgroundMap, m_BkMapRect, m_tmpRect, m_paint);
		m_DragonManager.doDraw(runCanvas, m_paint);
	}

	// 游戏逻辑处理
	private void onBeforeDrawLogic() {
		if (m_DragonManager != null)
			m_DragonManager.onBeforeDrawLogic();
	}
	// 游戏逻辑处理
	private void onAfterDrawLogic() {
		if (m_DragonManager != null)
			m_DragonManager.onAfterDrawLogic();
	}

}