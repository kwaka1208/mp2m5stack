#include <M5Stack.h>

#define MODE_DEFAULT 0
#define MODE_PATTERN 1

// パターン定義: ここを編集して自由に変更できます
// PATTERN: MediaPipe のジェスチャー名（送られてくる文字列）
// PATTERN_LABEL: 画面に表示する短いラベル
const String PATTERN[]       = {"Closed_Fist", "Victory", "Open_Palm"};
const String PATTERN_LABEL[] = {"G", "C", "P"};
const int    PATTERN_LEN     = sizeof(PATTERN) / sizeof(PATTERN[0]);

int currentMode = MODE_DEFAULT;
int patternStep = 0;
String gesture  = "";

void showModeLabel();
void drawButtons();
void showResult(String g);
void showPatternProgress();
void showPatternMode(String g);

void setup() {
  M5.begin();
  M5.Power.begin();
  Serial.begin(115200);
  M5.Lcd.fillScreen(BLACK);
  showModeLabel();
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(30, 110);
  M5.Lcd.print("Ready...");
  drawButtons();
}

void loop() {
  M5.update();

  // ボタンA: デフォルトモードへ
  if (M5.BtnA.wasPressed()) {
    currentMode = MODE_DEFAULT;
    patternStep = 0;
    M5.Lcd.fillScreen(BLACK);
    showModeLabel();
    M5.Lcd.setTextSize(3);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(30, 110);
    M5.Lcd.print("Ready...");
    drawButtons();
  }

  // ボタンB: パターンモードへ
  if (M5.BtnB.wasPressed()) {
    currentMode = MODE_PATTERN;
    patternStep = 0;
    M5.Lcd.fillScreen(BLACK);
    showModeLabel();
    showPatternProgress();
    drawButtons();
  }

  if (Serial.available()) {
    gesture = Serial.readStringUntil('\n');
    gesture.trim();
    if (currentMode == MODE_DEFAULT) {
      showResult(gesture);
    } else {
      showPatternMode(gesture);
    }
  }

  delay(50);
}

void showModeLabel() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(YELLOW, BLACK);
  M5.Lcd.setCursor(0, 0);
  if (currentMode == MODE_DEFAULT) {
    M5.Lcd.print(" [A] Janken          ");
  } else {
    M5.Lcd.print(" [B] Action          ");
  }
}

void drawButtons() {
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(CYAN, BLACK);
  M5.Lcd.setCursor(10, 225);
  M5.Lcd.print(" [A] Janken       [B] Action        ");
  M5.Lcd.setTextColor(WHITE, BLACK);
}

// パターン進行状況を中段に表示
void showPatternProgress() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(10, 80);
  M5.Lcd.print("Pattern:            ");
  M5.Lcd.setCursor(10, 115);
  for (int i = 0; i < PATTERN_LEN; i++) {
    if (i < patternStep) {
      M5.Lcd.setTextColor(GREEN, BLACK);
      M5.Lcd.print(PATTERN_LABEL[i]);
    } else if (i == patternStep) {
      M5.Lcd.setTextColor(YELLOW, BLACK);
      M5.Lcd.print("?");
    } else {
      M5.Lcd.setTextColor(DARKGREY, BLACK);
      M5.Lcd.print("?");
    }
    if (i < PATTERN_LEN - 1) {
      M5.Lcd.setTextColor(WHITE, BLACK);
      M5.Lcd.print(">");
    }
  }
  M5.Lcd.print("          ");
}

void showPatternMode(String g) {
  if (g == PATTERN[patternStep]) {
    patternStep++;
    if (patternStep == PATTERN_LEN) {
      // パターン完成
      M5.Lcd.fillScreen(BLACK);
      showModeLabel();
      M5.Lcd.setTextSize(3);
      M5.Lcd.setTextColor(GREEN, BLACK);
      M5.Lcd.setCursor(40, 95);
      M5.Lcd.print("PERFECT!");
      M5.Speaker.tone(523, 100);
      delay(120);
      M5.Speaker.tone(659, 100);
      delay(120);
      M5.Speaker.tone(784, 100);
      delay(120);
      M5.Speaker.tone(1047, 300);
      delay(700);
      patternStep = 0;
      M5.Lcd.fillScreen(BLACK);
      showModeLabel();
      showPatternProgress();
      drawButtons();
    } else {
      showPatternProgress();
    }
  } else {
    // ミス: リセット
    patternStep = 0;
    M5.Lcd.fillScreen(BLACK);
    showModeLabel();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.setCursor(30, 105);
    M5.Lcd.print("MISS! Reset");
    M5.Speaker.tone(200, 300);
    delay(800);
    M5.Lcd.fillScreen(BLACK);
    showModeLabel();
    showPatternProgress();
    drawButtons();
  }
}

void showResult(String g) {
  M5.Lcd.fillScreen(BLACK);
  showModeLabel();
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(20, 110);

  if (g == "Closed_Fist") {
    M5.Lcd.print("GU!");
    M5.Speaker.tone(523, 150);
  } else if (g == "Open_Palm") {
    M5.Lcd.print("PA!");
    M5.Speaker.tone(659, 150);
  } else if (g == "Victory") {
    M5.Lcd.print("CHOKI!");
    M5.Speaker.tone(784, 150);
  } else if (g == "Thumb_Up") {
    M5.Lcd.print("GOOD!");
    M5.Speaker.tone(880, 150);
  } else {
    M5.Lcd.print(g);
  }
  drawButtons();
}
