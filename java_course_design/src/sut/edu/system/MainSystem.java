package sut.edu.system;

import java.io.IOError;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.ServerSocket;
import java.net.Socket;
import java.sql.SQLException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;

import sut.edu.db.DBConnectionInfo;
import sut.edu.db.Database;
import sut.edu.log.Logger;

public class MainSystem {
    enum STATUS {
        OK("done"),
        CMD_NOT_FOUND("command not found, check your input"),
        SYNTAX_ERROR("syntax error, check your input"),
        WRONG_ARGS("wrong arguments, check your input"),
        NO_AUTHOR("your are not admin");

        private String message;
        STATUS(String msg) {
            this.message = msg;
        }

        public String getMessage() {
            return this.message;
        }
    }

    private static final int kServerPort = 55533;
    private static final String kUrl = "jdbc:mysql://localhost:3306/java_course";
    private static final String kUserName = "root";
    private static final String kPassword = "123456789";
    private static final String kHelpInfo =
            "user and admin:\n" +
                    "   help -- display this info\n" +
                    "   getlog -- display all system log\n" +
                    "   exit -- quit this system\n" +
                    "admin:\n" +
                    "   adduser [user_name] [user_identity] [user_password] -- add a new user\n" +
                    "   deleteuser [user_name] -- delete a user\n" +
                    "   changepassword [user_name] [new_password] -- change the password of a user\n" +
                    "   changeidentity [user_name] [new_identity] -- change the level of a user, the level can be admin or user\n";
    
    private static HashMap<String, Method> adminCall;

    static {
        adminCall = new HashMap<>();
        try {
            Class<?> c = Manager.class;
            adminCall.put("adduser", c.getMethod("AddUser", String.class, String.class, String.class));
            adminCall.put("deleteuser", c.getMethod("DeleteUser", String.class));
            adminCall.put("changepassword", c.getMethod("ChangeUserPassword", String.class, String.class));
            adminCall.put("changeidentity", c.getMethod("ChangeUserIdentity", String.class, String.class));
        } catch (NoSuchMethodException e) {
            e.printStackTrace();
            System.exit(-1);
        }
    }

    private Manager manager;
    private Interactive interactive;

    public MainSystem(Manager m, Interactive i) {
        manager = m;
        interactive = i;
    }

    public void Start() {
        interactive.PushMessage("Log System");
        String name;

        while(true) {
            interactive.PushMessage("login name:");
            name = interactive.PullMessage();

            interactive.PushMessage("password:");
            String password = interactive.PullMessage();

            if(password.equals(manager.GetUserPassword(name))) break;
            interactive.PushMessage("wrong password");
        }

        String identity = manager.GetUserIdentity(name);

        interactive.PushMessage("welcome");
        interactive.PushMessage(kHelpInfo);
        Logger.getSingleton().appendLog(String.format("%s %s login", identity, name));


        while(true) {
            String commandLine = interactive.PullMessage();

            if(commandLine == null) break;

            String[] commands = commandLine.split("\\s+");
            if(commands[0].equals("exit")) break;
            else if(commands[0].equals("help")) {
                interactive.PushMessage(kHelpInfo);
            }else if(commands[0].equals("getlog")) {
                List<String> list = Logger.getSingleton().readWholeLog();
                StringBuilder s = new StringBuilder();
                for(var i: list) {
                    s.append(i).append('\n');
                }
                interactive.PushMessage(s.toString());
            }else {
                STATUS res = executeCommand(commands[0], Arrays.copyOfRange(commands, 1, commands.length), identity.equals("admin"));
                interactive.PushMessage(res.getMessage());
            }
            Logger.getSingleton().appendLog(String.format("user %s execute: %s", name, commandLine));
        }

    }

    private STATUS executeCommand(String command, Object[] args, boolean isAdmin) {
        Method method = adminCall.get(command);
        if(!isAdmin && method != null) return STATUS.NO_AUTHOR;

        if(method != null) {
            try {
                Object returnVal = method.invoke(manager, args);
                if(!(boolean) returnVal) {
                    return STATUS.WRONG_ARGS;
                }
            }catch(IllegalAccessException | InvocationTargetException | IllegalArgumentException e) {
                return STATUS.SYNTAX_ERROR;
            }
        }else {
            return STATUS.CMD_NOT_FOUND;
        }

        return STATUS.OK;
    }

    public static void main(String[] args) {
        System.out.println();
        try {
            final Manager manager = new Manager(new Database(new DBConnectionInfo(kUrl, kUserName, kPassword)));
            Thread tRemote = new Thread(
                () -> {
                    try {
                        ServerSocket serverSocket = new ServerSocket(kServerPort);
                        while(true) {
                            Socket socket = serverSocket.accept();
                            new Thread(
                                () -> {
                                    try {
                                        MainSystem system = new MainSystem(manager, new SocketInteractive(socket));
                                        system.Start();
                                    }catch(IOException e) {}
                                }
                            ).start();
                        }
                    }catch(Exception e) {}
                }
            );
            tRemote.start();

            MainSystem localSys = new MainSystem(manager, new StdIOInteractive());
            localSys.Start();
            System.exit(0);
        }catch(SQLException e) {
            System.exit(-1);
        }

        
    }
}
