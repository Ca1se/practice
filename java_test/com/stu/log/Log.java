package com.stu.log;

import java.util.ArrayList;

public class Log {
    private class LogInfo {
        LogInfo(User user, String loginTime, String ipAddress) {
            this.user = user;
            this.loginTime = loginTime;
            this.ipAddress = ipAddress;
        }
        User user;
        String loginTime;
        String ipAddress;
    }

    private ArrayList<LogInfo> infoList;

    public Log() {
        infoList = new ArrayList<>();
    }

    public void AddLogInformation(User user, String logTime, String ipAddress) {
        infoList.add(new LogInfo(user, logTime, ipAddress));
    }

    public void dumpLog() {
        // dump operation
    }
}
