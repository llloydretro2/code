import requests
import re

Html = 'https://www.bilibili.com/read/cv6160480?from=search'
simulated_headers = {
        'User-Agent':'Mozilla/5.0(Macintosh; Intel Mac OS X 10_13_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/65.0.3325.162 Safari/537.36'
    }

ExposedHtml = requests.get(Html, headers=simulated_headers).text
content = re.findall('<p>(.*?)</p>', ExposedHtml)
OutputString = ""
for i in content:
    OutputString += i
    OutputString += '\n'
    OutputString = OutputString.replace('&#39;', "'")
    OutputString = OutputString.replace('<br/>', "")
    OutputString = OutputString.replace('&#34;', '"')

with open('output.txt', 'a') as file:
    file.write(OutputString)