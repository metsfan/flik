package org.cocos2dx.cpp;

import android.app.Application;
import android.content.Context;
import android.support.multidex.MultiDex;

/**
 * Created by adam on 10/7/16.
 */

public class MultiDexApplicationImpl extends Application {

    @Override
    public void onCreate() {
        MultiDex.install(this);

        super.onCreate();
    }

    @Override
    protected void attachBaseContext(Context base) {
        super.attachBaseContext(base);

        MultiDex.install(this);
    }
}
