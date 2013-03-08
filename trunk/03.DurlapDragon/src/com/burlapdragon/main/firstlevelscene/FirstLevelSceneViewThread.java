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

// ��Ⱦ�߳�
public class FirstLevelSceneViewThread extends Thread {
	private SurfaceHolder m_sHolder = null;
	// ������,�����ȡ��Ӧ�õĸ�����Դ,��ͼƬ�����֡��ַ�����
	private Context m_Context = null;
	// UI�̵߳�Handler
	private FirstLevelSceneHandler m_ActiveHandler = null;
	// ��Ϸ�Ƿ���ͣ
	private boolean m_bIsPaused = false;
	// ��Ϸ�߳����п���
	private boolean m_bRunning = false;
	// ��ǰsurface/canvas�ĸ߶�,��surfaceChanged�����б�����
	private int m_nCanvasHeight = 0;
	// ��ǰsurface/canvas�Ŀ��,��surfaceChanged�����б�����
	private int m_nCanvasWidth = 0;
	private Paint m_paint = null;
	// һ�����Ԫ��ĳߴ�
	private Rect m_CellSize = null;
	// ��������ж�
	private CheckDirectionEvent m_DObj = null;

	// ������ͼ
	private Bitmap m_bmpBackgroundMap = null;
	private Rect m_BkMapRect = null;
	private Rect m_tmpRect = null;
	
	// ����
	private DragonManager m_DragonManager = null;


	// �Զ��幹�캯��������Active��UI�̵߳���ز���
	public FirstLevelSceneViewThread(SurfaceHolder holder, Context context,
			FirstLevelSceneHandler handler) {
		m_sHolder = holder;
		m_Context = context;
		m_ActiveHandler = handler;
		doStart();
	}

	// ��ʼ����Ϸ��ʼʱ�Ĳ���
	private void doStart() {
		
		// ����Paint
		m_paint = new Paint();
		// ���ÿ����Ч��
		// m_paint.setAntiAlias(true);
		// ���û�ˢ����ɫ
		// m_paint.setColor(Color.BLUE);

		m_CellSize = new Rect(0, 0 ,0 ,0);
		m_tmpRect = new Rect(0, 0, 0, 0);
		m_BkMapRect = new Rect(0, 0, 0, 0);
		m_DObj = new CheckDirectionEvent();
		
		m_DragonManager = new DragonManager(m_Context);
	}

	// ��Ϸ�����Ĳ���
	private void doEnd() {
		// TODO
	}

	// ����surface/canvas�Ŀ�Ⱥ͸߶�
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
			
			// ��ʼ��Manager
			if (m_DragonManager != null && !m_DragonManager.isInit()){
				Rect rct = new Rect(0, 0, m_nCanvasWidth, m_nCanvasHeight);
				m_DragonManager.initManager(m_CellSize.right, m_CellSize.bottom, rct);
			}
		}
	}

	// ������Ϸ�߳����п���
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
			// �ȹ��˶�㴥��
			int nIndex = event.getActionIndex();
			if (nIndex != 0)
				return true;


			// ֻȡ�ô�������Чֵ
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

	// ��ͣ��Ϸ�߼�
	public void pause() {
		synchronized (m_sHolder) {
			m_bIsPaused = true;
		}
	}

	// �ָ�������Ϸ�߼�
	public void unpause() {
		// �����Ϸ����ʱ��,������Ӧ�������������������
		synchronized (m_sHolder) {
			m_bIsPaused = false;
		}
	}

	// �̵߳�ִ�к���
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
			
			// һ֡��ʱ�䳬��
			if ((int)lSleepTime >= CommonDefines.GAME_ONE_FRAME_TIME)
				continue;
			
			int nSleep = (int)(CommonDefines.GAME_ONE_FRAME_TIME - lSleepTime);

			try {
				Thread.sleep(nSleep);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

		// �߳̽���
		doEnd();
	}

	// ��Ϸ�滭
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

	// ��Ϸ�߼�����
	private void onBeforeDrawLogic() {
		if (m_DragonManager != null)
			m_DragonManager.onBeforeDrawLogic();
	}
	// ��Ϸ�߼�����
	private void onAfterDrawLogic() {
		if (m_DragonManager != null)
			m_DragonManager.onAfterDrawLogic();
	}

}