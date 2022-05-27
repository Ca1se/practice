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
            autoLogin(function () {}, checkLogin);

            $.ajax({
                type: 'GET',
                url: 'works',
                success: function (json) {
                    let data = JSON.parse(json);
                    let $section = $('section');
                    data.forEach(function (val) {
                        let $box = $(`<div class='box'>\${val.workName}</div>`);
                        $box.on('click', function (event) {
                            let target = event.target;
                            location.href=`designer?workId=\${val.workId}`;
                        });
                        $section.append($box);
                    });
                }
            });

        });

    </script>
</head>
<body>
<div class="content">
    <header>
        <div class="logo"><a href="index.html"></a></div>
        <div class="newwork"><a class="button newwork_btn" href="designer">新建</a></div>
    </header>
    <section>

    </section>
</div>
</body>
</html>