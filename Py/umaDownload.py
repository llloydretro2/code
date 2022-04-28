import requests
import re
import os

headHtml = 'https://www.manhuagui.com/comic/39501/'

headText = requests.get(headHtml).text
linkSuffix = re.findall('<a href="/comic/39501/(.*?).html', headText)[1:]
fullLinks = []
for i in linkSuffix:
    fullLinks.append('https://www.manhuagui.com/comic/39501/' + i + '.html')

for pageLink in fullLinks:
    pageText = requests.get(pageLink).text
    print(pageText)
    pageNum = re.findall('\(<span id="page"></span>/(.*?)\)<', pageText)[0]
    firstPicLink = re.findall('')
    print(pageNum)
    break