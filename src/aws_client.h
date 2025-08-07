#ifndef AWS_CLIENT_H
#define AWS_CLIENT_H

#include <curl/curl.h>

// Structure to store response data
struct APIResponse {
    char *data;
    size_t size;
};

// Structure to store AWS credentials
struct AWSCredentials {
    char *access_key;
    char *secret_key;
    char *session_token;
};

// HTTP method enumeration
typedef enum {
    HTTP_GET,
    HTTP_POST
} HTTPMethod;

// Structure to store AWS request parameters
struct AWSRequest {
    const char *service;
    const char *region;
    const char *endpoint;
    const char *action;
    const char *version;
    const char *post_data;
    HTTPMethod method;  // HTTP method (GET or POST)
};

// Function prototypes
struct AWSCredentials* get_aws_credentials(void);
void free_aws_credentials(struct AWSCredentials *creds);
struct curl_slist* setup_headers(const struct AWSCredentials *creds, HTTPMethod method);
int execute_aws_request(const struct AWSRequest *request, struct APIResponse *response);

// Core library functions only
// For service-specific functions, refer to implementations in example/services/

#endif // AWS_CLIENT_H
