#coding=utf8
import re
# from google.cloud import translate  
import urllib.request
import sys
# translate_client = translate.Client()

language = 'zh_CN'  #将要翻译的语言
length = 4      #提选出小于此长度的单词
times = 5       #提选出小于此次数的单词

input = open("input.txt",'r',encoding='utf-8')
output = open('words.txt','w+',encoding='utf-8')

typ = sys.getfilesystemencoding()

def translate(querystr, to_l="zh", from_l="en"):
    C_agent = {'User-Agent': "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Safari/537.36"}
    flag = 'class="t0">'
    tarurl = "http://translate.google.com/m?hl=%s&sl=%s&q=%s \
        " % (to_l, from_l, querystr.replace(" ", "+"))
    request = urllib.request.Request(tarurl, headers=C_agent)
    page = str(urllib.request.urlopen(request).read().decode(typ))
    target = page[page.find(flag) + len(flag):]
    target = target.split("<")[0]
    return target

def main():
    try:
        all_word = input.read()
        l = re.split(r'[^A-Za-z]+',all_word)
        d = {}
        for i in l:
            i = i.lower()
            if d.get(i)==None:
                d[i] = 1
            else:
                d[i] = d[i] +1
        ju = 0
        for word in sorted(d,key=d.get,reverse=True):
            if len(word)<length or d[word]<times:
                continue

            # translation = translate_client.translate(word,target_language=language)  
            # tran = translation['translatedText']
            # tran = translate(word)
            # string = "%-18s%-10s%-7d\t"%(word,tran,d[word])
            string = "%-17s\t\t%-6d\t" %(word,d[word])
            ju += 1
            if ju%8==0:
                string += '\n'
            output.write(string)
    finally:
        input.close()
        output.close()

main()