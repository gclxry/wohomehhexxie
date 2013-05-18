
package sdk360;

import sdk360.appserver.QihooUserInfo;
import sdk360.appserver.QihooUserInfoListener;
import sdk360.appserver.QihooUserInfoTask;
import sdk360.appserver.TokenInfo;
import sdk360.appserver.TokenInfoListener;
import sdk360.appserver.TokenInfoTask;
import sdk360.friend.SdkFriend;
import sdk360.login.SdkLogin;
import sdk360.login.SdkLoginListener;
import android.app.Activity;
import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;

import com.qihoo.gamecenter.sdk.buildin.Matrix;
import com.qihoo.gamecenter.sdk.protocols.IDispatcherCallback;

public class Sdk360Manager {

    private final String TAG = "uif.SdkManager";

    // 开始登录
    public final static int MSG_LOGON = 1;
    // 开始取得TokenInfo
    public final static int MSG_GET_TOKEN_INFO = 2;
    // 开始取得 UserInfo
    public final static int MSG_GET_USER_INFO = 3;
    // 登录结果
    public final static int MSG_LOGON_RESULT = 4;
    
    private Sdk360State m360SdkState = new Sdk360State();
    private SdkLogin mSdkLogin = null;
    private boolean mIsInit = false;
    private boolean mbInLogon = false;

    // ---------------------------------调用360SDK接口初始化和销毁------------------------------------
    /**
     * @param isLandScape 是否横屏显示登录界面
     */
    public void init360Sdk(Activity activity, boolean isLandScape) {
        if (activity == null || mIsInit)
            return;

        mIsInit = true;
        Matrix.init(activity, isLandScape, new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
                if (SdkDefs.DEG_I) {
                    Log.v(TAG, "Matrix.init onFinished = " + data);
                }
            }
        });
    }

    public void destroy360Sdk(Activity activity) {
        if (mIsInit) {
            mIsInit = false;
            Matrix.destroy(activity);
        }
    }

    public Sdk360State getSdkState() {
        return m360SdkState;
    }

    public void sendToLogon(Handler handler) {
        if (handler == null)
            return;

        Message msg = handler.obtainMessage(MSG_LOGON);
        handler.sendMessage(msg);
    }

    private void sendToGetTokenInfo(Handler handler) {
        if (handler == null)
            return;

        Message msg = handler.obtainMessage(MSG_GET_TOKEN_INFO);
        handler.sendMessage(msg);
    }

    private void sendToGetUserInfo(Handler handler) {
        if (handler == null)
            return;

        Message msg = handler.obtainMessage(MSG_GET_USER_INFO);
        handler.sendMessage(msg);
    }
    
    private void sendLogonResult(Handler handler, int nResult){
        mbInLogon = false;
        if (handler == null)
            return;

        Message msg = handler.obtainMessage(MSG_LOGON_RESULT);
        msg.arg1 = nResult;
        handler.sendMessage(msg);
    }

    // ---------------------------------调用360SDK接口------------------------------------
    /**
     * 使用360SDK的登录接口
     * 
     * @param isLandScape 是否横屏显示登录界面
     * @param isBgTransparent 是否以透明背景显示登录界面
     * @param clientId 即AppKey
     */
    public void doSdkLogin(Context context, final Handler handler) {
        if (context == null || handler == null || m360SdkState == null || mbInLogon)
            return;

        if (m360SdkState.isLogon()){
            // 已经登录了
            sendLogonResult(handler, 0);
            return;
        }

        mbInLogon = true;
        if (mSdkLogin == null) {
            mSdkLogin = new SdkLogin();
        }

        mSdkLogin.doSdkLogin(context, true, true, Matrix.getAppKey(context),
                new SdkLoginListener() {
                    @Override
                    public void onGotAuthorizationCode(String code) {
                        m360SdkState.mAuthorizationCode = code;
                        if (TextUtils.isEmpty(code)) {
                            sendLogonResult(handler, -1);
                        } else {
                            sendToGetTokenInfo(handler);
                        }
                    }
                });
    }

    public void doGetTokenInfo(Context context, final Handler handler) {
        if (context == null || handler == null || m360SdkState == null
                || TextUtils.isEmpty(m360SdkState.mAuthorizationCode))
            return;

        // 请求应用服务器，用AuthorizationCode换取AccessToken
        TokenInfoTask.doRequest(context, m360SdkState.mAuthorizationCode,
                Matrix.getAppKey(context), new TokenInfoListener() {
                    @Override
                    public void onGotTokenInfo(TokenInfo tokenInfo) {
                        m360SdkState.mTokeninfo = tokenInfo;
                        if (tokenInfo == null) {
                            sendLogonResult(handler, -2);
                        } else {
                            sendToGetUserInfo(handler);
                        }
                    }
                });
    }

    public void doGet360UserInfo(Context context, final Handler handler) {
        if (context == null || handler == null || m360SdkState == null
                || m360SdkState.mTokeninfo == null)
            return;

        // 请求应用服务器，用AccessToken换取UserInfo
        QihooUserInfoTask.doRequest(context, m360SdkState.mTokeninfo.getAccessToken(),
                Matrix.getAppKey(context), new QihooUserInfoListener() {
                    @Override
                    public void onGotUserInfo(QihooUserInfo userInfo) {
                        m360SdkState.mUsrInfo = userInfo;
                        sendLogonResult(handler, (userInfo == null ? -3 : 0));
                    }
                });
    }

    // ---------------------------------------------获取游戏好友接口-------------------------
    private SdkFriend mSdkFriend = null;

    // usrInfo : 必须参数，用户信息
    // tokeninfo : 必须参数，用户token信息
    protected void doSdkGetGameFriend(Context context, QihooUserInfo usrInfo, TokenInfo tokeninfo,
            int nStart,
            int nCount) {
        if (context == null)
            return;

        if (mSdkFriend == null) {
            mSdkFriend = new SdkFriend(context);
        }
        mSdkFriend.doSdkGetGameFriend(usrInfo, tokeninfo, nStart, nCount);
    }

}
