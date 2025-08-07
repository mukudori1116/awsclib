#include "../../src/aws_client.h"
#include <stdio.h>
#include <stdlib.h>

// Example of EC2 DescribeRegions using GET method
// EC2 supports both GET and POST methods
int ec2_describe_regions_get() {
    struct AWSRequest request = {
        .service = "ec2",
        .region = "us-east-1",
        .endpoint = "https://ec2.us-east-1.amazonaws.com/",
        .action = "DescribeRegions",
        .version = "2016-11-15",
        .post_data = "Action=DescribeRegions&Version=2016-11-15",
        .method = HTTP_GET
    };
    
    struct APIResponse response = {0};
    int result = execute_aws_request(&request, &response);
    
    if (response.data) {
        free(response.data);
    }
    
    return result;
}

// Example of EC2 DescribeAvailabilityZones using GET method
int ec2_describe_availability_zones_get() {
    struct AWSRequest request = {
        .service = "ec2",
        .region = "us-east-1",
        .endpoint = "https://ec2.us-east-1.amazonaws.com/",
        .action = "DescribeAvailabilityZones",
        .version = "2016-11-15",
        .post_data = "Action=DescribeAvailabilityZones&Version=2016-11-15",
        .method = HTTP_GET
    };
    
    struct APIResponse response = {0};
    int result = execute_aws_request(&request, &response);
    
    if (response.data) {
        free(response.data);
    }
    
    return result;
}

// Example of S3 ListBuckets using GET method (REST API style)
// S3 REST API uses GET method for ListBuckets
int s3_list_buckets_get() {
    struct AWSRequest request = {
        .service = "s3",
        .region = "us-east-1",
        .endpoint = "https://s3.amazonaws.com/",
        .action = "ListBuckets",
        .version = "",
        .post_data = "",  // No query parameters needed for S3 ListBuckets
        .method = HTTP_GET
    };
    
    struct APIResponse response = {0};
    int result = execute_aws_request(&request, &response);
    
    if (response.data) {
        free(response.data);
    }
    
    return result;
}

// Example of CloudWatch DescribeAlarms using GET method
// CloudWatch supports GET method for read operations
int cloudwatch_describe_alarms_get() {
    struct AWSRequest request = {
        .service = "monitoring",
        .region = "us-east-1",
        .endpoint = "https://monitoring.us-east-1.amazonaws.com/",
        .action = "DescribeAlarms",
        .version = "2010-08-01",
        .post_data = "Action=DescribeAlarms&Version=2010-08-01",
        .method = HTTP_GET
    };
    
    struct APIResponse response = {0};
    int result = execute_aws_request(&request, &response);
    
    if (response.data) {
        free(response.data);
    }
    
    return result;
}
