/*
 * For use with Teensy V2.0, Arduino 1.1 and Xbox 360 
 * Universal Media Remote from Microsoft. 
 *
 * Based off IRrecvDemo https://github.com/shirriff/Arduino-IRremote
 *
 * Version 0.1 Sep. 16, 2012
 *   Initial release.
 * 
 * Copyright 2012 Nathan Warner
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <IRremote.h>

int RECV_PIN = 11;
long code = 0;
long t = 0;
long t_save = 0;
long hold_flag = 0;
unsigned long play_1 = -2146438122; // play pause (space)
unsigned long play_2 = -2146470890;
unsigned long pause_1 = -2146438120; // play pause (space)
unsigned long pause_2 = -2146470888;
unsigned long right_1 = -2146470879; // (right)
unsigned long right_2 = -2146438111;
unsigned long left_1 = -2146438112; // (left)
unsigned long left_2 = -2146470880;
unsigned long up_1 = -2146438114;  // (up)
unsigned long up_2 = -2146470882;
unsigned long down_1 = -2146438113; // (down)
unsigned long down_2 = -2146470881;
unsigned long ok_1 = -2146438110;  // (enter)
unsigned long ok_2 = -2146470878;
unsigned long stop_1 = -2146470887;  // (x)
unsigned long stop_2 = -2146438119;
unsigned long ff_1 = -2146470892;  // fast forward (f)
unsigned long ff_2 = -2146438124;
unsigned long rw_1 = -2146470891;  // rewind (r)
unsigned long rw_2 = -2146438123;
unsigned long skip_right_1 = -2146470886; // (right)
unsigned long skip_right_2 = -2146438118;
unsigned long skip_left_1 = -2146470885; // (quote)
unsigned long skip_left_2 = -2146438117;
unsigned long info_1 = -2146470897; // show info (i)
unsigned long info_2 = -2146438129;
unsigned long display_1 = -2146470833; // show video (tab)
unsigned long display_2 = -2146438065;
unsigned long x_1 = -2146470808;  // toggle watched (W)
unsigned long x_2 = -2146438040;
unsigned long back_1 = -2146470877;  // (esc)
unsigned long back_2 = -2146438109;
unsigned long dvd_menu_1 = -2146438108; // xbmc power menu (S)
unsigned long dvd_menu_2 = -2146470876;
unsigned long y_1 = -2146438106;  // start xbmc (ctrl-alt-x)
unsigned long y_2 = -2146470874; 
unsigned long a_1 = -2146470810;  // context (c)
unsigned long a_2 = -2146438042;
unsigned long b_1 = -2146438107;  // (backspace)
unsigned long b_2 = -2146470875;


IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {             // Did we received ir data?
    //Serial.println(results.value, HEX);
    if (results.value != code) {             // Did we get a new code?
      code = results.value;                  // Save the new code.
      t_save = millis();                     // Save the time we got a new code.
      press_key(code);                       // Press the key
    }
    else {                                   // We got a new code
      t = millis();                          // save the current millis
      int t_diff = t-t_save;                 // diff between first time we saw the code
      if (t_diff > 300 && t_diff < 1000){    
        press_key(code);
      }
      if (t_diff > 1000 && hold_flag == 0){ 
        hold_key(code);
      }
    }
    irrecv.resume();                            // Receive the next value
  }
  else{                                         // Didn't receive a code
    if((millis()-t) > 100 && hold_flag == 1){   // check for hold and unhold 
      unhold_key();                             // unhold kay
    } 
  }
}

void set_keys(long code){
       if(code == up_1 || code == up_2){
         Keyboard.set_key1(KEY_UP);
       }
       if(code == down_1 || code == down_2){
         Keyboard.set_key1(KEY_DOWN);
       }
       if(code == right_1 || 
          code == right_2 ||
          code == skip_right_1 ||
          code == skip_right_2){
         Keyboard.set_key1(KEY_RIGHT);
       }
       if(code == left_1 || code == left_2){
         Keyboard.set_key1(KEY_LEFT);
       }
        if(code == play_1 ||
         code == play_2 ||
         code == pause_1 ||
         code == pause_2){
         Keyboard.set_key1(KEY_SPACE);
       }
       if(code == skip_left_1 || code == skip_left_2){
         Keyboard.set_key1(KEY_QUOTE);
       }
       if(code == ok_1 || code == ok_2){
         Keyboard.set_key1(KEY_ENTER);
       }
       if(code == stop_1 || code == stop_2){
         Keyboard.set_key1(KEY_X);
       }
       if(code == ff_1 || code == ff_2){
         Keyboard.set_key1(KEY_F);
       }
       if(code == rw_1 || code == rw_2){
         Keyboard.set_key1(KEY_R);
       }
       if(code == info_1 || code == info_2){
         Keyboard.set_key1(KEY_I);
       }
       if(code == display_1 || code == display_2){
         Keyboard.set_key1(KEY_TAB);
       }
       if(code == x_1 || code == x_2){
         Keyboard.set_key1(KEY_W);
       }
       if(code == back_1 || code == back_2){
         Keyboard.set_key1(KEY_ESC);
       }
       if(code == dvd_menu_1 || code == dvd_menu_2){
         Keyboard.set_key1(KEY_S);
       }
       if(code == b_1 || code == b_2){
         Keyboard.set_key1(KEY_BACKSPACE);
       }
       if(code == y_1 || code == y_2){
         Keyboard.set_modifier(MODIFIERKEY_CTRL | MODIFIERKEY_ALT);
         Keyboard.set_key1(KEY_X);
       }
       if(code == a_1 || code == a_2){
         Keyboard.set_key1(KEY_C);
       }
}
void press_key(long code){
  set_keys(code);
  Keyboard.send_now();
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
}

void hold_key(long code){
  hold_flag=1;
  set_keys(code);
  Keyboard.send_now();
}

void unhold_key(){
  hold_flag=0;
  Keyboard.set_modifier(0);
  Keyboard.set_key1(0);
  Keyboard.send_now();
} 

