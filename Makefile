PIO = uv run pio
VENV = .venv/bin/python
GITHUB = https://github.com/kwaka1208/mp2m5stack

# 仮想環境チェック
$(VENV):
	uv venv .venv
	uv pip install -r requirements.txt

# PlatformIOのインストールとバージョン確認
ready: $(VENV)
	$(PIO) --version

# ビルド
build: $(VENV)
	$(PIO) run

# ビルド + M5Stackへのアップロード
upload: $(VENV)
	$(PIO) run --target upload

# シリアルモニタ起動
monitor: $(VENV)
	$(PIO) device monitor

# webサーバ起動
serve:
	npx serve web

github:
	open $(GITHUB)
