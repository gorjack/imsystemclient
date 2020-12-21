# -*- coding:gbk -*-

import time
import threading
import traceback
import win32api

class Timer(threading.Thread):
    
    def __init__(self, interval, name, bSetTitle = False):
        threading.Thread.__init__(self)
        self.__interval = interval
        self.__name = name
        self.__stop = False
        self.__bSetTitle = bSetTitle
        self.mins = 0
        self.secs = 0
           
    def run(self):
        try:
            start_time = time.time()
            while not self.__stop:
                elapsed_time = time.time() - start_time
                self.mins = (int)(elapsed_time / 60)
                self.secs = (int)(elapsed_time % 60)
                if self.__bSetTitle:
                    new_title = self.__name + '��(�Ѻ�ʱ��' + str(self.mins) + '��' + str(self.secs) + '��)'
                    win32api.SetConsoleTitle(new_title)
                time.sleep(self.__interval)
        except:
            traceback.print_exc()
            
    def stop(self):  
        self.__stop = True

    def name(self):
        return self.__name
        
