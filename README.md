# mp2m5stack

IoT体験授業 2コマ目（MediaPipe版）のファームウェアプロジェクトです。  
パソコン上の MediaPipe が手ジェスチャーを判定し、その結果を USB（シリアル通信）で受け取って M5Stack Grey (ESP32) 上で表示・音出力します。

### 受け取れるジェスチャー

| MediaPipe の名前 | ジェスチャー |
|-----------------|------------|
| `Closed_Fist` | グー |
| `Open_Palm` | パー |
| `Victory` | チョキ |
| `Pointing_Up` | 人差し指 |
| `Thumb_Up` | いいね |
| `Thumb_Down` | 下向き親指 |
| `ILoveYou` | ILY |

## 環境構築

### 前提条件

- [uv](https://docs.astral.sh/uv/) がインストールされていること

### 手順

#### 1. 仮想環境を作成する

```bash
uv venv .venv
```

#### 2. PlatformIO をインストールする

```bash
uv pip install platformio
```

#### 3. 動作確認（ビルド）

```bash
uv run pio run
```

初回実行時は ESP32 のプラットフォームやライブラリを自動ダウンロードするため、数分かかります。

## 主なコマンド

| 操作 | コマンド |
|------|---------|
| ビルド | `uv run pio run` |
| 書き込み | `uv run pio run -t upload` |
| シリアルモニタ | `uv run pio device monitor` |
| ビルド＋書き込み | `uv run pio run -t upload && uv run pio device monitor` |
| ライブラリ更新 | `uv run pio lib update` |

## プロジェクト構成

```
mp2m5stack/
├── platformio.ini   # PlatformIO 設定（M5Stack Grey / ESP32）
├── src/             # ソースコード
└── README.md
```
