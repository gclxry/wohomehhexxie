package utility.method;

import android.content.Context;
import android.telephony.TelephonyManager;

public class UifUtils {
    
    public static String getImei(Context context) {
        if (context == null)
            return null;
        
        return ((TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE))
                .getDeviceId();
    }
    
}
