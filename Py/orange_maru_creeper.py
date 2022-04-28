import requests
import re
import os

simulated_headers = {
        'User-Agent':'Mozilla/5.0(Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.162 Safari/537.36'
    }

html = 'https://nhentai.net/search/?q=touhou&sort=popular?page=1'

exposed_html = requests.get(html, headers=simulated_headers)

suiffix = re.findall('class="gallery".*?a href="(.*?)"', exposed_html.text)

comic_page = 'https://nhentai.net'

comic_num = 0

for i in suiffix:
    comic_num += 1
    sub_html = comic_page + i
    exposed_sub_html = requests.get(sub_html)
    page_num = re.findall('<span class="name">(.*?)</span>', exposed_sub_html.text)[0]
    name = re.findall('<h1>(.*?)</h1>', exposed_sub_html.text)[0].replace('/','／') .replace('\\','＼')

    count = 0
    for a in range(1, int(page_num)+1):
        count += 1
        img_html = sub_html + str(a) + '/'
        exposed_img_html = requests.get(img_html)
        download_link = re.findall('img src="(.*?)"', exposed_img_html.text)[1]
        img = requests.get(download_link)
        dic = '/Users/retrolloyd/Desktop/NH/' + name + '/'
        download_dic = dic + str(count) + '.jpg'
        if not os.path.isdir(dic):
            os.makedirs(dic)
        with open(download_dic, 'wb') as f:
            print('Procsiiing... NO.', str(count))
            f.write(img.content)
            print('Done')
    print('One comic doen\n\n\n')