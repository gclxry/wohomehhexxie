package com.example.androidtest;

import android.util.Log;
import android.view.animation.Interpolator;

public class AnimationFlyViewInterpolator implements Interpolator {
    @Override
    public float getInterpolation(float input) {
        Log.v ("animation", "input=" + input);
        return input;
    }
}
