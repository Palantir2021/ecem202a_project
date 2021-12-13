package io.github.webbluetoothcg.bletestperipheral;

import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattService;
import android.os.Bundle;
import android.os.Handler;
import android.os.ParcelUuid;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;


import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Random;
import java.util.UUID;

/**
 * Created by Henny on 2017-06-15.
 */

public class AccelerometerServiceFragment extends ServiceFragment {

    // CONSTANTS
    public static final UUID SENSOR_READ_SERVICE = UUID.fromString("0000A101-0000-1000-8000-00805F9B34FB");

    public static final UUID ACC_X = UUID.fromString("0000A102-0000-1000-8000-00805f9b34fb");
    public static final UUID ACC_Y = UUID.fromString("0000A102-0000-1000-8000-00805f9b34fc");
    public static final UUID ACC_Z = UUID.fromString("0000A102-0000-1000-8000-00805f9b34fd");

    private static final int EXPONENT_MASK = 0x7f800000;
    private static final int EXPONENT_SHIFT = 23;
    private static final int MANTISSA_MASK = 0x007fffff;
    private static final int MANTISSA_SHIFT = 0;

    // GATT
    private BluetoothGattService sensorReadService;
    private BluetoothGattCharacteristic xAccCharacteristic, yAccCharacteristic, zAccCharacteristic;

    private ServiceFragmentDelegate serviceFragmentDelegate;

    private Handler updateHandler;
    private final long updateInterval = 20;
    private boolean isNotifying = false;
    private Random randomGenerator;

    private TextView xValueText, yValueText, zValueText;
    private Button notifyButton;

    float xValue, yValue, zValue;

    private View.OnClickListener notifyButtonListener = new View.OnClickListener() {
        @Override
        public void onClick(View v) {
            if (!isNotifying) startNotifying();
            else stopNotifying();
        }
    };

    Runnable updateTask = new Runnable() {
        @Override
        public void run() {
            try {
                randomizeValues();
                updateCharacteristics();
                sendNotifications();
            } finally {
                // 100% guarantee that this always happens, even if
                updateHandler.postDelayed(updateTask, updateInterval);
            }
        }
    };

    public AccelerometerServiceFragment() {
        setUpCharacteristics();
        setUpService();

        updateHandler = new Handler();
        randomGenerator = new Random();
    }

    // Lifecycle

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        View view = LayoutInflater.from(getActivity()).inflate(R.layout.fragment_accelerator, container, false);

        xValueText = (TextView) view.findViewById(R.id.x_value);
        yValueText = (TextView) view.findViewById(R.id.y_value);
        zValueText = (TextView) view.findViewById(R.id.z_value);
        notifyButton = (Button) view.findViewById(R.id.button_accelerometer_notify);
        notifyButton.setOnClickListener(notifyButtonListener);

        serviceFragmentDelegate = (ServiceFragmentDelegate) getActivity();

        return view;
    }

    // Gatt utils
    @Override
    public BluetoothGattService getBluetoothGattService() {
        return sensorReadService;
    }

    @Override
    public ParcelUuid getServiceUUID() {
        return new ParcelUuid(SENSOR_READ_SERVICE);
    }


    // Characteristics handling

    private void setUpCharacteristics() {
        xAccCharacteristic =
                new BluetoothGattCharacteristic(ACC_X,
                        BluetoothGattCharacteristic.PROPERTY_READ | BluetoothGattCharacteristic.PROPERTY_NOTIFY,
                        BluetoothGattCharacteristic.PERMISSION_READ);
        yAccCharacteristic =
                new BluetoothGattCharacteristic(ACC_Y,
                        BluetoothGattCharacteristic.PROPERTY_READ | BluetoothGattCharacteristic.PROPERTY_NOTIFY,
                        BluetoothGattCharacteristic.PERMISSION_READ);
        zAccCharacteristic =
                new BluetoothGattCharacteristic(ACC_Z,
                        BluetoothGattCharacteristic.PROPERTY_READ | BluetoothGattCharacteristic.PROPERTY_NOTIFY,
                        BluetoothGattCharacteristic.PERMISSION_READ);

        xAccCharacteristic.addDescriptor(
                Peripheral.getClientCharacteristicConfigurationDescriptor());

        xAccCharacteristic.addDescriptor(
                Peripheral.getCharacteristicUserDescriptionDescriptor("X read value: "));

        yAccCharacteristic.addDescriptor(
                Peripheral.getClientCharacteristicConfigurationDescriptor());

        yAccCharacteristic.addDescriptor(
                Peripheral.getCharacteristicUserDescriptionDescriptor("Y read value: "));

        zAccCharacteristic.addDescriptor(
                Peripheral.getClientCharacteristicConfigurationDescriptor());

        zAccCharacteristic.addDescriptor(
                Peripheral.getCharacteristicUserDescriptionDescriptor("Z read value: "));
    }

    private void setUpService() {
        sensorReadService = new BluetoothGattService(SENSOR_READ_SERVICE,
                BluetoothGattService.SERVICE_TYPE_PRIMARY);
        sensorReadService.addCharacteristic(xAccCharacteristic);
        sensorReadService.addCharacteristic(yAccCharacteristic);
        sensorReadService.addCharacteristic(zAccCharacteristic);
    }

    private void startNotifying() {
        updateHandler.post(updateTask);
    }

    private void stopNotifying() {
        updateHandler.removeCallbacks(updateTask);
    }

    private void randomizeValues() {
//        xValue = (float) (randomGenerator.nextInt(4092)*(Math.pow(-1,randomGenerator.nextInt(2)))*0.0039*9.80665);
//        yValue = (float) (randomGenerator.nextInt(4092)*(Math.pow(-1,randomGenerator.nextInt(2)))*0.0039*9.80665);
//        zValue = (float) (randomGenerator.nextInt(4092)*(Math.pow(-1,randomGenerator.nextInt(2)))*0.0039*9.80665);

        xValue = (float) (randomGenerator.nextFloat()*16*(Math.pow(-1,randomGenerator.nextInt(2))));
        yValue = (float) (randomGenerator.nextFloat()*16*(Math.pow(-1,randomGenerator.nextInt(2))));
        zValue = (float) (randomGenerator.nextFloat()*16*(Math.pow(-1,randomGenerator.nextInt(2))));
    }

    private void updateCharacteristics() {
        byte[] xBytes = getReversedBytesFromFloat(xValue);
        byte[] yBytes = getReversedBytesFromFloat(yValue);
        byte[] zBytes = getReversedBytesFromFloat(zValue);

        xAccCharacteristic.setValue(xBytes);
        yAccCharacteristic.setValue(yBytes);
        zAccCharacteristic.setValue(zBytes);
    }

    private void updateTextValues() {
        xValueText.setText(String.valueOf(xValue));
        yValueText.setText(String.valueOf(yValue));
        zValueText.setText(String.valueOf(zValue));
    }

    private void sendNotifications() {
        serviceFragmentDelegate.sendNotificationToDevices(xAccCharacteristic);
        serviceFragmentDelegate.sendNotificationToDevices(yAccCharacteristic);
        serviceFragmentDelegate.sendNotificationToDevices(zAccCharacteristic);
    }

    private int[] getMantissaExponentFromFloat(float val) {
        int bits = Float.floatToIntBits(val);
        int exponent = (bits & EXPONENT_MASK) >>> EXPONENT_SHIFT;
        int mantissa = (bits & MANTISSA_MASK) >>> MANTISSA_SHIFT;
        int formatted[] = new int[2];
        formatted[0] = mantissa;
        formatted[1] = exponent;

        return formatted;
    }

    private byte[] getReversedBytesFromFloat(float val) {
        return ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN).putFloat(val).array();
    }

    @Override
    public void notificationsEnabled(BluetoothGattCharacteristic characteristic, boolean indicate) {
        if (characteristic.getUuid() != ACC_X && characteristic.getUuid() != ACC_Y && characteristic.getUuid() != ACC_Z) {
            return;
        }
        if (indicate) {
            return;
        }
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getActivity(), R.string.notificationsEnabled, Toast.LENGTH_SHORT)
                        .show();
            }
        });
    }

    @Override
    public void notificationsDisabled(BluetoothGattCharacteristic characteristic) {
        if (characteristic.getUuid() != ACC_X && characteristic.getUuid() != ACC_Y && characteristic.getUuid() != ACC_Z) {
            return;
        }
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(getActivity(), R.string.notificationsNotEnabled, Toast.LENGTH_SHORT)
                        .show();
            }
        });
    }
}
