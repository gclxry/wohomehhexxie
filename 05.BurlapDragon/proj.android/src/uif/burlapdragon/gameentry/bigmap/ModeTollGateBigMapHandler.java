package uif.burlapdragon.gameentry.bigmap;

import android.os.Handler;
import android.os.Message;

public class ModeTollGateBigMapHandler extends Handler {
	private ModeTollGateBigMapSelectActivity m_MapActivity = null;

	public ModeTollGateBigMapHandler(
			ModeTollGateBigMapSelectActivity MapActivity) {
		m_MapActivity = MapActivity;
	}

	@Override
	public void handleMessage(Message msg) {
		if (m_MapActivity != null)
			m_MapActivity.onHandleMessage(msg);
	}
}
