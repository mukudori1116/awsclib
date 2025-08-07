#include "../../src/aws_client.h"
#include <stdio.h>
#include <stdlib.h>

// Execute STS GetCallerIdentity
int sts_get_caller_identity() {
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
        free(response.data);
    }
    
    return result;
}
