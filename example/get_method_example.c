#include "services/aws_services.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    printf("=== AWS API GET Method Examples ===\n");
    printf("Note: Not all AWS APIs support GET method. Here are examples that do:\n\n");
    
    printf("1. STS GetCallerIdentity (POST method - STS only supports POST):\n");
    int sts_result = sts_get_caller_identity();
    
    printf("\n2. EC2 DescribeRegions (GET method):\n");
    int ec2_regions_result = ec2_describe_regions_get();
    
    printf("\n3. EC2 DescribeAvailabilityZones (GET method):\n");
    int ec2_az_result = ec2_describe_availability_zones_get();
    
    printf("\n4. S3 ListBuckets (GET method - REST API style):\n");
    int s3_result = s3_list_buckets_get();
    
    printf("\n5. CloudWatch DescribeAlarms (GET method):\n");
    int cw_result = cloudwatch_describe_alarms_get();
    
    printf("\n=== AWS API Method Support ===\n");
    printf("POST-only services:\n");
    printf("  - STS (Security Token Service)\n");
    printf("  - IAM (Identity and Access Management)\n");
    printf("  - Most write operations\n\n");
    
    printf("GET-supported services:\n");
    printf("  - EC2 (for read operations like Describe*)\n");
    printf("  - S3 (REST API style)\n");
    printf("  - CloudWatch (for read operations)\n");
    printf("  - Route53 (for read operations)\n\n");
    
    printf("=== When to Use Each Method ===\n");
    printf("POST: Required for STS, IAM, and most write operations\n");
    printf("GET:  Preferred for read operations when supported\n");
    printf("      - Better for caching\n");
    printf("      - Easier to debug (visible in URL)\n");
    printf("      - RESTful design\n");
    
    // Return success if at least some requests succeeded
    int success_count = (sts_result == 0 ? 1 : 0) + 
                       (ec2_regions_result == 0 ? 1 : 0) + 
                       (s3_result == 0 ? 1 : 0);
    
    printf("\n=== Results ===\n");
    printf("Successful requests: %d/5\n", success_count + 
           (ec2_az_result == 0 ? 1 : 0) + (cw_result == 0 ? 1 : 0));
    
    return success_count > 0 ? 0 : 1;
}
