# -*- coding:gbk -*-

import os
import shutil

class RCVersionConf:

    def __init__(self):
        self.ver_major = 1
        self.ver_minor = 0
        self.ver_revision = 0
        self.ver_build = 0
        self.exe_name = ''
        self.product_name_cn = ''


# RC�ļ��汾�޸���
class RCVersioner:

    # ���ݰ汾�Ÿ�дRC�ļ�
    def versionRC(self, file_list):
        #�İ汾��
        for one_file in file_list:
            f_in = open(one_file)
            all_lines_in = []
            all_lines_out = []
            # ��ÿһ��
            try:
                strTable = 0
                all_lines_in = f_in.readlines()
                for line in all_lines_in:
                    if line.find('FILEVERSION') >= 0:
                        all_lines_out.append(' FILEVERSION %d,%d,%d,%04d\n' % (self.__conf.ver_major, self.__conf.ver_minor, self.__conf.ver_revision, self.__conf.ver_build))
                    elif line.find('PRODUCTVERSION') >= 0:
                        all_lines_out.append(' PRODUCTVERSION %d,%d,%d,%04d\n' % (self.__conf.ver_major, self.__conf.ver_minor, self.__conf.ver_revision, self.__conf.ver_build))
                    elif line.find('VALUE \"FileVersion\"') >= 0:
                        all_lines_out.append('            VALUE \"FileVersion\", \"%d, %d, %d, %04d\"\n' % (self.__conf.ver_major, self.__conf.ver_minor, self.__conf.ver_revision, self.__conf.ver_build))
                    elif line.find('VALUE \"ProductVersion\"') >= 0:
                        all_lines_out.append('            VALUE \"ProductVersion\", \"%d, %d, %d, %04d\"\n' % (self.__conf.ver_major, self.__conf.ver_minor, self.__conf.ver_revision, self.__conf.ver_build))
                    elif line.find('VALUE \"ProductName\"') >= 0:
                        all_lines_out.append('            VALUE \"ProductName\", \"%s\"\n' % (self.__conf.product_name_cn))
                    elif line.find('VALUE \"Comments\"') >= 0:
                        all_lines_out.append('            VALUE \"Comments\", \"%s\"\n' % (self.__conf.product_name_cn))
                    elif line.find('VALUE \"FileDescription\"') >= 0:
                        all_lines_out.append('            VALUE \"FileDescription\", \"%s\"\n' % (self.__conf.product_name_cn))
                    elif line.find('VALUE \"InternalName\"') >= 0:
                        all_lines_out.append('            VALUE \"InternalName\", \"%s\"\n' % (self.__conf.product_name_cn))
                    elif line.find('_ID_RSA_PRIVATE') >= 0:
                        strTable = 1
                        dirname = os.path.dirname(one_file)
                        priDirname = os.path.join(dirname, 'client_prikey.pem')
                        exits = os.path.exists(priDirname)
                        if exits:
                            pri_all_in = open(priDirname).read()
                            if pri_all_in.strip() != '':
                                all_lines_out.append('    _ID_RSA_PRIVATE           \"%s\"\n' % (pri_all_in))
                            else:
                                all_lines_out.append(line)    
                        else:
                            all_lines_out.append(line)
                    elif line.find('END') == 0 and strTable == 1:
                        strTable = 0
                        all_lines_out.append(line)
                    else:
                        if strTable == 0:
                            all_lines_out.append(line)
            except:
                raise Exception('RC�ļ��汾��ȡ����')
            finally:
                f_in.close()
            # дÿһ��
            try:
                f_out = open(one_file, 'w')
                for line in all_lines_out:
                    f_out.write(line)
            except:
                raise Exception('RC�ļ��汾�޸ĳ���')
            finally:
                f_out.close()

    # ��ԭRC�ļ��й�˾����
    def versionRCrevert(self, file_list):
        for one_file in file_list:
            f_in = open(one_file)
            all_lines_in = []
            all_lines_out = []
            # ��ÿһ��
            try:
                all_lines_in = f_in.readlines()
                for line in all_lines_in:
                    if line.find('VALUE \"ProductName\"') >= 0:
                        all_lines_out.append('            VALUE \"ProductName\", %s\n' % ('APP_NAME'))
                    elif line.find('VALUE \"Comments\"') >= 0:
                        all_lines_out.append('            VALUE \"Comments\", %s\n' % ('MODULE_NAME'))
                    elif line.find('VALUE \"FileDescription\"') >= 0:
                        all_lines_out.append('            VALUE \"FileDescription\", %s\n' % ('MODULE_NAME'))
                    elif line.find('VALUE \"InternalName\"') >= 0:
                        all_lines_out.append('            VALUE \"InternalName\", %s\n' % ('MODULE_NAME'))
                    else:
                        all_lines_out.append(line)
            except:
                raise Exception('RC�ļ��汾��ȡ����')
            finally:
                f_in.close()
            # дÿһ��
            try:
                f_out = open(one_file, 'w')
                for line in all_lines_out:
                    f_out.write(line)
            except:
                raise Exception('RC�ļ���ԭ����')
            finally:
                f_out.close()

    # ���캯��
    def __init__(self, conf):
        self.__conf = conf
