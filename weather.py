import requests

API_key = "30495057e77d3ce6879a2de24c1c8c94"
city_name = "Cheongju"
location_url = f"http://api.openweathermap.org/geo/1.0/direct?q={city_name}&limit={5}&appid={API_key}"
response = requests.get(location_url)
location_data = response.json()
lat = location_data[0]['lat']
lon = location_data[0]['lon']
weather_url = f"https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API_key}"
weather_response = requests.get(weather_url)
weather_data = weather_response.json()
main_data = weather_data['weather'][0]['main']