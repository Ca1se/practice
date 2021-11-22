package sut.edu.system;

import sut.edu.db.Database;
import sut.edu.log.Logger;

import java.io.Console;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.HashMap;

public class MainSystem {
    private static final String URL = "jdbc:mysql://localhost:3306/manager_system";
    private static final String NAME = "root";
    private static final String PASSWD = "123456789";
    private static final int port = 55533;

    private static HashMap<String, Method> userMethod;
    private static HashMap<String, Method> adminMethod;

    private Manager manager;

    /*
    static {
        userMethod = new HashMap<>();
        adminMethod = new HashMap<>();
        try {
            adminMethod.put("help", Manager.class.getMethod("printHelpInfo"));
            adminMethod.put("getlog", Manager.class.getMethod("printLogInfo"));
            adminMethod.put("adduser", Manager.class.getMethod("addUser", String.class, String.class, String.class));
            adminMethod.put("deleteuser", Manager.class.getMethod("deleteUser", String.class));
            adminMethod.put("changepassword", Manager.class.getMethod("changeUserPassword", String.class, String.class));
            adminMethod.put("changeidentity", Manager.class.getMethod("changeUserIdentity", String.class, String.class));

            userMethod.put("help", Manager.class.getMethod("printHelpInfo"));
            userMethod.put("getlog", Manager.class.getMethod("printLogInfo"));
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }


    public MainSystem() {
        manager = new Manager();
    }

    public void start() {
        Console console = System.console();
        String user_name;
        String password;

        while(true) {
            System.out.println("Log Management System");
            System.out.print("user: ");
            user_name = console.readLine();
            System.out.print("password: ");
            password = String.valueOf(console.readPassword());
            if(checkLoginInfo(user_name, password)) {
                break;
            }else {
                System.out.println("Wrong login information");
            }
        }

        var identity = manager.getUserIdentity(user_name);
        Logger.getSingleton().appendLog(String.format("%s %s login locally", identity.getString(), user_name));
        System.out.println("welcome");

        manager.printHelpInfo();

        while(true) {
            System.out.print("> ");
            String commandLine = console.readLine();
            ArrayList<String> res = parseCommand(commandLine);
            String command = res.get(0);
            if(command.equals("exit")) break;
            if(executeCommand(command, res.subList(1, res.size()).toArray(), identity == Manager.IDENTITY.admin)) {
                Logger.getSingleton().appendLog(String.format("%s %s executed command: %s", identity.getString(), user_name, commandLine));
            }
        }

    }

    private boolean executeCommand(String command, Object[] params, boolean isAdmin) {
        Method method = null;
        if(isAdmin) method = adminMethod.get(command);
        else method = userMethod.get(command);

        if(method != null) {
            try {
                Object returnVal = method.invoke(manager, params);
                if(returnVal != null) {
                    if((boolean) returnVal) {
                        System.out.println("done");
                    }else {
                        System.out.println("failed");
                    }
                }
            } catch (IllegalAccessException | InvocationTargetException | IllegalArgumentException e) {
                System.out.println("syntax error");
                return false;
            }
        }else {
            System.out.println("command not found");
            return false;
        }
        return true;
    }


    private ArrayList<String> parseCommand(String cmdLine) {
        ArrayList<String> list = new ArrayList<>();
        int pre = 0, pos;
        while((pos = cmdLine.indexOf(' ', pre)) != -1) {
            list.add(cmdLine.substring(pre, pos));
            pre = pos + 1;
        }
        list.add(cmdLine.substring(pre));
        return list;
    }

    private boolean checkLoginInfo(String name, String passwd) {
        return manager.getUserPassword(name).equals(passwd);
    }

    */
}
