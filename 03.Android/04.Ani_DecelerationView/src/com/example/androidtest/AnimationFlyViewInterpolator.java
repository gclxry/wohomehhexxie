package com.example.androidtest;

import android.view.animation.Interpolator;

public class AnimationFlyViewInterpolator implements Interpolator {
    @Override
    public float getInterpolation(float input) {
        // 抛物线y轴算法
        return (2 * input * input - 2 * input);
    }
}
