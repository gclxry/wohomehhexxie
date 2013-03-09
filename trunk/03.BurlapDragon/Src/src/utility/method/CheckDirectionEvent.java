package utility.method;

import android.view.MotionEvent;

// 判断当前手指滑动的方向，结果输出：上、下、左、右
public class CheckDirectionEvent {

	// ////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 手指向上滑动
	public static final int DIRECTION_UP = 1;
	// 手指向下滑动
	public static final int DIRECTION_DOWN = 2;
	public static final int DIRECTION_LEFT = 3;
	public static final int DIRECTION_RIGHT = 4;
	// 无方向
	public static final int DIRECTION_NONE = 5;
	// 参数、计算结果错误
	public static final int DIRECTION_ERROR = 6;
	// ////////////////////////////////////////////////////////////////////////////////////////////////////////
	private int m_nCheckRule = 50;
	private boolean m_bIsDown = false;
	// 当前这一轮DOWN、MOVE、UP的返回值
	private int m_nCurrentEventReturn = DIRECTION_NONE;
	private int m_nDownX = 0;
	private int m_nDownY = 0;

	// 设置触控判断方向的伐值
	public void SetCheckRule(int nRule) {
		m_nCheckRule = nRule;
	}

	private void Reset() {
		m_bIsDown = false;
		m_nCurrentEventReturn = DIRECTION_NONE;
		m_nDownX = 0;
		m_nDownY = 0;
	}

	public int onTouchEventCheck(MotionEvent objEvent, int nIndex) {
		// 先过滤多点触摸
		if (objEvent.getActionIndex() != nIndex)
			return DIRECTION_ERROR;

		// 只取得触摸的有效值
		int nMotion = objEvent.getActionMasked();
		if (nMotion == MotionEvent.ACTION_DOWN) {
			Reset();
			m_nDownX = (int) objEvent.getX();
			m_nDownY = (int) objEvent.getY();
			m_bIsDown = true;
		} else if (nMotion == MotionEvent.ACTION_UP
				|| nMotion == MotionEvent.ACTION_CANCEL) {
			if (m_nCurrentEventReturn == DIRECTION_NONE) {
				int nX = (int) objEvent.getX();
				int nY = (int) objEvent.getY();
				CheckDirection(nX, nY);

				if (m_nCurrentEventReturn != DIRECTION_NONE)
					return m_nCurrentEventReturn;
			}
			Reset();
		} else if (nMotion == MotionEvent.ACTION_MOVE) {
			if (!m_bIsDown || (m_nCurrentEventReturn != DIRECTION_NONE))
				return m_nCurrentEventReturn;

			int nX = (int) objEvent.getX();
			int nY = (int) objEvent.getY();
			CheckDirection(nX, nY);
		}

		return m_nCurrentEventReturn;
	}

	private int CheckDirection(int nCurX, int nCurY) {
		boolean bUp = false, bDown = false, bLeft = false, bRight = false;

		int nHSpace = nCurX - m_nDownX;
		int nVSpace = nCurY - m_nDownY;

		if (nVSpace >= m_nCheckRule)
			bDown = true;
		if (nVSpace <= (0 - m_nCheckRule))
			bUp = true;
		if (nHSpace >= m_nCheckRule)
			bRight = true;
		if (nHSpace <= (0 - m_nCheckRule))
			bLeft = true;

		nHSpace = Math.abs(nHSpace);
		nVSpace = Math.abs(nVSpace);

		m_nCurrentEventReturn = DIRECTION_NONE;
		if (bUp) {
			m_nCurrentEventReturn = DIRECTION_UP;
			if (bLeft && nHSpace > nVSpace) {
				m_nCurrentEventReturn = DIRECTION_LEFT;
			} else if (bRight && nHSpace > nVSpace) {
				m_nCurrentEventReturn = DIRECTION_RIGHT;
			}
		} else if (bDown) {
			m_nCurrentEventReturn = DIRECTION_DOWN;
			if (bLeft && nHSpace > nVSpace) {
				m_nCurrentEventReturn = DIRECTION_LEFT;
			} else if (bRight && nHSpace > nVSpace) {
				m_nCurrentEventReturn = DIRECTION_RIGHT;
			}
		} else if (bLeft) {
			m_nCurrentEventReturn = DIRECTION_LEFT;
		} else if (bRight) {
			m_nCurrentEventReturn = DIRECTION_RIGHT;
		}
		/*
		 * int nDirectionCtns = 0; if (bUp) nDirectionCtns++; if (bDown)
		 * nDirectionCtns++; if (bLeft) nDirectionCtns++; if (bRight)
		 * nDirectionCtns++;
		 * 
		 * m_nCurrentEventReturn = DIRECTION_NONE; if (nDirectionCtns == 1) { if
		 * (bUp) { m_nCurrentEventReturn = DIRECTION_UP; } else if (bDown) {
		 * m_nCurrentEventReturn = DIRECTION_DOWN; } else if (bLeft) {
		 * m_nCurrentEventReturn = DIRECTION_LEFT; } else if (bRight) {
		 * m_nCurrentEventReturn = DIRECTION_RIGHT; } }
		 */

		return m_nCurrentEventReturn;
	}
}
