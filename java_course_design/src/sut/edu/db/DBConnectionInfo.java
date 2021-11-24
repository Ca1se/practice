package sut.edu.db;

public class DBConnectionInfo {
    private final String url;
    private final String userName;
    private final String password;

    public DBConnectionInfo(String url, String userName, String password) {
        this.url = url;
        this.userName = userName;
        this.password = password;
    }

    public String getUrl() {
        return url;
    }

    public String getUserName() {
        return userName;
    }

    public String getPassword() {
        return password;
    }
}
