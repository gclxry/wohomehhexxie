
package com.example.androidtest;

import android.graphics.Camera;
import android.graphics.Matrix;
import android.view.animation.Animation;
import android.view.animation.Transformation;

public class Rotate3dAnimation extends Animation {
    // 围绕着X轴转
    public final static int ROTATE_X = 1;
    // 围绕着Y轴转
    public final static int ROTATE_Y = 2;
    // 围绕着XY轴同时转
    public final static int ROTATE_X_Y = 3;
    private int mRotate = ROTATE_X;
    
    // 开始角度
    private final float mFromDegrees;
    // 结束角度
    private final float mToDegrees;
    // 中心点
    private final float mCenterX;
    private final float mCenterY;
    private final float mDepthZ;
    // 是否需要扭曲
    private final boolean mReverse;
    // 摄像头
    private Camera mCamera = null;

    // fromDegrees：开始角度，比如：0.0f
    // toDegrees：目标角度，比如：90.0f（结合两个参数，代表从0度转到90度）
    // centerX、centerY：旋转的中心点
    // depthZ：旋转的Z轴的深度，这个可以营造出围绕旋转中心远近的效果
    // reverse：是否需要扭曲
    // nRotate：围绕转轴方向，ROTATE_Y：围绕着Y轴转（centerX参数将失效）；ROTATE_X：围绕着X轴转（centerY参数将失效）
    // ROTATE_X_Y：同时围绕x、y轴转
    public Rotate3dAnimation(float fromDegrees, float toDegrees, float centerX,
            float centerY, float depthZ, boolean reverse, int nRotate) {
        mFromDegrees = fromDegrees;
        mToDegrees = toDegrees;
        mCenterX = centerX;
        mCenterY = centerY;
        mDepthZ = depthZ;
        mReverse = reverse;
        mRotate = nRotate;
    }

    @Override
    public void initialize(int width, int height, int parentWidth,
            int parentHeight) {
        super.initialize(width, height, parentWidth, parentHeight);
        mCamera = new Camera();
    }

    // 生成 Transformation
    @Override
    protected void applyTransformation(float interpolatedTime, Transformation trans) {
        final float fromDegrees = mFromDegrees;
        // 生成中间角度
        float degrees = fromDegrees
                + ((mToDegrees - fromDegrees) * interpolatedTime);
        final float centerX = mCenterX;
        final float centerY = mCenterY;
        final Camera camera = mCamera;
        final Matrix matrix = trans.getMatrix();
        camera.save();
        
        // TBD：扭曲，还没搞懂这个扭曲是干什么的，先放着
        if (mReverse) {
            camera.translate(0.0f, 0.0f, mDepthZ * interpolatedTime);
        } else {
            camera.translate(0.0f, 0.0f, mDepthZ * (1.0f - interpolatedTime));
        }
        
        // 要修改成不同角度的旋转，需要修改这个地方，下面这个是水平旋转或者垂直旋转        
        // 看是围绕着哪个轴转
        if (mRotate == ROTATE_X) {
            camera.rotateY(degrees);
        } else if (mRotate == ROTATE_Y) {
            camera.rotateX(degrees);
        } else {
            camera.rotateX(degrees);
            camera.rotateY(degrees);
        }
        
        // 取得变换后的矩阵
        camera.getMatrix(matrix);
        camera.restore();
        matrix.preTranslate(-centerX, -centerY);
        matrix.postTranslate(centerX, centerY);
    }
}
