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

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if (text == "wipe")
    {
      colorWipe(100, 2);
    }

    if (text == "cycle")
    {
      rainbowCycle(2);
    }

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

    if (text == "/ledon")
    {
      //strip.setPixelColor(1, strip.Color(250, 0, 0));  // указываем цвет первого пикселя
      //strip.show();  // отправляем информацию на ленту
      
      digitalWrite(ledPin, LOW); // turn the LED on (HIGH is the voltage level)
      ledStatus = 1;
      bot.sendMessage(chat_id, "Led is ON", "");
    }

    if (text == "/ledoff")
    {
      // strip.Color(0, 0, 0)
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      strip.show();
      
      bot.sendMessage(chat_id, "Led is OFF", "");
    }

    if (text == "/status")
    {
      if (ledStatus)
      {
        bot.sendMessage(chat_id, "Led is ON", "");
      }
      else
      {
        bot.sendMessage(chat_id, "Led is OFF", "");
      }
    }

    if (text == "/start")
    {
      String welcome = "Чтобы изменить цвет - пришлите мне эмодзи-сердечко, которое покрашено в этот цвет!";
      bot.sendMessage(chat_id, welcome, "Markdown");
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

  pinMode(ledPin, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(ledPin, HIGH); // initialize pin as off (active LOW)

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