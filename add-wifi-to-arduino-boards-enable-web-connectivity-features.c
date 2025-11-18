// Include IO and timing to simulate WiFi connection and web interactions
#include <stdio.h> // Print network status and HTTP logs
#include <unistd.h> // Sleep between operations
#include <string.h> // Basic string handling

// Track WiFi and simple request counters
static int wifi_connected = 0; // WiFi connection flag (0=disconnected,1=connected)
static int request_count = 0; // Number of HTTP requests issued

// Attempt to connect to a WiFi network using SSID and password
int wifi_connect(const char *ssid, const char *pass) { // Connect function
  if (!ssid || !pass) { // Validate inputs
    printf("WiFi connect error: missing SSID or password\n"); // Error log
    return 0; // Fail
  } // End validation
  printf("Connecting to WiFi SSID='%s'...\n", ssid); // Log SSID
  usleep(300000); // Simulate connection time (300ms)
  wifi_connected = 1; // Mark connected (simulation)
  printf("WiFi connected\n"); // Log success
  return 1; // Success
} // End wifi_connect

// Perform an HTTP GET request when connected
int http_get(const char *url) { // HTTP GET simulation
  if (!wifi_connected) { // Ensure connection
    printf("WiFi not connected\n"); // Error
    return 0; // Abort
  } // End check
  if (!url || strlen(url) == 0) { // Validate URL
    printf("Invalid URL\n"); // Error
    return 0; // Abort
  } // End validation
  request_count++; // Increment request counter
  printf("HTTP GET %s (req=%d)\n", url, request_count); // Log request
  usleep(200000); // Simulate network latency (200ms)
  printf("HTTP 200 OK\n"); // Simulated response
  return 1; // Success
} // End http_get

// Perform an HTTP POST request with JSON payload
int http_post_json(const char *url, const char *json) { // HTTP POST simulation
  if (!wifi_connected) { // Ensure connection
    printf("WiFi not connected\n"); // Error
    return 0; // Abort
  } // End check
  if (!url || !json) { // Validate
    printf("Invalid POST parameters\n"); // Error
    return 0; // Abort
  } // End validation
  request_count++; // Increment counter
  printf("HTTP POST %s body=%s (req=%d)\n", url, json, request_count); // Log POST
  usleep(250000); // Simulate latency (250ms)
  printf("HTTP 201 Created\n"); // Simulated success
  return 1; // Success
} // End http_post_json

int main(void) { // Entry point
  printf("Add WiFi to Arduino Boards: Enable Web Connectivity Features\n"); // Title
  wifi_connect("MyNetwork", "MyPassword"); // Connect to network
  http_get("http://example.com/api/status"); // GET request
  http_post_json("http://example.com/api/sensor", "{\"temp\":26,\"hum\":55}"); // POST JSON
  http_get("http://example.com/api/config"); // Another GET
  usleep(200000); // Small delay before exit
  return 0; // Exit
} // End main

