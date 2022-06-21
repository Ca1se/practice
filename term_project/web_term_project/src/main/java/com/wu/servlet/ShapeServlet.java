package com.wu.servlet;

import com.alibaba.fastjson.JSON;
import com.wu.dao.WorkDao;
import com.wu.dao.WorkDaoImpl;
import com.wu.domain.ShapeBean;
import com.wu.domain.WorkBean;
import com.wu.domain.WorkJson;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

@WebServlet(name = "ShapeServlet", urlPatterns = "/shapes")
public class ShapeServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        try {
            Integer workId = Integer.parseInt(req.getParameter("workId"));

            WorkBean work = new WorkBean();
            work.setId(workId);

            WorkDao dao = new WorkDaoImpl();
            List<ShapeBean> shapes = dao.getShapes(work);
            String json = JSON.toJSONString(shapes);

            resp.getWriter().print(json);
            resp.setStatus(200);
        }catch (SQLException e) {
            e.printStackTrace();
            resp.setStatus(500);
        }
    }
}
