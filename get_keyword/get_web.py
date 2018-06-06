#-*- coding:utf8 -*-
import requests
import  sys

URL_GET = "http://opac.lib.whu.edu.cn/F/HXPJNR5S4FGAYKQKQ1C8Q1KVGBMC2BHVDNBLM7BRF29RQC47XQ-22495?func=item-global&doc_library=WHU09&doc_number=000765738&year=&volume=&sub_library="
URL_GET = "http://opac.lib.whu.edu.cn/F/KQ227DN4BSLGG2JIC3B1X6YPAGXUES1IHGDMFQGD86Y4SNKGTS-13400?func=item-global&doc_library=WHU09&doc_number=000765738"

def use_params_requests():
    #构建请求参数
    #发送请求
    response = requests.get(URL_GET)
    response.encoding="gbk2312"
    #处理响应
    print ('>>>>>>Status Code:')
    print(response.status_code)
    text=response.text
    #text=response.text.encode('gb2312', 'ignore')
    on_the_shelter=str(u"在架上")
    login_need1="name"
    login_need2="password"
    login_need3="login"
    if text.find(login_need1)>0 and text.find(login_need2)>0 and text.find(login_need3)>0:
        print ("login needed, the url has been invalid")
        return
    if text.find(on_the_shelter)>0:
        print ("哇，书到了")
    else:
        print ("还没有到哦")


if __name__ == '__main__':

    use_params_requests()
    input("1")

