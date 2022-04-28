import os
import sys
import io

#encoding=:utf-8
sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='gb18030')

download_dir = 'C:\\Users\\15532\\Desktop\\'
website = 'https://www.bilibili.com/video/av81163963'
downloads = []
with open('downloads') as file:
    for i in file.readlines():
        downloads.append(i)

def download():
    os.chdir(download_dir)
    download_function = 'you-get ' + website
    os.system(download_function)
    print(website + ' completed')

def download_many():
    os.chdir(download_dir)
    for i in downloads:
        download_function = 'you-get ' + i
        os.system(download_function)
        print(i + ' completed')

def converter():
    convert_list = []
    for file in os.listdir(download_dir):
        if '.flv' in file:
            convert_list.append(file)
    for convert_target in convert_list:
        os.chdir(download_dir)
        convert_function = 'ffmpeg -i ' + '"' +convert_target + '"' + ' ' + '"' + convert_target.replace('.flv', '') + '.mp4' + '"'
        print(convert_function)
        os.system(convert_function)
        print(convert_target + ' completed')

def clear_cmt():
    os.chdir(download_dir)
    for file in os.listdir(download_dir):
        if '.cmt' in file:
            os.remove(file)
            print(file + ' removed')

if __name__ == '__main__':
    download_many()
    converter()
    clear_cmt()