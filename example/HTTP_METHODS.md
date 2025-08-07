# AWS API HTTP Methods Support

This document explains which AWS services support GET vs POST methods.

## POST-Only Services

These services only support POST method:

### STS (Security Token Service)
- GetCallerIdentity
- AssumeRole
- GetSessionToken
- All STS operations require POST

### IAM (Identity and Access Management)
- ListUsers
- ListRoles
- GetUser
- All IAM operations require POST

### Lambda
- ListFunctions
- InvokeFunction
- All Lambda operations require POST

## GET-Supported Services

These services support GET method for read operations:

### EC2 (Elastic Compute Cloud)
- DescribeRegions ✓
- DescribeAvailabilityZones ✓
- DescribeInstances ✓
- DescribeImages ✓
- Most Describe* operations support GET

### S3 (Simple Storage Service)
- ListBuckets ✓ (REST API style)
- GetObject ✓
- HeadObject ✓
- S3 REST API primarily uses GET for read operations

### CloudWatch
- DescribeAlarms ✓
- GetMetricStatistics ✓
- ListMetrics ✓
- Most read operations support GET

### Route53
- ListHostedZones ✓
- GetHostedZone ✓
- ListResourceRecordSets ✓

## Method Selection Guidelines

### Use POST when:
- Service only supports POST (STS, IAM, Lambda)
- Performing write operations
- Sending large amounts of data
- Security requirements prefer POST

### Use GET when:
- Service supports GET for the operation
- Performing read-only operations
- Want better caching behavior
- Easier debugging (parameters visible in URL)
- Following RESTful design principles

## Implementation Notes

In this library:
- Set `method = HTTP_POST` for POST requests
- Set `method = HTTP_GET` for GET requests
- For GET requests, `post_data` becomes query parameters in the URL
- For POST requests, `post_data` is sent in the request body

## Examples

```c
// POST request (required for STS)
struct AWSRequest post_request = {
    .service = "sts",
    .region = "us-east-1",
    .endpoint = "https://sts.amazonaws.com/",
    .action = "GetCallerIdentity",
    .version = "2011-06-15",
    .post_data = "Action=GetCallerIdentity&Version=2011-06-15",
    .method = HTTP_POST
};

// GET request (supported by EC2)
struct AWSRequest get_request = {
    .service = "ec2",
    .region = "us-east-1",
    .endpoint = "https://ec2.us-east-1.amazonaws.com/",
    .action = "DescribeRegions",
    .version = "2016-11-15",
    .post_data = "Action=DescribeRegions&Version=2016-11-15",
    .method = HTTP_GET
};
```

## Testing Method Support

To test if a service supports GET method:
1. Try the GET request
2. If you get a 405 Method Not Allowed error, use POST
3. If you get a 400 Bad Request or 403 Forbidden, check your parameters
4. If you get a 200 OK, the service supports GET for that operation
