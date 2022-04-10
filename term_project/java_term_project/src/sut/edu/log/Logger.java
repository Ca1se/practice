package sut.edu.log;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class Logger {
    private class Time {
        private SimpleDateFormat simpleDateFormat;
        public Time() {
            simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        }

        public String getNowTime() {
            return simpleDateFormat.format(new Date());
        }
    }

    private FileUtil file;
    private Time time;

    private static String logFilePath = "server.log";
    private static Logger logger = null;

    private Logger(String logFilePath) throws IOException {
        file = new FileUtil(logFilePath);
        time = new Time();
    }

    private static void newLogger() {
        try {
            logger = new Logger(logFilePath);
        }catch(IOException e) {
            System.err.println("Logger::startLogger: Failed to start logger");
            e.printStackTrace();
        }
    }

    public static void setLogFilePath(String logFilePath) {
        Logger.logFilePath = logFilePath;
    }

    public static Logger getSingleton() {
        if(logger == null) newLogger();
        return logger;
    }

    public void stop() {
        try {
            logger.file.close();
        }catch(IOException e) {
            System.err.println("Logger::stopLogger: Failed to stop logger");
            e.printStackTrace();
        }finally {
            logger = null;
        }
    }

    public void appendLog(String logMsg) {
        try {
            file.appendNewLine(String.format("[%s]: %s", time.getNowTime(), logMsg));
        }catch(IOException e) {
            System.err.println("Logger::appendLog: Failed to append log massage");
            e.printStackTrace();
        }
    }

    public ArrayList<String> readWholeLog() {
        ArrayList<String> logList = new ArrayList<>();
        String tmp;
        try {
            try {
                file.flushWriter();
                while((tmp = file.readLine()) != null) {
                    logList.add(tmp);
                }
            }catch(IOException e) {
                System.err.println("Logger::readWholeLog: Failed to read log file");
                e.printStackTrace();
                return null;
            }finally {
                file.resetReader();
            }
        }catch(IOException e) {
            e.printStackTrace();
        }
        return logList;
    }

}
