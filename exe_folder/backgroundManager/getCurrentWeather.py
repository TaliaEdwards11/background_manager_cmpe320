import requests
from lxml import html

subscription_key = "ad64677e0df94b2b8aee94959ba6dce1"
search_url = "https://api.bing.microsoft.com/v7.0/search"

headers = {"Ocp-Apim-Subscription-Key" : subscription_key}

search_term = "site:weather.gc.ca/city weather"

params = {"q": search_term, "answerCount": 1, "count": 1}

response = requests.get(search_url, headers=headers, params=params)
response.raise_for_status()
new_url = response.json()["webPages"]["value"][0]["url"]

website_response = requests.get("https://weather.gc.ca/city/pages/on-69_metric_e.html")
website_response.raise_for_status()
tree = html.fromstring(website_response.content)

currentWeather = tree.xpath('//dd[@class="mrgn-bttm-0"]/text()')[2]

plusWeather = currentWeather.replace(' ', '+')


with open('..\\BG_Manager\\weather.txt', 'w') as f:
    f.write(plusWeather)