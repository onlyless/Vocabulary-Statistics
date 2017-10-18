## 统计文本中单词频率
<p>这个小程序可以统计文件input.txt文本中所有英文单词的词频（由高到低排序），并给出每个单词的翻译</p>


<p>这个程序有两种方法，第一种用goole-cloud库，收费的，不过运行时间快一些，第二种模拟网页请求，时间略长,不能大量翻译.</p>
<p>本程序用的两种方法都可以运行，第一种在本机运行后，超出了免费翻译次数，于是就用的第二种，要用第一种的话，把源代码中注释的代码取消注释即可，再把第二种的注释就可以了

### 一.运行前需要安装google-cloud库,并安装Google Cloud SDK

#### 1.安装相关模块

``` shell
pip install --upgrade google-cloud-translate  
```

#### 2.调用api进行翻译之前，需要安装相关证书

安装  [Google Cloud SDK](https://cloud.google.com/sdk/)
因为在本地上运行，使用的第一种方式，安装之后会有自动弹出验证邮箱的界面，如果没有在Google cloud sdk shell  运行
``` shell
gcloud auth application-default login
```

### 二.使用urllib取googletranslate
模拟一个头文件，请求到translate.google.com去，然后解析出翻译文本

### 运行方式
把将要统计的文本放入Input.txt文件中，直接运行

``` python
python word.py
```
即可

### 更新：
output.txt文件中是统计二十篇四级英语听力的输出