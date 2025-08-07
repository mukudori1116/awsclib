#ifndef AWS_SERVICES_H
#define AWS_SERVICES_H

#include "../../src/aws_client.h"

// STS service functions
int sts_get_caller_identity(void);

// GET method examples (services that support GET requests)
int ec2_describe_regions_get(void);
int ec2_describe_availability_zones_get(void);
int s3_list_buckets_get(void);
int cloudwatch_describe_alarms_get(void);

#endif // AWS_SERVICES_H
