package com.wu.dao;

import com.wu.db.DBUtil;
import com.wu.domain.UserLogBean;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

public class LogDaoImpl implements LogDao {
    @Override
    public void userLog(UserLogBean logInfo) throws SQLException {
        Connection conn = DBUtil.getConnection();

        String sql = "insert into log (ip, username, action, date) values (?, ?, ?, ?)";
        PreparedStatement statement = conn.prepareStatement(sql);
        statement.setString(1, logInfo.getIp());
        statement.setString(2, logInfo.getUsername());
        statement.setString(3, logInfo.getAction());
        statement.setDate(4, logInfo.getDate());
        statement.executeUpdate();
    }

    public List<UserLogBean> convertToList(ResultSet rs) throws SQLException {
        List<UserLogBean> ret = new ArrayList<>();

        while (rs.next()) {
            UserLogBean log = new UserLogBean();
            log.setIp(rs.getString(1));
            log.setUsername(rs.getString(2));
            log.setAction(rs.getString(3));
            log.setDate(rs.getDate(4));
            ret.add(log);
        }

        return ret;
    }

    @Override
    public List<UserLogBean> getUserLog() throws SQLException {
        Connection conn = DBUtil.getConnection();

        String sql = "select * from log";
        PreparedStatement statement = conn.prepareStatement(sql);
        ResultSet result = statement.executeQuery();
        return convertToList(result);
    }
}
