# -*- coding:gbk -*-

import shutil
import sys
import os
import shutil


# һЩͨ�ú����������Ķ�����
class Util:
    
    # ����һ���ļ�
    def copyFile(self, src_dir, dst_dir, file_name):
        shutil.copyfile(src_dir + '\\' + file_name, dst_dir + '\\' + file_name)
        
    # ���һ��Ŀ¼
    def clearDir(self, src_dir):
        if os.path.isdir(src_dir):
            for f in os.listdir(src_dir):
                abs_path = src_dir + os.sep + f
                if os.path.isfile(abs_path):
                    os.remove(abs_path)
                elif os.path.isdir(abs_path) and f != '.' and f != '..':
                    self.clearDir(abs_path)
                    os.rmdir(abs_path)
    
    # �ݹ鸴���ļ��У�����������Ŀ¼��SVNĿ¼
    def copyDirR(self, src_dir, dst_dir):
        base_name = os.path.basename(dst_dir)
        if base_name != '.svn' and base_name != '.' and base_name != '..':
            if os.path.isdir(src_dir):
                if not os.path.isdir(dst_dir):
                    os.mkdir(dst_dir)
                for f in os.listdir(src_dir):
                    abs_path = src_dir + os.sep + f
                    if os.path.isfile(abs_path):
                        shutil.copy(abs_path, dst_dir + os.sep + f)
                    else:
                        dst_subdir = dst_dir + os.sep + f
                        self.copyDirR(abs_path, dst_subdir)

    # �����ļ����������ļ������ݹ�
    def copyDir(self, src_dir, dst_dir):
        base_name = os.path.basename(dst_dir)
        if base_name != '.svn' and base_name != '.' and base_name != '..':
            if os.path.isdir(src_dir):
                if not os.path.isdir(dst_dir):
                    os.mkdir(dst_dir)
                for f in os.listdir(src_dir):
                    abs_path = src_dir + os.sep + f
                    if os.path.isfile(abs_path):
                        shutil.copy(abs_path, dst_dir + os.sep + f)

    # �ݹ鴴��Ŀ¼���縸Ŀ¼����Ŀ¼�򴴽���Ŀ¼
    def makeDir(self, d):
        p, v = os.path.split(d)
        if os.path.isdir(p):
            os.mkdir(d)
        elif p != d and len(p) > 0:
            self.makeDir(p)
            os.mkdir(d)
