package sdk360.appserver;

import com.qihoo.gamecenter.sdk.buildin.Matrix;
import com.qihoo.gamecenter.sdk.protocols.IDispatcherCallback;
import com.qihoo.gamecenter.sdk.protocols.ProtocolConfigs;
import com.qihoo.gamecenter.sdk.protocols.ProtocolKeys;

import android.content.Context;
import android.content.Intent;

public class AddFriendTask {

    public static void doAddFriendTask(Context context, String strToken, final AddFriendListener listener){
        
        Intent intent = new Intent();
        // function code 必须参数，使用SDK接口添加好友
        intent.putExtra(ProtocolKeys.FUNCTION_CODE, ProtocolConfigs.FUNC_CODE_ADD_FRIENDS);
        // 必须参数，APP KEY
        intent.putExtra(ProtocolKeys.APP_KEY, Matrix.getAppKey(context));
        // 必须参数，access_token
        intent.putExtra(ProtocolKeys.ACCESS_TOKEN, strToken);
        
        Matrix.execute(context, intent, new IDispatcherCallback() {
            @Override
            public void onFinished(String data) {
                if(listener != null)
                    listener.onAddFriendTaskResult(data);
            }
        });
    }
    
    
}
