## 必要な環境

- libcurl (AWS Signature Version 4サポート付き)
- gcc
- make

### macOSでの依存関係インストール

```bash
# Homebrewを使用
brew install curl
```

## AWS認証情報の設定

```bash
export AWS_ACCESS_KEY_ID="your-access-key"
export AWS_SECRET_ACCESS_KEY="your-secret-key"
# オプション: セッショントークンがある場合
export AWS_SESSION_TOKEN="your-session-token"
```

