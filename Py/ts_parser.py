import requests
import re
import os
import random

simulated_headers = [
    "Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10_6_8; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50",
    "Mozilla/5.0 (Windows; U; Windows NT 6.1; en-us) AppleWebKit/534.50 (KHTML, like Gecko) Version/5.1 Safari/534.50",
    "Mozilla/5.0 (Windows NT 10.0; WOW64; rv:38.0) Gecko/20100101 Firefox/38.0",
    "Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; .NET4.0C; .NET4.0E; .NET CLR 2.0.50727; .NET CLR 3.0.30729; .NET CLR 3.5.30729; InfoPath.3; rv:11.0) like Gecko",
    "Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)",
    "Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 6.0)",
    "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1)",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10.6; rv:2.0.1) Gecko/20100101 Firefox/4.0.1",
    "Mozilla/5.0 (Windows NT 6.1; rv:2.0.1) Gecko/20100101 Firefox/4.0.1",
    "Opera/9.80 (Macintosh; Intel Mac OS X 10.6.8; U; en) Presto/2.8.131 Version/11.11",
    "Opera/9.80 (Windows NT 6.1; U; en) Presto/2.8.131 Version/11.11",
    "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_7_0) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.56 Safari/535.11",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Maxthon 2.0)",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; TencentTraveler 4.0)",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1)",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; The World)",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; Trident/4.0; SE 2.X MetaSr 1.0; SE 2.X MetaSr 1.0; .NET CLR 2.0.50727; SE 2.X MetaSr 1.0)",
    "Mozilla/4.0 (compatible; MSIE 7.0; Windows NT 5.1; 360SE)",
]
#https://cvc.phncdn.com/hls/videos/201908/07/240265611/,720P_1500K,480P_600K,240P_400K,_240265611.mp4.urlset/seg-6-f1-v1-a1.ts?7O_O_zvtLX46i4L_Wa1Q50gBSLdb8r-fzm0DGSUrytZsA7IJt0xQBCyA12eEa_tQNEVA2ZKwZ_du3Jrh12_dR7nPiAiAfFIXjVIV_aQgyb7JKSD0NpeTbBYZJOCI7aG1a0vxJyzMsQcu4SpelJ0X1Co2AphuCJ8YVNqbwjz84o15A1m6s8L_gVKiR55o_oac8QO1Q5ZTYXTG-rZJNVQ

links = []
dic_name = '爱圣天使'
dic = ''
conbine_order = 'cat '
up = 225
down = 0
prefix = 'https://fc.aa1803.com/a/dcdprxjqlr/dcdprxjqlr_'


dic = '/Users/lloydretro2/Desktop/' + dic_name + '/'
if not os.path.isdir(dic):
    os.makedirs(dic)

for i in range(down, up+1):
    if i < 10:
        link = prefix + '00' + str(i) + '.ts'
    elif i < 100:
        link  = prefix + '0' + str(i) + '.ts'
    elif i < 1000:
        link = prefix + str(i) + '.ts'
    # link = prefix + str(i) + '.ts'
    # link = 'https://cvc.phncdn.com/hls/videos/201908/07/240265611/,720P_1500K,480P_600K,240P_400K,_240265611.mp4.urlset/seg-' + str(i) + '-f1-v1-a1.ts?7O_O_zvtLX46i4L_Wa1Q50gBSLdb8r-fzm0DGSUrytZsA7IJt0xQBCyA12eEa_tQNEVA2ZKwZ_du3Jrh12_dR7nPiAiAfFIXjVIV_aQgyb7JKSD0NpeTbBYZJOCI7aG1a0vxJyzMsQcu4SpelJ0X1Co2AphuCJ8YVNqbwjz84o15A1m6s8L_gVKiR55o_oac8QO1Q5ZTYXTG-rZJNVQ'

    links.append(link)

print('Link loading down.')

count = down - 1
for i in links:
    count += 1
    agent = random.choice(simulated_headers)
    used_header = {
        'User-Agent': agent
    }
    video = requests.get(i, headers=used_header)
    v_num = str(count) + '.ts'
    direct_dic = dic + v_num
    print(i)
    with open(direct_dic, 'wb') as f:
        f.write(video.content)
    print('done')

for i in range(1, up):
    conbine_order = conbine_order + str(i) + '.ts '

conbine_order = conbine_order + '> ' + dic_name + '.MPEG'
os.chdir(dic)
os.system(conbine_order)