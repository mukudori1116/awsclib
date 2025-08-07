#include "../src/aws_client.h"
#include <stdio.h>
#include <stdlib.h>

// Custom request example using core library directly
int custom_sts_get_caller_identity() {
    printf("Executing STS GetCallerIdentity using core library directly\n");
    
    struct AWSRequest request = {
        .service = "sts",
        .region = "us-east-1",
        .endpoint = "https://sts.amazonaws.com/",
        .action = "GetCallerIdentity",
        .version = "2011-06-15",
        .post_data = "Action=GetCallerIdentity&Version=2011-06-15",
        .method = HTTP_POST
    };
    
    struct APIResponse response = {0};
    int result = execute_aws_request(&request, &response);
    
    if (response.data) {
        printf("Response data:\n%s\n", response.data);
        free(response.data);
    }
    
    return result;
}

int main(void) {
    printf("=== AWS API Custom Request Example ===\n");
    printf("This example uses the core library directly without service implementations\n\n");
    
    int result = custom_sts_get_caller_identity();
    
    // Example of GET request (using EC2 DescribeRegions which supports GET)
    printf("\n=== GET Request Example ===\n");
    printf("Executing EC2 DescribeRegions using GET method\n");
    
    struct AWSRequest get_request = {
        .service = "ec2",
        .region = "us-east-1",
        .endpoint = "https://ec2.us-east-1.amazonaws.com/",
        .action = "DescribeRegions",
        .version = "2016-11-15",
        .post_data = "Action=DescribeRegions&Version=2016-11-15",
        .method = HTTP_GET
    };
    
    struct APIResponse get_response = {0};
    int get_result = execute_aws_request(&get_request, &get_response);
    
    if (get_response.data) {
        printf("GET Response data:\n%s\n", get_response.data);
        free(get_response.data);
    }
    
    printf("\n=== How to Create Custom Requests ===\n");
    printf("1. Create struct AWSRequest\n");
    printf("2. Set service, region, endpoint, action, version, post_data\n");
    printf("3. Set method (HTTP_GET or HTTP_POST)\n");
    printf("4. Call execute_aws_request()\n");
    printf("5. Process response data\n");
    printf("6. Free memory\n");
    
    printf("\n=== HTTP Method Usage ===\n");
    printf("POST: Data sent in request body (required for STS, IAM, write operations)\n");
    printf("GET:  Data sent as query parameters in URL (supported by EC2, S3, CloudWatch for reads)\n");
    printf("\nNote: Not all AWS services support GET method. Check AWS documentation for each service.\n");
    
    return result;
}
