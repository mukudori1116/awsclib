# AWS Client Library Examples

このディレクトリには、AWS Client Libraryの使用例が含まれています。

## サンプルファイル

### 1. basic_usage.c
The simplest usage example. Executes STS GetCallerIdentity.

```bash
make basic
./basic_usage
```

### 2. all_services.c
Detailed STS GetCallerIdentity usage example.

```bash
make sts-example
./sts_example
```

### 3. custom_request.c
Shows how to create custom requests using the core library directly.

```bash
make custom
./custom_request
```

### 4. get_method_example.c
Examples of AWS APIs that support GET method.

```bash
make get-example
./get_method_example
```

## ビルドと実行

```bash
# Build all examples
make examples

# Build individually
make basic
make sts-example
make custom
make get-example

# Run
./basic_usage
./sts_example
./custom_request
./get_method_example
```

## Adding New Services Example

```c
#include "../src/aws_client.h"

int your_custom_service() {
    struct AWSRequest request = {
        .service = "your-service",
        .region = "us-east-1",
        .endpoint = "https://your-service.us-east-1.amazonaws.com/",
        .action = "YourAction",
        .version = "2023-01-01",
        .post_data = "Action=YourAction&Version=2023-01-01&Param1=Value1",
        .method = HTTP_POST  // or HTTP_GET if supported
    };
    
    struct APIResponse response = {0};
    int result = execute_aws_request(&request, &response);
    
    if (response.data) {
        printf("Response: %s\n", response.data);
        free(response.data);
    }
    
    return result;
}
```

## Notes

- AWS credentials (AWS_ACCESS_KEY_ID, AWS_SECRET_ACCESS_KEY) must be set
- Set AWS_SESSION_TOKEN if using temporary credentials
- Appropriate IAM permissions are required for each service
- Check `HTTP_METHODS.md` for service-specific HTTP method support
