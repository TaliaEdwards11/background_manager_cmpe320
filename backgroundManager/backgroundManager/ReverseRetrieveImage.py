import requests, json, sys, os.path
from PIL import Image, ImageFile
from io import BytesIO

ImageFile.LOAD_TRUNCATED_IMAGES = True

subscription_key = "ad64677e0df94b2b8aee94959ba6dce1"
reverse_search_url = 'https://api.bing.microsoft.com/v7.0/images/visualsearch'


def retrieveReverseImage(reserve_search_url, headers, image_path):
    original_image = Image.open(image_path)
    original_image_path = splitPath(image_path, "original")
    original_image.save(original_image_path)
    original_image.close()
    while os.path.getsize(image_path) > 1024 * 1024:
        image = Image.open(image_path)
        image = image.resize((int(image.size[0] / 1.5), int(image.size[1] / 1.5)), Image.ANTIALIAS)
        image.save(image_path, optimize=True, quality=95)
        image.close()
    file = {'image': ('myfile', open(image_path, 'rb'))}
    try:
        response = requests.post(reverse_search_url, headers=headers, files=file)
        file["image"][1].close()
        os.remove(image_path)
        image2 = Image.open(original_image_path)
        image2.save(image_path)
        image2.close()
        os.remove(original_image_path)
        response.raise_for_status()
        image_results = response.json()
        image_urls = [img["contentUrl"] for img in image_results['tags'][0]["actions"][2]["data"]["value"][:3]]
        for i, img in enumerate(image_urls):
            image_data = requests.get(img)
            image_data.raise_for_status()
            retrieved_image = Image.open(BytesIO(image_data.content))
            image_name = findImageName(image_path)

            save_image_path = "..\\BG_Manager\\images\\" + str(i) + "reverse" + image_name
            retrieved_image.save(save_image_path)
    except Exception as ex:
        raise ex

def splitPath(path, modifier):
    split_path = path.split('.')
    new_image_path = ''.join(split_path[:-1]) + modifier + '.' + split_path[-1]
    return new_image_path

def findImageName(path):
    return path.split('\\')[-1]


if len(sys.argv) != 2:
    sys.exit("Not enough args")

image_path = sys.argv[1]

headers = {"Ocp-Apim-Subscription-Key": subscription_key}

retrieveReverseImage(reverse_search_url, headers, image_path)


