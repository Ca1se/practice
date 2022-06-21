package com.wu.servlet;

import com.wu.dao.LogDao;
import com.wu.dao.LogDaoImpl;
import com.wu.domain.UserLogBean;
import com.alibaba.fastjson.JSON;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.List;

@WebServlet(name = "LogServlet", urlPatterns = "/log")
public class LogServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            LogDao dao = new LogDaoImpl();
            List<UserLogBean> log = dao.getUserLog();
            String json = JSON.toJSONString(log);

            resp.setStatus(200);
            PrintWriter out = resp.getWriter();
            out.print(json);
        }catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
