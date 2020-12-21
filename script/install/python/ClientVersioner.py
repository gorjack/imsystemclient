# -*- coding:gbk -*-

import sys
import os
import shutil

# �汾������
class ClientVersioner:

    def setClientVersion(self):
        # ����config.lua
        config_lua_file = self.__conf.root_dir + '\\_runtime\\config\\' + self.__conf.config_file
        f_in = open(config_lua_file)
        all_lines_in = []
        all_lines_out = []
        # ��ÿһ��
        try:
            all_lines_in = f_in.readlines()
            for line in all_lines_in:
                if line.find('g_client_version_config') >= 0:                    
                    all_lines_out.append('g_client_version_config = {m_strExeNameMain="%s", m_strExeName="%s", m_strProductName="%s", m_strBrowserExe="XtAmpBrowser.exe", m_strBrowserName="ѸͶ�ʹ��Ż�", m_strRegion="%s", m_strInstallerFile="%s", m_strBrokerName="%s"}\n' % (self.__conf.product_name_en, self.__conf.product_name_en + '.exe', self.__conf.product_name_cn, self.__conf.region, self.__conf.update_temp_file, self.__conf.broker_name_cn))
                else:
                    all_lines_out.append(line)
        except:
            raise Exception(self.__conf.config_file + '��ȡ����')
        finally:
            f_in.close()
        # дÿһ��
        f_out = open(config_lua_file, 'w')
        try:
            for line in all_lines_out:
                f_out.write(line)
        except:
            raise Exception(self.__conf.config_file + '�޸ĳ���')
        finally:
            f_out.close()

    # ��ʼ������
    def __init__(self, conf):
        self.__conf = conf
