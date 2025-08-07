#include "services/aws_services.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("=== AWS STS GetCallerIdentity Usage Example ===\n");
    
    printf("\nExecuting STS GetCallerIdentity...\n");
    int result = sts_get_caller_identity();
    
    if (result == 0) {
        printf("\n✓ Successfully retrieved authentication information\n");
        printf("The response contains the following information:\n");
        printf("- Account: AWS Account ID\n");
        printf("- Arn: User or Role ARN\n");
        printf("- UserId: User ID\n");
    } else {
        printf("\n✗ Failed to retrieve authentication information\n");
        printf("Please check the following:\n");
        printf("- AWS_ACCESS_KEY_ID is set\n");
        printf("- AWS_SECRET_ACCESS_KEY is set\n");
        printf("- AWS_SESSION_TOKEN is set if required\n");
        printf("- Network connection is working\n");
    }
    
    return result;
}
