import os
import signal
import time
import datetime

# Change this to your process name
processName = "MarketRecord.exe"
storageDir = "D:\\Workspaces\\ctp\\data"

def isExist(pn):
    for line in os.popen("tasklist"):
        fields = line.split()
        if len(fields) >= 2:
            if fields[0] == pn:
                return True
    return False

def strTime():
    return time.strftime('%H:%M:%S',time.localtime(time.time()))

if __name__=='__main__':
    while True:
        curTime = strTime()
        day = datetime.datetime.now().weekday() + 1;
        if day >= 1 and day <= 5:
            if curTime>"08:30:00" and curTime<"16:00:00":
                if not isExist(processName):
                    os.system("start " + processName+" "+storageDir)
            elif curTime>"16:30:00":
                if isExist(processName):
                    os.system("taskkill /f /im "+processName)
        else:
            if isExist(processName):
                os.system("taskkill /f /im "+processName)
        time.sleep(1)
