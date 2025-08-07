#include "aws_client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Callback function to receive response data
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, struct APIResponse *response) {
    size_t realsize = size * nmemb;
    char *ptr = realloc(response->data, response->size + realsize + 1);
    
    if (ptr == NULL) {
        printf("Memory allocation failed in realloc\n");
        return 0;
    }
    
    response->data = ptr;
    memcpy(&(response->data[response->size]), contents, realsize);
    response->size += realsize;
    response->data[response->size] = 0;
    
    return realsize;
}

// Get AWS credentials from environment variables
struct AWSCredentials* get_aws_credentials() {
    struct AWSCredentials *creds = malloc(sizeof(struct AWSCredentials));
    if (!creds) return NULL;
    
    const char *access_key = getenv("AWS_ACCESS_KEY_ID");
    const char *secret_key = getenv("AWS_SECRET_ACCESS_KEY");
    const char *session_token = getenv("AWS_SESSION_TOKEN");
    
    if (!access_key || !secret_key) {
        free(creds);
        return NULL;
    }
    
    creds->access_key = strdup(access_key);
    creds->secret_key = strdup(secret_key);
    creds->session_token = session_token ? strdup(session_token) : NULL;
    
    return creds;
}

// Free AWS credentials memory
void free_aws_credentials(struct AWSCredentials *creds) {
    if (creds) {
        free(creds->access_key);
        free(creds->secret_key);
        free(creds->session_token);
        free(creds);
    }
}

// Setup HTTP headers
struct curl_slist* setup_headers(const struct AWSCredentials *creds, HTTPMethod method) {
    struct curl_slist *headers = NULL;
    
    // Set Content-Type only for POST requests
    if (method == HTTP_POST) {
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
    }
    headers = curl_slist_append(headers, "Accept-Encoding: identity");
    
    // Add session token to headers if available
    if (creds->session_token) {
        char token_header[1024];
        snprintf(token_header, sizeof(token_header), "X-Amz-Security-Token: %s", creds->session_token);
        headers = curl_slist_append(headers, token_header);
    }
    
    return headers;
}

// Execute AWS API request
int execute_aws_request(const struct AWSRequest *request, struct APIResponse *response) {
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize curl\n");
        return 1;
    }
    
    // Get AWS credentials
    struct AWSCredentials *creds = get_aws_credentials();
    if (!creds) {
        fprintf(stderr, "AWS credentials not set. Please set AWS_ACCESS_KEY_ID and AWS_SECRET_ACCESS_KEY.\n");
        curl_easy_cleanup(curl);
        return 1;
    }
    
    printf("Using access key: %s\n", creds->access_key);
    if (creds->session_token) {
        printf("Session token is configured\n");
    }
    
    // Combine credentials (ACCESS_KEY:SECRET_KEY format)
    char credentials[512];
    snprintf(credentials, sizeof(credentials), "%s:%s", creds->access_key, creds->secret_key);
    
    // Set endpoint URL and configure HTTP method
    if (request->method == HTTP_GET) {
        // For GET requests, append query parameters to URL
        char full_url[2048];
        if (request->post_data && strlen(request->post_data) > 0) {
            snprintf(full_url, sizeof(full_url), "%s?%s", request->endpoint, request->post_data);
        } else {
            snprintf(full_url, sizeof(full_url), "%s", request->endpoint);
        }
        curl_easy_setopt(curl, CURLOPT_URL, full_url);
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    } else {
        // For POST requests, use original behavior
        curl_easy_setopt(curl, CURLOPT_URL, request->endpoint);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request->post_data);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(request->post_data));
    }
    
    // Set HTTP headers
    struct curl_slist *headers = setup_headers(creds, request->method);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    
    // Set AWS Signature Version 4 authentication
    char sigv4_string[256];
    snprintf(sigv4_string, sizeof(sigv4_string), "aws:amz:%s:%s", request->region, request->service);
    curl_easy_setopt(curl, CURLOPT_AWS_SIGV4, sigv4_string);
    
    // Set credentials
    curl_easy_setopt(curl, CURLOPT_USERPWD, credentials);
    
    // Set response processing
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    
    // Enable debug information
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    
    printf("Executing AWS %s %s (%s)...\n", request->service, request->action, 
           request->method == HTTP_GET ? "GET" : "POST");
    
    // Execute request
    CURLcode res = curl_easy_perform(curl);
    
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        
        printf("\n=== Response ===\n");
        printf("HTTP Status Code: %ld\n", response_code);
        printf("Response Body:\n%s\n", response->data ? response->data : "No response");
    }
    
    // Cleanup
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    free_aws_credentials(creds);
    
    return (res == CURLE_OK) ? 0 : 1;
}

// Main function (for testing)
#ifndef LIB_MODE
int main(void) {
    printf("=== AWS API Core Library ===\n");
    printf("This library should be used from other programs.\n");
    printf("To run examples: make run-basic\n");
    return 0;
}
#endif
