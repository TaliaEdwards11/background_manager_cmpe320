import requests, sys
from PIL import Image
from io import BytesIO

def retrieveImage(searchUrl, headers, params):
	response = requests.get(search_url, headers=headers, params=params)
	response.raise_for_status()
	search_results = response.json()
	image_urls= [img["contentUrl"] for img in search_results["value"]]
	for i, img in enumerate(image_urls):
                image_data = requests.get(img)
                image_data.raise_for_status()
                retrieved_image = Image.open(BytesIO(image_data.content))
                retrieved_image.save("..\\BG_Manager\\images\\"  + str(i) + params["q"].replace('+', '') + ".jpg")


subscription_key = "ad64677e0df94b2b8aee94959ba6dce1"
search_url = "https://api.bing.microsoft.com/v7.0/images/search"

if len(sys.argv) != 2:
	sys.exit("Not enough args")

search_term = sys.argv[1]

headers = {"Ocp-Apim-Subscription-Key" : subscription_key}

params  = {"q": search_term, "imageType": "photo", "count": 3, "safeSearch": "strict", "aspect" : "Wide"}

retrieveImage(search_url, headers, params)
