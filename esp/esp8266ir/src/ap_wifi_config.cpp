#include <ap_wifi_config.h>

const char *apSSID = "IR_REMOTE";

bool ap_switch = false;

IPAddress local_IP(192, 168, 56, 1);
IPAddress gateway(192, 168, 56, 1);
IPAddress subnet(255, 255, 255, 0);

void init_wifi_ap()
{
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.softAP(apSSID);

    Serial.print("AP IP address: ");
    Serial.println(WiFi.softAPIP());

    Serial.println("AP started");

    ap_switch = true;
}

void stop_wifi_ap()
{
    WiFi.mode(WIFI_STA);

    ap_switch = false;
}

bool get_wifi_ap()
{
    return ap_switch;
}