package sut.edu.system;

import sut.edu.db.Database;
import sut.edu.log.Logger;

import java.util.HashMap;
import java.util.Objects;

public class Manager {
    private static final String HELP_INFO =
            "user and admin:\n" +
                    "   help -- display this info\n" +
                    "   getlog -- display all system log\n" +
                    "   exit -- quit this system\n" +
                    "admin:\n" +
                    "   adduser [user_name] [user_identity] [user_password] -- add a new user\n" +
                    "   deleteuser [user_name] -- delete a user\n" +
                    "   changepassword [user_name] [new_password] -- change the password of a user\n" +
                    "   changeidentity [user_name] [new_identity] -- change the level of a user, the level can be admin or user\n";

    public enum IDENTITY {
        user("user"),
        admin("admin");

        private String str;
        IDENTITY(String s) {
            this.str = s;
        }

        public String getString() {
            return str;
        }
    }

    public void printHelpInfo() {
        System.out.println(HELP_INFO);
    }

    public void printLogInfo() {
        for(var it: Logger.getSingleton().readWholeLog()) {
            System.out.println(it);
        }
    }

    public boolean addUser(String name, String identity, String passwd) {
        HashMap<String, String> map = new HashMap<>();
        map.put("user_name", name);
        map.put("user_identity", identity);
        map.put("user_password", passwd);
        return Database.insertStringValue("user_info", map);
    }

    public boolean deleteUser(String name) {
        HashMap<String, String> map = new HashMap<>();
        map.put("user_name", name);
        return Database.deleteValue("user_info", map);
    }

    public boolean changeUserPassword(String name, String passwd) {
        HashMap<String, String> map = new HashMap<>();
        map.put("user_name", name);
        return Database.updateStringValue("user_info", map, "user_password", passwd);
    }

    public boolean changeUserIdentity(String name, String identity) {
        HashMap<String, String> map = new HashMap<>();
        map.put("user_name", name);
        if(!Objects.equals(identity, IDENTITY.admin.getString()) && !Objects.equals(identity, IDENTITY.user.getString())) return false;
        return Database.updateStringValue("user_info", map, "user_identity", identity);
    }

    public String getUserPassword(String name) {
        HashMap<String, String> map = new HashMap<>();
        map.put("user_name", name);
        var res = Database.getStringValue("user_info", map, "user_password");
        return res.size() != 0 ? res.get(0) : "";
    }

    public IDENTITY getUserIdentity(String name) {
        HashMap<String, String> map = new HashMap<>();
        map.put("user_name", name);
        var res = Database.getStringValue("user_info", map, "user_identity");
        return res.size() != 0 ? Enum.valueOf(IDENTITY.class, res.get(0)) : null;
    }
}
