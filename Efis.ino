
//https://ta-laboratories.com/blog/2018/09/07/recreating-a-7-segment-display-with-adafruit-gfx-ssd1306-oled/
// Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)
//https://github.com/keshikan/DSEG

/*
 The Arduino Mega with Mobiflight is connected to the SDA and SCL Pins of the second Arduino. In my case i used an Leonaro.
 The Oled display (AZDelivery 1x 0,96 Zoll OLED Display - I2C SSD1306 Chip 128 x 64 Pixel I2C)
 is connected to the second Arduino SDA to pin 13 and SCL to pin 11
*/

#include <U8g2lib.h>
#include <Wire.h>


#define DISPLAY_SDA 13
#define DISPLAY_SCL 11

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 11, /* data=*/ 13, /* reset=*/ U8X8_PIN_NONE);

bool isStd = false;
bool isHpa = true;
String valHpa="8888";
String valHg="88,88";


const uint8_t u8g2_font_7segment28_tf[2701] U8G2_FONT_SECTION("u8g2_font_7segment28_tf") = 
  "`\0\5\5\5\6\6\5\6\33%\0\376#\376\22\376\3\250\7\27\12t \6\0\0\341\11!\6\0"
  "\0\241\17\42\13\347\10\267\12\204A\276!\0#\64m\12\337[\204!\30a\10E\30\202\21\206`\204"
  "!\14&\60Cd\204!\30a\10F\30\202\21\206\60\230\300\14\221\21\206`\204!\24a\10F\30B"
  "\1\0$<\315\12\335k\2\26(\243$c\20\201\30\202@\202Q\220\200\20$\60\303\10\316 \2d"
  "\244\3\5\201\70\301\30L@\10\22\20\202\4D\10\302\10\306\20\6\21\210a$\246P\201\1\0%K"
  "t\22\37.\212#\224\243\10e\30\3\21\212h\10F(\302\20\214P\4!\34\241\10B\70\303\30\202"
  "\220\16!\250B\10\242P\202\70\222\20\206\61\34A\10E\70\202\20\212`\204!\24\301\10C(\42\62"
  "\214\241\10\345(\302)\4\0&\61n\22\237L\12t\230a\14E\134\31\210`\4\61\34\3\21\311\70"
  "\203\20H\61\206A\224!\24\246\10\302!\302`\206\61\220b a\30\5\11\2\0'\7\342\10w\11"
  "\34(\31\206\22]J\204!\20a\10D\30\2\21\15\201\210_\21\210\250\10\2\0)\31\206\12]\12"
  "\204\42\20\241\10D(\2\21\25\201\210\337\20\210h\10\2\0*\26\10\11\365:\4#\14!\10A\31"
  "B!\206 \204\21\210@\0+\17\214\21'\134\4%\256`EP\342\12\0,\7d\20\37\12\30-"
  "\13t(\277\37\244@\5)\0.\6\0\0!\10/\33h\2\37j\204\62\24\301\210\212`DE\60"
  "\242\42\30Q\21\214\250\14E\60\0\60$\266$\235/$\62\5!D\201\210\5\64\377\203\205\34h`"
  "\3:\310\2\232\377\213D\210B \246!\11\0\61\24#\274\241/\202\360\201#\10\42(A\370\300\21"
  "\4\21\0\62$\266$\235/$\62\221(\4T\230\343\377\250 \244\20\4*\4A\22\2\35\346\370\277"
  ")\204\210LC\22\0\63#\265,\235\37\244\61\215(\4S\220\343\377\246\20\244P\11)\4S\220\343"
  "\377\246 \242\20\204IH\2\0\64\35\66$\241\17\204I\304\2\232\377\301B\16A\12A\240\206\24\2"
  "*\314\361T\250\1\65$\266$\235/$\62\5!Db\230\343\377\246@\203 \15jH!\240\302"
  "\34\377G\205\21\205@LC\22\0\66&\266$\235/$\62\5!Db\230\343\377\246@\203 \15*"
  "\4A\12\203,\240\371\277H\204(\4b\32\222\0\0\67\37v$\241/$\62\5!D\201\210\5\64"
  "\377\203\205\34h\360\1\26Pa\216\377\243B\15\0\70(\266$\235/$\62\5!D\201\210\5\64\377"
  "\203\205\34\202\24\202@\205 Ha\220\5\64\377\27\211\20\205@LC\22\0\71'\266$\235/$\62"
  "\5!D\201\210\5\64\377\203\205\34\202\24\202@\15)\4T\230\343\377\250\60\242\20\210iH\2\0:"
  "\24\205\12\355\31\6\221\4B\10\37\260\202H\2\21\206\0\0;\12\342\31\35\12\14h\204\0<\23\254"
  "\21%\274\202\64\230\242\224\35A\25\251L\15+\0=\12\14\21+\14\260\17D\14>\24\254\21%\14"
  "\202\65\250\42\225)\341\24\245\314\14)X\0?\36k\22\337;\212\202\210\201\10B\60\304!\216\220\4"
  "$:\3\22%\321\7\200\220D\5\0@S\227\22\335\236\216\306(\342\20gXC\31\232@\6R\4"
  "a\10b \311\20\204@\206A\20!\10c(\3!\210`\204B\214\301\10\205\30\302\21\12\61\204#"
  "\24b\10F(\305\20\214P\204 \14\241\14d\20\302\20\6\61\206!\14#\34d\30\244\63H\0A"
  "%w$\241/\244\62\11!D!\10C\64\340\371\37\64$\21\244 \4J\4A\12\204\64\340\371\277"
  "X\314 \0B!w$\235\17\204:\320\361T\250A\220\10%\202 \5B\32\360\374_,B\24"
  "\202\61\21i\0C\26\225\42\235/$Q\5)\10s\220\343\377\244\20\242\61\11)\0D!w$\235"
  "_\203:L\362t\20R\20\2%\202 \5B\32\360\374_,B\24\202\61\21i\0E!\265$"
  "\235/\244Q\205(\14r\374\237\24f\20$Q\5)\10s\220\343\377\244\20\242\61\11)\0F\35u"
  "$\241/\244Q\205(\14r\374\237\24f\20$Q\5)\10s\220\343\377\244\60\1G#\267$\235/"
  "\244\62\11!Dc\240\343\377\250P\203\17\270\200\22\322\200\347\377b\21\242\20\214\211H\3\0H\35\67"
  "$\241\17\204:\320\361T\250A\220\10%\202 \5B\32\360\374_,f\20\0I\16\4\272\241/"
  "\204\360\1*\14\42\10\0J\35w$\235_\203:L\362t\250\302\15(!\15x\376/\26!\12"
  "\301\230\210\64\0K!w$\241/\244\62\11!Dc\240\343\377\250P\203 \21J\4A\12\204\64\340"
  "\371\277X\314 \0L\35u$\235\17\204\71\310\361R\230\301\7T@\205\71\310\361R\10\321\230"
  "\204\24\0M!w$\241/\244\62\11!D!\10C\64\340\371\37\64$A\205\33PB\32\360\374_"
  ",f\20\0N\25W\42\241/$B\211 H\201\220\6<\377\27\213\31\4\0O\31\227\42\235/$"
  "B\211 H\201\220\6<\377\27\213\20\205`LD\32\0P$w$\241/\244\62\11!D!\10C"
  "\64\340\371\37\64$\21\244 \4J\4A\32B\35\350\370?*T\0Q$w$\241/\244\62\11!"
  "D!\10C\64\340\371\37\64$\21\244 \4\212HA\240\303$\377G\207\32\4\0R\22U\42\241/"
  "$Q\5)\10s\220\343\377\244\60\1S%\266$\235/\244A\205 HB\240\303\34\377\233\2\15\202"
  "\64\250!\205\200\12s\374\37\25F\24\2\61\221H\0T\37u$\235\17\204\71\310\361R\230A\220"
  "D\25\244 \314A\216\377\223B\210\306$\244\0\0U\25W\42\235\17\2JH\3\236\377\213E\210B"
  "\60&\42\15\0V!w$\235\17\204\31\204!\32\360\374\17\32\222\240\302\15(!\15x\376/\26!"
  "\12\301\230\210\64\0W%w$\235\17\204\31\204!\32\360\374\17\32\222\10R\20\2%\202 \5B\32"
  "\360\374_,B\24\202\61\21i\0X!\67$\241\17\204\31\204!\32\360\374\17\32\222\10R\20\2%"
  "\202 \5B\32\360\374_,f\20\0Y$w$\235\17\204\31\204!\32\360\374\17\32\222\10R\20\2"
  "E\244 \320a\222\377\243\303\210B\60&\42\15\0Z \267$\235/\244\62\225(\4u\230\344\377\350"
  "P\205\33X\241\16t\374\37\25BT&\42\15\0[\14\205\22\35\12\230!\376\377\15\0\134\31h\2"
  "\37\12\4\63\30\261#\30\321\21\214\350\10Ft\4#\62\203\21\0]\13\205\12\35\12\224!\376\377\3"
  "^\30\13\11uK\6\64\34!\10F\10B\21\206\60FB(B\20\216\0_\13s\60\235\37\242\360"
  "\1#\0`\13\205\10\12\206\61\14\201\10a%w$\241/\244\62\11!D!\10C\64\340\371\37"
  "\64$\21\244 \4J\4A\12\204\64\340\371\277X\314 \0b!w$\235\17\204:\320\361T\250"
  "A\220\10%\202 \5B\32\360\374_,B\24\202\61\21i\0c\26\225\42\235/$Q\5)\10s"
  "\220\343\377\244\20\242\61\11)\0d!w$\235_\203:L\362t\20R\20\2%\202 \5B\32"
  "\360\374_,B\24\202\61\21i\0e!\265$\235/\244Q\205(\14r\374\237\24f\20$Q\5)"
  "\10s\220\343\377\244\20\242\61\11)\0f\35u$\241/\244Q\205(\14r\374\237\24f\20$Q\5"
  ")\10s\220\343\377\244\60\1g#\267$\235/\244\62\11!Dc\240\343\377\250P\203\17\270\200\22\322"
  "\200\347\377b\21\242\20\214\211H\3\0h\35\67$\241\17\204:\320\361T\250A\220\10%\202 \5"
  "B\32\360\374_,f\20\0i\16\4\272\241/\204\360\1*\14\42\10\0j\35w$\235_\203:L"
  "\362t\250\302\15(!\15x\376/\26!\12\301\230\210\64\0k!w$\241/\244\62\11!Dc"
  "\240\343\377\250P\203 \21J\4A\12\204\64\340\371\277X\314 \0l\35u$\235\17\204\71\310\361"
  "R\230\301\7T@\205\71\310\361R\10\321\230\204\24\0m!w$\241/\244\62\11!D!\10C"
  "\64\340\371\37\64$A\205\33PB\32\360\374_,f\20\0n\25W\42\241/$B\211 H\201\220"
  "\6<\377\27\213\31\4\0o\31\227\42\235/$B\211 H\201\220\6<\377\27\213\20\205`LD\32"
  "\0p$w$\241/\244\62\11!D!\10C\64\340\371\37\64$\21\244 \4J\4A\32B\35\350"
  "\370?*T\0q$w$\241/\244\62\11!D!\10C\64\340\371\37\64$\21\244 \4\212HA"
  "\240\303$\377G\207\32\4\0r\22U\42\241/$Q\5)\10s\220\343\377\244\60\1s w$\235"
  "\17\204:\320\361T\250A\220\10E\244 \320a\222\377\243\303\210B\60&\42\15\0t\37u$\235"
  "\17\204\71\310\361R\230A\220D\25\244 \314A\216\377\223B\210\306$\244\0\0u\25W\42\235\17"
  "\2JH\3\236\377\213E\210B\60&\42\15\0v!w$\235\17\204\31\204!\32\360\374\17\32\222\240"
  "\302\15(!\15x\376/\26!\12\301\230\210\64\0w%w$\235\17\204\31\204!\32\360\374\17\32\222"
  "\10R\20\2%\202 \5B\32\360\374_,B\24\202\61\21i\0x!\67$\241\17\204\31\204!\32"
  "\360\374\17\32\222\10R\20\2%\202 \5B\32\360\374_,f\20\0y$w$\235\17\204\31\204!"
  "\32\360\374\17\32\222\10R\20\2E\244 \320a\222\377\243\303\210B\60&\42\15\0z \267$\235/"
  "\244\62\225(\4u\230\344\377\350P\205\33X\241\16t\374\37\25BT&\42\15\0{\26\210\2]Z"
  "\6B\214\241\10F|E C\31\216\310\210\67\0|\11\202\22\335\11>\220\0}\26\210\12]\12\206"
  "B\230\301\210\337\21\316P\6\42\24\301\210\67\0~\16\216\10=\34\212\223\20\202$\247\10\0\14\206"
  "\12\37\12\16\42\376\377\221\3\0\0\0";


void setup() {
  Serial.begin(9600);    // start serial for output

  Wire.begin(0x27);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event

  u8g2.begin();
  updateDisplay();
}


void loop() {
  updateDisplay();  
  delay(5);
}

// function that executes whenever data is received from master
void receiveEvent() {
  char msgArray[9]="";


  // // if smaller than 32 ignore
   if(Wire.available()==32)
   {
     for (int i=0; i <= 8; i++){
       uint8_t hibits = (uint8_t)Wire.read();      
       Wire.read(); // ignore
       uint8_t lowbits = (uint8_t)Wire.read(); 
       Wire.read(); // ignore

       msgArray[i] = msgArray[i] | (hibits & 0xf0);
       msgArray[i] = msgArray[i] | ((lowbits & 0xf0)>>4);
       if(msgArray[i] == 0x20){
         msgArray[i]='\0';
       }
     }
     if(msgArray[7] != '\0'){
         msgArray[8]='\0';
     }

    handleCommand(String(msgArray));

   }else{
    while(Wire.available()){
      Wire.read();
    }
   }
}

void handleCommand(String command){
    //Serial.println(command);
  

   if(command.startsWith("#0")){
    valHpa=command.substring(2);
   }
   if(command.startsWith("#1")){
    valHg=command.substring(2);
   }
   if(command.startsWith("#2")){
     if(command.substring(2)=="1"){
      isHpa=true;
     }else{
       isHpa=false;
     }
   }
   if(command.startsWith("#3")){
     if(command.substring(2)=="0"){
      isStd=true;
     }else{
       isStd=false;
     }
   } 
}

 void updateDisplay(void) {
  u8g2.clearBuffer();					// clear the internal memory

  if(isStd)
  {
    u8g2.setFont(u8g2_font_7segment28_tf);
    u8g2.drawStr(30,55, "Std");
  }else{
   u8g2.setFont(u8g2_font_9x15_tf);	// choose a suitable font
   u8g2.drawStr(100,10, "QNH");	// write something to the internal memory
   u8g2.setFont(u8g2_font_7segment28_tf);
   if(isHpa){
    u8g2.drawStr(10,55, valHpa.c_str());
   }else{
    u8g2.drawStr(2,55, valHg.c_str());
   }
  }

  u8g2.sendBuffer();					// transfer internal memory to the display
 }
