
package sdk360.login;

import sdk360.AppMpc;
import sdk360.SdkDefs;
import sdk360.SdkUtils;
import utility.method.UifUtils;
import android.content.Context;
import android.content.Intent;
import android.text.TextUtils;
import android.util.Log;

import com.qihoo.gamecenter.sdk.buildin.Matrix;
import com.qihoo.gamecenter.sdk.buildin.activity.ContainerActivity;
import com.qihoo.gamecenter.sdk.protocols.IDispatcherCallback;
import com.qihoo.gamecenter.sdk.protocols.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;

public class SdkLogin {

    private final String TAG = "uif.SdkLogin";
    private SdkLoginListener mSdkListener = null;

    public SdkLogin() {
    }

    /**
     * 使用360SDK的登录接口
     * 
     * @param isLandScape 是否横屏显示登录界面
     * @param isBgTransparent 是否以透明背景显示登录界面
     * @param clientId 即AppKey
     */
    public void doSdkLogin(Context context, boolean isLandScape, boolean isBgTransparent, String clientId, SdkLoginListener sdkListener) {
        mSdkListener = sdkListener;
        Intent intent = getLoginIntent(context, isLandScape, isBgTransparent, clientId);
        Matrix.invokeActivity(context, intent, mLoginCallback);
    }

    /***
     * 生成调用360SDK登录接口的Intent
     * 
     * @param isLandScape 是否横屏
     * @param isBgTransparent 是否背景透明
     * @param clientId 即AppKey
     * @return Intent
     */
    private Intent getLoginIntent(Context context, boolean isLandScape, boolean isBgTransparent, String clientId) {

        Intent intent = new Intent(context, ContainerActivity.class);

        // 界面相关参数，360SDK界面是否以横屏显示。
        intent.putExtra(ProtocolKeys.IS_SCREEN_ORIENTATION_LANDSCAPE, isLandScape);

        // 界面相关参数，360SDK登录界面背景是否透明。
        intent.putExtra(ProtocolKeys.IS_LOGIN_BG_TRANSPARENT, isBgTransparent);

        // *** 以下非界面相关参数 ***

        // Client Id 即 App Key。
        if (!TextUtils.isEmpty(clientId))
            intent.putExtra(ProtocolKeys.CLIENT_ID, clientId);

        // 必需参数，登录回应模式：CODE模式，即返回Authorization Code的模式。
        intent.putExtra(ProtocolKeys.RESPONSE_TYPE, SdkDefs.RESPONSE_TYPE_CODE);

        // 必需参数，手机的IMEI。
        intent.putExtra(ProtocolKeys.APP_IMEI, UifUtils.getImei(context));

        // 必需参数，360SDK版本号。
        intent.putExtra(ProtocolKeys.INSDK_VERSION, Matrix.getVersion(context));

        // 必需参数，App 版本号。
        intent.putExtra(ProtocolKeys.APP_VERSION, Matrix.getAppVersionName(context));

        // 必需参数，App Key。
        intent.putExtra(ProtocolKeys.APP_KEY, Matrix.getAppKey(context));

        // App 渠道号。
        intent.putExtra(ProtocolKeys.APP_CHANNEL, Matrix.getChannel());

        // 必需参数，使用360SDK的登录模块。
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_LOGIN);

        // 必须参数，登录的渠道号，每个游戏会分配不同的字串，用于区分用户从哪里登录
        intent.putExtra(ProtocolKeys.LOGIN_FROM, AppMpc.getMpc());

        return intent;
    }

    // 登录、注册的回调
    private IDispatcherCallback mLoginCallback = new IDispatcherCallback() {

        @Override
        public void onFinished(String data) {
            if (SdkDefs.DEG_I) {
                Log.d(TAG, "mLoginCallback, data is " + data);
            }
            if (mSdkListener != null) {
                String authorizationCode = SdkUtils.parseAuthorizationCode(data);
                mSdkListener.onGotAuthorizationCode(authorizationCode);
            }
        }
    };

}
