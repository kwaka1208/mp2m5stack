"""
MediaPipe Model Maker を使ったカスタムジェスチャー認識モデルの学習スクリプト

【事前準備】
  pip install mediapipe-model-maker

【フォルダ構成】
  dataset/
    gesture_A/        ← 任意のジェスチャー名（M5Stack に送られる文字列になる）
      001.jpg
      002.jpg
      ...（最低 20 枚以上推奨）
    gesture_B/
      001.jpg
      ...
    none/             ← 手なし・判定したくないポーズの画像（必須ではないが推奨）
      001.jpg
      ...

【実行】
  python mediapipe.py

【出力】
  exported_model/gesture_recognizer.task
  → このファイルを index.html の「カスタムモデル」で読み込む
"""

import os
from mediapipe_model_maker import gesture_recognizer

DATASET_DIR = "dataset"
EXPORT_DIR  = "exported_model"


def main():
    print("=== データセット読み込み ===")
    data = gesture_recognizer.Dataset.from_folder(dirname=DATASET_DIR)
    print(f"  総サンプル数: {len(data)}")

    train_data, rest_data       = data.split(0.8)
    validation_data, test_data  = rest_data.split(0.5)
    print(f"  学習: {len(train_data)}  検証: {len(validation_data)}  テスト: {len(test_data)}")

    print("\n=== 学習開始 ===")
    options = gesture_recognizer.GestureRecognizerOptions(
        model_options=gesture_recognizer.ModelOptions(
            dropout_rate=0.05,
            layer_widths=[],
        ),
        hparams=gesture_recognizer.HParams(
            learning_rate=0.001,
            batch_size=2,
            epochs=10,
            export_dir=EXPORT_DIR,
        ),
    )
    model = gesture_recognizer.GestureRecognizer.create(
        train_data=train_data,
        validation_data=validation_data,
        options=options,
    )

    print("\n=== テストデータで評価 ===")
    loss, acc = model.evaluate(test_data, batch_size=1)
    print(f"  Loss: {loss:.4f}  Accuracy: {acc:.4f}")

    print("\n=== モデルをエクスポート ===")
    model.export_model()
    task_path = os.path.join(EXPORT_DIR, "gesture_recognizer.task")
    print(f"  保存先: {task_path}")
    print("\n完了！index.html の「カスタムモデル」欄でこのファイルを選択してください。")


if __name__ == "__main__":
    main()
