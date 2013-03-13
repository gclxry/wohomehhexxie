package uif.burlapdragon.gameentry.smallmap;

import android.os.Handler;
import android.os.Message;

public class ModeTollGateSmallMapHandler extends Handler {
	private ModeTollGateSmallMapSelectActivity m_MapActivity = null;

	public ModeTollGateSmallMapHandler(
			ModeTollGateSmallMapSelectActivity MapActivity) {
		m_MapActivity = MapActivity;
	}

	@Override
	public void handleMessage(Message msg) {
		if (m_MapActivity != null)
			m_MapActivity.onHandleMessage(msg);
	}
}
