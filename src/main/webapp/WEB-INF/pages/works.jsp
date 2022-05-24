<%@ page contentType="text/html; charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
    <title>Nice Paint - 我的文件</title>
    <link rel="stylesheet" href="styles/global.css" type="text/css">
    <link rel="stylesheet" href="styles/works.css" type="text/css">
    <script src="https://ajax.aspnetcdn.com/ajax/jQuery/jquery-3.6.0.min.js" type="text/javascript"></script>
    <script src="scripts/login.js" type="text/javascript"></script>
    <script type="text/javascript">
        function checkLogin() {
            location.href="LoginPage";
        }

        $(function () {
            autoLogin(null, checkLogin);
        });
    </script>
</head>
<body>
<div class="content">
    <header>
        <div class="logo"><a href="index.html"></a></div>
    </header>
    <section>
        <button class="get-log" style="margin: 100px" onclick="window.location.href='log.html'">登录日志</button>
        <input type="file" style="margin: 100px" onchange="up(this)">
    </section>
</div>
</body>
</html>