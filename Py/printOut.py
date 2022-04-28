import os

path = '/Users/lloydretro2/Desktop'

g = os.walk(path)

list = []

for path, dir_list, file_list in g:
    for file_name in file_list:
        print(os.path.join(path, file_name))
        list.append(os.path.join(path, file_name))

1_shenghuo.jpg
1_zhengjian.jpg