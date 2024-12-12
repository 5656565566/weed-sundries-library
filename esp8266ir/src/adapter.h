#ifndef ADAPTER_H
#define ADAPTER_H

#include <ir_Airton.h>
#include <ir_Airwell.h>
#include <ir_Amcor.h>
#include <ir_Argo.h>
#include <ir_Bosch.h>
#include <ir_Carrier.h>
#include <ir_Coolix.h>
#include <ir_Corona.h>
#include <ir_Daikin.h>
#include <ir_Delonghi.h>
#include <ir_Ecoclim.h>
#include <ir_Electra.h>
#include <ir_Fujitsu.h>
#include <ir_Goodweather.h>
#include <ir_Gree.h>
#include <ir_Haier.h>
#include <ir_Hitachi.h>
#include <ir_Kelon.h>
#include <ir_Kelvinator.h>
#include <ir_LG.h>
#include <ir_Midea.h>
#include <ir_Mirage.h>
#include <ir_Mitsubishi.h>
#include <ir_MitsubishiHeavy.h>
#include <ir_NEC.h>
#include <ir_Neoclima.h>
#include <ir_Panasonic.h>
#include <ir_Rhoss.h>
#include <ir_Samsung.h>
#include <ir_Sanyo.h>
#include <ir_Sharp.h>
#include <ir_Tcl.h>
#include <ir_Technibel.h>
#include <ir_Teco.h>
#include <ir_Toshiba.h>
#include <ir_Transcold.h>
#include <ir_Trotec.h>
#include <ir_Truma.h>
#include <ir_Vestel.h>
#include <ir_Whirlpool.h>
#include <ir_York.h>

class IAirConditioner
{
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void setTemperature(int temperature) = 0;
    virtual void setFanSpeed(int speed) = 0;
    virtual void setMode(int mode) = 0;
    virtual void setEcono(bool on) = 0;
    virtual void setTurbo(bool on) = 0;
    virtual void setSleep(bool on) = 0;
    virtual void setTimer(uint16_t minutes) = 0;
    virtual void setLight(bool on) = 0;

    virtual ~IAirConditioner() {}
};

class IRAirtonAcAdapter : public IAirConditioner
{
public:
    IRAirtonAcAdapter(IRAirtonAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRAirtonAc *_ac;
};

class IRAirwellAcAdapter : public IAirConditioner
{
public:
    IRAirwellAcAdapter(IRAirwellAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPowerToggle(true);
    }

    void turnOff() override
    {
        _ac->setPowerToggle(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRAirwellAc *_ac;
};

class IRAmcorAcAdapter : public IAirConditioner
{
public:
    IRAmcorAcAdapter(IRAmcorAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRAmcorAc *_ac;
};

class IRArgoACAdapter : public IAirConditioner
{
public:
    IRArgoACAdapter(IRArgoAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRArgoAC *_ac;
};

class IRBosch144ACAdapter : public IAirConditioner
{
public:
    IRBosch144ACAdapter(IRBosch144AC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRBosch144AC *_ac;
};

class IRCoolixACAdapter : public IAirConditioner
{
public:
    IRCoolixACAdapter(IRCoolixAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }
    void setTurbo(bool on) override
    {
        _ac->setTurbo();
    }
    void setSleep(bool on) override
    {
        _ac->setSleep();
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRCoolixAC *_ac;
};

class IRCoronaAcAdapter : public IAirConditioner
{
public:
    IRCoronaAcAdapter(IRCoronaAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRCoronaAc *_ac;
};

class IRDaikin128Adapter : public IAirConditioner
{
public:
    IRDaikin128Adapter(IRDaikin128 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPowerToggle(true);
    }

    void turnOff() override
    {
        _ac->setPowerToggle(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLightToggle(on);
    }

private:
    IRDaikin128 *_ac;
};

class IRDaikin152Adapter : public IAirConditioner
{
public:
    IRDaikin152Adapter(IRDaikin152 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
        _ac->setComfort(on);
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRDaikin152 *_ac;
};

class IRDaikin160Adapter : public IAirConditioner
{
public:
    IRDaikin160Adapter(IRDaikin160 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRDaikin160 *_ac;
};

class IRDaikin176Adapter : public IAirConditioner
{
public:
    IRDaikin176Adapter(IRDaikin176 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRDaikin176 *_ac;
};

class IRDaikin216Adapter : public IAirConditioner
{
public:
    IRDaikin216Adapter(IRDaikin216 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRDaikin216 *_ac;
};

class IRDaikin2Adapter : public IAirConditioner
{
public:
    IRDaikin2Adapter(IRDaikin2 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRDaikin2 *_ac;
};

class IRDaikin64Adapter : public IAirConditioner
{
public:
    IRDaikin64Adapter(IRDaikin64 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPowerToggle(true);
    }

    void turnOff() override
    {
        _ac->setPowerToggle(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRDaikin64 *_ac;
};

class IRDelonghiAcAdapter : public IAirConditioner
{
public:
    IRDelonghiAcAdapter(IRDelonghiAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRDelonghiAc *_ac;
};

class IREcoclimAcAdapter : public IAirConditioner
{
public:
    IREcoclimAcAdapter(IREcoclimAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IREcoclimAc *_ac;
};

class IRElectraAcAdapter : public IAirConditioner
{
public:
    IRElectraAcAdapter(IRElectraAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRElectraAc *_ac;
};

class IRFujitsuACAdapter : public IAirConditioner
{
public:
    IRFujitsuACAdapter(IRFujitsuAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRFujitsuAC *_ac;
};

class IRGoodweatherAcAdapter : public IAirConditioner
{
public:
    IRGoodweatherAcAdapter(IRGoodweatherAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRGoodweatherAc *_ac;
};

class IRGreeACAdapter : public IAirConditioner
{
public:
    IRGreeACAdapter(IRGreeAC *_ac) : _ac(_ac)
    {
        _ac->begin();
    }

    void turnOn() override
    {
        _ac->setPower(true);
        _ac->send();
    }

    void turnOff() override
    {
        _ac->setPower(false);
        _ac->send();
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
        _ac->send();
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
        _ac->send();
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
        _ac->send();
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
        _ac->send();
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
        _ac->send();
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
        _ac->send();
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setTimer(minutes);
        _ac->send();
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
        _ac->send();
    }

private:
    IRGreeAC *_ac;
};

class IRHaierACAdapter : public IAirConditioner
{
public:
    IRHaierACAdapter(IRHaierAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setOnTimer(1);
        _ac->send();
    }

    void turnOff() override
    {
        _ac->setOffTimer(1);
        _ac->send();
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
        _ac->send();
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
        _ac->send();
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
        _ac->send();
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
        _ac->send();
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRHaierAC *_ac;
};

class IRHaierAC160Adapter : public IAirConditioner
{
public:
    IRHaierAC160Adapter(IRHaierAC160 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
        _ac->send();
    }

    void turnOff() override
    {
        _ac->setPower(false);
        _ac->send();
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
        _ac->send();
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
        _ac->send();
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
        _ac->send();
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
        _ac->send();
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
        _ac->send();
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRHaierAC160 *_ac;
};

class IRHaierAC176Adapter : public IAirConditioner
{
public:
    IRHaierAC176Adapter(IRHaierAC176 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
        _ac->send();
    }

    void turnOff() override
    {
        _ac->setPower(false);
        _ac->send();
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
        _ac->send();
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
        _ac->send();
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
        _ac->send();
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
        _ac->send();
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
        _ac->send();
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRHaierAC176 *_ac;
};

class IRHaierACYRW02Adapter : public IAirConditioner
{
public:
    IRHaierACYRW02Adapter(IRHaierACYRW02 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
        _ac->send();
    }

    void turnOff() override
    {
        _ac->setPower(false);
        _ac->send();
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
        _ac->send();
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
        _ac->send();
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
        _ac->send();
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
        _ac->send();
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
        _ac->send();
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRHaierACYRW02 *_ac;
};

class IRHitachiAcAdapter : public IAirConditioner
{
public:
    IRHitachiAcAdapter(IRHitachiAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
        _ac->send();
    }

    void turnOff() override
    {
        _ac->setPower(false);
        _ac->send();
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
        _ac->send();
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
        _ac->send();
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
        _ac->send();
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRHitachiAc *_ac;
};

class IRKelonAcAdapter : public IAirConditioner
{
public:
    IRKelonAcAdapter(IRKelonAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setTogglePower(true);
    }

    void turnOff() override
    {
        _ac->setTogglePower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setTimer(minutes);
    }

    void setLight(bool on) override
    {
    }

private:
    IRKelonAc *_ac;
};

class IRKelvinatorACAdapter : public IAirConditioner
{
public:
    IRKelvinatorACAdapter(IRKelvinatorAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRKelvinatorAC *_ac;
};

class IRLgAcAdapter : public IAirConditioner
{
public:
    IRLgAcAdapter(IRLgAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRLgAc *_ac;
};

class IRMideaACAdapter : public IAirConditioner
{
public:
    IRMideaACAdapter(IRMideaAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
        _ac->send();
    }

    void turnOff() override
    {
        _ac->setPower(false);
        _ac->send();
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
        _ac->send();
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
        _ac->send();
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
        _ac->send();
    }

    void setTurbo(bool on) override
    {
        _ac->setTurboToggle(true);
        _ac->send();
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
        _ac->send();
    }

    void setEcono(bool on) override
    {
        _ac->setEconoToggle(true);
        _ac->send();
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setOffTimer(minutes);
        _ac->send();
    }

    void setLight(bool on) override
    {
        _ac->setLightToggle(true);
        _ac->send();
    }

private:
    IRMideaAC *_ac;
};

class IRMirageAcAdapter : public IAirConditioner
{
public:
    IRMirageAcAdapter(IRMirageAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRMirageAc *_ac;
};

class IRMitsubishiACAdapter : public IAirConditioner
{
public:
    IRMitsubishiACAdapter(IRMitsubishiAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setTimer(minutes);
    }

    void setLight(bool on) override
    {
    }

private:
    IRMitsubishiAC *_ac;
};

class IRMitsubishiHeavy88AcAdapter : public IAirConditioner
{
public:
    IRMitsubishiHeavy88AcAdapter(IRMitsubishiHeavy88Ac *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRMitsubishiHeavy88Ac *_ac;
};

class IRMitsubishiHeavy152AcAdapter : public IAirConditioner
{
public:
    IRMitsubishiHeavy152AcAdapter(IRMitsubishiHeavy152Ac *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRMitsubishiHeavy152Ac *_ac;
};

class IRNeoclimaAcAdapter : public IAirConditioner
{
public:
    IRNeoclimaAcAdapter(IRNeoclimaAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRNeoclimaAc *_ac;
};

class IRPanasonicAcAdapter : public IAirConditioner
{
public:
    IRPanasonicAcAdapter(IRPanasonicAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRPanasonicAc *_ac;
};

class IRRhossAcAdapter : public IAirConditioner
{
public:
    IRRhossAcAdapter(IRRhossAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRRhossAc *_ac;
};

class IRSamsungAcAdapter : public IAirConditioner
{
public:
    IRSamsungAcAdapter(IRSamsungAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRSamsungAc *_ac;
};

class IRSanyoAcAdapter : public IAirConditioner
{
public:
    IRSanyoAcAdapter(IRSanyoAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRSanyoAc *_ac;
};

class IRSharpAcAdapter : public IAirConditioner
{
public:
    IRSharpAcAdapter(IRSharpAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRSharpAc *_ac;
};

class IRTcl112AcAdapter : public IAirConditioner
{
public:
    IRTcl112AcAdapter(IRTcl112Ac *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRTcl112Ac *_ac;
};

class IRTechnibelAcAdapter : public IAirConditioner
{
public:
    IRTechnibelAcAdapter(IRTechnibelAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setTimer(minutes);
    }

    void setLight(bool on) override
    {
    }

private:
    IRTechnibelAc *_ac;
};

class IRTecoAcAdapter : public IAirConditioner
{
public:
    IRTecoAcAdapter(IRTecoAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setTimer(minutes);
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRTecoAc *_ac;
};

class IRToshibaACAdapter : public IAirConditioner
{
public:
    IRToshibaACAdapter(IRToshibaAC *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
        _ac->setEcono(on);
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRToshibaAC *_ac;
};

class IRTranscoldAcAdapter : public IAirConditioner
{
public:
    IRTranscoldAcAdapter(IRTranscoldAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setEcono(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRTranscoldAc *_ac;
};

class IRTrotec3550Adapter : public IAirConditioner
{
public:
    IRTrotec3550Adapter(IRTrotec3550 *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setTimer(minutes);
    }

    void setLight(bool on) override
    {
    }

private:
    IRTrotec3550 *_ac;
};

class IRTrumaAcAdapter : public IAirConditioner
{
public:
    IRTrumaAcAdapter(IRTrumaAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRTrumaAc *_ac;
};

class IRVestelAcAdapter : public IAirConditioner
{
public:
    IRVestelAcAdapter(IRVestelAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPower(true);
    }

    void turnOff() override
    {
        _ac->setPower(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
        _ac->setTurbo(on);
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setTimer(uint16_t minutes) override
    {
        _ac->setTimer(minutes);
    }

    void setLight(bool on) override
    {
    }

private:
    IRVestelAc *_ac;
};

class IRWhirlpoolAcAdapter : public IAirConditioner
{
public:
    IRWhirlpoolAcAdapter(IRWhirlpoolAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        _ac->setPowerToggle(true);
    }

    void turnOff() override
    {
        _ac->setPowerToggle(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
        _ac->setSleep(on);
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
        _ac->setLight(on);
    }

private:
    IRWhirlpoolAc *_ac;
};

class IRYorkAcAdapter : public IAirConditioner
{
public:
    IRYorkAcAdapter(IRYorkAc *_ac) : _ac(_ac) {}

    void turnOn() override
    {
        // _ac->setPowerToggle(true);
    }

    void turnOff() override
    {
        // _ac->setPowerToggle(false);
    }

    void setTemperature(int temperature) override
    {
        _ac->setTemp(temperature);
    }

    void setFanSpeed(int speed) override
    {
        _ac->setFan(speed);
    }

    void setMode(int mode) override
    {
        _ac->setMode(mode);
    }

    void setEcono(bool on) override
    {
    }

    void setTurbo(bool on) override
    {
    }
    void setSleep(bool on) override
    {
    }

    void setTimer(uint16_t minutes) override
    {
    }

    void setLight(bool on) override
    {
    }

private:
    IRYorkAc *_ac;
};

#endif