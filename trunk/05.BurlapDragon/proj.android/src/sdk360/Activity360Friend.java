
package sdk360;


import sdk360.appserver.QihooUserInfo;
import sdk360.appserver.QihooUserInfoListener;
import sdk360.appserver.TokenInfo;
import sdk360.appserver.TokenInfoListener;
import sdk360.login.SdkLoginListener;
import uif.burlapdragon.BurlapDragonApplication;
import uif.burlapdragon.R;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.widget.ListView;

public class Activity360Friend extends SdkUserBaseActivity {

    // 开始登录
    public final int MSG_LOGON  = 1;
    // 开始取得TokenInfo
    public final int MSG_GET_TOKEN_INFO  = 2;
    // 开始取得 UserInfo
    public final int MSG_GET_USER_INFO  = 3;

    private final String TAG = "uif.Activity360Friend";

    private ListView mGameFriendList;
    private int mFriendCtns = 0;

    @Override
    public void onHandleMessage(Message msg) {
    }

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_friend);

        initView();
    }
    
    private void initView() {
        mGameFriendList = (ListView) this.findViewById(R.id.GameFriendList);
    }

    private void getFriendList() {
    }

    private void loadGameFriend() {
    }

    @Override
    public void onLoginResult(int errorCode) {
    }

}
