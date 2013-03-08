package com.burlapdragon.main.gameentry.bigmap;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.VelocityTracker;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.ViewGroup;
import android.widget.Scroller;

public class ModeTollGateBigMapView extends ViewGroup {

	private Context m_Context = null;
	private Handler m_Handler = null;
	private Scroller m_Scroller = null;
	private VelocityTracker m_VelocityTracker = null;
	// ���������µĵ��X����
	private float m_fTouchDownX = 0.0f;
	private float m_fTouchDownY = 0.0f;
	// �����յ���Touch��X����
	private float m_fLastionMotionX = 0.0f;
	// ��ǰѡ�е�View
	private int m_nCurScreen = 0;
	// ��С�Ļ�������
	public final static int SNAP_VELOCITY = 600;

	// ��ͨ��ģʽС��ͼѡ�����
	public final static int OPEN_SMALL_MAP_VIEW = 1;
	private int m_nTouchSlop = 0;

	// ����ʹ�ô˹��캯������new����
	public ModeTollGateBigMapView(Context context) {
		super(context);
	}

	@SuppressWarnings("deprecation")
	public ModeTollGateBigMapView(Context context, Handler handlerObj) {
		super(context);
		m_Context = context;
		m_Handler = handlerObj;
		m_Scroller = new Scroller(m_Context);
		// ��ʼ��һ����С��������
		m_nTouchSlop = ViewConfiguration.get(m_Context).getScaledTouchSlop();

		// ���һ����ͼ
		for (int i = 1; i <= ModeTollGateBigMapViewItem.BIG_MAP_TYPE_CTNS; i++) {
			ModeTollGateBigMapViewItem mapItem = new ModeTollGateBigMapViewItem(
					m_Context);
			if (mapItem != null) {
				mapItem.setMapTypeId(i);
				this.addView(mapItem);
			}
		}
	}

	@Override
	protected void onLayout(boolean changed, int l, int t, int r, int b) {
		int nWidth = this.getWidth();
		int nHeight = this.getHeight();
		int nLeftOffset = 0;
		int nCtns = this.getChildCount();
		for (int i = 0; i < nCtns; i++) {
			View childView = this.getChildAt(i);
			if (childView == null)
				continue;

			childView.layout(nLeftOffset, 0, nLeftOffset + nWidth, nHeight);
			nLeftOffset += nWidth;
		}
	}

	// ���ƴ����¼��ķַ�������������ͼ�ĵ���¼����ǻ����¼�
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		// �ȹ��˶�㴥��
		if (event.getActionIndex() != 0)
			return true;

		// ��Ӵ�������MotionEvent �� ���ڼ��㴥������
		if (m_VelocityTracker == null)
			m_VelocityTracker = VelocityTracker.obtain();

		if (m_VelocityTracker != null)
			m_VelocityTracker.addMovement(event);

		// ֻȡ�ô�������Чֵ
		int nMotion = event.getActionMasked();

		// ���ж��Ƿ�Ϊ����ĵ��
		if (nMotion == MotionEvent.ACTION_UP) {
			int nStepX = Math.abs((int) (m_fTouchDownX - event.getX()));
			int nStepY = Math.abs((int) (m_fTouchDownY - event.getY()));
			if (nStepX <= m_nTouchSlop && nStepY <= m_nTouchSlop) {
				// ����ĵ��
				recycleVelocityTracker();
				// ��С��ͼ
				openSmallMapActivity(m_nCurScreen + 1);
				return true;
			}
		}

		if (nMotion == MotionEvent.ACTION_DOWN) {
			m_fTouchDownX = event.getX();
			m_fTouchDownY = event.getY();
			m_fLastionMotionX = m_fTouchDownX;
		} else if (nMotion == MotionEvent.ACTION_MOVE) {
			// ÿ�λ�����Ļ����ĻӦ���ƶ��ľ���
			int nDetaX = (int) (m_fLastionMotionX - event.getX());
			// ��ʼ���������� detaX > 0 ���һ��� �� detaX < 0 ���󻬶�
			scrollBy(nDetaX, 0);

			m_fLastionMotionX = event.getX();
		} else if (nMotion == MotionEvent.ACTION_UP
				|| nMotion == MotionEvent.ACTION_CANCEL) {

			final VelocityTracker velocityTracker = m_VelocityTracker;
			velocityTracker.computeCurrentVelocity(1000);
			// ��������
			int velocityX = (int) velocityTracker.getXVelocity();

			if (velocityX > SNAP_VELOCITY && m_nCurScreen > 0) {
				// �������ʴﵽ��һ����׼(�������һ�����������һ����Ļ) ���Ͻ�����������
				snapToScreen(m_nCurScreen - 1);
			} else if (velocityX < -SNAP_VELOCITY
					&& m_nCurScreen < (getChildCount() - 1)) {
				// ������������������һ����Ļ)
				snapToScreen(m_nCurScreen + 1);
			} else {
				// ��ǰΪ�����ƶ��ģ�������ж��Ǳ����ڱ���Ļ���ǵ���һ��Ļ
				snapToDestination();
			}

			recycleVelocityTracker();
		}

		return true;
	}

	// ����VelocityTracker����
	private void recycleVelocityTracker() {
		// ����VelocityTracker����
		if (m_VelocityTracker != null) {
			m_VelocityTracker.recycle();
			m_VelocityTracker = null;
		}
	}

	// �����ƶ��������Ҫ����ƫ��ֵ�ж�Ŀ�������ĸ���
	private void snapToDestination() {
		// �ж��Ƿ񳬹���һ�����м�λ�ã�����ﵽ�͵ִ���һ�������򱣳���ԭ��Ļ
		// ������һ���򵥹�ʽ��˼�ǣ����赱ǰ����ƫ��ֵ�� scrollCurX ����ÿ����Ļһ��Ŀ�ȣ�����ÿ����Ļ�Ŀ�Ⱦ���
		int destScreen = (getScrollX() + this.getWidth() / 2) / this.getWidth();
		snapToScreen(destScreen);
	}

	// ������ʵ����ת��Ļ�ķ���
	private void snapToScreen(int whichScreen) {
		m_nCurScreen = whichScreen;

		// ��ֹ��ĻԽ�磬��������Ļ��
		if (m_nCurScreen >= getChildCount())
			m_nCurScreen = getChildCount() - 1;
		if (m_nCurScreen < 0)
			m_nCurScreen = 0;

		// Ϊ�˴ﵽ��һ��Ļ���ߵ�ǰ��Ļ��������Ҫ���������ľ���.����dxֵ���������󻬶���Ҳ�������һ���
		int nDx = m_nCurScreen * this.getWidth() - getScrollX();
		m_Scroller.startScroll(getScrollX(), 0, nDx, 0, Math.abs(nDx) * 2);
		// ���ڴ����¼��������»���View�����Դ�ʱ��Ҫ�ֶ�ˢ��View ����ûЧ��
		invalidate();
	}

	// ��С��ͼ������ nMapTypeId ��С��ͼ����
	private void openSmallMapActivity(int nMapTypeId) {

		Log.v("MTGBMV_INFO", "openSmallMapActivity");
		if (m_Handler != null && nMapTypeId > 0) {
			Message msg = new Message();
			msg.what = ModeTollGateBigMapView.OPEN_SMALL_MAP_VIEW;
			msg.arg1 = nMapTypeId;
			m_Handler.sendMessage(msg);
		}
	}

	@Override
	public void computeScroll() {
		Log.v("MTGBMV_INFO", "computeScroll");

		// �������true����ʾ������û�н���
		// ��Ϊǰ��startScroll������ֻ����startScroll���ʱ�Ż�Ϊfalse
		if (m_Scroller.computeScrollOffset()) {
			// �����˶���Ч�������ݵ�ǰֵ ÿ�ι���һ��
			scrollTo(m_Scroller.getCurrX(), m_Scroller.getCurrY());

			// ��ʱͬ��Ҳ��Ҫˢ��View ������Ч�����������
			postInvalidate();
		}
	}
}
