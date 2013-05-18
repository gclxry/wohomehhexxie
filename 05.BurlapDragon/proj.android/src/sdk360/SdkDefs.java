package sdk360;

public class SdkDefs {
    
    public final static boolean DEG_I = true;
    public final static boolean DEG_W= true;
    public final static boolean DEG_E = true;

    // 登录响应模式：CODE模式。
    public static final String RESPONSE_TYPE_CODE = "code";
    // 360SDK登录返回的Json字符串中的Json name，代表CODE模式登录返回的Authorization Code（授权码，60秒有效）。
    public static final String JSON_NAME_CODE = "code";

    /**
     * 应用服务器为应用客户端提供的接口Url，用于通过AuthorizationCode获取TokenInfo
     * (DEMO使用的应用服务器url仅限DEMO示范使用
     * ，禁止正式上线游戏把DEMO应用服务器当做正式应用服务器使用，请使用方自己搭建自己的应用服务器。)
     */
    public static final String DEMO_APP_SERVER_URL_GET_TOKEN_BY_CODE = "http://demo.openapi.360.cn/game/mobileSDK/api.php?type=get_token_by_code&debug=1&code=";
}
