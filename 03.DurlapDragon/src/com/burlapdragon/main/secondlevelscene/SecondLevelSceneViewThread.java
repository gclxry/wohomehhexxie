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

// ��Ⱦ�߳�
public class SecondLevelSceneViewThread extends Thread {
	private SurfaceHolder m_sHolder;
	// ������,�����ȡ��Ӧ�õĸ�����Դ,��ͼƬ�����֡��ַ�����
	private Context m_Context;
	// UI�̵߳�Handler
	private SecondLevelSceneHandler m_ActiveHandler;
	// ��Ϸ�Ƿ���ͣ
	private boolean m_bIsPaused = false;
	// ��Ϸ�߳����п���
	private boolean m_bRunning = false;
	// ��ǰsurface/canvas�ĸ߶�,��surfaceChanged�����б�����
	private int m_nCanvasHeight = 0;
	// ��ǰsurface/canvas�Ŀ��,��surfaceChanged�����б�����
	private int m_nCanvasWidth = 0;
	private Paint m_paint;

	// ����PNG����ͼƬ
	private Bitmap m_bmpAnimation;
	private int m_nCurPalyId = 0;

	// �Զ��幹�캯��������Active��UI�̵߳���ز���
	public SecondLevelSceneViewThread(SurfaceHolder holder, Context context,
			SecondLevelSceneHandler handler) {
		m_sHolder = holder;
		m_Context = context;
		m_ActiveHandler = handler;
		// ����Paint
		m_paint = new Paint();
		// ���ÿ����Ч��
		// m_paint.setAntiAlias(true);
		// ���û�ˢ����ɫ
		// m_paint.setColor(Color.BLUE);

		doStart();
	}

	// ��ʼ����Ϸ��ʼʱ�Ĳ���
	private void doStart() {
		m_DObj = new CheckDirectionEvent();
		m_strMoveString = "";
		m_nCurPalyId = 0;
		m_bmpAnimation = Plotting.decodeResourceNoScaled(
				m_Context.getResources(), R.drawable.v7);
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

			// ��Ҫ����ÿ�λ����Ŀ�Ⱥ͸߶ȸı�ʱ, �������ͼƬ����Դ�����ŵ����������Ļ�Ĵ���
			// TODO
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

	private CheckDirectionEvent m_DObj;
	private String m_strD = "";

	public boolean onTouchEvent(MotionEvent event) {
		synchronized (m_sHolder) {
			// �ȹ��˶�㴥��
			int nIndex = event.getActionIndex();
			if (nIndex != 0)
				return true;

			Display("NO", event);

			// ֻȡ�ô�������Чֵ
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
				m_strD = "��";
				break;

			case CheckDirectionEvent.DIRECTION_DOWN:
				m_strD = "��";
				break;

			case CheckDirectionEvent.DIRECTION_LEFT:
				m_strD = "��";
				break;

			case CheckDirectionEvent.DIRECTION_RIGHT:
				m_strD = "��";
				break;

			default:
				m_strD = "û��";
				break;
			}

			return true;
		}
	}

	private String m_strMoveString;

	public void Display(String eventType, MotionEvent event) {
		// ��������������Ϣ
		int x = (int) event.getX();
		int y = (int) event.getY();
		// ��ʾ����ѹ����С
		float pressure = event.getPressure();
		// ��ʾ����ߴ�
		float size = event.getSize();
		// ��ȡ����������Ϣ
		int RawX = (int) event.getRawX();
		int RawY = (int) event.getRawY();

		String msg = "";

		msg += "�¼�����" + eventType + "\r\n";
		msg += "�������" + String.valueOf(x) + "," + String.valueOf(y) + "\r\n";
		msg += "��������" + String.valueOf(RawX) + "," + String.valueOf(RawY)
				+ "\r\n";
		msg += "����ѹ��" + String.valueOf(pressure) + ",";
		msg += "����ߴ�" + String.valueOf(size) + "\r\n";

		m_strMoveString = msg;
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

		// �߳̽���
		doEnd();
	}

	// ��Ϸ�滭
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

	// ��Ϸ�߼�����
	public void logic() {
		Log.v(this.getClass().getName(), "logic");
		// TODO
	}

}