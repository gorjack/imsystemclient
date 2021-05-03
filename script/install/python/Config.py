# -*- coding:gbk -*-

import ConfigParser
import sys
import os
import MySQLdb
import _winreg
import xtCommon

sys.path.append('../../../_xtPlatform/script/python/')
import RCVersioner

# ���ݿ�������
class DBConfig:
    # ��ʼ������
    def __init__(self):
        self.db_host = 'localhost'
        self.db_port = 3306
        self.db_user = 'root'
        self.db_pass = ''
        self.db_name = ''

# ������������
class Config:
    
    # ��ȡ�����ļ�
    def loadConfig(self, config_file):
        self.conf_parser = ConfigParser.ConfigParser()
        self.conf_file = config_file
        print '���������ļ���' + self.conf_file
        if os.path.isfile(self.conf_file):
            self.conf_parser.read(self.conf_file)
        else:
            raise Exception('�����ļ�' + self.conf_file + '�����ڡ�')
    
    # ��ȡע���
    def loadReg(self):
        key = _winreg.OpenKey(_winreg.HKEY_LOCAL_MACHINE, 'System\\CurrentControlSet\\Control\\Session Manager\\Environment', 0, _winreg.KEY_READ)
        self.qt_path = _winreg.QueryValueEx(key, 'QT5DIR')[0]
        _winreg.CloseKey(key)

    # ��������
    def parseConfig(self):

        self.client_version = int(self.conf_parser.get('Product', 'client_version'))
        self.product_name_cn = self.conf_parser.get('Product', 'product_name_cn')
        self.product_name_en = self.conf_parser.get('Product', 'product_name_en')

        conf_id = self.conf_parser.get('Version', 'id')
        conf_name = self.conf_parser.get('Version', 'name')

        #self.rc_conf.exe_name = self.conf_parser.get('Product', 'xt_exe_name')
        #self.rc_conf.product_name_cn = self.product_name_cn
        #self.version = '%d.%d.%d.%04d' % (self.rc_conf.ver_major, self.rc_conf.ver_minor, self.rc_conf.ver_revision, self.rc_conf.ver_build)
        self.version = "0.0.0.0"
        print '��ǰ�汾�ţ�' + self.version
        self.out_tag = self.conf_parser.get('Product', 'output_file_tag')
        self.output_dir = self.conf_parser.get('Path', 'output_dir')
        self.out_file = self.outputFile(self.version)
        self.out_file_full = '%s\\%s' % (self.output_dir, self.out_file)
        self.nsi_script = self.conf_parser.get('NSIS', 'ScriptName')
    def getVersion(self, id, name, dbconfig):
        try:
            conn = MySQLdb.connect(host=dbconfig.db_host, user=dbconfig.db_user, passwd=dbconfig.db_pass, db=dbconfig.db_name, port=dbconfig.db_port)
            cur = conn.cursor()
            cur.execute('insert version(v_id, v_name) values(%s, "%s") on duplicate key update v_id_build = v_id_build + 1' % (id, name))
            cur.execute('select v_id_major, v_id_minor, v_id_revision, v_id_build from version where v_id = %s' % id)
            row = cur.fetchone()
            id_major = int(row[0])
            id_minor = int(row[1])
            id_revision = int(row[2])
            id_build = int(row[3])
            conn.commit()
            cur.close()
            conn.close()
            return True,id_major,id_minor,id_revision,id_build
        except:
            return False,0,0,0,0


    def outputFile(self, v):
        if (len(self.out_tag) > 0):
            return '%s_%s_%s.exe' % (self.product_name_en, self.out_tag, v)
        else:
            return '%s_%s.exe' % (self.product_name_en, v)

    
    # С�汾�ż�1
    def incVersion(self):
        self.ver_newbuild = self.rc_conf.ver_build + 1
        print '�°汾�� %d' % self.ver_newbuild
        self.conf_parser.set('Version', 'Build', self.ver_newbuild)
        with open(self.conf_file, 'wt') as configfile:
            self.conf_parser.write(configfile)
    

    # ����SVN�汾��
    def updateRevision(self, revision):
        self.svn_last_changed = revision
        self.conf_parser.set('SVN', 'LastChanged', self.svn_last_changed)
        with open(self.conf_file, 'wt') as configfile:
            self.conf_parser.write(configfile)

    
    # ��ʼ������
    def __init__(self, config_file):
        self.loadConfig(config_file)
        self.loadReg()
        self.root_dir = os.path.abspath('..\..\..')
        print '�����Ŀ¼��' + self.root_dir

