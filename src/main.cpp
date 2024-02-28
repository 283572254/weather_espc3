#include <Wire.h>  
#include <Adafruit_SSD1306.h> 
 
#define scl 5
#define sda 18
 
//新建iic对象以及显示屏对象
TwoWire I2Cone = TwoWire(0);
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &I2Cone);
 
void setup() 
{
  I2Cone.begin(sda, scl, 400000); 
   //初始化显示屏
   display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
   //清屏
   display.clearDisplay();
   //设置字体大小
   display.setTextSize(2);
   display.setTextColor(INVERSE);  
} 
void loop()
{
     display.setTextColor(WHITE);//开像素点发光
     display.setCursor(0,19);
     display.print("nihao");
     display.display();
}