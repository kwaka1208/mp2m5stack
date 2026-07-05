#include <M5Stack.h>

void showResult(String g);

String gesture = "";

void setup() {
  M5.begin();
  M5.Power.begin();
  Serial.begin(115200);
  M5.Lcd.setTextSize(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(30, 110);
  M5.Lcd.print("Ready...");        // ★ 待っている間の言葉
}

void loop() {
  // ====== ここは完成ずみ・さわらない（USBで1行うけとる） ======
  if (Serial.available()) {
    gesture = Serial.readStringUntil('\n');
    gesture.trim();
    showResult(gesture);
  }
  // ==========================================================

  M5.update();
  delay(50);
}

void showResult(String g) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(20, 110);

  // ★ 名前は MediaPipe が送ってくるものに合わせてある（変えなくても動く）
  if (g == "Closed_Fist") {
    M5.Lcd.print("GU!");             // ★ 表示を自由に
    M5.Speaker.tone(523, 150);       // ★
  } else if (g == "Open_Palm") {
    M5.Lcd.print("PA!");             // ★
    M5.Speaker.tone(659, 150);       // ★
  } else if (g == "Victory") {
    M5.Lcd.print("CHOKI!");          // ★
    M5.Speaker.tone(784, 150);       // ★
  } else if (g == "Thumb_Up") {
    M5.Lcd.print("GOOD!");           // ★ いいね
    M5.Speaker.tone(880, 150);       // ★
  } else {
    M5.Lcd.print(g);                 // 知らない名前はそのまま表示
  }
}
