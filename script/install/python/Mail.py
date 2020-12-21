# -*- coding:gbk -*-

import sys
import os
import shutil
import smtplib
from email.mime.text import MIMEText

# �ʼ���
class Mail:
    
    def sendMail(self, to_list, subject, content, is_html):
        me = self.__user_name + '<' + self.__user_name + '>'
        if True == is_html:
            msg = MIMEText(content, 'html')
        else:
            msg = MIMEText(content, 'plain')
        msg['Accept-Language'] = 'zh-CN'
        msg['Accept-Charset'] = 'ISO-8859-1,gbk'
        msg['Content-Type'] = 'application/octet-stream'
        msg['Subject'] = subject
        msg['From'] = me
        msg['To'] = ';'.join(to_list)
        msg.set_charset('gbk')
        self.__smtp.sendmail(me, to_list, msg.as_string())
    
    def __init__(self, user_name, password, smtp_host, port = 25, ssl = False):
        self.__user_name = user_name
        self.__password = password
        self.__smtp_host = smtp_host
        self.__smtp_port = port
        if ssl:
            self.__smtp = smtplib.SMTP_SSL()
        else:
            self.__smtp = smtplib.SMTP()
        self.__smtp.connect(self.__smtp_host, self.__smtp_port)
        self.__smtp.login(self.__user_name, self.__password)
        
    def __del__(self):
        self.__smtp.close()


# ���ࣺ����ʼ���
class BuildMail(Mail):
    
    def sendBuildSuccessMail(self, url, pdbUrl, show_name, svn_log, addr_list):
        content = '���ص�ַ��<br/>' + url + '<br/><br/>' + 'PDB���ص�ַ��<br/>' + pdbUrl + '<br/><br/>' + svn_log
        Mail.sendMail(self, addr_list, show_name + ' ������', content, True)
    
    def sendBuildFailMail(self, show_name, build_log, addr_list):
        content = build_log
        Mail.sendMail(self, addr_list, show_name + ' ���ʧ��', content, False)
    
    def __init__(self):
        Mail.__init__(self, 'package@thinktrader.net', 'package.rzrk1', 'smtp.thinktrader.net', 25, False)


