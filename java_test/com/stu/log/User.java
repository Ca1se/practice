package com.stu.log;

public class User {
    private String name;
    private String passwd;
    private String email;
    private String sex;

    public User(String name, String passwd, String email, String sex) {
        this.name = name;
        this.passwd = passwd;
        this.email = email;
        this.sex = sex;
    }

    public String getName() {
        return name;
    }

    public String getEmail() {
        return email;
    }

    public String getPasswd() {
        return passwd;
    }

    public String getSex() {
        return sex;
    }
}
