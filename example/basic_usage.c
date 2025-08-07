#include "services/aws_services.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("=== AWS STS GetCallerIdentity Basic Usage Example ===\n");
    
    printf("\nExecuting STS GetCallerIdentity...\n");
    int result = sts_get_caller_identity();
    
    if (result == 0) {
        printf("\n✓ GetCallerIdentity executed successfully\n");
    } else {
        printf("\n✗ GetCallerIdentity execution failed\n");
    }
    
    return result;
}
