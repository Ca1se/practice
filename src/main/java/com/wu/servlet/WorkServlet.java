package com.wu.servlet;

import com.alibaba.fastjson.JSON;
import com.wu.dao.WorkDao;
import com.wu.dao.WorkDaoImpl;
import com.wu.domain.UserBean;
import com.wu.domain.WorkJson;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

@WebServlet(name="WorkServlet", urlPatterns = "/works")
public class WorkServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        this.doGet(req, resp);
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        UserBean user = (UserBean) req.getSession().getAttribute("user");
        if(user != null) {
            try {
                WorkDao dao = new WorkDaoImpl();
                List<WorkJson> works = dao.getWorks(user);

                String json = JSON.toJSONString(works);
                resp.setCharacterEncoding("UTF-8");
                resp.getWriter().print(json);
                resp.setStatus(200);
            }catch (SQLException e) {
                e.printStackTrace();
                resp.setStatus(500);
            }
        }else {
            resp.setStatus(404);
        }
    }
}
