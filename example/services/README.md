# AWS STS Service Implementation Example

このディレクトリには、AWS Client Libraryを使用したSTS GetCallerIdentityの実装例が含まれています。

## ファイル構成

- `aws_services.h` - STS関数のプロトタイプ
- `aws_sts.c` - AWS STS (Security Token Service) GetCallerIdentity実装

## 実装されている機能

### STS (Security Token Service)
- `sts_get_caller_identity()` - 現在の認証情報を取得

## 使用方法

### 1. ヘッダーファイルをインクルード

```c
#include "services/aws_services.h"
```

### 2. 関数を呼び出し

```c
int main() {
    // STS GetCallerIdentity実行
    int result = sts_get_caller_identity();
    
    if (result == 0) {
        // 成功時の処理
        printf("認証情報の取得に成功しました\n");
    }
    
    return result;
}
```

## 新しいサービスの追加

この実装例を参考に、他のAWSサービスも同様に実装できます：

```c
// 例：EC2 DescribeInstances
int ec2_describe_instances() {
    struct AWSRequest request = {
        .service = "ec2",
        .region = "us-east-1",
        .endpoint = "https://ec2.us-east-1.amazonaws.com/",
        .action = "DescribeInstances",
        .version = "2016-11-15",
        .post_data = "Action=DescribeInstances&Version=2016-11-15"
    };
    
    struct APIResponse response = {0};
    int result = execute_aws_request(&request, &response);
    
    if (response.data) {
        free(response.data);
    }
    
    return result;
}
```

## 注意事項

- この実装は使用例であり、本番環境での使用前に十分なテストが必要です
- STS:GetCallerIdentityに対する適切なIAM権限が必要です
- エラーハンドリングやレスポンス解析は必要に応じて拡張してください
