package com.zhangyunfei.bluetirepersuretools.activity;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.example.bluetoothlib.contract.ConnectionCallback;


/**
 * Created by zhangyunfei on 16/9/17.
 */
public class BluetoothConnectionCallbackImpl implements ConnectionCallback {

    private static final String TAG = "BLUE";
    private android.os.Handler mHandler;

    public BluetoothConnectionCallbackImpl(Handler mHandler) {
        this.mHandler = mHandler;
    }

    public void onStateChange(int oldState, int newState) {
        Log.e(TAG, "## 消息状态发生改变: " + +oldState + " -> " + newState);
        // Give the new state to the Handler so the UI Activity can update
        mHandler.obtainMessage(BluetoothDemoActivity2.MESSAGE_STATE_CHANGE, newState, -1).sendToTarget();
    }

    @Override
    public void onConnected(String deviceName) {
        Log.e(TAG, "## 连接成功: " + deviceName);
        // Send the name of the connected device back to the UI Activity
        Message msg = mHandler.obtainMessage(BluetoothDemoActivity2.CONNECTED);
        Bundle bundle = new Bundle();
        bundle.putString(BluetoothDemoActivity2.DEVICE_NAME, deviceName);
        msg.setData(bundle);
        mHandler.sendMessage(msg);
    }

    @Override
    public void onConnectionFailed(String str) {
        Log.e(TAG, "## 连接失败 ");
        // Send a failure message back to the Activity
        Message msg = mHandler.obtainMessage(BluetoothDemoActivity2.MESSAGE_TOAST);
        Bundle bundle = new Bundle();
        bundle.putString(BluetoothDemoActivity2.TOAST, "Unable to connect device");
        msg.setData(bundle);
        mHandler.sendMessage(msg);
    }

    @Override
    public void onConnectionLost() {
        Log.e(TAG, "## 连接丢失 ");
        // Send a failure message back to the Activity
        Message msg = mHandler.obtainMessage(BluetoothDemoActivity2.MESSAGE_TOAST);
        Bundle bundle = new Bundle();
        bundle.putString(BluetoothDemoActivity2.TOAST, "Device connection was lost");
        msg.setData(bundle);
        mHandler.sendMessage(msg);
    }

    @Override
    public void onReadMessage(byte[] tmp) {
        Log.e(TAG, "## 读取到消息 len = " + tmp.length);
        // Send the obtained bytes to the UI Activity
        mHandler.obtainMessage(BluetoothDemoActivity2.MESSAGE_READ, tmp)
                .sendToTarget();
    }

    @Override
    public void onWriteMessage(byte[] buffer) {
        Log.e(TAG, "## 发送消息 len = " + buffer.length);
        // Share the sent message back to the UI Activity
        mHandler.obtainMessage(BluetoothDemoActivity2.MESSAGE_WRITE, -1, -1, buffer)
                .sendToTarget();
    }

    @Override
    public void onConnectStart(String mBluetoothDeviceAddress) {
        Log.e(TAG, "## onConnectStart ");

    }
}
