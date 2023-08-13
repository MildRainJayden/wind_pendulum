# README

# wind_pendulum

[https://img.shields.io/badge/star-welcome!-red](https://img.shields.io/badge/star-welcome!-red)

[https://img.shields.io/badge/%20welcome_to_pull_your_requests!-8A2BE2](https://img.shields.io/badge/%20welcome_to_pull_your_requests!-8A2BE2)

某年电赛题目风力摆实现的源码，使用platformio开发，arduino uno框架

## 硬件部分

Arduino控制板、mpu6050模块、L298N电机驱动模块、万用板、四个航模风扇（后由于IO口不够改为两个）、电池、杜邦线、导线若干

组装参考图如下

![Untitled](README%209dbb64453a0c4e5184ab597abba7eaa6/Untitled.png)

## 软件部分

利用mpu6050实现了风力摆的姿态解算，得出四元数与Pitch、Yaw、Roll角，Pitch、Yaw、Roll角为航模较为重要的数据，通过将振幅、周期等拟合正弦函数实现了摆的角度摆动，控制算法采用较为经典的PID算法。

![Pitch、Yaw、Roll角](README%209dbb64453a0c4e5184ab597abba7eaa6/Untitled%201.png)

Pitch、Yaw、Roll角

![欧拉角与四元数](README%209dbb64453a0c4e5184ab597abba7eaa6/Untitled%202.png)

欧拉角与四元数