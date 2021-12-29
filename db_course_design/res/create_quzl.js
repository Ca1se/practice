var quz_cnt = 1;

$(document).ready(function () {
    $('#btn_add_quz').click(function () {
        var quz_html = `<p class=\"quz_p\">
                            <label>问题${quz_cnt + 1}</label>
                            <div class=\"quz\">
                                <input type=\"text\" class=\"quz_field\" placeholder=\"问题内容\"></br>
                                <input type=\"text\" class=\"quz_field\" placeholder=\"选项内容\"></br>
                                <input type=\"text\" class=\"quz_field\" placeholder=\"选项内容\"></br>
                                <input type=\"text\" class=\"quz_field\" placeholder=\"选项内容\"></br>
                                <input type=\"text\" class=\"quz_field\" placeholder=\"选项内容\"></br>
                            </div>
                        </p>`;
        $('form').append(quz_html);
        quz_cnt++;
    });

    $('#btn_del_quz').click(function() {
        if(quz_cnt > 1) {
            var ch = $('#btn_del_quz').children('.quz_p');
            $('form').remove($(ch[ch.length - 1]));
            quz_cnt--;
        }
    });

    $('#btn_quzl_submit').click(function () {
        var data_form = {};
        var quzlname = $('#quzl_name').val();

        if (quzlname === '') {
            alert('请输入问卷名');
            return;
        }

        data_form['quzlname'] = quzlname;
        data_form['quzlist'] = [];
        var quz_list = data_form['quzlist'];

        $('.quz').each(function (i, e) {
            var tmp = $(e).children('input');
            var quz = {};
            var opt_list;
            for (var index = 0; index < tmp.length; index++) {
                var elem = tmp[index];
                if (index == 0) {
                    var quz_content = $(elem).val();
                    if (quz_content === '') {
                        alert('请输入问题内容');
                        return;
                    }
                    quz['quzcontent'] = quz_content;
                    quz['optlist'] = [];
                    opt_list = quz['optlist'];
                } else {
                    var opt_content = $(elem).val();
                    if (opt_content === '') {
                        quz_list[i] = quz;
                        return;
                    }
                    opt_list[index - 1] = { optcontent: opt_content };
                }
            }
            quz_list[i] = quz;
        });

        $.ajax({
            type: "POST",
            url: "/quzl/create",
            data: JSON.stringify(data_form),
            success: function (response) {
                alert(response);
                window.location.href='/';
            },
            error: function (xhr) {
                var text = xhr.responseText;
                alert(text.substring(text.indexOf('message') + 8));
                document.cookie = 'session_id=; expires=Thu, 01 Jan 1970 00:00:00 GMT';
            }
        });
    });

});


