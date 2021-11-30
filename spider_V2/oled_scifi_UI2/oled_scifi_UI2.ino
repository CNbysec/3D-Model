#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
 u8g2.begin();
u8g2.enableUTF8Print();

}

void loop() {
display1();
display2();


  
}


  void display1(){
u8g2.clearBuffer();	
u8g2.drawTriangle(5,0, 0,0, 0,5);
 u8g2.drawLine(7, 0, 0, 7);
 u8g2.drawLine(7, 0, 116, 0);
 u8g2.drawLine(3, 7, 7, 3);
 u8g2.drawLine(7, 3, 33, 3);
u8g2.drawLine(68, 1, 116, 1);
u8g2.drawLine(116, 0, 128, 12);
u8g2.drawLine(69, 2, 117, 2);
u8g2.drawLine(118, 3, 124, 9);
u8g2.drawLine(117, 3, 123, 9);
u8g2.drawLine(3, 7, 3, 32);
u8g2.drawLine(4, 7, 4, 32);
u8g2.drawLine(3, 55, 12, 64);
u8g2.drawLine(0, 7, 0, 18);
u8g2.drawLine(0, 48, 0, 56);
u8g2.drawLine(0, 56, 6, 62);
u8g2.drawLine(9, 57, 13, 61);
u8g2.drawLine(13, 61, 25, 61);
//u8g2.drawLine(12, 63, 40, 63);
u8g2.drawLine(46, 62, 49, 59);
u8g2.drawLine(49, 59, 70, 59);
u8g2.drawLine(43, 63, 67, 63);
u8g2.drawLine(67, 63, 71, 59);
u8g2.drawLine(76, 59, 112, 59);
u8g2.drawLine(113, 59, 128, 44);
u8g2.drawLine(127, 44, 127, 12);
u8g2.drawLine(100, 63, 115, 63);
u8g2.drawLine(115, 63, 127, 51);
u8g2.drawLine(3, 33, 42, 62);
u8g2.drawLine(3, 32, 43, 62);
u8g2.drawLine(12, 33, 56, 33);
u8g2.drawLine(56, 33, 62, 27);
u8g2.drawLine(62, 27, 100, 27);
u8g2.drawLine(109, 27, 126, 10);
u8g2.drawLine(109, 27, 126, 44);
u8g2.drawLine(108, 27, 126, 9);
u8g2.drawLine(108, 27, 126, 45);
u8g2.drawLine(124, 10, 128, 10);
//u8g2.drawCircle(95, 43, 12, U8G2_DRAW_ALL);
//u8g2.drawCircle(69, 42, 10, U8G2_DRAW_UPPER_RIGHT);
//u8g2.drawCircle(69, 42, 10, U8G2_DRAW_LOWER_LEFT);
//u8g2.drawLine(37, 51, 55, 51);
u8g2.drawBox(10, 8, 10, 2);
u8g2.drawBox(14, 8, 2, 12);//T
u8g2.drawBox(24, 8, 10, 2);
u8g2.drawBox(24, 13, 10, 2);
u8g2.drawBox(24, 18, 10, 2);//E
u8g2.drawBox(38, 8, 10, 2);
u8g2.drawBox(38, 18, 10, 2);
u8g2.drawBox(46, 8, 2, 12);//C
u8g2.drawBox(52, 8, 2, 12);//I
u8g2.drawBox(58, 8, 10, 2);
u8g2.drawBox(58, 18, 10, 2);
u8g2.drawBox(58, 8, 2, 12);
u8g2.drawBox(67, 8, 2, 12);
u8g2.drawBox(62, 12, 3, 4);//O
u8g2.drawBox(72, 8, 10, 2);
u8g2.drawBox(72, 8, 2, 12);//R
u8g2.drawBox(86, 8, 10, 2);
u8g2.drawBox(86, 13, 10, 2);
u8g2.drawBox(86, 18, 10, 2);//E                         
u8g2.drawTriangle(119, 63, 127, 55,128,64);
  
    u8g2.setFont(u8g2_font_trixel_square_tr);   
    //u8g2.drawStr(12,29,"BODERLAND3");
    u8g2.drawStr(12,29,"AURORA-1V");
    //u8g2.drawStr(30,43,"made by Bruce in china");
    //u8g2.drawStr(60,53,"2020/1/25");
    u8g2.drawStr(30,43,"made by Murphy in china");
    u8g2.drawStr(60,53,"2021/5/28");
    
   u8g2.setFont(u8g2_font_missingplanet_t_all);
    u8g2.drawStr(115,32,"68");
        u8g2.setFont(u8g2_font_artossans8_8u);
     //u8g2.drawStr(25,47,"AMMO");
  u8g2.sendBuffer();				
  delay(6000);  }




  void display2(){
    u8g2.clearBuffer();  
u8g2.drawTriangle(5,0, 0,0, 0,5);
 u8g2.drawLine(7, 0, 0, 7);
 u8g2.drawLine(7, 0, 116, 0);
 u8g2.drawLine(3, 7, 7, 3);
 u8g2.drawLine(7, 3, 33, 3);
u8g2.drawLine(68, 1, 116, 1);
u8g2.drawLine(116, 0, 128, 12);
u8g2.drawLine(69, 2, 117, 2);
u8g2.drawLine(118, 3, 124, 9);
u8g2.drawLine(117, 3, 123, 9);
u8g2.drawLine(3, 7, 3, 32);
u8g2.drawLine(4, 7, 4, 32);
u8g2.drawLine(3, 55, 12, 64);
u8g2.drawLine(0, 7, 0, 18);
u8g2.drawLine(0, 48, 0, 56);
u8g2.drawLine(0, 56, 6, 62);
u8g2.drawLine(9, 57, 13, 61);
u8g2.drawLine(13, 61, 25, 61);
//u8g2.drawLine(12, 63, 40, 63);
u8g2.drawLine(46, 62, 49, 59);
u8g2.drawLine(49, 59, 70, 59);
u8g2.drawLine(43, 63, 67, 63);
u8g2.drawLine(67, 63, 71, 59);
u8g2.drawLine(76, 59, 112, 59);
u8g2.drawLine(113, 59, 128, 44);
u8g2.drawLine(127, 44, 127, 12);
u8g2.drawLine(100, 63, 115, 63);
u8g2.drawLine(115, 63, 127, 51);
u8g2.drawLine(3, 33, 42, 62);
u8g2.drawLine(3, 32, 43, 62);
u8g2.drawLine(12, 33, 56, 33);
u8g2.drawLine(56, 33, 62, 27);
u8g2.drawLine(62, 27, 100, 27);
u8g2.drawLine(109, 27, 126, 10);
u8g2.drawLine(109, 27, 126, 44);
u8g2.drawLine(108, 27, 126, 9);
u8g2.drawLine(108, 27, 126, 45);
u8g2.drawLine(124, 10, 128, 10);
//u8g2.drawCircle(95, 43, 12, U8G2_DRAW_ALL);
//u8g2.drawCircle(69, 42, 10, U8G2_DRAW_UPPER_RIGHT);
//u8g2.drawCircle(69, 42, 10, U8G2_DRAW_LOWER_LEFT);
//u8g2.drawLine(37, 51, 55, 51);
 u8g2.drawBox(10, 8, 10, 2);
u8g2.drawBox(14, 8, 2, 12);//T
u8g2.drawBox(24, 8, 10, 2);
u8g2.drawBox(24, 13, 10, 2);
u8g2.drawBox(24, 18, 10, 2);//E
u8g2.drawBox(38, 8, 10, 2);
u8g2.drawBox(38, 18, 10, 2);
u8g2.drawBox(46, 8, 2, 12);//C
u8g2.drawBox(52, 8, 2, 12);//I
u8g2.drawBox(58, 8, 10, 2);
u8g2.drawBox(58, 18, 10, 2);
u8g2.drawBox(58, 8, 2, 12);
u8g2.drawBox(67, 8, 2, 12);
u8g2.drawBox(62, 12, 3, 4);//O
u8g2.drawBox(72, 8, 10, 2);
u8g2.drawBox(72, 8, 2, 12);//R
u8g2.drawBox(86, 8, 10, 2);
u8g2.drawBox(86, 13, 10, 2);
u8g2.drawBox(86, 18, 10, 2);//E                                             
u8g2.drawTriangle(119, 63, 127, 55,128,64);
  u8g2.setFont(u8g2_font_trixel_square_tr);   
    //u8g2.drawStr(12,29,"BODERLAND3");
    u8g2.drawStr(12,29,"AURORA-1V");
   u8g2.setFont(u8g2_font_missingplanet_t_all);
    u8g2.drawStr(115,32,"68");
        u8g2.drawStr(30,45,"AURORA-TURRET");
    u8g2.drawStr(60,55,"CHARGING...");
    
u8g2.sendBuffer();  
delay(6000);
  }
