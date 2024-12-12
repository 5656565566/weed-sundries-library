#ifndef AIRCONDITION_H
#define AIRCONDITION_H

#include <IRremoteESP8266.h>
#include <Arduino.h>

#include "adapter.h"

class AirConditionerController
{
public:
    // 构造函数，传入空调型号
    AirConditionerController(uint8_t irPin);

    // 开启空调
    void turnOn();

    // 关闭空调
    void turnOff();

    // 设置温度
    void setTemperature(int temperature);

    // 设置风速
    void setFanSpeed(int speed);

    // 选择设备
    void selectACModel(String model);

    // 设置模式
    void setMode(int mode);

    // 设置背光
    bool setLight();

    // 睡眠模式
    bool setSleep();

    // 强劲模式
    bool setTurbo();

    // 环保模式
    bool setEcono();

    // 定时模式 
    void setTimer(uint16_t minutes);

private:
    bool light;
    bool sleep;
    bool turbo;
    bool econo;

    String _model;  // 空调型号
    uint8_t _irPin; // 红外发射管针脚
    IAirConditioner* currentAC = nullptr;

    IRAirtonAc *airtonAc;
    IRAirwellAc *airwellAc;
    IRAmcorAc *amcorAc;
    IRArgoAC *argoAc;
    IRBosch144AC *boschAc;

    IRCoolixAC *coolixAc;
    IRCoronaAc *coronaAc;

    IRDaikin128 *daikinAc128;
    IRDaikin152 *daikinAc152;
    IRDaikin160 *daikinAc160;
    IRDaikin176 *daikinAc176;
    IRDaikin216 *daikinAc216;
    IRDaikin2 *daikinAc2;
    IRDaikin64 *daikinAc64;

    IRDelonghiAc *delonghiAc;
    IREcoclimAc *ecoclimAc;
    IRElectraAc *electraAc;
    IRFujitsuAC *fujitsuAc;
    IRGoodweatherAc *goodweatherAc;
    IRGreeAC *greeAc;

    IRHaierAC *haierAc;
    IRHaierAC160 *haierAc160;
    IRHaierAC176 *haierAc176;
    IRHaierACYRW02 *haierAcACYRW02;

    IRHitachiAc *hitachiAc;
    IRKelonAc *kelonAc;
    IRKelvinatorAC *kelvinatorAc;
    IRLgAc *lgAc;
    IRMideaAC *mideaAc;
    IRMirageAc *mirageAc;
    IRMitsubishiAC *mitsubishiAc;

    IRMitsubishiHeavy88Ac *mitsubishiHeavy88Ac;
    IRMitsubishiHeavy152Ac *mitsubishiHeavy152Ac;

    IRNeoclimaAc *neoclimaAc;
    IRPanasonicAc *panasonicAc;
    IRRhossAc *rhossAc;
    IRSamsungAc *samsungAc;
    IRSanyoAc *sanyoAc;
    IRSharpAc *sharpAc;
    IRTcl112Ac *tclAc;
    IRTechnibelAc *technibelAc;
    IRTecoAc *tecoAc;
    IRToshibaAC *toshibaAc;
    IRTranscoldAc *transcoldAc;
    IRTrotec3550 *trotecAc;
    IRTrumaAc *trumaAc;
    IRVestelAc *vestelAc;
    IRWhirlpoolAc *whirlpoolAc;
    IRYorkAc *yorkAc;
};

#endif
