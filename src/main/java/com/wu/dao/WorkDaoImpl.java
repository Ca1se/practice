package com.wu.dao;


import com.wu.db.DBUtil;
import com.wu.domain.ShapeBean;
import com.wu.domain.WorkBean;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

public class WorkDaoImpl implements WorkDao {
    @Override
    public void saveWork(WorkBean work, List<ShapeBean> shapes) throws SQLException {
        Connection conn = DBUtil.getConnection();

        String save_work = "insert into works (name, author_id) value (?, ?)";
        PreparedStatement statement = conn.prepareStatement(save_work);
        statement.setString(1, work.getName());
        statement.setInt(2, work.getAuthor_id());
        statement.executeUpdate();

        String last_save = "select id from works order by id desc LIMIT 1";
        statement = conn.prepareStatement(last_save);
        ResultSet res = statement.executeQuery();
        res.next();
        Integer work_id = res.getInt("id");

        String save_shape = "insert into shapes (type, x, y, z, width, height, rotation, color, fill, work_id)values";
        StringBuffer sql = new StringBuffer(save_shape);
        for(int i = 0; i < shapes.size(); i++) {
            ShapeBean shape = shapes.get(i);
            sql.append(String.format("(%d, %d, %d, %d, %d, %d, %d, '%s', %d, %d)",
                        shape.getType(), shape.getX(), shape.getY(), shape.getZ(),
                        shape.getWidth(), shape.getHeight(), shape.getRotation(),
                        shape.getColor(), (shape.getFill() ? 1 : 0), work_id
                    ));
            if(i != shapes.size() - 1) {
                sql.append(',');
            }else {
                sql.append(';');
            }
        }
        statement = conn.prepareStatement(sql.toString());
        statement.executeUpdate();
    }

    @Override
    public void updateWork(WorkBean work, List<ShapeBean> shapes) throws SQLException {
        Connection conn = DBUtil.getConnection();

        String update_work = "update works set name=? where id=?";
        PreparedStatement statement = conn.prepareStatement(update_work);
        statement.setString(1, work.getName());
        statement.setInt(2, work.getId());
        statement.executeUpdate();

        String delete_old = "delete from shapes where work_id=?";
        statement = conn.prepareStatement(delete_old);
        statement.setInt(1, work.getId());
        statement.executeUpdate();

        String save_shape = "insert into shapes (type, x, y, z, width, height, rotation, color, fill, work_id)values";
        StringBuffer sql = new StringBuffer(save_shape);
        for(int i = 0; i < shapes.size(); i++) {
            ShapeBean shape = shapes.get(i);
            sql.append(String.format("(%d, %d, %d, %d, %d, %d, %d, '%s', %d, %d)",
                    shape.getType(), shape.getX(), shape.getY(), shape.getZ(),
                    shape.getWidth(), shape.getHeight(), shape.getRotation(),
                    shape.getColor(), (shape.getFill() ? 1 : 0), work.getId()
            ));
            if(i != shapes.size() - 1) {
                sql.append(',');
            }else {
                sql.append(';');
            }
        }
        statement = conn.prepareStatement(sql.toString());
        statement.executeUpdate();
    }
}
