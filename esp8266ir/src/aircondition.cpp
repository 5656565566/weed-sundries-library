#include "aircondition.h"

AirConditionerController::AirConditionerController(uint8_t irPin)
{
    _irPin = irPin;
    light = false;
    sleep = false;
    turbo = false;
    econo = false;
}

void AirConditionerController::turnOn()
{
    if(currentAC == nullptr){
        return;
    }
    currentAC->turnOn();
    Serial.println("Turning on Air Conditioner");
}

void AirConditionerController::turnOff()
{
    if(currentAC == nullptr){
        return;
    }
    currentAC->turnOff();
    Serial.println("Turning off Air Conditioner");
}

void AirConditionerController::setTemperature(int temperature)
{
    if(currentAC == nullptr){
        return;
    }
    currentAC->setTemperature(temperature);
    Serial.println("Setting temperature to " + String(temperature) + "°C");
}

void AirConditionerController::setFanSpeed(int speed)
{
    if(currentAC == nullptr){
        return;
    }
    currentAC->setFanSpeed(speed); // The desired setting. 0 is auto, 1-3 is the speed
    Serial.println("Setting fan speed to " + String(speed));
}

void AirConditionerController::setMode(int mode)
{
    if(currentAC == nullptr){
        return;
    }
    currentAC->setMode(mode);
    Serial.println("Setting mode to " + String(mode));
}

bool AirConditionerController::setLight()
{
    light = !light;

    if (currentAC != nullptr)
    {
        currentAC->setLight(light); // 调用适配器中的 setLight 方法
        Serial.println("Light set to " + String(light ? "ON" : "OFF"));
    }
    else
    {
        Serial.println("Error: currentAC is null.");
    }

    return light;
}

bool AirConditionerController::setSleep()
{
    sleep = !sleep;
    if (currentAC != nullptr)
    {
        currentAC->setSleep(sleep); // 调用适配器中的 setSleep 方法
        Serial.println("Sleep mode " + String(sleep ? "enabled" : "disabled"));
    }
    else
    {
        Serial.println("Error: currentAC is null.");
    }
    return sleep;
}

bool AirConditionerController::setTurbo()
{
    turbo = !turbo;
    if (currentAC != nullptr)
    {
        currentAC->setTurbo(turbo); // 调用适配器中的 setTurbo 方法
        Serial.println("Turbo mode " + String(turbo ? "enabled" : "disabled"));
    }
    else
    {
        Serial.println("Error: currentAC is null.");
    }
    return turbo;
}

bool AirConditionerController::setEcono()
{
    econo = !econo;
    if (currentAC != nullptr)
    {
        currentAC->setEcono(econo); // 调用适配器中的 setEcono 方法
        Serial.println("Econo mode " + String(econo ? "enabled" : "disabled"));
    }
    else
    {
        Serial.println("Error: currentAC is null.");
    }
    return econo;
}

void AirConditionerController::setTimer(uint16_t minutes)
{
    if (currentAC != nullptr)
    {
        currentAC->setTimer(minutes); // 调用适配器中的 setTimer 方法
        Serial.println("Timer set to " + String(minutes) + " minutes.");
    }
    else
    {
        Serial.println("Error: currentAC is null.");
    }
}

void AirConditionerController::selectACModel(String model)
{
    _model = model;
    // 先清空之前的空调对象
    if (currentAC != nullptr)
    {
        delete currentAC;
        currentAC = nullptr;
    }

    // 根据型号选择对应的空调类并初始化适配器
    if (_model == "Airton")
    {
        airtonAc = new IRAirtonAc(_irPin);
        currentAC = new IRAirtonAcAdapter(airtonAc);
    }
    else if (_model == "Airwell")
    {
        airwellAc = new IRAirwellAc(_irPin);
        currentAC = new IRAirwellAcAdapter(airwellAc);
    }
    else if (_model == "Amcor")
    {
        amcorAc = new IRAmcorAc(_irPin);
        currentAC = new IRAmcorAcAdapter(amcorAc); // 适配器实例
    }
    else if (_model == "Argo")
    {
        argoAc = new IRArgoAC(_irPin);
        currentAC = new IRArgoACAdapter(argoAc);
    }
    else if (_model == "Bosch144")
    {
        boschAc = new IRBosch144AC(_irPin);
        currentAC = new IRBosch144ACAdapter(boschAc);
    }
    else if (_model == "Coolix")
    {
        coolixAc = new IRCoolixAC(_irPin);
        currentAC = new IRCoolixACAdapter(coolixAc);
    }
    else if (_model == "Corona")
    {
        coronaAc = new IRCoronaAc(_irPin);
        // currentAC = new IRCoronaAcAdapter(coronaAc);
    }
    else if (_model == "Daikin128")
    {
        daikinAc128 = new IRDaikin128(_irPin);
        currentAC = new IRDaikin128Adapter(daikinAc128);
    }
    else if (_model == "Daikin152")
    {
        daikinAc152 = new IRDaikin152(_irPin);
        currentAC = new IRDaikin152Adapter(daikinAc152);
    }
    else if (_model == "Daikin160")
    {
        daikinAc160 = new IRDaikin160(_irPin);
        currentAC = new IRDaikin160Adapter(daikinAc160);
    }
    else if (_model == "Daikin176")
    {
        daikinAc176 = new IRDaikin176(_irPin);
        currentAC = new IRDaikin176Adapter(daikinAc176);
    }
    else if (_model == "Daikin216")
    {
        daikinAc216 = new IRDaikin216(_irPin);
        currentAC = new IRDaikin216Adapter(daikinAc216);
    }
    else if (_model == "Daikin2")
    {
        daikinAc2 = new IRDaikin2(_irPin);
        currentAC = new IRDaikin2Adapter(daikinAc2);
    }
    else if (_model == "Daikin64")
    {
        daikinAc64 = new IRDaikin64(_irPin);
        currentAC = new IRDaikin64Adapter(daikinAc64);
    }
    else if (_model == "Delonghi")
    {
        delonghiAc = new IRDelonghiAc(_irPin);
        currentAC = new IRDelonghiAcAdapter(delonghiAc);
    }
    else if (_model == "Ecoclim")
    {
        ecoclimAc = new IREcoclimAc(_irPin);
        currentAC = new IREcoclimAcAdapter(ecoclimAc);
    }
    else if (_model == "Electra")
    {
        electraAc = new IRElectraAc(_irPin);
        currentAC = new IRElectraAcAdapter(electraAc);
    }
    else if (_model == "Fujitsu")
    {
        fujitsuAc = new IRFujitsuAC(_irPin);
        currentAC = new IRFujitsuACAdapter(fujitsuAc);
    }
    else if (_model == "Goodweather")
    {
        goodweatherAc = new IRGoodweatherAc(_irPin);
        currentAC = new IRGoodweatherAcAdapter(goodweatherAc);
    }
    else if (_model == "Gree")
    {
        greeAc = new IRGreeAC(_irPin);
        currentAC = new IRGreeACAdapter(greeAc);
    }
    else if (_model == "Haier")
    {
        haierAc = new IRHaierAC(_irPin);
        currentAC = new IRHaierACAdapter(haierAc);
    }
    else if (_model == "Haier160")
    {
        haierAc160 = new IRHaierAC160(_irPin);
        currentAC = new IRHaierAC160Adapter(haierAc160);
    }
    else if (_model == "Haier176")
    {
        haierAc176 = new IRHaierAC176(_irPin);
        currentAC = new IRHaierAC176Adapter(haierAc176);
    }
    else if (_model == "HaierACYRW02")
    {
        haierAcACYRW02 = new IRHaierACYRW02(_irPin);
        currentAC = new IRHaierACYRW02Adapter(haierAcACYRW02);
    }
    else if (_model == "Hitachi")
    {
        hitachiAc = new IRHitachiAc(_irPin);
        currentAC = new IRHitachiAcAdapter(hitachiAc);
    }
    else if (_model == "Kelon")
    {
        kelonAc = new IRKelonAc(_irPin);
        currentAC = new IRKelonAcAdapter(kelonAc);
    }
    else if (_model == "Kelvinator")
    {
        kelvinatorAc = new IRKelvinatorAC(_irPin);
        currentAC = new IRKelvinatorACAdapter(kelvinatorAc);
    }
    else if (_model == "Lg")
    {
        lgAc = new IRLgAc(_irPin);
        currentAC = new IRLgAcAdapter(lgAc);
    }
    else if (_model == "Midea")
    {
        mideaAc = new IRMideaAC(_irPin);
        currentAC = new IRMideaACAdapter(mideaAc);
    }
    else if (_model == "Mirage")
    {
        mirageAc = new IRMirageAc(_irPin);
        currentAC = new IRMirageAcAdapter(mirageAc);
    }
    else if (_model == "Mitsubishi")
    {
        mitsubishiAc = new IRMitsubishiAC(_irPin);
        currentAC = new IRMitsubishiACAdapter(mitsubishiAc);
    }
    else if (_model == "MitsubishiHeavy88")
    {
        mitsubishiHeavy88Ac = new IRMitsubishiHeavy88Ac(_irPin);
        currentAC = new IRMitsubishiHeavy88AcAdapter(mitsubishiHeavy88Ac);
    }
    else if (_model == "MitsubishiHeavy152")
    {
        mitsubishiHeavy152Ac = new IRMitsubishiHeavy152Ac(_irPin);
        currentAC = new IRMitsubishiHeavy152AcAdapter(mitsubishiHeavy152Ac);
    }
    else if (_model == "Neoclima")
    {
        neoclimaAc = new IRNeoclimaAc(_irPin);
        currentAC = new IRNeoclimaAcAdapter(neoclimaAc);
    }
    else if (_model == "Panasonic")
    {
        panasonicAc = new IRPanasonicAc(_irPin);
        currentAC = new IRPanasonicAcAdapter(panasonicAc);
    }
    else if (_model == "Rhoss")
    {
        rhossAc = new IRRhossAc(_irPin);
        currentAC = new IRRhossAcAdapter(rhossAc);
    }
    else if (_model == "Samsung")
    {
        samsungAc = new IRSamsungAc(_irPin);
        currentAC = new IRSamsungAcAdapter(samsungAc);
    }
    else if (_model == "Sanyo")
    {
        sanyoAc = new IRSanyoAc(_irPin);
        currentAC = new IRSanyoAcAdapter(sanyoAc);
    }
    else if (_model == "Sharp")
    {
        sharpAc = new IRSharpAc(_irPin);
        currentAC = new IRSharpAcAdapter(sharpAc);
    }
    else if (_model == "Tcl112")
    {
        tclAc = new IRTcl112Ac(_irPin);
        currentAC = new IRTcl112AcAdapter(tclAc);
    }
    else if (_model == "Technibel")
    {
        technibelAc = new IRTechnibelAc(_irPin);
        currentAC = new IRTechnibelAcAdapter(technibelAc);
    }
    else if (_model == "Teco")
    {
        tecoAc = new IRTecoAc(_irPin);
        currentAC = new IRTecoAcAdapter(tecoAc);
    }
    else if (_model == "Toshiba")
    {
        toshibaAc = new IRToshibaAC(_irPin);
        currentAC = new IRToshibaACAdapter(toshibaAc);
    }
    else if (_model == "Transcold")
    {
        transcoldAc = new IRTranscoldAc(_irPin);
        currentAC = new IRTranscoldAcAdapter(transcoldAc);
    }
    else if (_model == "Trotec3550")
    {
        trotecAc = new IRTrotec3550(_irPin);
        currentAC = new IRTrotec3550Adapter(trotecAc);
    }
    else if (_model == "Truma")
    {
        trumaAc = new IRTrumaAc(_irPin);
        currentAC = new IRTrumaAcAdapter(trumaAc);
    }
    else if (_model == "Vestel")
    {
        vestelAc = new IRVestelAc(_irPin);
        currentAC = new IRVestelAcAdapter(vestelAc);
    }
    else if (_model == "Whirlpool")
    {
        whirlpoolAc = new IRWhirlpoolAc(_irPin);
        currentAC = new IRWhirlpoolAcAdapter(whirlpoolAc);
    }
    else if (_model == "York")
    {
        yorkAc = new IRYorkAc(_irPin);
        currentAC = new IRYorkAcAdapter(yorkAc);
    }
    else
    {
        Serial.println("Unsupported air conditioner model.");
    }
}
