#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Adafruit_NeoPixel.h>

// Replace with your network credentials
#define WIFI_SSID "MVMV"
#define WIFI_PASSWORD "PMPUtheBEST"

// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "YOUR_TOKEN"

Adafruit_NeoPixel strip(300, 4, NEO_GRB + NEO_KHZ800);

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);
unsigned long bot_lasttime; // last time messages' scan has been done

const int ledPin = LED_BUILTIN;
int ledStatus = 0;

void handleNewMessages(int numNewMessages)
{
  //Serial.print("handleNewMessages ");
  //Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    //Красный
    if (text == "❤️")
    {
      // strip.Color(255, 0, 0)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 0, 0));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Красный!", "");
    }
    
    //Оранжевый
    if (text == "🧡")
    {
      // strip.Color(255, 165, 0)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 165, 0));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Оранжевый!", "");
    }

    //Желтый
    if (text == "💛")
    {
      // strip.Color(255, 255, 0)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 0));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Желтый!", "");
    }

    //Зеленый
    if (text == "💚")
    {
      // strip.Color(0, 128, 0)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 128, 0));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Зеленый!", "");
    }

    //Синий
    if (text == "💙")
    {
      // strip.Color(0, 0, 255)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Синий!", "");
    }

    //Фиолетовый
    if (text == "💜")
    {
      // strip.Color(128, 0, 128)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(128, 0, 128));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Фиолетовый!", "");
    }

    //Черный
    if (text == "🖤")
    {
      // strip.Color(0, 0, 0)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Черный!", "");
    }

    //Белый
    if (text == "🤍")
    {
      // strip.Color(255, 255, 255)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(255, 255, 255));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Белый!", "");
    }

    //Коричневый
    if (text == "🤎")
    {
      // strip.Color(165, 42, 42)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(165, 42, 42));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Цвет изменен на Коричневый!", "");
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  strip.begin();                    // инициализируем объект NeoPixel
  strip.show();                     // отключаем все пиксели на ленте
  strip.setBrightness(50);          // указываем яркость (максимум 255)

  // attempt to connect to Wifi network:
  configTime(0, 0, "pool.ntp.org");      // get UTC time via NTP
  secured_client.setTrustAnchors(&cert); // Add root certificate for api.telegram.org
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  // Check NTP/Time, usually it is instantaneous and you can delete the code below.
  Serial.print("Retrieving time: ");
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);
}

void loop()
{
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }
}