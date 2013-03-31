package com.burlapdragon.main.secondlevelscene;

import com.burlapdragon.main.R;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Rect;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import utility.method.*;

// 渲染线程
public class SecondLevelSceneViewThread extends Thread {
	private SurfaceHolder m_sHolder;
	// 上下文,方便获取到应用的各项资源,如图片、音乐、字符串等
	private Context m_Context;
	// UI线程的Handler
	private SecondLevelSceneHandler m_ActiveHandler;
	// 游戏是否暂停
	private boolean m_bIsPaused = false;
	// 游戏线程运行开关
	private boolean m_bRunning = false;
	// 当前surface/canvas的高度,在surfaceChanged方法中被设置
	private int m_nCanvasHeight = 0;
	// 当前surface/canvas的宽度,在surfaceChanged方法中被设置
	private int m_nCanvasWidth = 0;
	private Paint m_paint;

	// 测试PNG序列图片
	private Bitmap m_bmpAnimation;
	private int m_nCurPalyId = 0;

	// 自定义构造函数，接受Active的UI线程的相关参数
	public SecondLevelSceneViewThread(SurfaceHolder holder, Context context,
			SecondLevelSceneHandler handler) {
		m_sHolder = holder;
		m_Context = context;
		m_ActiveHandler = handler;
		// 创建Paint
		m_paint = new Paint();
		// 设置抗锯齿效果
		// m_paint.setAntiAlias(true);
		// 设置画刷的颜色
		// m_paint.setColor(Color.BLUE);

		doStart();
	}

	// 初始化游戏开始时的参数
	private void doStart() {
		m_DObj = new CheckDirectionEvent();
		m_strMoveString = "";
		m_nCurPalyId = 0;
		m_bmpAnimation = Plotting.decodeResourceNoScaled(
				m_Context.getResources(), R.drawable.v7);
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

			// 不要忘记每次画布的宽度和高度改变时, 在这里对图片等资源做缩放等相关适配屏幕的处理
			// TODO
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

	private CheckDirectionEvent m_DObj;
	private String m_strD = "";

	public boolean onTouchEvent(MotionEvent event) {
		synchronized (m_sHolder) {
			// 先过滤多点触摸
			int nIndex = event.getActionIndex();
			if (nIndex != 0)
				return true;

			Display("NO", event);

			// 只取得触摸的有效值
			int nMotion = event.getActionMasked();
			if (nMotion == MotionEvent.ACTION_DOWN) {
				m_nCurPalyId = 0;
				Display("ACTION_DOWN", event);
			} else if (nMotion == MotionEvent.ACTION_UP) {
				Display("ACTION_UP", event);
			} else if (nMotion == MotionEvent.ACTION_MOVE) {
				Display("ACTION_MOVE", event);
			}

			int nD = CheckDirectionEvent.DIRECTION_NONE;
			nD = m_DObj.onTouchEventCheck(event, 0);
			switch (nD) {
			case CheckDirectionEvent.DIRECTION_UP:
				m_strD = "上";
				break;

			case CheckDirectionEvent.DIRECTION_DOWN:
				m_strD = "下";
				break;

			case CheckDirectionEvent.DIRECTION_LEFT:
				m_strD = "左";
				break;

			case CheckDirectionEvent.DIRECTION_RIGHT:
				m_strD = "右";
				break;

			default:
				m_strD = "没有";
				break;
			}

			return true;
		}
	}

	private String m_strMoveString;

	public void Display(String eventType, MotionEvent event) {
		// 触点相对坐标的信息
		int x = (int) event.getX();
		int y = (int) event.getY();
		// 表示触屏压力大小
		float pressure = event.getPressure();
		// 表示触点尺寸
		float size = event.getSize();
		// 获取绝对坐标信息
		int RawX = (int) event.getRawX();
		int RawY = (int) event.getRawY();

		String msg = "";

		msg += "事件类型" + eventType + "\r\n";
		msg += "相对坐标" + String.valueOf(x) + "," + String.valueOf(y) + "\r\n";
		msg += "绝对坐标" + String.valueOf(RawX) + "," + String.valueOf(RawY)
				+ "\r\n";
		msg += "触点压力" + String.valueOf(pressure) + ",";
		msg += "触点尺寸" + String.valueOf(size) + "\r\n";

		m_strMoveString = msg;
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
				continue;
			}

			Canvas runCanvas = null;
			try {
				runCanvas = m_sHolder.lockCanvas(null);
				synchronized (m_sHolder) {
					doDraw(runCanvas);
				}

				logic();
			} finally {
				if (runCanvas != null) {
					m_sHolder.unlockCanvasAndPost(runCanvas);
				}
			}

			try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		// 线程结束
		doEnd();
	}

	// 游戏绘画
	private void doDraw(Canvas runCanvas) {
		Log.v(this.getClass().getName(), "doDraw");
		runCanvas.drawColor(Color.BLUE);

		if (m_bmpAnimation != null) {
			Rect srcRct = new Rect(0, 0, 0, 0);
			Rect dstRct = new Rect(0, 0, 0, 0);
			srcRct.left = 0;
			srcRct.top = m_nCurPalyId * 195;
			srcRct.right = srcRct.left + 240;
			srcRct.bottom = srcRct.top + 195;

			dstRct.left = dstRct.top = 0;
			dstRct.right = 240;
			dstRct.bottom = 195;

			runCanvas.drawBitmap(m_bmpAnimation, srcRct, dstRct, m_paint);

			if (m_strMoveString.length() > 0) {
				runCanvas.drawText(m_strMoveString, 0, 220, m_paint);
			}

			if (m_strD.length() > 0)
				runCanvas.drawText(m_strD, 0, 260, m_paint);

			m_nCurPalyId++;
			if (m_nCurPalyId >= 7) {
				m_nCurPalyId = 0;
			}
		}
	}

	// 游戏逻辑处理
	public void logic() {
		Log.v(this.getClass().getName(), "logic");
		// TODO
	}

}