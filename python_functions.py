import requests

# Base URL for your ESP8266 server
base_url = "http://192.168.1.5"  # Replace with the actual IP address of your ESP8266

# Define the URLs for the fan and light controls
fan_l1_url = f"{base_url}/fan_l1"
fan_l2_url = f"{base_url}/fan_l2"
fan_l3_url = f"{base_url}/fan_l3"
fan_reset_url = f"{base_url}/fan_reset"

light_l1_url = f"{base_url}/led_l1"
light_l2_url = f"{base_url}/led_l2"
light_reset_url = f"{base_url}/light_reset"

def fan_l1():
    response = requests.get(fan_l1_url)
    print("Fan Level 1 Response:", response.text)

def fan_l2():

    response = requests.get(fan_l2_url)
    print("Fan Level 2 Response:", response.text)

def fan_l3():
    response = requests.get(fan_l3_url)
    print("Fan Level 3 Response:", response.text)

def fan_reset():
    response = requests.get(fan_reset_url)
    print("Fan Reset Response:", response.text)

def light_l1():
    response = requests.get(light_l1_url)
    print("Light Level 1 Response:", response.text)

def light_l2():
    response = requests.get(light_l2_url)
    print("Light Level 2 Response:", response.text)

def light_reset():
    response = requests.get(light_reset_url)
    print("Light Reset Response:", response.text)

