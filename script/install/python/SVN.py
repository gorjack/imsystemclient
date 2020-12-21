# -*- coding:gbk -*-

# �˽ű��ļ�����win32ƽ̨��

import sys
import os


# svn��
class SVN:
   
    # ��ȡ��ǰSVN�汾��
    def __getRevision(self):
        tmp_info_file = 'tmp_svn_info.txt'
        cmd_line = 'svn info \"' + self.__root_path + '\" > ' + tmp_info_file
        r = ''
        if 0 != os.system(cmd_line):
            raise Exception('��ȡ��ǰsvn�汾���������⡣')
        f = open(tmp_info_file)
        try:
            all_lines = f.readlines()
            for line in all_lines:
                segs = line.split(': ')
                if segs[0] == 'Last Changed Rev':
                    r = segs[1]
        except:
            raise Exception('��ȡsvn�汾�Ŵ���')
        finally:
            f.close()
            if len(r) <= 0:
                raise Exception('δ�ܶ�ȡ��svn�汾��')
            return r
    
    # ��ʼ������
    def __init__(self, root_path, name):
        self.__root_path = root_path
        self.__name = name
        self.to_revision = 1
    
    # ��ȡ��־�����汾
    def getToRevision(self):
        self.to_revision = int(self.__getRevision())
    
    # ����svn
    def update(self):
        cmd_line = 'svn update \"' + self.__root_path + '\" --accept mine-full'
        print '\n--------------------'
        print '���� ' + self.__name + ' SVN��'
        print cmd_line
        print '--------------------\n'
        if 0 != os.system(cmd_line):
            raise Exception('����svn�������⡣')

    # ��ԭ
    def revert(self):
        cmd_line = 'svn revert \"' + self.__root_path + '\"'
        if 0 != os.system(cmd_line):
            raise Exception('��ԭ' + self.__root_path + '��������')

    # ��ȡsvn������־
    def getLog(self, from_revision):
        tmp_log_file = 'tmp_svn_log.txt'
        all_text = ''
        if from_revision <= self.to_revision:
            cmd_line = 'svn log \"' + self.__root_path + '\" -r ' + str(self.to_revision) + ':' + str(from_revision) + ' > ' + tmp_log_file
            print cmd_line
            if 0 != os.system(cmd_line):
                #raise Exception('��ȡsvn��־�������⡣')
                print '��ȡsvn��־�������⡣'
            f = open(tmp_log_file)
            try:
                all_lines = f.readlines()
                for line in all_lines:
                    all_text = all_text + line + '<br/>'
            except:
                raise Exception('��ȡsvn��־����')
            finally:
                f.close()
                return all_text
        return all_text

