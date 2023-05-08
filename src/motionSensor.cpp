#include "motionSensor.h"

//vars
MPU6050 mpu;
volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

bool dmpReady = false;  // set true if DMP init was successful
// uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
// uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
// uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer
String errorDetails = "";

Quaternion q;           // [w, x, y, z]         quaternion container
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

int MotionSensor_init() {
    // MPU6050 init
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock.
        Wire.setWireTimeout(3000, true); // set timeout to avoid I2C freezing
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);
    if (!mpu.testConnection()) {
        errorDetails = "MPU6050 connection failed";
        return -1;
    }

    // DMP init
    devStatus = mpu.dmpInitialize();
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788);
    if (devStatus == 0) {
        mpu.CalibrateAccel(6);
        mpu.CalibrateGyro(6);
        mpu.setDMPEnabled(true);
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), __dmpDataReady, RISING);
        // mpuIntStatus = mpu.getIntStatus();
        mpu.getIntStatus();
        dmpReady = true;
        // packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        errorDetails = "DMP Initialization failed (code " + String(devStatus) + ")";
        return -2;
    }
    return 0;
}

ypr_t MotionSensor_getYPR() {
    ypr_t ans = {0, 0, 0};
    if (dmpReady && mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        ans.yaw = ypr[0] * 180/M_PI;
        ans.pitch = ypr[1] * 180/M_PI;
        ans.roll = ypr[2] * 180/M_PI;
    }
    return ans;
}

ypr_t MotionSensor_getYPRFixed() {
    static ypr_t last = {0, 0, 0};
    ypr_t now = MotionSensor_getYPR();
    if (__abs(now.yaw - last.yaw) > FIX_VALUE ||
        __abs(now.pitch - last.pitch) > FIX_VALUE ||
        __abs(now.roll - now.roll) > FIX_VALUE)
        return last;
    else {
        last = now;
        return now;
    }
}

String MotionSensor_getErrorDetails() {
    return errorDetails;
}

void __dmpDataReady() {
    mpuInterrupt = true;
}

float __abs(float x) {
    return x > 0 ? x : -x;
}