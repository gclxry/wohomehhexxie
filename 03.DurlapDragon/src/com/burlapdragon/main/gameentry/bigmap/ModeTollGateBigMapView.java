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
	// 触摸屏按下的点的X坐标
	private float m_fTouchDownX = 0.0f;
	private float m_fTouchDownY = 0.0f;
	// 最后接收到的Touch的X坐标
	private float m_fLastionMotionX = 0.0f;
	// 当前选中的View
	private int m_nCurScreen = 0;
	// 最小的滑动速率
	public final static int SNAP_VELOCITY = 600;

	// 打开通关模式小地图选择界面
	public final static int OPEN_SMALL_MAP_VIEW = 1;
	private int m_nTouchSlop = 0;

	// 不能使用此构造函数进行new操作
	public ModeTollGateBigMapView(Context context) {
		super(context);
	}

	@SuppressWarnings("deprecation")
	public ModeTollGateBigMapView(Context context, Handler handlerObj) {
		super(context);
		m_Context = context;
		m_Handler = handlerObj;
		m_Scroller = new Scroller(m_Context);
		// 初始化一个最小滑动距离
		m_nTouchSlop = ViewConfiguration.get(m_Context).getScaledTouchSlop();

		// 添加一级地图
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

	// 控制触摸事件的分发，例如是子视图的点击事件还是滑动事件
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		// 先过滤多点触摸
		if (event.getActionIndex() != 0)
			return true;

		// 添加触摸对象MotionEvent ， 用于计算触摸速率
		if (m_VelocityTracker == null)
			m_VelocityTracker = VelocityTracker.obtain();

		if (m_VelocityTracker != null)
			m_VelocityTracker.addMovement(event);

		// 只取得触摸的有效值
		int nMotion = event.getActionMasked();

		// 先判断是否为纯粹的点击
		if (nMotion == MotionEvent.ACTION_UP) {
			int nStepX = Math.abs((int) (m_fTouchDownX - event.getX()));
			int nStepY = Math.abs((int) (m_fTouchDownY - event.getY()));
			if (nStepX <= m_nTouchSlop && nStepY <= m_nTouchSlop) {
				// 纯粹的点击
				recycleVelocityTracker();
				// 打开小地图
				openSmallMapActivity(m_nCurScreen + 1);
				return true;
			}
		}

		if (nMotion == MotionEvent.ACTION_DOWN) {
			m_fTouchDownX = event.getX();
			m_fTouchDownY = event.getY();
			m_fLastionMotionX = m_fTouchDownX;
		} else if (nMotion == MotionEvent.ACTION_MOVE) {
			// 每次滑动屏幕，屏幕应该移动的距离
			int nDetaX = (int) (m_fLastionMotionX - event.getX());
			// 开始缓慢滑屏。 detaX > 0 向右滑动 ， detaX < 0 向左滑动
			scrollBy(nDetaX, 0);

			m_fLastionMotionX = event.getX();
		} else if (nMotion == MotionEvent.ACTION_UP
				|| nMotion == MotionEvent.ACTION_CANCEL) {

			final VelocityTracker velocityTracker = m_VelocityTracker;
			velocityTracker.computeCurrentVelocity(1000);
			// 计算速率
			int velocityX = (int) velocityTracker.getXVelocity();

			if (velocityX > SNAP_VELOCITY && m_nCurScreen > 0) {
				// 滑动速率达到了一个标准(快速向右滑屏，返回上一个屏幕) 马上进行切屏处理
				snapToScreen(m_nCurScreen - 1);
			} else if (velocityX < -SNAP_VELOCITY
					&& m_nCurScreen < (getChildCount() - 1)) {
				// 快速向左滑屏，返回下一个屏幕)
				snapToScreen(m_nCurScreen + 1);
			} else {
				// 当前为缓慢移动的，因此先判断是保留在本屏幕还是到下一屏幕
				snapToDestination();
			}

			recycleVelocityTracker();
		}

		return true;
	}

	// 回收VelocityTracker对象
	private void recycleVelocityTracker() {
		// 回收VelocityTracker对象
		if (m_VelocityTracker != null) {
			m_VelocityTracker.recycle();
			m_VelocityTracker = null;
		}
	}

	// 缓慢移动，因此需要根据偏移值判断目标屏是哪个？
	private void snapToDestination() {
		// 判断是否超过下一屏的中间位置，如果达到就抵达下一屏，否则保持在原屏幕
		// 这样的一个简单公式意思是：假设当前滑屏偏移值即 scrollCurX 加上每个屏幕一半的宽度，除以每个屏幕的宽度就是
		int destScreen = (getScrollX() + this.getWidth() / 2) / this.getWidth();
		snapToScreen(destScreen);
	}

	// 真正的实现跳转屏幕的方法
	private void snapToScreen(int whichScreen) {
		m_nCurScreen = whichScreen;

		// 防止屏幕越界，即超过屏幕数
		if (m_nCurScreen >= getChildCount())
			m_nCurScreen = getChildCount() - 1;
		if (m_nCurScreen < 0)
			m_nCurScreen = 0;

		// 为了达到下一屏幕或者当前屏幕，我们需要继续滑动的距离.根据dx值，可能想左滑动，也可能像右滑动
		int nDx = m_nCurScreen * this.getWidth() - getScrollX();
		m_Scroller.startScroll(getScrollX(), 0, nDx, 0, Math.abs(nDx) * 2);
		// 由于触摸事件不会重新绘制View，所以此时需要手动刷新View 否则没效果
		invalidate();
	}

	// 打开小地图，参数 nMapTypeId 是小地图类型
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

		// 如果返回true，表示动画还没有结束
		// 因为前面startScroll，所以只有在startScroll完成时才会为false
		if (m_Scroller.computeScrollOffset()) {
			// 产生了动画效果，根据当前值 每次滚动一点
			scrollTo(m_Scroller.getCurrX(), m_Scroller.getCurrY());

			// 此时同样也需要刷新View ，否则效果可能有误差
			postInvalidate();
		}
	}
}
