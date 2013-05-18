
package sdk360;

import org.json.JSONException;
import org.json.JSONObject;

import sdk360.appserver.QihooUserInfo;

import android.content.Context;
import android.text.TextUtils;
import android.util.Log;
import android.widget.Toast;

public class SdkUtils {

    private final static String TAG = "uif.SdkUtils";

    /**
     * 从Json字符中获取授权码
     * 
     * @param intent Intent数据
     * @return 授权码
     */
    public static String parseAuthorizationCode(String data) {
        String authorizationCode = null;
        if (!TextUtils.isEmpty(data)) {
            try {
                JSONObject json = new JSONObject(data);
                int errCode = json.optInt("errno");
                if (errCode == 0) {
                    // 只支持code登陆模式
                    JSONObject content = json.optJSONObject("data");
                    authorizationCode = content.optString(SdkDefs.JSON_NAME_CODE);
                }
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        if (SdkDefs.DEG_I) {
            Log.d(TAG, "parseAuthorizationCode=" + authorizationCode);
        }
        return authorizationCode;
    }

    public static boolean checkLoginInfo(Context context, QihooUserInfo info) {
        if (null == info || !info.isValid()) {
            if (context != null) {
                Toast.makeText(context, "需要登录才能执行此操作", Toast.LENGTH_SHORT).show();
            }
            return false;
        }
        return true;
    }

}
