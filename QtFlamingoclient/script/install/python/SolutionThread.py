# -*- coding:gbk -*-

# 此脚本文件依赖win32平台。

import sys

sys.path.append('../../../_xtPlatform/script/python/')
import BuildModule
import Solution
import Timer
import PackLog

from threading import Thread

class SolutionThread(Thread):

    def __init__(self, product_name, name, version, dir, sln, projects, clean, build, configuration = 'Release', platform = 'win32'):
        Thread.__init__(self)
        self.__product_name = product_name
        self.__name = name
        self.__version = version
        self.__dir = dir
        self.__sln = sln
        self.__projects = projects
        self.__clean = clean
        self.__build = build
        self.__stop = False
        self.__build_timer = Timer.Timer(1, self.__name)
        self.__build_solution = Solution.Solution(self.__dir, self.__sln, self.__clean, configuration, platform)

    def run(self):
        print (self.__product_name + ' ' + self.__version + ' 正在编译' + self.__name + '……')
        # win32api.SetConsoleTitle(curr_title)
        self.__build_timer.start()
        try:
            self.__build_solution.buildSolution(self.__build, self.__projects)
            self.__build_timer.stop()
            PackLog.pack_log.writeLog('\n编译工程：' + self.__projects)
        except:
            self.__build_timer.stop()

    def status(self):
        return self.__build_solution.status()
        
    def solutionName(self):
        return self.__build_solution.solutionName()
        
    def log(self):
        return self.__build_solution.build_log

    def stop(self):
        self.__build_solution.terminate()
        self.__build_timer.stop()

    def timer(self):
        return self.__build_timer

    def getIdString(self):
        return self.__name + '_' + self.__dir
